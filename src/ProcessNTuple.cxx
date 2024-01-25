// Driver to post-proccess ntuples for S. Gardiner's cross-section tools

#include "../include/Utility.h"
#include "../include/EventContainer.h"
#include "../include/Selection.h"
#include "../include/BDTTool.h"

#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TParameter.h"

// Helper function to set branch addresses for the output TTree
void set_event_output_branch_addresses(TTree& out_tree, EventContainer& ev, bool create);

// Helper functions that creates a branch (or just sets a new address)
// simple variable in an output TTree
void set_output_branch_address(TTree& out_tree, const std::string& branch_name, void* address, bool create, const std::string& leaf_spec);
// pointer to an object in an output TTree
template <typename T> void set_object_output_branch_address( TTree& out_tree, const std::string& branch_name, T*& address, bool create = false);
// vector of doubles
void set_output_branch_address_vector(TTree& out_tree, const std::string& branch_name, void* address, std::vector<double>* address_ptr, bool create);

int main(int argc, char *argv[]) {

	// parse arguments
	if ( argc != 5 ) {
    	std::cout << "Usage: ProcessNTuple INPUT_PELEE_NTUPLE_FILE OUTPUT_FILE TYPE_ENUM RUN_ENUM" << std::endl;
    	return 1;
	}

	std::string input_filename( argv[1] );
	std::string output_filename( argv[2] );
	std::string type_str ( argv[3] );
	std::string runPeriod_str ( argv[4] );
	Utility::FileTypeEnums type = static_cast<Utility::FileTypeEnums>(stoi(type_str));
	Utility::RunPeriodEnums runPeriod = static_cast<Utility::RunPeriodEnums>(stoi(runPeriod_str));

	std::cout << "Processing file: " << input_filename << ", type enum: " << type << ", run period enum: " << runPeriod << std::endl;
  
	// Get the TTrees containing the event ntuples and subrun POT information
	// read file
	TFile *inputFile = NULL;
	TTree *eventsTree = NULL;
	TTree *subrunsTree = NULL;
	inputFile = new TFile(input_filename.c_str());  
	
	if (type == 99) { // 7
 		eventsTree = (TTree*)inputFile->Get("NeutrinoSelectionFilter");
 		subrunsTree = (TTree*)inputFile->Get("SubRun");
	}
	else {
		eventsTree = (TTree*)inputFile->Get("nuselection/NeutrinoSelectionFilter");
   	subrunsTree = (TTree*)inputFile->Get("nuselection/SubRun");
	}
	
	// initialise classes
	Utility _utility(true,true,true);
	Selection _selection(_utility);
	BDTTool _BDTTool(true, true, true, true, _utility);
	EventContainer _event(eventsTree, _utility);
    
  // Create output tree
  TFile* outFile = new TFile( output_filename.c_str(), "recreate" );
	outFile->cd();
	TTree* outTree = new TTree( "stv_tree", "STV analysis tree" );

	// Get the total POT from the subruns TTree. Save it in the output
	// TFile as a TParameter<float>. Real data doesn't have this TTree,
	// so check that it exists first.
	float pot;
	float summed_pot = 0.;
	bool has_pot_branch = ( subrunsTree->GetBranch("pot") != nullptr );
	if ( has_pot_branch ) {
    subrunsTree->SetBranchAddress( "pot", &pot );
    for ( int se = 0; se < subrunsTree->GetEntries(); ++se ) {
    	subrunsTree->GetEntry( se );
    	summed_pot += pot;
   	}
	}

  TParameter<float>* summed_pot_param = new TParameter<float>( "summed_pot", summed_pot );
	summed_pot_param->Write();
	
	bool created_output_branches = false;
	
	// Event loop
	int n_entries = eventsTree->GetEntries();
	std::cout << "Number events: " << n_entries << std::endl;

	for (int e = 0; e < n_entries; e++) {
	//for (int e = 16000; e < 32000; e++) {
		  
		// get current entry
  	eventsTree->GetEntry(e);    	

    if ( (e != 0) && (n_entries >= 10) &&  (e % (n_entries/10) == 0) ) {
      std::cout << Form("%i0%% Completed...\n", e / (n_entries/10));
    }

    // apply selection
    // populates necessary variables to pass to stv tree
    bool passSelection = _selection.ApplyBDTBasedSelection(_event, _BDTTool, type, runPeriod);

    // keep/discard events depending on classification to account for signal/background enhanced samples 
    // for running with intrinsic nue
    if (type == 0 || type == 7) {	// intrinsic nue overlay
    	if (!((_event.classification == Utility::kCCNue1piXp || _event.classification == Utility::kCCNueNpi || _event.classification == Utility::kCCNuepizero ||
    				_event.classification == Utility::kCCNueNp || _event.classification == Utility::kCCNueOther))) continue;
    }
    else if (type == 2) { // standard nu overlay
    	if (((_event.classification == Utility::kCCNue1piXp || _event.classification == Utility::kCCNueNpi || _event.classification == Utility::kCCNuepizero ||
    				_event.classification == Utility::kCCNueNp || _event.classification == Utility::kCCNueOther))) continue;
    }
    else if (type == 5) { // nue detvar
    	if (!(_event.classification == Utility::kCCNue1piXp || _event.classification == Utility::kCCNueNpi || _event.classification == Utility::kCCNuepizero ||
    				_event.classification == Utility::kCCNueNp || _event.classification == Utility::kCCNueOther)) continue;
		}
    // populate beamline variations if required
    if (type == 0 || type == 2 || type == 4) {	// only for nue, nu or dirt overlay
			_event.calculateBeamlineVariationWeights(runPeriod);
    }

    // update weights for NuWro or Flugg fake data --- note: needs manually changing for other samples, need to make proper way to configure
    if (type == 7) {
    	_event.updateNuWroCVWeights(runPeriod);
    }

    //_event.calculateFluggWeights(runPeriod);
     
    // set the output TTree branch addresses, creating the branches if needed
  	// (during the first event loop iteration)
  	if ( !created_output_branches ) {
  		set_event_output_branch_addresses( *outTree, _event, true );
  		created_output_branches = true;
  	}
  	else set_event_output_branch_addresses( *outTree, _event, false );

    // fill output tree
  	outTree->Fill();

	} // end of event loop

	// write output file
	outTree->Write();
  outFile->Close();
  delete outFile;

	return 0;
}


// Helper function to set branch addresses for the output TTree
void set_event_output_branch_addresses(TTree& out_tree, EventContainer& ev, bool create = false) {
	
	// Signal definition flags
	set_output_branch_address(out_tree, "is_mc", &ev.is_mc_, create, "is_mc/O");
	set_output_branch_address(out_tree, "mc_is_signal", &ev.mc_is_signal_, create, "mc_is_signal/O");

	// MC event category
	set_output_branch_address( out_tree, "category", &ev.category_, create, "category/I");

	// Horn current
	set_output_branch_address( out_tree, "hornCurrent", &ev.hornCurrent_, create, "hornCurrent/I");

	// CV Event weights
	set_output_branch_address( out_tree, "spline_weight", &ev.weightSpline, create, "spline_weight/F");
	set_output_branch_address( out_tree, "tuned_cv_weight", &ev.weightTune, create, "tuned_cv_weight/F");
	set_output_branch_address( out_tree, "ppfx_cv_weight", &ev.ppfx_cv, create, "ppfx_cv_weight/F");
	set_output_branch_address( out_tree, "normalisation_weight", &ev.normalisation_weight, create, "normalisation_weight/F");

	// Fake data weight (testing)
	//set_output_branch_address( out_tree, "fake_data_weight", &ev.fake_data_weight, create, "fake_data_weight/F");	// comment out when not needed, should implement proper way to run

	// If MC weights are available, store them in the output TTree
	if ( ev.mc_weights_map_ ) {

    // Make separate branches for the various sets of systematic variation
    // weights in the map
    for ( auto& pair : *ev.mc_weights_map_ ) {

    	if (pair.first == "flux_all") continue; 	// skip empty BNB flux weights, PFFX used instead

    	// also want to skip other PPFX weights that are included in ppfx_all multisim, i.e. are duplicate
    	// helps reduce file size 
    	if (pair.first == "ppfx_mippk_PPFXMIPPKaon" ||
    		  pair.first == "ppfx_mipppi_PPFXMIPPPion" ||
    		  pair.first == "ppfx_other_PPFXOther" ||
    		  pair.first == "ppfx_targatt_PPFXTargAtten" ||
    		  pair.first == "ppfx_think_PPFXThinKaon" ||
    		  pair.first == "ppfx_thinmes_PPFXThinMeson" ||
    		  pair.first == "ppfx_thinn_PPFXThinNuc" ||
    		  pair.first == "ppfx_thinna_PPFXThinNucA" ||
    		  pair.first == "ppfx_thinnpi_PPFXThinNeutronPion" ||
    		  pair.first == "ppfx_thinpi_PPFXThinPion" ||
    		  pair.first == "ppfx_totabs_PPFXTotAbsorp"
    		) continue;

			// Prepend "weight_" to the name of the vector of weights in the map
			std::string weight_branch_name = "weight_" + pair.first;

			// Store a pointer to the vector of weights (needed to set the branch
			// address properly) in the temporary map of pointers
			ev.mc_weights_ptr_map_[ weight_branch_name ] = &pair.second;

			// Set the branch address for this vector of weights
			set_object_output_branch_address< std::vector<double> >( out_tree, weight_branch_name, ev.mc_weights_ptr_map_.at(weight_branch_name), create);

			// Output list of weights present, for faking structure
			//std::cout << "Name: " << pair.first << ", Size: " << pair.second.size() << std::endl;
    }
	}

	// if beamline weights are available, store them in the output TTree
	if (ev.beamlineVarWeightsPresent) {
		// we only need to create these once, why is address set every loop?
		// if generalised using map would want to set in same way, i.e. don't know a priori full list 
		if (create) {
			out_tree.Branch( "weight_Horn_2kA", "std::vector<double>", &(ev.Horn_2kA) );
			out_tree.Branch( "weight_Horn1_x_3mm", "std::vector<double>", &(ev.Horn1_x_3mm) );
			out_tree.Branch( "weight_Horn1_y_3mm", "std::vector<double>", &(ev.Horn1_y_3mm) );
			out_tree.Branch( "weight_Beam_spot_1_1mm", "std::vector<double>", &(ev.Beam_spot_1_1mm) );
			out_tree.Branch( "weight_Beam_spot_1_5mm", "std::vector<double>", &(ev.Beam_spot_1_5mm) );
			out_tree.Branch( "weight_Horn2_x_3mm", "std::vector<double>", &(ev.Horn2_x_3mm) );
			out_tree.Branch( "weight_Horn2_y_3mm", "std::vector<double>", &(ev.Horn2_y_3mm) );
			out_tree.Branch( "weight_Horns_0mm_water", "std::vector<double>", &(ev.Horns_0mm_water) );
			out_tree.Branch( "weight_Horns_2mm_water", "std::vector<double>", &(ev.Horns_2mm_water) );
			out_tree.Branch( "weight_Beam_shift_x_1mm", "std::vector<double>", &(ev.Beam_shift_x_1mm) );
			out_tree.Branch( "weight_Beam_shift_y_1mm", "std::vector<double>", &(ev.Beam_shift_y_1mm) );
			out_tree.Branch( "weight_Target_z_7mm", "std::vector<double>", &(ev.Target_z_7mm) );		
		}
	}

	// NueCC1piXp selection criteria
	set_output_branch_address( out_tree, "sel_passLooseRejection", &ev.sel_passLooseRejection_, create, "sel_passLooseRejection/O");
	set_output_branch_address( out_tree, "sel_passBDTPi0Rejection", &ev.sel_passBDTPi0Rejection_, create, "sel_passBDTPi0Rejection/O");
	set_output_branch_address( out_tree, "sel_NueCC1piXp", &ev.sel_NueCC1piXp_, create, "sel_NueCC1piXp/O");

	// Observables
	// BDT Scores
	set_output_branch_address( out_tree, "sel_BDTScoreElectronPhoton", &ev.BDTScoreElectronPhoton, create, "sel_BDTScoreElectronPhoton/D");	// Reco
	if (ev.primaryTrackPionlikeLoose) {
		set_output_branch_address( out_tree, "sel_BDTScorePionProton", &ev.primaryTrackBDTScorePionProton, create, "sel_BDTScorePionProton/D");	// Reco
	}
	else if (ev.secondaryTrackPionlikeLoose) {
		set_output_branch_address( out_tree, "sel_BDTScorePionProton", &ev.secondaryTrackBDTScorePionProton, create, "sel_BDTScorePionProton/D");	// Reco
	}
	else {
		set_output_branch_address( out_tree, "sel_BDTScorePionProton", &ev.tertiaryTrackBDTScorePionProton, create, "sel_BDTScorePionProton/D");	// Reco
	}

	// Shower/Electron energy
	set_output_branch_address( out_tree, "sel_shr_energy_cali", &ev.shr_energy_cali, create, "sel_shr_energy_cali/F");	// Reco
	set_output_branch_address( out_tree, "mc_shr_bkt_E", &ev.shr_bkt_E, create, "mc_shr_bkt_E/F");						// Truth - shower energy
	set_output_branch_address( out_tree, "mc_elec_e", &ev.elec_e, create, "mc_elec_e/F");										// Truth - electron energy

	// Electron NuMI angle (beta)
	set_output_branch_address( out_tree, "sel_reco_cos_electron_effective_angle", &ev.reco_cos_electron_effective_angle, create, "sel_reco_cos_electron_effective_angle/F");	// Reco
	set_output_branch_address( out_tree, "mc_true_cos_electron_effective_angle", &ev.true_cos_electron_effective_angle, create, "mc_true_cos_electron_effective_angle/F");		// Truth

	// Pion Energy
	set_output_branch_address( out_tree, "sel_reco_energy_pion", &ev.reco_energy_pion, create, "sel_reco_energy_pion/F");	// Reco - range-based
	set_output_branch_address( out_tree, "mc_pion_e", &ev.pion_e, create, "mc_pion_e/F");											// Truth - pion energy

	// Pion NuMI angle (beta)
	set_output_branch_address( out_tree, "sel_reco_cos_pion_effective_angle", &ev.reco_cos_pion_effective_angle, create, "sel_reco_cos_pion_effective_angle/F");	// Reco
	set_output_branch_address( out_tree, "mc_true_cos_pion_effective_angle", &ev.true_cos_pion_effective_angle, create, "mc_true_cos_pion_effective_angle/F");		// Truth

	// Number protons
	set_output_branch_address( out_tree, "sel_numberProtons", &ev.numberProtons, create, "sel_numberProtons/I");	// Reco
	set_output_branch_address( out_tree, "mc_nproton", &ev.nproton, create, "mc_nproton/I");											// Truth

	// Track BDT properties
	set_output_branch_address( out_tree, "sel_bragg_mip_pion_loose", &ev.trk_bragg_mip_pion_loose, create, "sel_bragg_mip_pion_loose/F");
	set_output_branch_address( out_tree, "sel_trk_daughters_pion_loose", &ev.trk_daughters_pion_loose, create, "sel_trk_daughters_pion_loose/I");
	set_output_branch_address( out_tree, "sel_trk_dEdx_trunk_pion_loose", &ev.trk_dEdx_trunk_pion_loose, create, "sel_trk_dEdx_trunk_pion_loose/F");
	set_output_branch_address( out_tree, "sel_trk_bragg_pion_pion_loose", &ev.trk_bragg_pion_pion_loose, create, "sel_trk_bragg_pion_pion_loose/F");
	set_output_branch_address( out_tree, "sel_trk_llr_pid_score_pion_loose", &ev.trk_llr_pid_score_pion_loose, create, "sel_trk_llr_pid_score_pion_loose/F");
	set_output_branch_address( out_tree, "sel_trk_score_pion_loose", &ev.trk_score_pion_loose, create, "sel_trk_score_pion_loose/F");
	set_output_branch_address( out_tree, "sel_trk_end_spacepoints_pion_loose", &ev.trk_end_spacepoints_pion_loose, create, "sel_trk_end_spacepoints_pion_loose/I");

	set_output_branch_address( out_tree, "sel_bragg_mip_pion", &ev.trk_bragg_mip_pion, create, "sel_bragg_mip_pion/F");
	set_output_branch_address( out_tree, "sel_trk_daughters_pion", &ev.trk_daughters_pion, create, "sel_trk_daughters_pion/I");
	set_output_branch_address( out_tree, "sel_trk_dEdx_trunk_pion", &ev.trk_dEdx_trunk_pion, create, "sel_trk_dEdx_trunk_pion/F");
	set_output_branch_address( out_tree, "sel_trk_bragg_pion_pion", &ev.trk_bragg_pion_pion, create, "sel_trk_bragg_pion_pion/F");
	set_output_branch_address( out_tree, "sel_trk_llr_pid_score_pion", &ev.trk_llr_pid_score_pion, create, "sel_trk_llr_pid_score_pion/F");
	set_output_branch_address( out_tree, "sel_trk_score_pion", &ev.trk_score_pion, create, "sel_trk_score_pion/F");
	set_output_branch_address( out_tree, "sel_trk_end_spacepoints_pion", &ev.trk_end_spacepoints_pion, create, "sel_trk_end_spacepoints_pion/I");

	// Shower BDT properties
	set_output_branch_address(out_tree,  "sel_n_showers_contained", &ev.n_showers_contained, create, "sel_n_showers_contained/I");
	set_output_branch_address( out_tree, "sel_shrmoliereavg", &ev.shrmoliereavg, create, "sel_shrmoliereavg/F");
	set_output_branch_address( out_tree, "sel_shr_distance", &ev.shr_distance, create, "sel_shr_distance/F");
	set_output_branch_address( out_tree, "sel_shr2_pfpgeneration", &ev.shr2_pfpgeneration, create, "sel_shr2_pfpgeneration/I");
	set_output_branch_address( out_tree, "sel_shr_trkfit_2cm_dedx_best", &ev.shr_trkfit_2cm_dedx_max, create, "sel_shr_trkfit_2cm_dedx_best/F");
	set_output_branch_address( out_tree, "sel_shr_trkfit_gap10_dedx_best", &ev.shr_trkfit_gap10_dedx_max, create, "sel_shr_trkfit_gap10_dedx_best/F");
	set_output_branch_address( out_tree, "sel_shr_energyFraction", &ev.shr_energyFraction, create, "sel_shr_energyFraction/F");
	set_output_branch_address( out_tree, "sel_shr2_distance", &ev.shr2_distance, create, "sel_shr2_distance/F");
  set_output_branch_address( out_tree, "sel_shrMCSMom", &ev.shrMCSMom, create, "sel_shrMCSMom/F");

  // Interaction type
  set_output_branch_address( out_tree, "mc_ccnc", &ev.ccnc, create, "mc_ccnc/I");
  set_output_branch_address( out_tree, "mc_interaction", &ev.interaction, create, "mc_interaction/I");
}

// Helper function that creates a branch (or just sets a new address) for a
// simple variable in an output TTree
void set_output_branch_address(TTree& out_tree, const std::string& branch_name, void* address, bool create = false, const std::string& leaf_spec = "" ) {
  if ( create ) {
    if ( leaf_spec != "" ) {
      out_tree.Branch( branch_name.c_str(), address, leaf_spec.c_str() );
    }
    else {
      out_tree.Branch( branch_name.c_str(), address );
    }
  }
  else {
    out_tree.SetBranchAddress( branch_name.c_str(), address );
  }
}
// pointer to an object in an output TTree
template <typename T> void set_object_output_branch_address( TTree& out_tree, const std::string& branch_name, T*& address, bool create) {
  if ( create ) out_tree.Branch( branch_name.c_str(), &address );
  else out_tree.SetBranchAddress( branch_name.c_str(), &address );
}
// vector of doubles for beamline weights (to do, make template)
void set_output_branch_address_vector(TTree& out_tree, const std::string& branch_name, void* address, std::vector<double>* address_ptr, bool create) {
	 if ( create ) out_tree.Branch( branch_name.c_str(), "std::vector<double>", address );
   else {
   	out_tree.SetBranchAddress( branch_name.c_str(), address_ptr );
   }
} 


