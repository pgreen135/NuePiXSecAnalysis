// Driver script to launch nue analysis code

#include "../include/Utility.h"
#include "../include/EventContainer.h"
#include "../include/Selection.h"
#include "../include/StackedHistTool.h"
#include "../include/BDTTool.h"
#include "../include/CreateTrainingTree.h"

#include <iostream>
#include <string>

#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TStyle.h>
#include <TEfficiency.h>
#include <TGraphAsymmErrors.h>

#include <TSystem.h>


int main() {
	
	// Files [Run 1]
	// with ppfx weights
	std::string filename_intrinsic = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1_slim_ppfx/neutrinoselection_filt_run1_intrinsic_slim.root";
	std::string filename_ccncpizero = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1_slim_ppfx/neutrinoselection_filt_run1_ccncpizero_slim.root";
	std::string filename_mc = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1_slim_ppfx/neutrinoselection_filt_run1_overlay_slim.root";

	// without ppfx weights
    //std::string filename_intrinsic = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1_slim_Mar23/neutrinoselection_filt_run1_ccncpizero_slim.root"; // Pi0-rich sample
    //std::string filename_mc = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1_slim/neutrinoselection_filt_run1_overlay_slim.root";
	std::string filename_dirt = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1_slim/neutrinoselection_filt_run1_dirt_slim.root";
	std::string filename_beamoff = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1_slim/neutrinoselection_filt_run1_beamoff_slim.root";

	// Files [Run 3b]
	//std::string filename_mc = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run3b_slim/neutrinoselection_filt_run3b_overlay_slim.root";

	// Weights [Run 1]
	// with ppfx weights
	double pot_weight_intrinsic = 1;
	//double pot_weight_intrinsic = 0.008406;	// intrinsic nue 2.37918e+22 [slim, ppfx]
	double pot_weight_ccncpizero = 1;
	//double pot_weight_ccncpizero = 0.015199; // 1.31585e+22 [slim, ppfx]
	//double pot_weight_mc = 1;	
	double pot_weight_mc = 0.08895; // [slim, ppfx] 2.24851e+21
	
	// without ppfx weights
	//double pot_weight_mc = 0.08569; 	// 2.33391e+21 [slim]
	//double weight_mc = 0.0862887; // 2.3178e+21 [slim Mar23 shr energies]
	double pot_weight_dirt = 0.12245; 	// 1.63329e+21 [slim]
	double pot_weight_beamoff = 0.5727; // HW_beam-on / HW_beam-off

	// Weights [Run 3b]
	//double weight_mc = 0.25081; // 1.99351e+21 [slim]

	// Initialise Classes
  	Utility _utility;
  	Selection _selection(_utility);
  	StackedHistTool _histStack("", "", 24, -0.1, 1.1, _utility);
  	BDTTool _BDTTool(true, true, false);
  	CreateTrainingTree _trainingTree(Utility::kPionProtonAlternate);

  	// Testing histogram
  	TH1F *hist_sig = new TH1F("", "", 22, -1.1, 1.1);
  	TH1F *hist_bg = new TH1F("", "", 22, -1.1, 1.1);
  	
  	TH2F *hist2D = new TH2F("", "", 22, 0, 1.1, 22, 0, 1.1);
  	TH2F *hist2D_bg = new TH2F("", "", 22, 0, 1.1, 22, 0, 1.1);
  	
  	//TH2F *hist2D = new TH2F("", "", 20, 0, 10, 30, 0, 15);
  	//TH2F *hist2D_bg = new TH2F("", "", 20, 0, 10, 30, 0, 15);

  	Double_t bins[22] = {0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 250, 300, 350, 400, 450, 500, 600, 700, 800, 900, 1000};
	TEfficiency* pEff = new TEfficiency("","",21,bins);

	// Dump BDT
	//_BDTTool.dumpBDTModel();	
	
	/*
	// --- Intrinsic Nue Overlay MC -- 
  	// read file
	TFile *f_intrinsic = NULL;
  	TTree *tree_intrinsic = NULL;
 	f_intrinsic = new TFile(filename_intrinsic.c_str());  
  	tree_intrinsic = (TTree*)f_intrinsic->Get("nuselection/NeutrinoSelectionFilter");
  	
  	// initialise event container
  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

  	// loop through events
  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
  	std::cout << "Initial number events [Intrinsic]: " << n_entries_intrinsic << std::endl;

  	for (int e = 0; e < n_entries_intrinsic; e++) {
  	//for (int e = 0; e < 10; e++) {
  		
    	tree_intrinsic->GetEntry(e);    	

	    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
	      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
	    }

	    //bool passSelection = _selection.ApplyCutBasedSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun1);
	    //if (!passSelection) {
	    //	pEff->Fill(false, _event_intrinsic.pion_e*1000 - 139.570);
	    //	continue;
	    //}

	    bool passSelection = _selection.ApplyBDTBasedSelection(_event_intrinsic, _BDTTool, Utility::kIntrinsic, Utility::kRun1);
	    if (!passSelection) {
	    //	pEff->Fill(false, _event_intrinsic.pion_e*1000 - 139.570);
	    	continue;
	    }

	    //bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun1);
	    //if (!passSelection) continue;

	    //bool passSelection = _selection.ApplyElectronPhotonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun1);
	    //if (!passSelection) continue;
	     
	    //pEff->Fill(true, _event_intrinsic.pion_e*1000 - 139.570);	

	    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.BDTScorePionProtonAlternate, pot_weight_intrinsic * _event_intrinsic.weight_cv);
	    //if (_event_intrinsic.primaryTrackPionlike) _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.primaryTrackBDTScorePionProton, pot_weight_intrinsic * _event_intrinsic.weight_cv);
	    //else if (_event_intrinsic.secondaryTrackPionlike) _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.secondaryTrackBDTScorePionProton, pot_weight_intrinsic * _event_intrinsic.weight_cv);
	  	//else _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.tertiaryTrackBDTScorePionProton, pot_weight_intrinsic * _event_intrinsic.weight_cv);
	   	
	    // fill stacked histogram, selected topologies only
	    //if (classification == Utility::kCCNue1pi0p || classification == Utility::kCCNue1piNp || classification == Utility::kCCNueNpi || classification == Utility::kCCNuepizero || 
	    //	classification == Utility::kCCNue1p || classification == Utility::kCCNueNp || classification == Utility::kCCNueOther || 
	    //	classification == Utility::kCCNue1piNp ){
	    	
	    	//_histStack.Fill(classification, _event_intrinsic.elec_e - (0.511/1000), weight_intrinsic);

	    	
		    // fill testing plot
		    // primary
		//    if (_event_intrinsic.trk_bkt_pdg == 2212 && _event_intrinsic.primaryTrackPionlike) {
		//    	hist2D_bg->Fill(_event_intrinsic.trk_bragg_pion_max, _event_intrinsic.trk_bragg_mip_max, weight_intrinsic);
		//    }
		//    if ((_event_intrinsic.trk_bkt_pdg == 211 || _event_intrinsic.trk_bkt_pdg == -211) && _event_intrinsic.primaryTrackPionlike) {
		//    	hist2D->Fill(_event_intrinsic.trk_bragg_pion_max, _event_intrinsic.trk_bragg_mip_max, weight_intrinsic);
		//    }
		    // secondary
		//    if (_event_intrinsic.trk2_bkt_pdg == 2212 && _event_intrinsic.secondaryTrackPionlike) {
		//    	hist2D_bg->Fill(_event_intrinsic.trk2_bragg_pion_max, _event_intrinsic.trk2_bragg_mip_max, weight_intrinsic);
		//    }
		//    if ((_event_intrinsic.trk2_bkt_pdg == 211 || _event_intrinsic.trk2_bkt_pdg == -211) && _event_intrinsic.secondaryTrackPionlike) {
		//    	hist2D->Fill(_event_intrinsic.trk2_bragg_pion_max, _event_intrinsic.trk2_bragg_mip_max, weight_intrinsic);
		//    }
		    // tertiary
		//   if (_event_intrinsic.trk3_bkt_pdg == 2212 && _event_intrinsic.tertiaryTrackPionlike) {
		//    	hist2D_bg->Fill(_event_intrinsic.trk3_bragg_pion_max, _event_intrinsic.trk3_bragg_mip_max, weight_intrinsic);
		//    }
		//    if ((_event_intrinsic.trk3_bkt_pdg == 211 || _event_intrinsic.trk3_bkt_pdg == -211) && _event_intrinsic.tertiaryTrackPionlike) {
		//    	hist2D->Fill(_event_intrinsic.trk3_bragg_pion_max, _event_intrinsic.trk3_bragg_mip_max, weight_intrinsic);
		//    }
		    
	    	//if (_event_intrinsic.primaryTrackValid) _histStack.Fill(classification, _event_intrinsic.trk_energy_muon, weight_intrinsic);
			//else if (_event_intrinsic.secondaryTrackValid) _histStack.Fill(classification, _event_intrinsic.trk2_energy_muon, weight_intrinsic);
			//else if (_event_intrinsic.tertiaryTrackValid) _histStack.Fill(classification, _event_intrinsic.trk3_energy_muon, weight_intrinsic);

		//}
		
		
	    // add event to training tree (if required)
	    // electron-photon
	    // _event_intrinsic.classification == Utility::kCCNuepizero ||
		//if (_event_intrinsic.classification == Utility::kCCNue1pi0p || _event_intrinsic.classification == Utility::kCCNue1piNp || _event_intrinsic.classification == Utility::kCCNueNpi ||
		//	_event_intrinsic.classification == Utility::kCCNue1p || _event_intrinsic.classification == Utility::kCCNueNp) _trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		// pion-proton, all events
		_trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);

	}
	*/
	
	/*
	// --- CC/NC PiZero Overlay ---

	// read file
	TFile *f_ccncpizero = NULL;
  	TTree *tree_ccncpizero = NULL;
 	f_ccncpizero = new TFile(filename_ccncpizero.c_str());  
  	tree_ccncpizero = (TTree*)f_ccncpizero->Get("nuselection/NeutrinoSelectionFilter");
  	
  	// initialise event container
  	EventContainer _event_ccncpizero(tree_ccncpizero, _utility); 	

  	// loop through events
  	int n_entries_ccncpizero = tree_ccncpizero->GetEntries();
  	std::cout << "Initial number events [CC/NC PiZero]: " << n_entries_ccncpizero << std::endl;
  	
  	for (int e = 0; e < n_entries_ccncpizero; e++) {

    	tree_ccncpizero->GetEntry(e);    	

	    if ( (e != 0) && (n_entries_ccncpizero >= 10) &&  (e % (n_entries_ccncpizero/10) == 0) ) {
	      std::cout << Form("%i0%% Completed...\n", e / (n_entries_ccncpizero/10));
	    }

	    //bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_ccncpizero, Utility::kCCNCPiZero, Utility::kRun1);
	    //if (!passSelection) continue;

	    bool passSelection = _selection.ApplyElectronPhotonBDTTrainingSelection(_event_ccncpizero, Utility::kCCNCPiZero, Utility::kRun1);
	    if (!passSelection) continue;
	     
	     // fill histogram
	    _histStack.Fill(_event_ccncpizero.classification, _event_ccncpizero.shr_energyFraction, pot_weight_ccncpizero * _event_ccncpizero.weight_cv);	 
		
	    // add event to training tree (if required)
	    if (_event_ccncpizero.classification == Utility::kCCNuepizero || _event_ccncpizero.classification == Utility::kCCNumupizero || _event_ccncpizero.classification == Utility::kNCpizero ) {
			_trainingTree.addEvent(_event_ccncpizero, _event_ccncpizero.classification);
		}

	}
	*/
	
	
	// --- Nu Overlay MC ---	
	// read file
	TFile *f_mc = NULL;
  	TTree *tree_mc = NULL;
 	f_mc = new TFile(filename_mc.c_str());  
  	tree_mc = (TTree*)f_mc->Get("nuselection/NeutrinoSelectionFilter");
  	
  	// initialise event container
  	EventContainer _event_mc(tree_mc, _utility); 	

  	// loop through events
  	int n_entries_mc = tree_mc->GetEntries();
  	std::cout << "Initial number events [MC]: " << n_entries_mc << std::endl;

  	for (int e = 0; e < n_entries_mc; e++) {
  		
    	tree_mc->GetEntry(e);    	

	    if ( (e != 0) && (n_entries_mc >= 10) &&  (e % (n_entries_mc/10) == 0) ) {
	      std::cout << Form("%i0%% Completed...\n", e / (n_entries_mc/10));
	    }

	    //bool passSelection = _selection.ApplyCutBasedSelection(_event_mc, Utility::kMC, Utility::kRun1);
	    //if (!passSelection) continue;

	    bool passSelection = _selection.ApplyBDTBasedSelection(_event_mc, _BDTTool, Utility::kMC, Utility::kRun1);
	    if (!passSelection) continue;

	    //bool passSelection = _selection.ApplyElectronPhotonBDTTrainingSelection(_event_mc, Utility::kMC, Utility::kRun1);
	    //if (!passSelection) continue;

	    //bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_mc, Utility::kMC, Utility::kRun1);
	    //if (!passSelection) continue;

	    // fill histogram
	    _histStack.Fill(_event_mc.classification, _event_mc.shrPCA1CMed_5cm, pot_weight_mc * _event_mc.weight_cv);	

	    // add event to training tree (if required)
	    // electron-photon bdt: only CC muon / NC
	    //if (_event_mc.classification == Utility::kCCNuepizero || _event_mc.classification == Utility::kCCNumupizero || _event_mc.classification == Utility::kNCpizero ) _trainingTree.addEvent(_event_mc, _event_mc.classification);
	    // pion-proton bdt: muon events only to avoid bias 
	    //if (_event_mc.nu_pdg == 14 || _event_mc.nu_pdg == -14) _trainingTree.addEvent(_event_mc, _event_mc.classification);




		// fill testing plot 
	    //if(classification == Utility::kCCNue1piNp || classification == Utility::kCCNue1pi0p) {
	    //	hist2D->Fill(_event_mc.shr_trkfit_gap10_dedx_max, _event_mc.shr_distance, weight_mc);
	    //}
	    
	    //if (classification == Utility::kCCNumupizero || classification == Utility::kNCpizero) {
	    //	hist2D_bg->Fill(_event_mc.shr_trkfit_gap10_dedx_max, _event_mc.shr_distance, weight_mc);
	    //}	 
	    

	    
	    
	    //if (_event_mc.npion == 1 && (_event_mc.trk_bkt_pdg == 211 || _event_mc.trk_bkt_pdg == -211)) {
	    //	hist2D->Fill(_event_mc.pion_e - (139.57/1000), _event_mc.trk_len);
	    //}

	   

	    
	    // fill histograms
	    // primary track
	    // muon
	    //if ((_event_mc.trk_bkt_pdg == 13 || _event_mc.trk_bkt_pdg == -13) && _event_mc.primaryTrackValid) hist2D_bg->Fill(_event_mc.trk_avg_deflection_separation_mean, _event_mc.trk_avg_deflection_mean);
	    // proton
	    if (_event_mc.trk_bkt_pdg == 2212 && _event_mc.primaryTrackValid) hist_bg->Fill(_event_mc.trk_llr_pid_score);
	    // pion
	    if ((_event_mc.trk_bkt_pdg == 211 || _event_mc.trk_bkt_pdg == -211) && _event_mc.primaryTrackValid) hist_sig->Fill(_event_mc.trk_llr_pid_score);
	    //if ((_event_mc.trk_bkt_pdg == 211 || _event_mc.trk_bkt_pdg == -211) && _event_mc.primaryTrackValid) hist2D->Fill(_event_mc.trk_avg_deflection_separation_mean, _event_mc.trk_avg_deflection_mean);
	    
	    // secondary track
	    // proton
	    //if (_event_mc.trk2_bkt_pdg == 2212 && _event_mc.secondaryTrackValid) hist_bg->Fill(_event_mc.trk2_llr_pid_score);
	    // pion
	    //if ((_event_mc.trk2_bkt_pdg == 211 || _event_mc.trk2_bkt_pdg == -211) && _event_mc.secondaryTrackValid) hist_sig->Fill(_event_mc.trk2_llr_pid_score);

	    // tertiary track
	    // proton
	    //if (_event_mc.trk3_bkt_pdg == 2212 && _event_mc.tertiaryTrackValid) hist_bg->Fill(_event_mc.trk3_llr_pid_score);
	    // pion
	    //if ((_event_mc.trk3_bkt_pdg == 211 || _event_mc.trk3_bkt_pdg == -211) && _event_mc.tertiaryTrackValid) hist_sig->Fill(_event_mc.trk3_llr_pid_score);
	  	
	    // do not add nues in training, use intrinsic simulation instead [comment out when testing with actual sample]
	    //if (classification == Utility::kCCNue1pi0p || classification == Utility::kCCNue1piNp || classification == Utility::kCCNueNpi || classification == Utility::kCCNuepizero || 
	    //	classification == Utility::kCCNue1p || classification == Utility::kCCNueNp || classification == Utility::kCCNueOther || 
	    //	classification == Utility::kCCNue1piNp ) continue;
	    	
	    
	    // fill testing plot
	    // primary
	    //if (_event_mc.trk_bkt_pdg == 2212 && _event_mc.primaryTrackPionlike) {
	    //	hist2D_bg->Fill(_event_mc.trk_bragg_pion_max, _event_mc.trk_bragg_mip_max, weight_mc);
	    //}
	    //if ((_event_mc.trk_bkt_pdg == 211 || _event_mc.trk_bkt_pdg == -211) && _event_mc.primaryTrackPionlike) {
	    //	hist2D->Fill(_event_mc.trk_bragg_pion_max, _event_mc.trk_bragg_mip_max, weight_mc);
	    //}
	    // secondary
	    //if (_event_mc.trk2_bkt_pdg == 2212 && _event_mc.secondaryTrackPionlike) {
	    //	hist2D_bg->Fill(_event_mc.trk2_bragg_pion_max, _event_mc.trk2_bragg_mip_max, weight_mc);
	    //}
	    //if ((_event_mc.trk2_bkt_pdg == 211 || _event_mc.trk2_bkt_pdg == -211) && _event_mc.secondaryTrackPionlike) {
	    //	hist2D->Fill(_event_mc.trk2_bragg_pion_max, _event_mc.trk2_bragg_mip_max, weight_mc);
	    //}
	    // tertiary
	    //if (_event_mc.trk3_bkt_pdg == 2212 && _event_mc.tertiaryTrackPionlike) {
	    //	hist2D_bg->Fill(_event_mc.trk3_bragg_pion_max, _event_mc.trk3_bragg_mip_max, weight_mc);
	    //}
	    //if ((_event_mc.trk3_bkt_pdg == 211 || _event_mc.trk3_bkt_pdg == -211) && _event_mc.tertiaryTrackPionlike) {
	    //	hist2D->Fill(_event_mc.trk3_bragg_pion_max, _event_mc.trk3_bragg_mip_max, weight_mc);
	    //}
	    

	    //if (_event_mc.n_showers_contained == 2) 
	    //_histStack.Fill(classification, _event_mc.nu_e, weight_mc);
		
		//if (_event_mc.primaryTrackValid) _histStack.Fill(classification, _event_mc.trk1_calo_energy, weight_mc);
		//else if (_event_mc.secondaryTrackValid) _histStack.Fill(classification, _event_mc.trk2_calo_energy, weight_mc);
		//else if (_event_mc.tertiaryTrackValid) _histStack.Fill(classification, _event_mc.trk3_calo_energy, weight_mc);

	  	//if (_event_mc.primaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.primaryTrackBDTScorePionProton, pot_weight_mc * _event_mc.weight_cv);
	    //else if (_event_mc.secondaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.secondaryTrackBDTScorePionProton, pot_weight_mc * _event_mc.weight_cv);
	  	//else _histStack.Fill(_event_mc.classification, _event_mc.tertiaryTrackBDTScorePionProton, pot_weight_mc * _event_mc.weight_cv);

	}
	
	
	

	/*
	// --- Beam Off ---
	// read file
	TFile *f_beamoff = NULL;
  	TTree *tree_beamoff = NULL;
 	f_beamoff = new TFile(filename_beamoff.c_str());  
  	tree_beamoff = (TTree*)f_beamoff->Get("nuselection/NeutrinoSelectionFilter");
  	
  	// initialise event container
  	EventContainer _event_beamoff(tree_beamoff, _utility); 	

  	// loop through events
  	int n_entries_beamoff = tree_beamoff->GetEntries();
  	std::cout << "Initial number events [Beam Off]: " << n_entries_beamoff << std::endl;

  	for (int e = 0; e < n_entries_beamoff; e++) {

    	tree_beamoff->GetEntry(e);

	    if ( (e != 0) && (n_entries_beamoff >= 10) &&  (e % (n_entries_beamoff/10) == 0) ) {
	      std::cout << Form("%i0%% Completed...\n", e / (n_entries_beamoff/10));
	    }

	    bool passSelection = _selection.ApplyCutBasedSelection(_event_beamoff, Utility::kEXT, Utility::kRun1);
	    if (!passSelection) continue;

	    // fill histogram
	    _histStack.Fill(_event_beamoff.classification, _event_beamoff.BDTScoreElectronPhoton, pot_weight_beamoff * _event_beamoff.weight_cv);

	}


	// --- Dirt ---
	// read file
	TFile *f_dirt = NULL;
  	TTree *tree_dirt = NULL;
 	f_dirt = new TFile(filename_dirt.c_str());  
  	tree_dirt = (TTree*)f_dirt->Get("nuselection/NeutrinoSelectionFilter");
  	
  	// initialise event container
  	EventContainer _event_dirt(tree_dirt, _utility); 	

  	// loop through events
  	int n_entries_dirt = tree_dirt->GetEntries();
  	std::cout << "Initial number events [Dirt]: " << n_entries_dirt << std::endl;

  	for (int e = 0; e < n_entries_dirt; e++) {

    	tree_dirt->GetEntry(e);

	    if ( (e != 0) && (n_entries_dirt >= 10) &&  (e % (n_entries_dirt/10) == 0) ) {
	      std::cout << Form("%i0%% Completed...\n", e / (n_entries_dirt/10));
	    }
	    
	    bool passSelection = _selection.ApplyCutBasedSelection(_event_dirt, Utility::kDirt, Utility::kRun1);
	    if (!passSelection) continue;

	    // fill histogram
	    _histStack.Fill(_event_dirt.classification, _event_dirt.BDTScoreElectronPhoton, pot_weight_dirt * _event_dirt.weight_cv);  

	}
	*/


	// write training tree
	_trainingTree.writeOutputFile();
	
	_histStack.PrintEventIntegrals();

	TCanvas *canv = new TCanvas("canv", "canv", 1080, 1080);
  	_histStack.DrawStack(canv, Utility::kPionProtonBDT);
  	//_histStack.PrintEventIntegrals();

  	
  	//canv->Print("plot_postCosmicImpactParameter_ShowerScore.root");
  	//canv->Print("plot_postShowerScore_HitRatio.root");
  	//canv->Print("plot_postHitRatio_LeadingShowerEnergy.root");
  	//canv->Print("plot_postNeutralPionRejection_MoliereAverage.root");
  	//canv->Print("plot_postTrackLength_TrackDistance.root");
  	canv->Print("plot_BDTScorePionProton.root");

  	
	/*
  	TCanvas *c1 = new TCanvas("c1","",200,10,1080,1080);
  	c1->cd();
  	gStyle->SetOptStat(0);
  	hist2D->Draw("COLZ");
  	
  	//hist2D_bg->GetXaxis()->SetTitle("Shower dE/dx [MeV/cm]");
	//hist2D_bg->GetYaxis()->SetTitle("Shower Distance [cm]");

	hist2D_bg->GetXaxis()->SetTitle("Pion Bragg Peak Score");
	hist2D_bg->GetYaxis()->SetTitle("MIP Bragg Peak Score");


	//hist2D->GetYaxis()->SetTitle("Mean Wiggliness [deg]");
	//hist2D->GetXaxis()->SetTitle("Mean Spacepoint Separation [cm]");
	
	
  	//hist2D->GetXaxis()->SetTitleSize(0.045);
  	//hist2D->GetYaxis()->SetTitleSize(0.045);

  	//hist2D->SetTitle("Muons");
	hist2D_bg->SetFillColor(kRed+2);
  	hist2D->SetFillColor(kCyan+2);

  

  	hist2D_bg->Draw("BOX");

  	c1->Modified();
  	
  	hist2D->Draw("BOX same");

  	c1->Modified();
  	
  	TLegend *leg = new TLegend(0.6,0.7,0.9,0.9, NULL,"brNDC");
	leg->AddEntry(hist2D,"Pion","f");
	leg->AddEntry(hist2D_bg,"Proton","f"); 
	leg->Draw("same");

	c1->Modified();

	gStyle->SetOptStat(0);
	
  	c1->Print("PionPID.root");
	*/


  	
	// normalise
	hist_bg->Scale(1/hist_bg->GetEntries());
	hist_sig->Scale(1/hist_sig->GetEntries());

  	
	TCanvas *c1 = new TCanvas("c1","",200,10,1080,1080);
  	c1->cd();
  	gStyle->SetOptStat(0);
  	hist_bg->Draw("HIST");
  	
  	hist_bg->GetXaxis()->SetTitle("Track Proton/Muon LLR PID Score");
	
  	hist_bg->GetXaxis()->SetTitleSize(0.045);
  	hist_bg->GetYaxis()->SetTitleSize(0.045);

  	hist_bg->SetLineWidth(3);
  	hist_bg->SetLineColor(kRed+2);

  	c1->Modified();
  	
  	hist_sig->SetLineColor(kCyan+2);
  	hist_sig->SetLineWidth(3);
  	hist_sig->Draw("HIST same");

  	c1->Modified();

  	TLegend *leg = new TLegend(0.6,0.7,0.9,0.9, NULL,"brNDC");
	leg->AddEntry(hist_sig,"Pion","l");
	leg->AddEntry(hist_bg,"Proton","l"); 
	leg->Draw("same");

	c1->Modified();

	gStyle->SetOptStat(0);

  	c1->Print("ProtonRejection_llrpidscore.root");

  	
  	/*
  	TCanvas *c1 = new TCanvas("c1","",200,10,1080,1080);
  	c1->cd();
  	gStyle->SetOptStat(0);

  	pEff->SetLineWidth(2);

	pEff->Draw("AP");
	c1->Pad()->Update();

  	TGraphAsymmErrors *gg=pEff->GetPaintedGraph();

  	c1->Clear();

  	gg->SetTitle("Selection Efficiency");
  	gg->GetXaxis()->SetTitle("Pion Truth KE [MeV]");
  	gg->GetYaxis()->SetTitle("Efficiency");

	gg->Draw("AP");
	c1->Print("SelectionEfficiency40MeV.root");
	*/
	
	return 0;
}