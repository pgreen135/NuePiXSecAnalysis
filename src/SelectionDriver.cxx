#include "../include/SelectionDriver.h"

#include <iostream>
#include <iomanip>
#include <string>

#include <TFile.h>
#include <TTree.h>
#include <TLine.h>

#include "../include/EventContainer.h"
#include "../include/CreateTrainingTree.h"
#include "../include/Selection.h"
#include "../include/StackedHistTool.h"
#include "../include/BDTTool.h"


// Constructor
SelectionDriver::SelectionDriver(): _utility(false) {
	
	std::cout << "Initialising Selection Driver Class" << std::endl;

}

// ------------------------------------------------------------------------------

// Draw stacked histogram


// ------------------------------------------------------------------------------

// Run BDT selection on all samples
void SelectionDriver::runBDTSelectionFull() {

	// lists of file names, weights and types to run over
	/*
	// All
	std::vector<std::string> filename_list = {filename_intrinsic_test_run1_fhc, filename_intrinsic_test_run1_rhc, filename_mc_run1_fhc, filename_mc_run1_rhc, filename_dirt_run1_fhc, filename_dirt_run1_rhc, filename_beamoff_run1_fhc, filename_beamoff_run1_rhc,
                                              filename_intrinsic_test_run2a_fhc, filename_intrinsic_test_run2b_rhc, filename_mc_run2a_fhc, filename_mc_run2b_rhc, filename_dirt_run2a_fhc, filename_dirt_run2b_rhc, filename_beamoff_run2a_fhc, filename_beamoff_run2b_rhc,
                                              filename_intrinsic_test_run3b_rhc, filename_mc_run3b_rhc, filename_dirt_run3b_rhc, filename_beamoff_run3b_rhc,
                                              filename_intrinsic_test_run4_fhc, filename_intrinsic_test_run4_rhc, filename_mc_run4_fhc, filename_mc_run4_rhc, filename_dirt_run4_fhc, filename_dirt_run4_rhc, filename_beamoff_run4_fhc, filename_beamoff_run4_rhc,
                                              filename_intrinsic_test_run5_fhc, filename_mc_run5_fhc, filename_dirt_run5_fhc, filename_beamoff_run5_fhc
											 };
	std::vector<double> pot_weight_list = {pot_weight_intrinsic_test_run1_fhc, pot_weight_intrinsic_test_run1_rhc, pot_weight_mc_run1_fhc, pot_weight_mc_run1_rhc, pot_weight_dirt_run1_fhc, pot_weight_dirt_run1_rhc, pot_weight_beamoff_run1_fhc, pot_weight_beamoff_run1_rhc,
										   pot_weight_intrinsic_test_run2a_fhc, pot_weight_intrinsic_test_run2b_rhc, pot_weight_mc_run2a_fhc, pot_weight_mc_run2b_rhc, pot_weight_dirt_run2a_fhc, pot_weight_dirt_run2b_rhc, pot_weight_beamoff_run2a_fhc, pot_weight_beamoff_run2b_rhc,
										   pot_weight_intrinsic_test_run3b_rhc, pot_weight_mc_run3b_rhc, pot_weight_dirt_run3b_rhc, pot_weight_beamoff_run3b_rhc,
										   pot_weight_intrinsic_test_run4_fhc, pot_weight_intrinsic_test_run4_rhc, pot_weight_mc_run4_fhc, pot_weight_mc_run4_rhc, pot_weight_dirt_run4_fhc, pot_weight_dirt_run4_rhc, pot_weight_beamoff_run4_fhc, pot_weight_beamoff_run4_rhc,
										   pot_weight_intrinsic_test_run5_fhc, pot_weight_mc_run5_fhc, pot_weight_dirt_run5_fhc, pot_weight_beamoff_run5_fhc 
										  };
	std::vector<Utility::FileTypeEnums> file_types_list = {Utility::kIntrinsic, Utility::kIntrinsic, Utility::kMC, Utility::kMC, Utility::kDirt, Utility::kDirt, Utility::kEXT, Utility::kEXT,
                                       					   Utility::kIntrinsic, Utility::kIntrinsic, Utility::kMC, Utility::kMC, Utility::kDirt, Utility::kDirt, Utility::kEXT, Utility::kEXT,
                                       					   Utility::kIntrinsic, Utility::kMC, Utility::kDirt, Utility::kEXT,
                                       					   Utility::kIntrinsic, Utility::kIntrinsic, Utility::kMC, Utility::kMC, Utility::kDirt, Utility::kDirt, Utility::kEXT, Utility::kEXT,
                                       					   Utility::kIntrinsic, Utility::kMC, Utility::kDirt, Utility::kEXT  
                                       					  };
	std::vector<Utility::RunPeriodEnums> run_periods_list = {Utility::kRun1a, Utility::kRun1b, Utility::kRun1a, Utility::kRun1b, Utility::kRun1a, Utility::kRun1b, Utility::kRun1a, Utility::kRun1b,
															 Utility::kRun2a, Utility::kRun2b, Utility::kRun2a, Utility::kRun2b, Utility::kRun2a, Utility::kRun2b, Utility::kRun2a, Utility::kRun2b,
															 Utility::kRun3b, Utility::kRun3b, Utility::kRun3b, Utility::kRun3b,
															 Utility::kRun4cd, Utility::kRun4ab, Utility::kRun4cd, Utility::kRun4ab, Utility::kRun4cd, Utility::kRun4ab, Utility::kRun4cd, Utility::kRun4ab,
															 Utility::kRun5, Utility::kRun5, Utility::kRun5, Utility::kRun5
															};
	*/
	
	// Intrinsic Nue only
	std::vector<std::string> filename_list = {filename_intrinsic_test_run1_fhc, filename_intrinsic_test_run1_rhc,
                                              filename_intrinsic_test_run2a_fhc, filename_intrinsic_test_run2b_rhc,
                                              filename_intrinsic_test_run3b_rhc,
                                              filename_intrinsic_test_run4_fhc, filename_intrinsic_test_run4_rhc,
                                              filename_intrinsic_test_run5_fhc
											 };
	std::vector<double> pot_weight_list = {pot_weight_intrinsic_test_run1_fhc, pot_weight_intrinsic_test_run1_rhc,
										   pot_weight_intrinsic_test_run2a_fhc, pot_weight_intrinsic_test_run2b_rhc,
										   pot_weight_intrinsic_test_run3b_rhc,
										   pot_weight_intrinsic_test_run4_fhc, pot_weight_intrinsic_test_run4_rhc,
										   pot_weight_intrinsic_test_run5_fhc
										  };
	std::vector<Utility::FileTypeEnums> file_types_list = {Utility::kIntrinsic, Utility::kIntrinsic, 
                                       					   Utility::kIntrinsic, Utility::kIntrinsic,
                                       					   Utility::kIntrinsic,
                                       					   Utility::kIntrinsic, Utility::kIntrinsic,
                                       					   Utility::kIntrinsic 
                                       					  };
	std::vector<Utility::RunPeriodEnums> run_periods_list = {Utility::kRun1a, Utility::kRun1b,
															 Utility::kRun2a, Utility::kRun2b,
															 Utility::kRun3b,
															 Utility::kRun4cd, Utility::kRun4ab,
															 Utility::kRun5
															};														
	
	/*
	// FHC
	std::vector<std::string> filename_list = {filename_intrinsic_test_run1_fhc, filename_mc_run1_fhc, filename_dirt_run1_fhc, filename_beamoff_run1_fhc,
                                              filename_intrinsic_test_run2a_fhc, filename_mc_run2a_fhc, filename_dirt_run2a_fhc, filename_beamoff_run2a_fhc,
                                              filename_intrinsic_test_run4_fhc, filename_mc_run4_fhc, filename_dirt_run4_fhc, filename_beamoff_run4_fhc,
                                              filename_intrinsic_test_run5_fhc, filename_mc_run5_fhc, filename_dirt_run5_fhc, filename_beamoff_run5_fhc
											 };
	std::vector<double> pot_weight_list = {pot_weight_intrinsic_test_run1_fhc, pot_weight_mc_run1_fhc, pot_weight_dirt_run1_fhc, pot_weight_beamoff_run1_fhc,
										   pot_weight_intrinsic_test_run2a_fhc, pot_weight_mc_run2a_fhc, pot_weight_dirt_run2a_fhc, pot_weight_beamoff_run2a_fhc,
										   pot_weight_intrinsic_test_run4_fhc, pot_weight_mc_run4_fhc, pot_weight_dirt_run4_fhc, pot_weight_beamoff_run4_fhc,
										   pot_weight_intrinsic_test_run5_fhc, pot_weight_mc_run5_fhc, pot_weight_dirt_run5_fhc, pot_weight_beamoff_run5_fhc 
										  };
	std::vector<Utility::FileTypeEnums> file_types_list = {Utility::kIntrinsic, Utility::kMC, Utility::kDirt, Utility::kEXT,
														   Utility::kIntrinsic, Utility::kMC, Utility::kDirt, Utility::kEXT,
														   Utility::kIntrinsic, Utility::kMC, Utility::kDirt, Utility::kEXT,
                                       					   Utility::kIntrinsic, Utility::kMC, Utility::kDirt, Utility::kEXT  
                                       					  };
	std::vector<Utility::RunPeriodEnums> run_periods_list = {Utility::kRun1a, Utility::kRun1a, Utility::kRun1a, Utility::kRun1a,
															 Utility::kRun2a, Utility::kRun2a, Utility::kRun2a, Utility::kRun2a,
															 Utility::kRun4cd, Utility::kRun4cd, Utility::kRun4cd, Utility::kRun4cd,
															 Utility::kRun5, Utility::kRun5, Utility::kRun5, Utility::kRun5
															};
	*/
	/*
	// RHC
	std::vector<std::string> filename_list = {filename_intrinsic_test_run1_rhc, filename_mc_run1_rhc, filename_dirt_run1_rhc, filename_beamoff_run1_rhc,
                                              filename_intrinsic_test_run2b_rhc, filename_mc_run2b_rhc, filename_dirt_run2b_rhc, filename_beamoff_run2b_rhc,
                                              filename_intrinsic_test_run3b_rhc, filename_mc_run3b_rhc, filename_dirt_run3b_rhc, filename_beamoff_run3b_rhc,
                                              filename_intrinsic_test_run4_rhc, filename_mc_run4_rhc, filename_dirt_run4_rhc, filename_beamoff_run4_rhc,
											 };
	std::vector<double> pot_weight_list = {pot_weight_intrinsic_test_run1_rhc, pot_weight_mc_run1_rhc, pot_weight_dirt_run1_rhc, pot_weight_beamoff_run1_rhc,
										   pot_weight_intrinsic_test_run2b_rhc, pot_weight_mc_run2b_rhc, pot_weight_dirt_run2b_rhc, pot_weight_beamoff_run2b_rhc,
										   pot_weight_intrinsic_test_run3b_rhc, pot_weight_mc_run3b_rhc, pot_weight_dirt_run3b_rhc, pot_weight_beamoff_run3b_rhc,
										   pot_weight_intrinsic_test_run4_rhc, pot_weight_mc_run4_rhc, pot_weight_dirt_run4_rhc, pot_weight_beamoff_run4_rhc,
										  };
	std::vector<Utility::FileTypeEnums> file_types_list = {Utility::kIntrinsic, Utility::kMC, Utility::kDirt, Utility::kEXT,
                                       					   Utility::kIntrinsic, Utility::kMC, Utility::kDirt, Utility::kEXT,
                                       					   Utility::kIntrinsic, Utility::kMC, Utility::kDirt, Utility::kEXT,
                                       					   Utility::kIntrinsic, Utility::kMC, Utility::kDirt, Utility::kEXT  
                                       					  };
	std::vector<Utility::RunPeriodEnums> run_periods_list = {Utility::kRun1b, Utility::kRun1b, Utility::kRun1b, Utility::kRun1b,
															 Utility::kRun2b, Utility::kRun2b, Utility::kRun2b, Utility::kRun2b,
															 Utility::kRun3b, Utility::kRun3b, Utility::kRun3b, Utility::kRun3b,
															 Utility::kRun4ab, Utility::kRun4ab, Utility::kRun4ab, Utility::kRun4ab,
															};
	*/

	// Data only
	// FHC
	/*
	std::vector<std::string> filename_list = {filename_beamon_run1_fhc, filename_beamon_run2a_fhc, filename_beamon_run4_fhc, filename_beamon_run5_fhc};                                       
	std::vector<double> pot_weight_list = {pot_weight_beamoff_run1_fhc, pot_weight_beamoff_run2a_fhc, pot_weight_beamoff_run4_fhc, pot_weight_beamoff_run5_fhc};
	std::vector<Utility::FileTypeEnums> file_types_list = {Utility::kData, Utility::kData, Utility::kData, Utility::kData};
	std::vector<Utility::RunPeriodEnums> run_periods_list = {Utility::kRun1a, Utility::kRun2a, Utility::kRun4cd, Utility::kRun5};
	*/
	// RHC
	/*
	std::vector<std::string> filename_list = {filename_beamon_run1_rhc, filename_beamon_run2b_rhc, filename_beamon_run3b_rhc, filename_beamon_run4_rhc};                                       
	std::vector<double> pot_weight_list = {pot_weight_beamoff_run1_rhc, pot_weight_beamoff_run2b_rhc, pot_weight_beamoff_run3b_rhc, pot_weight_beamoff_run4_rhc};
	std::vector<Utility::FileTypeEnums> file_types_list = {Utility::kData, Utility::kData, Utility::kData, Utility::kData};
	std::vector<Utility::RunPeriodEnums> run_periods_list = {Utility::kRun1b, Utility::kRun2b, Utility::kRun3b, Utility::kRun4ab};
	*/
	
	/*
	std::vector<std::string> filename_list = {filename_intrinsic_test_run1_fhc};
	std::vector<double> pot_weight_list = {pot_weight_intrinsic_test_run1_fhc};
    std::vector<Utility::FileTypeEnums> file_types_list	= {Utility::kIntrinsic};
    std::vector<Utility::RunPeriodEnums> run_periods_list = {Utility::kRun1a};
	*/

	// construct classes
	BDTTool _BDTTool(true, true, true, true, _utility);
	Selection _selection(_utility);

	// construct stacks
	StackedHistTool _histStack_contained_fraction("", "", 20, 0, 1.001, _utility);
	StackedHistTool _histStack_associated_hits_fraction("", "", 20, 0, 1.001, _utility);
	StackedHistTool _histStack_shr_score("", "", 20, 0, 1.001, _utility);
	StackedHistTool _histStack_shr_hits_fraction("", "", 20, 0, 1.001, _utility);
	StackedHistTool _histStack_shr_trk_len("", "", 60, 0, 300, _utility);
	StackedHistTool _histStack_shr_energy("", "", 30, 0, 3, _utility);
	StackedHistTool _histStack_trk_energy_muon("", "", 40, 0, 1.6, _utility);
	StackedHistTool _histStack_trk_length("", "", 60, 0, 300, _utility);
	StackedHistTool _histStack_trk_vertex_distance("", "", 15, 0, 15, _utility);
	StackedHistTool _histStack_topological_score("", "", 20, 0, 1.001, _utility);
	StackedHistTool _histStack_cosmic_IP("", "", 20, 0, 100, _utility);
	StackedHistTool _histStack_number_protons("", "", 3, 0, 3, _utility);
	StackedHistTool _histStack_number_protons_true("", "", 5, 0, 5, _utility);
	StackedHistTool _histStack_number_tracks("", "", 6, 0, 6, _utility);
	StackedHistTool _histStack_BDT_score_electronphoton("", "", 20, 0, 1.001, _utility);
	StackedHistTool _histStack_BDT_score_pionproton("", "", 20, 0, 1.001, _utility);

	StackedHistTool _histStack_electron_angle("", "", 40, -1, 1, _utility);
	StackedHistTool _histStack_pion_angle("", "", 40, -1, 1, _utility);

	StackedHistTool _histStack_shr_energy_interaction("", "", 10, 0, 3, _utility, "Interaction");
   	
	// Passing event vectors (Binning Test)
	std::vector<double> variable_reco_vec;
	std::vector<double> variable_true_vec;
	std::vector<double> weight_vec;

	// 2D histograms
	// electron energy
	TH2F *electronEnergy2D = new TH2F("", "", 35, 0, 3.5, 35, 0, 3.5);
	// pion energy
	TH2F *pionEnergy2D = new TH2F("", "", 20, 0, 1.0, 20, 0, 1.0);
	// number of protons
	TH2I *numberProtons2D = new TH2I("", "", 2, 0, 2, 2, 0, 2);
	// electron angle
	TH2F *electronAngle2D = new TH2F("", "", 36, 0, 180, 36, 0, 180);
	//TH2F *electronAngle2D = new TH2F("", "", 40, -1, 1, 40, -1, 1);
	// pion angle
	TH2F *pionAngle2D = new TH2F("", "", 36, 0, 180, 36, 0, 180);
	//TH2F *pionAngle2D = new TH2F("", "", 40, -1, 1, 40, -1, 1);

	// Counter (Data)
	int n_data_pass = 0;

	// driver loop
	for (unsigned int idx = 0; idx < filename_list.size(); idx++) {

		std::cout << "Processing file " << filename_list[idx] << std::endl;

		// read file
		TFile *f = NULL;
	  	TTree *tree = NULL;
	 	f = new TFile(filename_list[idx].c_str()); 
	 	if (file_types_list[idx] == Utility::kIntrinsic || file_types_list[idx] == Utility::kMC) {
	 		tree = (TTree*)f->Get("NeutrinoSelectionFilter");
	 	}
	 	else {
	 		tree = (TTree*)f->Get("nuselection/NeutrinoSelectionFilter");
	 	}

	 	// initialise event container
	  	EventContainer _event(tree, _utility);

	  	// loop through events
	  	int n_entries = tree->GetEntries();
	  	std::cout << "Initial number events: " << n_entries << std::endl;

	  	for (int e = 0; e < n_entries; e++) {
	  		
	    	tree->GetEntry(e);    	

		    if ( (e != 0) && (n_entries >= 10) &&  (e % (n_entries/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries/10));
		    }

		    if (file_types_list[idx] == Utility::kIntrinsic) {
		    	if (_event.run % 2 != 0) std::cout << "Error: incorrect run included -- run: " << _event.run << std::endl; 
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event, _BDTTool, file_types_list[idx], run_periods_list[idx]);
		    if (!passSelection) continue;	

		    // select which events to keep or remove if signal enhanced sample or standard nu overlay
		    if (file_types_list[idx] == Utility::kIntrinsic) {
		    	if (!((_event.classification == Utility::kCCNue1piXp || _event.classification == Utility::kCCNueNpi || _event.classification == Utility::kCCNuepizero ||
    				_event.classification == Utility::kCCNueNp || _event.classification == Utility::kCCNueOther))) continue;
		    }
		    else if (file_types_list[idx] == Utility::kMC) {
		    	if (((_event.classification == Utility::kCCNue1piXp || _event.classification == Utility::kCCNueNpi || _event.classification == Utility::kCCNuepizero ||
    				_event.classification == Utility::kCCNueNp || _event.classification == Utility::kCCNueOther))) continue;
		    }

		    // evaluate correct POT weight accounting for special cases
		    double pot_weight = 0;
		    if (file_types_list[idx] == Utility::kEXT && run_periods_list[idx] == Utility::kRun3b) {
		    	if (_event.run < 16880) pot_weight = pot_weight_beamoff_run3b_rhc_pre;
		    	else pot_weight = pot_weight_beamoff_run3b_rhc_post;
		    }
		    else {
		    	pot_weight = pot_weight_list[idx];
		    }

		    if (file_types_list[idx] == Utility::kData) n_data_pass++;
		    
		    // fill histogram(s)
		    _histStack_contained_fraction.Fill(_event.classification, _event.contained_fraction, pot_weight * _event.weight_cv);
		    _histStack_associated_hits_fraction.Fill(_event.classification, _event.associated_hits_fraction, pot_weight * _event.weight_cv);
		    _histStack_shr_score.Fill(_event.classification, _event.shr_score, pot_weight * _event.weight_cv);
		    _histStack_shr_hits_fraction.Fill(_event.classification, _event.hits_ratio, pot_weight * _event.weight_cv);
		    _histStack_shr_trk_len.Fill(_event.classification, _event.shr_trk_len, pot_weight * _event.weight_cv);
		    _histStack_shr_energy.Fill(_event.classification, _event.shr_energy_cali, pot_weight * _event.weight_cv);
		    _histStack_topological_score.Fill(_event.classification, _event.topological_score, pot_weight * _event.weight_cv);
		    _histStack_cosmic_IP.Fill(_event.classification, _event.CosmicIPAll3D, pot_weight * _event.weight_cv);
		    _histStack_BDT_score_electronphoton.Fill(_event.classification, _event.BDTScoreElectronPhoton, pot_weight * _event.weight_cv);
		    _histStack_number_protons.Fill(_event.classification, _event.numberProtons, pot_weight * _event.weight_cv);
		    _histStack_number_protons_true.Fill(_event.classification, _event.nproton, pot_weight * _event.weight_cv);
		    _histStack_number_tracks.Fill(_event.classification, _event.n_tracks_contained, pot_weight * _event.weight_cv);

		    // angles
		    _histStack_electron_angle.Fill(_event.classification, _event.reco_cos_electron_effective_angle, pot_weight * _event.weight_cv);
		    _histStack_pion_angle.Fill(_event.classification, _event.reco_cos_pion_effective_angle, pot_weight * _event.weight_cv);

		    //if (_event.sel_passBDTPi0Rejection_) {

		    if (_event.primaryTrackPionlike) {
		    	_histStack_trk_energy_muon.Fill(_event.classification, _event.trk_energy_muon, pot_weight * _event.weight_cv);
		    	_histStack_trk_length.Fill(_event.classification, _event.trk_len, pot_weight * _event.weight_cv);
		    	_histStack_trk_vertex_distance.Fill(_event.classification, _event.trk_distance, pot_weight * _event.weight_cv);
		    	_histStack_BDT_score_pionproton.Fill(_event.classification, _event.primaryTrackBDTScorePionProton, pot_weight * _event.weight_cv);		 
		    }
	        else if (_event.secondaryTrackPionlike) {
	        	_histStack_trk_energy_muon.Fill(_event.classification, _event.trk2_energy_muon, pot_weight * _event.weight_cv);
		    	_histStack_trk_length.Fill(_event.classification, _event.trk2_len, pot_weight * _event.weight_cv);
		    	_histStack_trk_vertex_distance.Fill(_event.classification, _event.trk2_distance, pot_weight * _event.weight_cv);
		    	_histStack_BDT_score_pionproton.Fill(_event.classification, _event.secondaryTrackBDTScorePionProton, pot_weight * _event.weight_cv);
	        }
	  	    else if (_event.tertiaryTrackPionlike) {
	  	    	_histStack_trk_energy_muon.Fill(_event.classification, _event.trk3_energy_muon, pot_weight * _event.weight_cv);
		    	_histStack_trk_length.Fill(_event.classification, _event.trk3_len, pot_weight * _event.weight_cv);
		    	_histStack_trk_vertex_distance.Fill(_event.classification, _event.trk3_distance, pot_weight * _event.weight_cv);
		    	_histStack_BDT_score_pionproton.Fill(_event.classification, _event.tertiaryTrackBDTScorePionProton, pot_weight * _event.weight_cv);
	  	    }	
	  	    //}	

	  	    if (_event.reco_cos_pion_effective_angle <= -1 || _event.reco_cos_pion_effective_angle >= 1) {
	  	    		std::cout << "Bad Pion Reco angle: " << _event.reco_cos_pion_effective_angle << std::endl;
	  	    }
	  	    if (_event.reco_cos_electron_effective_angle <= -1 || _event.reco_cos_electron_effective_angle >= 1) {
	  	    		std::cout << "Bad Electron Reco angle: " << _event.reco_cos_electron_effective_angle << std::endl;
	  	    }

	  	    //std::cout << "Pion Reco: " << _event.reco_cos_pion_effective_angle << ", True: " << _event.true_cos_pion_effective_angle << std::endl;
	  	    //std::cout << "Electron Reco: " << _event.reco_cos_electron_effective_angle << ", True: " << _event.true_cos_electron_effective_angle << std::endl;

	  	    // fill vectors (signal)
	  	    if (_event.classification == Utility::kCCNue1piXp) {
	  	    	// electron energy
	  	    	/*
	  	    	variable_true_vec.push_back(_event.elec_e);
	  	    	variable_reco_vec.push_back(_event.shr_energy_cali);
	  	    	weight_vec.push_back(pot_weight * _event.weight_cv);
				*/
	  	    	// electron angle
	  	    	/*
	  	    	variable_true_vec.push_back(_event.true_cos_electron_effective_angle);
	  	    	variable_reco_vec.push_back(_event.reco_cos_electron_effective_angle);
	  	    	weight_vec.push_back(pot_weight * _event.weight_cv);
	  	    	*/
	  	    	// pion angle
	  	    	variable_true_vec.push_back(_event.true_cos_pion_effective_angle);
	  	    	variable_reco_vec.push_back(_event.reco_cos_pion_effective_angle);
	  	    	weight_vec.push_back(pot_weight * _event.weight_cv);

	  	    	// sanity check:
	  	    	if (_event.true_cos_pion_effective_angle < -1 || _event.true_cos_pion_effective_angle > 1) {
	  	    		std::cout << "Bad True angle: " << _event.true_cos_pion_effective_angle << std::endl;
	  	    	}
	  	    	if (_event.reco_cos_pion_effective_angle < -1 || _event.reco_cos_pion_effective_angle > 1) {
	  	    		std::cout << "Bad Reco angle: " << _event.reco_cos_pion_effective_angle << std::endl;
	  	    	}
	  		}

	  		// fill 2D histograms (signal)
	  		if (_event.classification == Utility::kCCNue1piXp) {
	  			// electron energy
	  			electronEnergy2D->Fill(_event.elec_e, _event.shr_energy_cali);
	  			// pion energy
	  			pionEnergy2D->Fill(_event.pion_e, _event.reco_energy_pion);
	  			

	  			// number protons
	  			numberProtons2D->Fill(_event.nprotonalternate, _event.numberProtons);

	  			_histStack_shr_energy_interaction.Fill(_event.interactionMode, _event.shr_energy_cali, pot_weight * _event.weight_cv);

	  			// electron angle
	  			electronAngle2D->Fill(_event.true_cos_electron_effective_angle, _event.reco_cos_electron_effective_angle);
	  			// pion angle
	  			pionAngle2D->Fill(_event.true_pion_effective_angle, _event.reco_pion_effective_angle);

	  		}
		}

		// clean up
		f->Close();
		delete f;	  	
	}

	std::cout << "Passing Data Events: " << n_data_pass << std::endl;

	/*
	std::cout << "Signal Events (Vector): ";
	double events_counter_vector = 0;
	for (int i = 0; i < weight_vec.size(); i++) {
		events_counter_vector += weight_vec[i];
	}
	std::cout << events_counter_vector << std::endl;

	
	// Optimise bins
	//double lower_edge = 0.03; // electron energy 30 MeV, from signal definition
	double lower_edge = -1; // angles
	
	std::vector<double> edges;
	edges.push_back(lower_edge);

	double new_edge = -0.9; // first new edge to check

	for (int bin = 0; bin < 5; bin++) {

		for (int b = 0; b < 100; b++ ) {

			double event_counter = 0;
			
			new_edge = new_edge + 0.05;

			for (int i = 0; i < variable_true_vec.size(); i++) {
				if (new_edge == 1) {
					if ( variable_true_vec[i] >= lower_edge && variable_true_vec[i] <= new_edge ) event_counter += weight_vec[i];
				}
				else {
					if ( variable_true_vec[i] >= lower_edge && variable_true_vec[i] < new_edge ) event_counter += weight_vec[i];
				}
			}

			std::cout << "Bin: [" << lower_edge << ", " << new_edge << "] --> Signal Events: " << event_counter << std::endl;

			if (bin == 0 && event_counter > 10.0) break;
			else if (bin == 1 && event_counter > 10) break;
			else if (event_counter >= 15) break;

			if (new_edge >= 1) break;

		}

		// store edge
		edges.push_back(new_edge);

		// set up for next loop
		lower_edge = new_edge;

		if (new_edge >= 1) break;
	}

	std::cout << "Bin edges: " << std::endl;
	for (int i = 0; i < edges.size(); i++) {
		std::cout << edges[i] << ", ";
	}
	std::cout << std::endl;
	*/

	/*
	// output vectors
	std::cout << "True electron energy: " << std::endl;
	std::sort(electron_energy_true_vec.begin(), electron_energy_true_vec.end());
	for (int i = 0; i < electron_energy_true_vec.size(); i++) {
		std::cout << electron_energy_true_vec[i] << ", ";
	}
	std::cout << std::endl;

	std::cout << "Backtracked true shower energy: " << std::endl;
	std::sort(shr_energy_true_vec.begin(), shr_energy_true_vec.end());
	for (int i = 0; i < shr_energy_true_vec.size(); i++) {
		std::cout << shr_energy_true_vec[i] << ", ";
	}
	std::cout << std::endl;

	std::cout << "Reconstructed electron energy (shower energy): " << std::endl;
	std::sort(shr_energy_reco_vec.begin(), shr_energy_reco_vec.end());
	for (int i = 0; i < shr_energy_reco_vec.size(); i++) {
		std::cout << shr_energy_reco_vec[i] << ", ";
	}
	std::cout << std::endl;
	*/

	// print event integrals
	_histStack_contained_fraction.PrintEventIntegrals();
	

	// draw histograms
	TCanvas *c1 = new TCanvas("c1", "c1", 1080, 1080);
  	_histStack_contained_fraction.DrawStack(c1, Utility::kContainedFraction);
  	c1->Print("plots/plot_contained_fraction.root");

  	TCanvas *c2 = new TCanvas("c2", "c2", 1080, 1080);
  	c2->cd();
  	_histStack_associated_hits_fraction.DrawStack(c2, Utility::kAssociatedHitsFraction);
  	c2->Print("plots/plot_associated_hits_fraction.root");

  	TCanvas *c3 = new TCanvas("c3", "c3", 1080, 1080);
  	c3->cd();
  	_histStack_shr_score.DrawStack(c3, Utility::kShowerScore);
  	c3->Print("plots/plot_shr_score.root");

  	TCanvas *c4 = new TCanvas("c4", "c4", 1080, 1080);
  	c4->cd();
  	_histStack_shr_hits_fraction.DrawStack(c4, Utility::kHitRatio);
  	c4->Print("plots/plot_shr_hits_fraction.root");

  	TCanvas *c4a = new TCanvas("c4a", "c4a", 1080, 1080);
  	c4a->cd();
  	_histStack_shr_trk_len.DrawStack(c4a, Utility::kTrackLength);
  	c4a->Print("plots/plot_shr_trk_length.root");

  	TCanvas *c4b = new TCanvas("c4b", "c4b", 1080, 1080);
  	c4b->cd();
  	_histStack_shr_energy.DrawStack(c4b, Utility::kShowerEnergy);
  	c4b->Print("plots/plot_shr_energy.root");

  	TCanvas *c4c = new TCanvas("c4c", "c4c", 1080, 1080);
  	c4c->cd();
  	_histStack_shr_energy_interaction.DrawStack(c4c, Utility::kShowerEnergy);
  	c4c->Print("plots/plot_shr_energy_interaction.root");
  	
  	TCanvas *c5 = new TCanvas("c5", "c5", 1080, 1080);
  	c5->cd();
  	_histStack_topological_score.DrawStack(c5, Utility::kTopologicalScore);
  	c5->Print("plots/plot_topological_score.root");

  	TCanvas *c6 = new TCanvas("c6", "c6", 1080, 1080);
  	c6->cd();
  	_histStack_cosmic_IP.DrawStack(c6, Utility::kCosmicImpactParameter);
  	c6->Print("plots/plot_cosmic_IP.root");

  	TCanvas *c6a = new TCanvas("c6a", "c6a", 1080, 1080);
  	c6a->cd();
  	_histStack_number_protons.DrawStack(c6a, Utility::kNumberProtons);
  	c6a->Print("plots/plot_number_protons.root");

  	TCanvas *c6c = new TCanvas("c6c", "c6c", 1080, 1080);
  	c6c->cd();
  	_histStack_number_protons_true.DrawStack(c6c, Utility::kNumberProtonsTrue);
  	c6c->Print("plots/plot_number_protons_true.root");

  	TCanvas *c6b = new TCanvas("c6b", "c6b", 1080, 1080);
  	c6b->cd();
  	_histStack_number_tracks.DrawStack(c6b, Utility::kNTrack);
  	c6b->Print("plots/plot_number_tracks.root");

  	TCanvas *c7 = new TCanvas("c7", "c7", 1080, 1080);
  	c7->cd();
  	_histStack_trk_energy_muon.DrawStack(c7, Utility::kTrackEnergy);
  	c7->Print("plots/plot_energy_muon.root");

  	TCanvas *c8 = new TCanvas("c8", "c8", 1080, 1080);
  	c8->cd();
  	_histStack_trk_length.DrawStack(c8, Utility::kTrackLength);
  	c8->Print("plots/plot_trk_length.root");

  	TCanvas *c9 = new TCanvas("c9", "c9", 1080, 1080);
  	c9->cd();
  	_histStack_trk_vertex_distance.DrawStack(c9, Utility::kTrackDistance);
  	c9->Print("plots/plot_trk_vertex_distance.root");

  	TCanvas *c10 = new TCanvas("c10", "c10", 1080, 1080);
  	c10->cd();
  	_histStack_BDT_score_electronphoton.DrawStack(c10, Utility::kElectronNeutralPionBDT);
  	TLine *l1 = new TLine(0.825,0,0.825,100);
  	l1->SetLineColor(kBlack);
 	l1->SetLineStyle(9);
 	l1->SetLineWidth(3);
  	l1->Draw("same");
  	c10->Print("plots/plot_BDT_score_electronphoton.root");
  	

  	TCanvas *c11 = new TCanvas("c11", "c11", 1080, 1080);
  	c11->cd();
  	_histStack_BDT_score_pionproton.DrawStack(c11, Utility::kPionProtonBDT);
  	TLine *l2 = new TLine(0.325,0,0.325,12);
  	l2->SetLineColor(kBlack);
 	l2->SetLineStyle(9);
 	l2->SetLineWidth(3);
  	l2->Draw("same");
  	c11->Print("plots/plot_BDT_score_pionproton.root");

  	TCanvas *c11a = new TCanvas("c11a", "c11a", 1080, 1080);
  	c11a->cd();
  	_histStack_electron_angle.DrawStack(c11a, Utility::kElectronBeta);
  	c11a->Print("plots/plot_electron_angle.root");

  	TCanvas *c11b = new TCanvas("c11b", "c11b", 1080, 1080);
  	c11b->cd();
  	_histStack_pion_angle.DrawStack(c11b, Utility::kPionBeta);
  	c11b->Print("plots/plot_pion_angle.root");

  	// create proton confusion matrix
    TCanvas *c12 = new TCanvas("c12", "c12", 1080, 1080);
    c12->cd();
    TH2F *hist = new TH2F("confusion_hist", "Confusion Matrix", 2, 0, 2, 2, 0, 2);

    // loop through true bins
    for (int true_idx = 1; true_idx <= 2; true_idx++) {
    	// loop through reco bins
    	for (int reco_idx = 1; reco_idx <= 2; reco_idx++) {
    		hist->SetBinContent(true_idx, reco_idx, _histStack_number_protons.GetBinValue(true_idx, reco_idx));
    	}
    }
    hist->GetXaxis()->SetTitle("True Protons");
    hist->GetYaxis()->SetTitle("Reconstructed Protons");
    hist->Draw("TEXT COL");
    c12->Print("plots/protonMatrix.root");

	// Draw 2D histograms
	// electron energy
  	TCanvas *c13 = new TCanvas("c13", "c13", 1080, 1080);
  	c13->cd();
  	electronEnergy2D->GetXaxis()->SetTitle("True Electron Energy [GeV]");
    electronEnergy2D->GetYaxis()->SetTitle("Reconstructed Electron Energy [GeV]");
    electronEnergy2D->Draw("COLZ");
    TLine *l13 = new TLine(0,0,3.5,3.5);
    l13->SetLineColor(kBlack);
 	l13->SetLineStyle(9);
 	l13->SetLineWidth(3);
 	l13->Draw("same");
    c13->Print("plots/electronEnergy2D.root");

    // pion energy
  	TCanvas *c14 = new TCanvas("c14", "c14", 1080, 1080);
  	c14->cd();
  	pionEnergy2D->GetXaxis()->SetTitle("True Pion Energy [GeV]");
    pionEnergy2D->GetYaxis()->SetTitle("Reconstructed Pion Energy [GeV]");
    pionEnergy2D->Draw("COLZ");
    TLine *l14 = new TLine(0,0,1.0,1.0);
    l14->SetLineColor(kBlack);
 	l14->SetLineStyle(9);
 	l14->SetLineWidth(3);
 	l14->Draw("same");
    c14->Print("plots/pionEnergy2D.root");

    // number protons
    TCanvas *c15 = new TCanvas("c15", "c15", 1080, 1080);
  	c15->cd();
  	numberProtons2D->GetXaxis()->SetTitle("True Protons");
    numberProtons2D->GetYaxis()->SetTitle("Reconstructed Protons");
    numberProtons2D->Draw("TEXT COL");
    c15->Print("plots/numberProtons2D.root");

    // electron angle
    TCanvas *c16 = new TCanvas("c16", "c16", 1080, 1080);
  	c16->cd();
  	electronAngle2D->GetXaxis()->SetTitle("True Electron #beta [Deg]");
    electronAngle2D->GetYaxis()->SetTitle("Reconstructed Electron #beta [Deg]");
    electronAngle2D->Draw("COLZ");
    TLine *l16 = new TLine(0,0,180,180);
    l16->SetLineColor(kBlack);
 	l16->SetLineStyle(9);
 	l16->SetLineWidth(3);
 	l16->Draw("same");
    c16->Print("plots/electronAngle2D.root");

    // pion angle
    TCanvas *c17 = new TCanvas("c17", "c17", 1080, 1080);
  	c17->cd();
  	pionAngle2D->GetXaxis()->SetTitle("True Pion #beta [Deg]");
    pionAngle2D->GetYaxis()->SetTitle("Reconstructed Pion #beta [Deg]");
    pionAngle2D->Draw("COLZ");
    TLine *l17 = new TLine(0,0,180,180);
    l17->SetLineColor(kBlack);
 	l17->SetLineStyle(9);
 	l17->SetLineWidth(3);
 	l17->Draw("same");
    c17->Print("plots/pionAngle2D.root");
}

// ------------------------------------------------------------------------------

// Run BDT selection on all samples
void SelectionDriver::optimiseBDTSelection() {

	// lists of file names, weights and types to run over
	// FHC
	/*
	std::vector<std::string> filename_list = {filename_intrinsic_test_run1_fhc, filename_mc_run1_fhc, filename_dirt_run1_fhc, filename_beamoff_run1_fhc,
                                              filename_intrinsic_test_run2a_fhc, filename_mc_run2a_fhc, filename_dirt_run2a_fhc, filename_beamoff_run2a_fhc,
                                              filename_intrinsic_test_run4_fhc, filename_mc_run4_fhc, filename_dirt_run4_fhc, filename_beamoff_run4_fhc,
                                              filename_intrinsic_test_run5_fhc, filename_mc_run5_fhc, filename_dirt_run5_fhc, filename_beamoff_run5_fhc
											 };
	std::vector<double> pot_weight_list = {pot_weight_intrinsic_test_run1_fhc, pot_weight_mc_run1_fhc, pot_weight_dirt_run1_fhc, pot_weight_beamoff_run1_fhc,
										   pot_weight_intrinsic_test_run2a_fhc, pot_weight_mc_run2a_fhc, pot_weight_dirt_run2a_fhc, pot_weight_beamoff_run2a_fhc,
										   pot_weight_intrinsic_test_run4_fhc, pot_weight_mc_run4_fhc, pot_weight_dirt_run4_fhc, pot_weight_beamoff_run4_fhc,
										   pot_weight_intrinsic_test_run5_fhc, pot_weight_mc_run5_fhc, pot_weight_dirt_run5_fhc, pot_weight_beamoff_run5_fhc 
										  };
	std::vector<Utility::FileTypeEnums> file_types_list = {Utility::kIntrinsic, Utility::kMC, Utility::kDirt, Utility::kEXT,
														   Utility::kIntrinsic, Utility::kMC, Utility::kDirt, Utility::kEXT,
														   Utility::kIntrinsic, Utility::kMC, Utility::kDirt, Utility::kEXT,
                                       					   Utility::kIntrinsic, Utility::kMC, Utility::kDirt, Utility::kEXT  
                                       					  };
	std::vector<Utility::RunPeriodEnums> run_periods_list = {Utility::kRun1a, Utility::kRun1a, Utility::kRun1a, Utility::kRun1a,
															 Utility::kRun2a, Utility::kRun2a, Utility::kRun2a, Utility::kRun2a,
															 Utility::kRun4cd, Utility::kRun4cd, Utility::kRun4cd, Utility::kRun4cd,
															 Utility::kRun5, Utility::kRun5, Utility::kRun5, Utility::kRun5
															};
	*/
	
	// RHC
	
	std::vector<std::string> filename_list = {filename_intrinsic_test_run1_rhc, filename_mc_run1_rhc, filename_dirt_run1_rhc, filename_beamoff_run1_rhc,
                                              filename_intrinsic_test_run2b_rhc, filename_mc_run2b_rhc, filename_dirt_run2b_rhc, filename_beamoff_run2b_rhc,
                                              filename_intrinsic_test_run3b_rhc, filename_mc_run3b_rhc, filename_dirt_run3b_rhc, filename_beamoff_run3b_rhc,
                                              filename_intrinsic_test_run4_rhc, filename_mc_run4_rhc, filename_dirt_run4_rhc, filename_beamoff_run4_rhc,
											 };
	std::vector<double> pot_weight_list = {pot_weight_intrinsic_test_run1_rhc, pot_weight_mc_run1_rhc, pot_weight_dirt_run1_rhc, pot_weight_beamoff_run1_rhc,
										   pot_weight_intrinsic_test_run2b_rhc, pot_weight_mc_run2b_rhc, pot_weight_dirt_run2b_rhc, pot_weight_beamoff_run2b_rhc,
										   pot_weight_intrinsic_test_run3b_rhc, pot_weight_mc_run3b_rhc, pot_weight_dirt_run3b_rhc, pot_weight_beamoff_run3b_rhc,
										   pot_weight_intrinsic_test_run4_rhc, pot_weight_mc_run4_rhc, pot_weight_dirt_run4_rhc, pot_weight_beamoff_run4_rhc,
										  };
	std::vector<Utility::FileTypeEnums> file_types_list = {Utility::kIntrinsic, Utility::kMC, Utility::kDirt, Utility::kEXT,
                                       					   Utility::kIntrinsic, Utility::kMC, Utility::kDirt, Utility::kEXT,
                                       					   Utility::kIntrinsic, Utility::kMC, Utility::kDirt, Utility::kEXT,
                                       					   Utility::kIntrinsic, Utility::kMC, Utility::kDirt, Utility::kEXT  
                                       					  };
	std::vector<Utility::RunPeriodEnums> run_periods_list = {Utility::kRun1b, Utility::kRun1b, Utility::kRun1b, Utility::kRun1b,
															 Utility::kRun2b, Utility::kRun2b, Utility::kRun2b, Utility::kRun2b,
															 Utility::kRun3b, Utility::kRun3b, Utility::kRun3b, Utility::kRun3b,
															 Utility::kRun4ab, Utility::kRun4ab, Utility::kRun4ab, Utility::kRun4ab,
															};															

	
	//std::vector<std::string> filename_list = {filename_intrinsic_test_run1_fhc, filename_mc_run1_fhc};
	//std::vector<double> pot_weight_list = {pot_weight_intrinsic_test_run1_fhc, pot_weight_mc_run1_fhc};
    //std::vector<Utility::FileTypeEnums> file_types_list	= {Utility::kIntrinsic, Utility::kMC};
    //std::vector<Utility::RunPeriodEnums> run_periods_list = {Utility::kRun1a, Utility::kRun1a};

    //std::vector<std::string> filename_list = {filename_intrinsic_test_run1_rhc, filename_mc_run1_rhc};
	//std::vector<double> pot_weight_list = {pot_weight_intrinsic_test_run1_rhc, pot_weight_mc_run1_rhc};
    //std::vector<Utility::FileTypeEnums> file_types_list	= {Utility::kIntrinsic, Utility::kMC};
    //std::vector<Utility::RunPeriodEnums> run_periods_list = {Utility::kRun1b, Utility::kRun1b};

	// construct classes
	BDTTool _BDTTool(true, true, true, true, _utility);
	Selection _selection(_utility);

	// values to test
	// Electron-Photon:     
	std::vector<double> bdt_1_values = {0.5, 0.525, 0.55, 0.575, 0.6, 0.625, 0.65, 0.675, 0.7, 0.725, 0.75, 0.775, 0.8, 0.825, 0.85, 0.875, 0.9};
	// Pion-Proton:		
	std::vector<double> bdt_2_values = {0.2, 0.225, 0.25, 0.275, 0.3, 0.325, 0.35, 0.375, 0.4, 0.425, 0.45, 0.475, 0.5, 0.525, 0.55, 0.575, 0.6};

	// construct stacks
	std::vector<std::vector<StackedHistTool>> _histStacks;

	for (int i = 0; i < bdt_1_values.size(); i++) {

		std::vector<StackedHistTool> hists_vec;

		for (int j = 0; j < bdt_2_values.size(); j++) {
			StackedHistTool _histStack("", "", 3, -1, 2, _utility);
			hists_vec.push_back(_histStack);
		}

		_histStacks.push_back(hists_vec);
	}
    
	// driver loop
	for (unsigned int idx = 0; idx < filename_list.size(); idx++) {

		std::cout << "Processing file " << filename_list[idx] << std::endl;

		// read file
		TFile *f = NULL;
	  	TTree *tree = NULL;
	 	f = new TFile(filename_list[idx].c_str()); 
	 	if (file_types_list[idx] == Utility::kIntrinsic || file_types_list[idx] == Utility::kMC) {
	 		tree = (TTree*)f->Get("NeutrinoSelectionFilter");
	 	}
	 	else {
	 		tree = (TTree*)f->Get("nuselection/NeutrinoSelectionFilter");
	 	}

	 	// initialise event container
	  	EventContainer _event(tree, _utility);

	  	// loop through events
	  	int n_entries = tree->GetEntries();
	  	std::cout << "Initial number events: " << n_entries << std::endl;

	  	for (int e = 0; e < n_entries; e++) {
	  		
	    	tree->GetEntry(e);    	

		    if ( (e != 0) && (n_entries >= 10) &&  (e % (n_entries/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event, _BDTTool, file_types_list[idx], run_periods_list[idx]);
		    if (!passSelection) continue;

		    // select which events to keep or remove if signal enhanced sample or standard nu overlay
		    if (file_types_list[idx] == Utility::kIntrinsic) {
		    	if (!((_event.classification == Utility::kCCNue1piXp || _event.classification == Utility::kCCNueNpi || _event.classification == Utility::kCCNuepizero ||
    				_event.classification == Utility::kCCNueNp || _event.classification == Utility::kCCNueOther))) continue;
		    }
		    else if (file_types_list[idx] == Utility::kMC) {
		    	if (((_event.classification == Utility::kCCNue1piXp || _event.classification == Utility::kCCNueNpi || _event.classification == Utility::kCCNuepizero ||
    				_event.classification == Utility::kCCNueNp || _event.classification == Utility::kCCNueOther))) continue;
		    }

		    // evaluate correct POT weight accounting for special cases
		    double pot_weight = 0;
		    if (file_types_list[idx] == Utility::kEXT && run_periods_list[idx] == Utility::kRun3b) {
		    	if (_event.run < 16880) pot_weight = pot_weight_beamoff_run3b_rhc_pre;
		    	else pot_weight = pot_weight_beamoff_run3b_rhc_post;
		    }
		    else {
		    	pot_weight = pot_weight_list[idx];
		    }

		    // fill histogram(s)
		    for (int i = 0; i < bdt_1_values.size(); i++) {
				for (int j = 0; j < bdt_2_values.size(); j++) {

					double bdt_1_cut = bdt_1_values[i];
					double bdt_2_cut = bdt_2_values[j];

					// check electron-photon BDT
					if (_event.BDTScoreElectronPhoton > bdt_1_cut) {
						
						// check pion-proton BDT
						bool primaryTrackPasses = false;
						bool secondaryTrackPasses = false;
						bool tertiaryTrackPasses = false;

						// primary track
						if (_event.primaryTrackPionlikeLoose && _event.primaryTrackBDTScorePionProton > bdt_2_cut) primaryTrackPasses = true;

						// secondary track
						if (_event.secondaryTrackPionlikeLoose && _event.secondaryTrackBDTScorePionProton  > bdt_2_cut) secondaryTrackPasses = true;

						// tertiary track
						if (_event.tertiaryTrackPionlikeLoose && _event.tertiaryTrackBDTScorePionProton > bdt_2_cut) tertiaryTrackPasses = true;

						// count number of tracks that pass
						int nPass = 0;
						if (primaryTrackPasses) nPass++;
						if (secondaryTrackPasses) nPass++;
						if (tertiaryTrackPasses) nPass++;	

						// require 1 and only 1 charged pion candidate
						if (nPass == 1) {
							_histStacks[i][j].Fill(_event.classification, _event.BDTScoreElectronPhoton, pot_weight * _event.weight_cv);
						}
					}
				}
			}	
		}

		// clean up
		f->Close();
		delete f;	  	
	}

	// find best cuts
	double bdt_1_cut_best = 0;
	double bdt_2_cut_best = 0;
	double efficiency_best = 0;
	double purity_best = 0;
	double efficiencytimespurity_best = 0;

	// print event integrals
	for (int i = 0; i < bdt_1_values.size(); i++) {
		for (int j = 0; j < bdt_2_values.size(); j++) {

			double bdt_1_cut = bdt_1_values[i];
			double bdt_2_cut = bdt_2_values[j];
			
			double efficiency = (_histStacks[i][j]).GetSignalIntegral() / 669.4; // RHC ALL
			/// 494.3; // FHC ALL
			//
			/// 131.9; // FHC Run 1

			//  / 472.7; // FHC ALL
			double purity = (_histStacks[i][j]).GetSignalIntegral() / (_histStacks[i][j]).GetTotalIntegral(); 
			double efficiencytimespurity = efficiency * purity;

			std::cout << std::fixed << std::setprecision(3) << "BDT [ " << bdt_1_cut << ", " << bdt_2_cut << "] --- Efficiency: " << std::setprecision(2) << efficiency*100 << ", Purity: " << purity*100 << ", Eff*Pur: " << std::setprecision(4) << efficiencytimespurity << std::endl;
			//std::cout << (_histStacks[i][j]).GetSignalIntegral() << " , " << (_histStacks[i][j]).GetTotalIntegral() << std::endl;

			if (efficiencytimespurity > efficiencytimespurity_best && purity > 0.575) {
				bdt_1_cut_best = bdt_1_cut;
				bdt_2_cut_best = bdt_2_cut;
				efficiency_best = efficiency;
				purity_best = purity;
				efficiencytimespurity_best = efficiencytimespurity;
			}
		}
	}

	std::cout << std::endl << std::endl;
	std::cout << "---> Best Cut: " << std::endl;
	std::cout << std::fixed << std::setprecision(3) << "BDT [ " << bdt_1_cut_best << ", " << bdt_2_cut_best << "] --- Efficiency: " << std::setprecision(2) << efficiency_best*100 << ", Purity: " << purity_best*100 << ", Eff*Pur: " << std::setprecision(4) << efficiencytimespurity_best << std::endl;
}

// ------------------------------------------------------------------------------


// Run BDT selection on FHC samples
void SelectionDriver::runBDTSelectionFHC() {

	//StackedHistTool _histStack("", "", 20, 0, 1.001, _utility);
	//StackedHistTool _histStack("", "", 5, 0, 5, _utility);
	StackedHistTool _histStack("", "", 3, -1, 2, _utility);
	BDTTool _BDTTool(true, true, true, true, _utility);
	Selection _selection(_utility);
	
	// ----------------- Run 1 FHC ------------------
	{
		
		// --- Nue Overlay MC ---
		// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_test_run1_fhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 1 FHC Intrinsic Nue Overlay Test]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }
    		
		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_intrinsic, _BDTTool, Utility::kIntrinsic, Utility::kRun1a);
		    if (!passSelection) continue;

		    // select which events to keep, needs to match those removed from nu overlay mc
		    if (!((_event_intrinsic.classification == Utility::kCCNue1piXp || _event_intrinsic.classification == Utility::kCCNueNpi || _event_intrinsic.classification == Utility::kCCNuepizero ||
    				_event_intrinsic.classification == Utility::kCCNueNp || _event_intrinsic.classification == Utility::kCCNueOther))) continue;

		 
		    // fill histogram
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.BDTScoreElectronPhoton, pot_weight_intrinsic_test_run1_fhc * _event_intrinsic.weight_cv);

		    //if (_event_intrinsic.primaryTrackPionlikeLoose) _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.primaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run1_fhc * _event_intrinsic.weight_cv);
	        //else if (_event_intrinsic.secondaryTrackPionlikeLoose) _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.secondaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run1_fhc * _event_intrinsic.weight_cv);
	  	    //else _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.tertiaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run1_fhc * _event_intrinsic.weight_cv);	
		
		}

		delete f_intrinsic;
		
		
		// --- Nu Overlay MC ---	
		// read file
		TFile *f_mc = NULL;
	  	TTree *tree_mc = NULL;
	 	f_mc = new TFile(filename_mc_run1_fhc.c_str());  
	  	tree_mc = (TTree*)f_mc->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_mc(tree_mc, _utility); 	

	  	// loop through events
	  	int n_entries_mc = tree_mc->GetEntries();
	  	std::cout << "Initial number events [Run 1 FHC Nu Overlay]: " << n_entries_mc << std::endl;

	  	for (int e = 0; e < n_entries_mc; e++) {
	  	//for (int e = 0; e < 10000; e++) {
	  		
	    	tree_mc->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_mc >= 10) &&  (e % (n_entries_mc/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_mc/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_mc, _BDTTool, Utility::kMC, Utility::kRun1a);
		    if (!passSelection) continue;

		    // select which events to remove, needs to match taken from from nue overlay mc
		    if (((_event_mc.classification == Utility::kCCNue1piXp || _event_mc.classification == Utility::kCCNueNpi || _event_mc.classification == Utility::kCCNuepizero ||
    				_event_mc.classification == Utility::kCCNueNp || _event_mc.classification == Utility::kCCNueOther))) continue;

		    // fill histogram
		    _histStack.Fill(_event_mc.classification, _event_mc.BDTScoreElectronPhoton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);

		    //if (_event_mc.primaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.primaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
	        //else if (_event_mc.secondaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.secondaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
	  	    //else if (_event_mc.tertiaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.tertiaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
	  	    //else {
	  	    //	std::cout << "HERE" << std::endl;
	  	   // }
		}

		delete f_mc;
		
		
		
		// --- Dirt Overlay MC ---
		// read file
		TFile *f_dirt = NULL;
	  	TTree *tree_dirt = NULL;
	 	f_dirt = new TFile(filename_dirt_run1_fhc.c_str());  
	  	tree_dirt = (TTree*)f_dirt->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_dirt(tree_dirt, _utility); 	

	  	// loop through events
	  	int n_entries_dirt = tree_dirt->GetEntries();
	  	std::cout << "Initial number events [Run 1 FHC Dirt Overlay]: " << n_entries_dirt << std::endl;

	  	for (int e = 0; e < n_entries_dirt; e++) {

	    	tree_dirt->GetEntry(e);

		    if ( (e != 0) && (n_entries_dirt >= 10) &&  (e % (n_entries_dirt/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_dirt/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_dirt, _BDTTool, Utility::kDirt, Utility::kRun1a);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_dirt.classification, _event_dirt.BDTScoreElectronPhoton, pot_weight_dirt_run1_fhc * _event_dirt.weight_cv);

		    //if (_event_dirt.primaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.primaryTrackBDTScorePionProton, pot_weight_dirt_run1_fhc * _event_dirt.weight_cv);
	        //else if (_event_dirt.secondaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.secondaryTrackBDTScorePionProton, pot_weight_dirt_run1_fhc * _event_dirt.weight_cv);
	  	    //else _histStack.Fill(_event_dirt.classification, _event_dirt.tertiaryTrackBDTScorePionProton, pot_weight_dirt_run1_fhc * _event_dirt.weight_cv);


		}

		delete f_dirt;

		// --- Beam Off ---
		// read file
		TFile *f_beamoff = NULL;
	  	TTree *tree_beamoff = NULL;
	 	f_beamoff = new TFile(filename_beamoff_run1_fhc.c_str());  
	  	tree_beamoff = (TTree*)f_beamoff->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_beamoff(tree_beamoff, _utility); 	

	  	// loop through events
	  	int n_entries_beamoff = tree_beamoff->GetEntries();
	  	std::cout << "Initial number events [Run 1 FHC Beam Off]: " << n_entries_beamoff << std::endl;

	  	for (int e = 0; e < n_entries_beamoff; e++) {

	    	tree_beamoff->GetEntry(e);

		    if ( (e != 0) && (n_entries_beamoff >= 10) &&  (e % (n_entries_beamoff/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_beamoff/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_beamoff, _BDTTool, Utility::kEXT, Utility::kRun1a);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_beamoff.classification, _event_beamoff.BDTScoreElectronPhoton, pot_weight_beamoff_run1_fhc * _event_beamoff.weight_cv);

		    //if (_event_beamoff.primaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.primaryTrackBDTScorePionProton, pot_weight_beamoff_run1_fhc * _event_beamoff.weight_cv);
	        //else if (_event_beamoff.secondaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.secondaryTrackBDTScorePionProton, pot_weight_beamoff_run1_fhc * _event_beamoff.weight_cv);
	  	    //else _histStack.Fill(_event_beamoff.classification, _event_beamoff.tertiaryTrackBDTScorePionProton, pot_weight_beamoff_run1_fhc * _event_beamoff.weight_cv);
		}

		delete f_beamoff;
		
	}
	
	// ----------------- Run 2a FHC ------------------
	{
		
		// --- Nue Overlay MC ---
		// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_test_run2a_fhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 2a FHC Intrinsic Nue Overlay Test]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_intrinsic, _BDTTool, Utility::kIntrinsic, Utility::kRun2a);
		    if (!passSelection) continue;

		    // select which events to keep, needs to match those removed from nu overlay mc
		    if (!((_event_intrinsic.classification == Utility::kCCNue1piXp || _event_intrinsic.classification == Utility::kCCNueNpi || _event_intrinsic.classification == Utility::kCCNuepizero ||
    				_event_intrinsic.classification == Utility::kCCNueNp || _event_intrinsic.classification == Utility::kCCNueOther))) continue;


		    // fill histogram
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.BDTScoreElectronPhoton, pot_weight_intrinsic_test_run2a_fhc * _event_intrinsic.weight_cv);

		    //if (_event_intrinsic.primaryTrackPionlikeLoose) _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.primaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run2a_fhc * _event_intrinsic.weight_cv);
	        //else if (_event_intrinsic.secondaryTrackPionlikeLoose) _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.secondaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run2a_fhc * _event_intrinsic.weight_cv);
	  	    //else _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.tertiaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run2a_fhc * _event_intrinsic.weight_cv);

		}

		delete f_intrinsic;

		
		// --- Nu Overlay MC ---	
		// read file
		TFile *f_mc = NULL;
	  	TTree *tree_mc = NULL;
	 	f_mc = new TFile(filename_mc_run2a_fhc.c_str());  
	  	tree_mc = (TTree*)f_mc->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_mc(tree_mc, _utility); 	

	  	// loop through events
	  	int n_entries_mc = tree_mc->GetEntries();
	  	std::cout << "Initial number events [Run 2a FHC Nu Overlay]: " << n_entries_mc << std::endl;

	  	for (int e = 0; e < n_entries_mc; e++) {
	  		
	    	tree_mc->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_mc >= 10) &&  (e % (n_entries_mc/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_mc/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_mc, _BDTTool, Utility::kMC, Utility::kRun2a);
		    if (!passSelection) continue;

		    // select which events to remove, needs to match taken from from nue overlay mc
		    if (((_event_mc.classification == Utility::kCCNue1piXp || _event_mc.classification == Utility::kCCNueNpi || _event_mc.classification == Utility::kCCNuepizero ||
    				_event_mc.classification == Utility::kCCNueNp || _event_mc.classification == Utility::kCCNueOther))) continue;

		    // fill histogram
		    _histStack.Fill(_event_mc.classification, _event_mc.BDTScoreElectronPhoton, pot_weight_mc_run2a_fhc * _event_mc.weight_cv);

		    //if (_event_mc.primaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.primaryTrackBDTScorePionProton, pot_weight_mc_run2a_fhc * _event_mc.weight_cv);
	        //else if (_event_mc.secondaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.secondaryTrackBDTScorePionProton, pot_weight_mc_run2a_fhc * _event_mc.weight_cv);
	  	    //else _histStack.Fill(_event_mc.classification, _event_mc.tertiaryTrackBDTScorePionProton, pot_weight_mc_run2a_fhc * _event_mc.weight_cv);	
		}

		delete f_mc;
		

		// --- Dirt Overlay MC ---
		// read file
		TFile *f_dirt = NULL;
	  	TTree *tree_dirt = NULL;
	 	f_dirt = new TFile(filename_dirt_run2a_fhc.c_str());  
	  	tree_dirt = (TTree*)f_dirt->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_dirt(tree_dirt, _utility); 	

	  	// loop through events
	  	int n_entries_dirt = tree_dirt->GetEntries();
	  	std::cout << "Initial number events [Run 2a FHC Dirt Overlay]: " << n_entries_dirt << std::endl;

	  	for (int e = 0; e < n_entries_dirt; e++) {

	    	tree_dirt->GetEntry(e);

		    if ( (e != 0) && (n_entries_dirt >= 10) &&  (e % (n_entries_dirt/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_dirt/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_dirt, _BDTTool, Utility::kDirt, Utility::kRun2a);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_dirt.classification, _event_dirt.BDTScoreElectronPhoton, pot_weight_dirt_run2a_fhc * _event_dirt.weight_cv); 

		    //if (_event_dirt.primaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.primaryTrackBDTScorePionProton, pot_weight_dirt_run2a_fhc * _event_dirt.weight_cv);
	        //else if (_event_dirt.secondaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.secondaryTrackBDTScorePionProton, pot_weight_dirt_run2a_fhc * _event_dirt.weight_cv);
	  	    //else _histStack.Fill(_event_dirt.classification, _event_dirt.tertiaryTrackBDTScorePionProton, pot_weight_dirt_run2a_fhc * _event_dirt.weight_cv); 
		}

		delete f_dirt;

		// --- Beam Off ---
		// read file
		TFile *f_beamoff = NULL;
	  	TTree *tree_beamoff = NULL;
	 	f_beamoff = new TFile(filename_beamoff_run2a_fhc.c_str());  
	  	tree_beamoff = (TTree*)f_beamoff->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_beamoff(tree_beamoff, _utility); 	

	  	// loop through events
	  	int n_entries_beamoff = tree_beamoff->GetEntries();
	  	std::cout << "Initial number events [Run 2a FHC Beam Off]: " << n_entries_beamoff << std::endl;

	  	for (int e = 0; e < n_entries_beamoff; e++) {

	    	tree_beamoff->GetEntry(e);

		    if ( (e != 0) && (n_entries_beamoff >= 10) &&  (e % (n_entries_beamoff/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_beamoff/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_beamoff, _BDTTool, Utility::kEXT, Utility::kRun2a);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_beamoff.classification, _event_beamoff.BDTScoreElectronPhoton, pot_weight_beamoff_run2a_fhc * _event_beamoff.weight_cv);

		    //if (_event_beamoff.primaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.primaryTrackBDTScorePionProton, pot_weight_beamoff_run2a_fhc * _event_beamoff.weight_cv);
	        //else if (_event_beamoff.secondaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.secondaryTrackBDTScorePionProton, pot_weight_beamoff_run2a_fhc * _event_beamoff.weight_cv);
	  	    //else _histStack.Fill(_event_beamoff.classification, _event_beamoff.tertiaryTrackBDTScorePionProton, pot_weight_beamoff_run2a_fhc * _event_beamoff.weight_cv);
		}

		delete f_beamoff;
	}
	
	
	// ----------------- Run 4 FHC ------------------
	{
		// --- Nue Overlay MC ---
		// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_test_run4_fhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 4 FHC Intrinsic Nue Overlay Test]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_intrinsic, _BDTTool, Utility::kIntrinsic, Utility::kRun4cd);
		    if (!passSelection) continue;

		    // select which events to keep, needs to match those removed from nu overlay mc
		    if (!((_event_intrinsic.classification == Utility::kCCNue1piXp || _event_intrinsic.classification == Utility::kCCNueNpi || _event_intrinsic.classification == Utility::kCCNuepizero ||
    				_event_intrinsic.classification == Utility::kCCNueNp || _event_intrinsic.classification == Utility::kCCNueOther))) continue;

		    // fill histogram
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.BDTScoreElectronPhoton, pot_weight_intrinsic_test_run4_fhc * _event_intrinsic.weight_cv);

		    //if (_event_intrinsic.primaryTrackPionlikeLoose) _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.primaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run4_fhc * _event_intrinsic.weight_cv);
	        //else if (_event_intrinsic.secondaryTrackPionlikeLoose) _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.secondaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run4_fhc * _event_intrinsic.weight_cv);
	  	    //else _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.tertiaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run4_fhc * _event_intrinsic.weight_cv);
		
		}

		delete f_intrinsic;

		
		// --- Nu Overlay MC ---	
		// read file
		TFile *f_mc = NULL;
	  	TTree *tree_mc = NULL;
	 	f_mc = new TFile(filename_mc_run4_fhc.c_str());  
	  	tree_mc = (TTree*)f_mc->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_mc(tree_mc, _utility); 	

	  	// loop through events
	  	int n_entries_mc = tree_mc->GetEntries();
	  	std::cout << "Initial number events [Run 4 FHC Nu Overlay]: " << n_entries_mc << std::endl;

	  	for (int e = 0; e < n_entries_mc; e++) {
	  		
	    	tree_mc->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_mc >= 10) &&  (e % (n_entries_mc/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_mc/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_mc, _BDTTool, Utility::kMC, Utility::kRun4cd);
		    if (!passSelection) continue;

		    // select which events to remove, needs to match taken from from nue overlay mc
		    if (((_event_mc.classification == Utility::kCCNue1piXp || _event_mc.classification == Utility::kCCNueNpi || _event_mc.classification == Utility::kCCNuepizero ||
    				_event_mc.classification == Utility::kCCNueNp || _event_mc.classification == Utility::kCCNueOther))) continue;

		    // fill histogram
		    _histStack.Fill(_event_mc.classification, _event_mc.BDTScoreElectronPhoton, pot_weight_mc_run4_fhc * _event_mc.weight_cv);

		    //if (_event_mc.primaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.primaryTrackBDTScorePionProton, pot_weight_mc_run4_fhc * _event_mc.weight_cv);
	        //else if (_event_mc.secondaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.secondaryTrackBDTScorePionProton, pot_weight_mc_run4_fhc * _event_mc.weight_cv);
	  	    //else _histStack.Fill(_event_mc.classification, _event_mc.tertiaryTrackBDTScorePionProton, pot_weight_mc_run4_fhc * _event_mc.weight_cv);

		}

		delete f_mc;
		

		// --- Dirt Overlay MC ---
		// read file
		TFile *f_dirt = NULL;
	  	TTree *tree_dirt = NULL;
	 	f_dirt = new TFile(filename_dirt_run4_fhc.c_str());  
	  	tree_dirt = (TTree*)f_dirt->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_dirt(tree_dirt, _utility); 	

	  	// loop through events
	  	int n_entries_dirt = tree_dirt->GetEntries();
	  	std::cout << "Initial number events [Run 4 FHC Dirt Overlay]: " << n_entries_dirt << std::endl;

	  	for (int e = 0; e < n_entries_dirt; e++) {

	    	tree_dirt->GetEntry(e);

		    if ( (e != 0) && (n_entries_dirt >= 10) &&  (e % (n_entries_dirt/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_dirt/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_dirt, _BDTTool, Utility::kDirt, Utility::kRun4cd);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_dirt.classification, _event_dirt.BDTScoreElectronPhoton, pot_weight_dirt_run4_fhc * _event_dirt.weight_cv); 

		    //if (_event_dirt.primaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.primaryTrackBDTScorePionProton, pot_weight_dirt_run4_fhc * _event_dirt.weight_cv);
	        //else if (_event_dirt.secondaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.secondaryTrackBDTScorePionProton, pot_weight_dirt_run4_fhc * _event_dirt.weight_cv);
	  	    //else _histStack.Fill(_event_dirt.classification, _event_dirt.tertiaryTrackBDTScorePionProton, pot_weight_dirt_run4_fhc * _event_dirt.weight_cv);
		}

		delete f_dirt;
	
		// --- Beam Off ---
		// read file
		TFile *f_beamoff = NULL;
	  	TTree *tree_beamoff = NULL;
	 	f_beamoff = new TFile(filename_beamoff_run4_fhc.c_str());  
	  	tree_beamoff = (TTree*)f_beamoff->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_beamoff(tree_beamoff, _utility); 	

	  	// loop through events
	  	int n_entries_beamoff = tree_beamoff->GetEntries();
	  	std::cout << "Initial number events [Run 4 FHC Beam Off]: " << n_entries_beamoff << std::endl;

	  	for (int e = 0; e < n_entries_beamoff; e++) {

	    	tree_beamoff->GetEntry(e);

		    if ( (e != 0) && (n_entries_beamoff >= 10) &&  (e % (n_entries_beamoff/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_beamoff/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_beamoff, _BDTTool, Utility::kEXT, Utility::kRun4cd);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_beamoff.classification, _event_beamoff.BDTScoreElectronPhoton, pot_weight_beamoff_run4_fhc * _event_beamoff.weight_cv);

		    //if (_event_beamoff.primaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.primaryTrackBDTScorePionProton, pot_weight_beamoff_run4_fhc * _event_beamoff.weight_cv);
	        //else if (_event_beamoff.secondaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.secondaryTrackBDTScorePionProton, pot_weight_beamoff_run4_fhc * _event_beamoff.weight_cv);
	  	    //else _histStack.Fill(_event_beamoff.classification, _event_beamoff.tertiaryTrackBDTScorePionProton, pot_weight_beamoff_run4_fhc * _event_beamoff.weight_cv);
		}

		delete f_beamoff;
	}
	
	
	// ----------------- Run 5 FHC ------------------
	{
		// --- Nue Overlay MC ---
		// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_test_run5_fhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 5 FHC Intrinsic Nue Overlay Test]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_intrinsic, _BDTTool, Utility::kIntrinsic, Utility::kRun5);
		    if (!passSelection) continue;

		    // select which events to keep, needs to match those removed from nu overlay mc
		    if (!((_event_intrinsic.classification == Utility::kCCNue1piXp || _event_intrinsic.classification == Utility::kCCNueNpi || _event_intrinsic.classification == Utility::kCCNuepizero ||
    				_event_intrinsic.classification == Utility::kCCNueNp || _event_intrinsic.classification == Utility::kCCNueOther))) continue;

		    // fill histogram
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.BDTScoreElectronPhoton, pot_weight_intrinsic_test_run5_fhc * _event_intrinsic.weight_cv);

		    //if (_event_intrinsic.primaryTrackPionlikeLoose) _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.primaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run5_fhc * _event_intrinsic.weight_cv);
	        //else if (_event_intrinsic.secondaryTrackPionlikeLoose) _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.secondaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run5_fhc * _event_intrinsic.weight_cv);
	  	    //else _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.tertiaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run5_fhc * _event_intrinsic.weight_cv);	
		
		}

		delete f_intrinsic;

		
		// --- Nu Overlay MC ---	
		// read file
		TFile *f_mc = NULL;
	  	TTree *tree_mc = NULL;
	 	f_mc = new TFile(filename_mc_run5_fhc.c_str());  
	  	tree_mc = (TTree*)f_mc->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_mc(tree_mc, _utility); 	

	  	// loop through events
	  	int n_entries_mc = tree_mc->GetEntries();
	  	std::cout << "Initial number events [Run 5 FHC Nu Overlay]: " << n_entries_mc << std::endl;

	  	for (int e = 0; e < n_entries_mc; e++) {
	  		
	    	tree_mc->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_mc >= 10) &&  (e % (n_entries_mc/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_mc/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_mc, _BDTTool, Utility::kMC, Utility::kRun5);
		    if (!passSelection) continue;

		    // select which events to remove, needs to match taken from from nue overlay mc
		    if (((_event_mc.classification == Utility::kCCNue1piXp || _event_mc.classification == Utility::kCCNueNpi || _event_mc.classification == Utility::kCCNuepizero ||
    				_event_mc.classification == Utility::kCCNueNp || _event_mc.classification == Utility::kCCNueOther))) continue;

		    // fill histogram
		    _histStack.Fill(_event_mc.classification, _event_mc.BDTScoreElectronPhoton, pot_weight_mc_run5_fhc * _event_mc.weight_cv);

		    //if (_event_mc.primaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.primaryTrackBDTScorePionProton, pot_weight_mc_run5_fhc * _event_mc.weight_cv);
	        //else if (_event_mc.secondaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.secondaryTrackBDTScorePionProton, pot_weight_mc_run5_fhc * _event_mc.weight_cv);
	  	    //else _histStack.Fill(_event_mc.classification, _event_mc.tertiaryTrackBDTScorePionProton, pot_weight_mc_run5_fhc * _event_mc.weight_cv);

		}

		delete f_mc;
		

		// --- Dirt Overlay MC ---
		// read file
		TFile *f_dirt = NULL;
	  	TTree *tree_dirt = NULL;
	 	f_dirt = new TFile(filename_dirt_run5_fhc.c_str());  
	  	tree_dirt = (TTree*)f_dirt->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_dirt(tree_dirt, _utility); 	

	  	// loop through events
	  	int n_entries_dirt = tree_dirt->GetEntries();
	  	std::cout << "Initial number events [Run 5 FHC Dirt Overlay]: " << n_entries_dirt << std::endl;

	  	for (int e = 0; e < n_entries_dirt; e++) {

	    	tree_dirt->GetEntry(e);

		    if ( (e != 0) && (n_entries_dirt >= 10) &&  (e % (n_entries_dirt/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_dirt/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_dirt, _BDTTool, Utility::kDirt, Utility::kRun5);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_dirt.classification, _event_dirt.BDTScoreElectronPhoton, pot_weight_dirt_run5_fhc * _event_dirt.weight_cv);

		    //if (_event_dirt.primaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.primaryTrackBDTScorePionProton, pot_weight_dirt_run5_fhc * _event_dirt.weight_cv);
	        //else if (_event_dirt.secondaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.secondaryTrackBDTScorePionProton, pot_weight_dirt_run5_fhc * _event_dirt.weight_cv);
	  	    //else _histStack.Fill(_event_dirt.classification, _event_dirt.tertiaryTrackBDTScorePionProton, pot_weight_dirt_run5_fhc * _event_dirt.weight_cv); 
		}

		delete f_dirt;

		// --- Beam Off --
		// read file
		TFile *f_beamoff = NULL;
	  	TTree *tree_beamoff = NULL;
	 	f_beamoff = new TFile(filename_beamoff_run5_fhc.c_str());  
	  	tree_beamoff = (TTree*)f_beamoff->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_beamoff(tree_beamoff, _utility); 	

	  	// loop through events
	  	int n_entries_beamoff = tree_beamoff->GetEntries();
	  	std::cout << "Initial number events [Run 5 FHC Beam Off]: " << n_entries_beamoff << std::endl;

	  	for (int e = 0; e < n_entries_beamoff; e++) {

	    	tree_beamoff->GetEntry(e);

		    if ( (e != 0) && (n_entries_beamoff >= 10) &&  (e % (n_entries_beamoff/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_beamoff/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_beamoff, _BDTTool, Utility::kEXT, Utility::kRun5);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_beamoff.classification, _event_beamoff.BDTScoreElectronPhoton, pot_weight_beamoff_run5_fhc * _event_beamoff.weight_cv);

		    //if (_event_beamoff.primaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.primaryTrackBDTScorePionProton, pot_weight_beamoff_run5_fhc * _event_beamoff.weight_cv);
	        //else if (_event_beamoff.secondaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.secondaryTrackBDTScorePionProton, pot_weight_beamoff_run5_fhc * _event_beamoff.weight_cv);
	  	    //else _histStack.Fill(_event_beamoff.classification, _event_beamoff.tertiaryTrackBDTScorePionProton, pot_weight_beamoff_run5_fhc * _event_beamoff.weight_cv);
		}

		delete f_beamoff;
	}

	// print event integrals
	_histStack.PrintEventIntegrals();

	TCanvas *canv = new TCanvas("canv", "canv", 1080, 1080);
  	//_histStack.DrawStack(canv, Utility::kElectronNeutralPionBDT);
  	//canv->Print("plot_electronPhoton_BDTScore_FHC.root");

  	//_histStack.DrawStack(canv, Utility::kPionProtonBDT);
  	//canv->Print("plot_pionProton_BDTScore_FHC.root");

  	_histStack.DrawStack(canv, Utility::kFHC);
  	canv->Print("plot_FHC.root");
}

// ------------------------------------------------------------------------------

// Run BDT selection on RHC samples
void SelectionDriver::runBDTSelectionRHC() {

	//StackedHistTool _histStack("", "", 20, 0, 1.001, _utility);
	//StackedHistTool _histStack("", "", 20, 0, 20, _utility);
	//StackedHistTool _histStack("", "", 20, 0, 100, _utility);
	StackedHistTool _histStack("", "", 3, -1, 2, _utility);
	BDTTool _BDTTool(true, true, true, true,  _utility);
	Selection _selection(_utility);

	/*
	// ----------------- Run 1 RHC ------------------
	{
		// --- Nue Overlay MC ---
		// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_test_run1_rhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 1 RHC Intrinsic Nue Overlay Test]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_intrinsic, _BDTTool, Utility::kIntrinsic, Utility::kRun1b);
		    if (!passSelection) continue;

		    // select which events to keep, needs to match those removed from nu overlay mc
		    if (!((_event_intrinsic.classification == Utility::kCCNue1piXp || _event_intrinsic.classification == Utility::kCCNueNpi || _event_intrinsic.classification == Utility::kCCNuepizero ||
    				_event_intrinsic.classification == Utility::kCCNueNp || _event_intrinsic.classification == Utility::kCCNueOther))) continue;

		    // fill histogram
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.BDTScoreElectronPhoton, pot_weight_intrinsic_test_run1_rhc * _event_intrinsic.weight_cv);

		    //if (_event_intrinsic.primaryTrackPionlikeLoose) _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.primaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run1_rhc * _event_intrinsic.weight_cv);
	        //else if (_event_intrinsic.secondaryTrackPionlikeLoose) _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.secondaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run1_rhc * _event_intrinsic.weight_cv);
	  	    //else _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.tertiaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run1_rhc * _event_intrinsic.weight_cv);	
		
		}

		delete f_intrinsic;

		// --- Nu Overlay MC ---	
		// read file
		TFile *f_mc = NULL;
	  	TTree *tree_mc = NULL;
	 	f_mc = new TFile(filename_mc_run1_rhc.c_str());  
	  	tree_mc = (TTree*)f_mc->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_mc(tree_mc, _utility); 	

	  	// loop through events
	  	int n_entries_mc = tree_mc->GetEntries();
	  	std::cout << "Initial number events [Run 1 RHC Nu Overlay]: " << n_entries_mc << std::endl;

	  	for (int e = 0; e < n_entries_mc; e++) {
	  		
	    	tree_mc->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_mc >= 10) &&  (e % (n_entries_mc/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_mc/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_mc, _BDTTool, Utility::kMC, Utility::kRun1b);
		    if (!passSelection) continue;

		    // select which events to remove, needs to match taken from from nue overlay mc
		    if (((_event_mc.classification == Utility::kCCNue1piXp || _event_mc.classification == Utility::kCCNueNpi || _event_mc.classification == Utility::kCCNuepizero ||
    				_event_mc.classification == Utility::kCCNueNp || _event_mc.classification == Utility::kCCNueOther))) continue;

		    // fill histogram
		    _histStack.Fill(_event_mc.classification, _event_mc.BDTScoreElectronPhoton, pot_weight_mc_run1_rhc * _event_mc.weight_cv);

		    //if (_event_mc.primaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.primaryTrackBDTScorePionProton, pot_weight_mc_run1_rhc * _event_mc.weight_cv);
	        //else if (_event_mc.secondaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.secondaryTrackBDTScorePionProton, pot_weight_mc_run1_rhc * _event_mc.weight_cv);
	  	    //else if (_event_mc.tertiaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.tertiaryTrackBDTScorePionProton, pot_weight_mc_run1_rhc * _event_mc.weight_cv);
	  	    //else std::cout << "HERE" << std::endl;	

		}

		delete f_mc;
		
	    
	    
		// --- Dirt Overlay MC ---
		// read file
		TFile *f_dirt = NULL;
	  	TTree *tree_dirt = NULL;
	 	f_dirt = new TFile(filename_dirt_run1_rhc.c_str());  
	  	tree_dirt = (TTree*)f_dirt->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_dirt(tree_dirt, _utility); 	

	  	// loop through events
	  	int n_entries_dirt = tree_dirt->GetEntries();
	  	std::cout << "Initial number events [Run 1 RHC Dirt Overlay]: " << n_entries_dirt << std::endl;

	  	for (int e = 0; e < n_entries_dirt; e++) {

	    	tree_dirt->GetEntry(e);

		    if ( (e != 0) && (n_entries_dirt >= 10) &&  (e % (n_entries_dirt/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_dirt/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_dirt, _BDTTool, Utility::kDirt, Utility::kRun1b);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_dirt.classification, _event_dirt.BDTScoreElectronPhoton, pot_weight_dirt_run1_rhc * _event_dirt.weight_cv);

		    //if (_event_dirt.primaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.primaryTrackBDTScorePionProton, pot_weight_dirt_run1_rhc * _event_dirt.weight_cv);
	        //else if (_event_dirt.secondaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.secondaryTrackBDTScorePionProton, pot_weight_dirt_run1_rhc * _event_dirt.weight_cv);
	  	    //else _histStack.Fill(_event_dirt.classification, _event_dirt.tertiaryTrackBDTScorePionProton, pot_weight_dirt_run1_rhc * _event_dirt.weight_cv); 
		}

		delete f_dirt;
		

		// --- Beam Off ---
		// read file
		TFile *f_beamoff = NULL;
	  	TTree *tree_beamoff = NULL;
	 	f_beamoff = new TFile(filename_beamoff_run1_rhc.c_str());  
	  	tree_beamoff = (TTree*)f_beamoff->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_beamoff(tree_beamoff, _utility); 	

	  	// loop through events
	  	int n_entries_beamoff = tree_beamoff->GetEntries();
	  	std::cout << "Initial number events [Run 1 RHC Beam Off]: " << n_entries_beamoff << std::endl;

	  	for (int e = 0; e < n_entries_beamoff; e++) {

	    	tree_beamoff->GetEntry(e);

		    if ( (e != 0) && (n_entries_beamoff >= 10) &&  (e % (n_entries_beamoff/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_beamoff/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_beamoff, _BDTTool, Utility::kEXT, Utility::kRun1b);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_beamoff.classification, _event_beamoff.BDTScoreElectronPhoton, pot_weight_beamoff_run1_rhc * _event_beamoff.weight_cv);

		    //if (_event_beamoff.primaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.primaryTrackBDTScorePionProton, pot_weight_beamoff_run1_rhc * _event_beamoff.weight_cv);
	        //else if (_event_beamoff.secondaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.secondaryTrackBDTScorePionProton, pot_weight_beamoff_run1_rhc * _event_beamoff.weight_cv);
	  	    //else _histStack.Fill(_event_beamoff.classification, _event_beamoff.tertiaryTrackBDTScorePionProton, pot_weight_beamoff_run1_rhc * _event_beamoff.weight_cv);
		}
		

		delete f_beamoff;
		
	}
	*/

	/*
	// ----------------- Run 2b RHC ------------------
	{
		// --- Nue Overlay MC ---
		// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_test_run2b_rhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 2b RHC Intrinsic Nue Overlay Test]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_intrinsic, _BDTTool, Utility::kIntrinsic, Utility::kRun2b);
		    if (!passSelection) continue;

		    // select which events to keep, needs to match those removed from nu overlay mc
		    if (!((_event_intrinsic.classification == Utility::kCCNue1piXp || _event_intrinsic.classification == Utility::kCCNueNpi || _event_intrinsic.classification == Utility::kCCNuepizero ||
    				_event_intrinsic.classification == Utility::kCCNueNp || _event_intrinsic.classification == Utility::kCCNueOther))) continue;

		    // fill histogram
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.BDTScoreElectronPhoton, pot_weight_intrinsic_test_run2b_rhc * _event_intrinsic.weight_cv);

		    //if (_event_intrinsic.primaryTrackPionlikeLoose) _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.primaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run2b_rhc * _event_intrinsic.weight_cv);
	        //else if (_event_intrinsic.secondaryTrackPionlikeLoose) _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.secondaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run2b_rhc * _event_intrinsic.weight_cv);
	  	    //else _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.tertiaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run2b_rhc * _event_intrinsic.weight_cv);	
		
		}

		delete f_intrinsic;

		// --- Nu Overlay MC ---	
		// read file
		TFile *f_mc = NULL;
	  	TTree *tree_mc = NULL;
	 	f_mc = new TFile(filename_mc_run2b_rhc.c_str());  
	  	tree_mc = (TTree*)f_mc->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_mc(tree_mc, _utility); 	

	  	// loop through events
	  	int n_entries_mc = tree_mc->GetEntries();
	  	std::cout << "Initial number events [Run 2b RHC Nu Overlay]: " << n_entries_mc << std::endl;

	  	for (int e = 0; e < n_entries_mc; e++) {
	  		
	    	tree_mc->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_mc >= 10) &&  (e % (n_entries_mc/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_mc/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_mc, _BDTTool, Utility::kMC, Utility::kRun2b);
		    if (!passSelection) continue;

		    // select which events to remove, needs to match taken from from nue overlay mc
		    if (((_event_mc.classification == Utility::kCCNue1piXp || _event_mc.classification == Utility::kCCNueNpi || _event_mc.classification == Utility::kCCNuepizero ||
    				_event_mc.classification == Utility::kCCNueNp || _event_mc.classification == Utility::kCCNueOther))) continue;

		    // fill histogram
		    _histStack.Fill(_event_mc.classification, _event_mc.BDTScoreElectronPhoton, pot_weight_mc_run2b_rhc * _event_mc.weight_cv);

		    //if (_event_mc.primaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.primaryTrackBDTScorePionProton, pot_weight_mc_run2b_rhc * _event_mc.weight_cv);
	        //else if (_event_mc.secondaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.secondaryTrackBDTScorePionProton, pot_weight_mc_run2b_rhc * _event_mc.weight_cv);
	  	    //else _histStack.Fill(_event_mc.classification, _event_mc.tertiaryTrackBDTScorePionProton, pot_weight_mc_run2b_rhc * _event_mc.weight_cv);

		}

		delete f_mc;

		
		// --- Dirt Overlay MC ---
		// read file
		TFile *f_dirt = NULL;
	  	TTree *tree_dirt = NULL;
	 	f_dirt = new TFile(filename_dirt_run2b_rhc.c_str());  
	  	tree_dirt = (TTree*)f_dirt->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_dirt(tree_dirt, _utility); 	

	  	// loop through events
	  	int n_entries_dirt = tree_dirt->GetEntries();
	  	std::cout << "Initial number events [Run 2b RHC Dirt Overlay]: " << n_entries_dirt << std::endl;

	  	for (int e = 0; e < n_entries_dirt; e++) {

	    	tree_dirt->GetEntry(e);

		    if ( (e != 0) && (n_entries_dirt >= 10) &&  (e % (n_entries_dirt/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_dirt/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_dirt, _BDTTool, Utility::kDirt, Utility::kRun2b);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_dirt.classification, _event_dirt.BDTScoreElectronPhoton, pot_weight_dirt_run2b_rhc * _event_dirt.weight_cv);

		    //if (_event_dirt.primaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.primaryTrackBDTScorePionProton, pot_weight_dirt_run2b_rhc * _event_dirt.weight_cv);
	        //else if (_event_dirt.secondaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.secondaryTrackBDTScorePionProton, pot_weight_dirt_run2b_rhc * _event_dirt.weight_cv);
	  	    //else _histStack.Fill(_event_dirt.classification, _event_dirt.tertiaryTrackBDTScorePionProton, pot_weight_dirt_run2b_rhc * _event_dirt.weight_cv); 
		}

		delete f_dirt;

		// --- Beam Off ---
		// read file
		TFile *f_beamoff = NULL;
	  	TTree *tree_beamoff = NULL;
	 	f_beamoff = new TFile(filename_beamoff_run2b_rhc.c_str());  
	  	tree_beamoff = (TTree*)f_beamoff->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_beamoff(tree_beamoff, _utility); 	

	  	// loop through events
	  	int n_entries_beamoff = tree_beamoff->GetEntries();
	  	std::cout << "Initial number events [Run 2b RHC Beam Off]: " << n_entries_beamoff << std::endl;

	  	for (int e = 0; e < n_entries_beamoff; e++) {

	    	tree_beamoff->GetEntry(e);

		    if ( (e != 0) && (n_entries_beamoff >= 10) &&  (e % (n_entries_beamoff/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_beamoff/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_beamoff, _BDTTool, Utility::kEXT, Utility::kRun2b);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_beamoff.classification, _event_beamoff.BDTScoreElectronPhoton, pot_weight_beamoff_run2b_rhc * _event_beamoff.weight_cv);

		    //if (_event_beamoff.primaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.primaryTrackBDTScorePionProton, pot_weight_beamoff_run2b_rhc * _event_beamoff.weight_cv);
	        //else if (_event_beamoff.secondaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.secondaryTrackBDTScorePionProton, pot_weight_beamoff_run2b_rhc * _event_beamoff.weight_cv);
	  	    //else _histStack.Fill(_event_beamoff.classification, _event_beamoff.tertiaryTrackBDTScorePionProton, pot_weight_beamoff_run2b_rhc * _event_beamoff.weight_cv);
		}

		delete f_beamoff;
		
	}
	*/
	
	/*
	// ----------------- Run 3b RHC ------------------
	{
		// --- Nue Overlay MC ---
		// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_test_run3b_rhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 3b RHC Intrinsic Nue Overlay Test]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_intrinsic, _BDTTool, Utility::kIntrinsic, Utility::kRun3b);
		    if (!passSelection) continue;

		    // select which events to keep, needs to match those removed from nu overlay mc
		    if (!((_event_intrinsic.classification == Utility::kCCNue1piXp || _event_intrinsic.classification == Utility::kCCNueNpi || _event_intrinsic.classification == Utility::kCCNuepizero ||
    				_event_intrinsic.classification == Utility::kCCNueNp || _event_intrinsic.classification == Utility::kCCNueOther))) continue;

		    // fill histogram
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.BDTScoreElectronPhoton, pot_weight_intrinsic_test_run3b_rhc * _event_intrinsic.weight_cv);

		    //if (_event_intrinsic.primaryTrackPionlikeLoose) _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.primaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run3b_rhc * _event_intrinsic.weight_cv);
	        //else if (_event_intrinsic.secondaryTrackPionlikeLoose) _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.secondaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run3b_rhc * _event_intrinsic.weight_cv);
	  	    //else _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.tertiaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run3b_rhc * _event_intrinsic.weight_cv);
		
		}

		delete f_intrinsic;

		// --- Nu Overlay MC ---	
		// read file
		TFile *f_mc = NULL;
	  	TTree *tree_mc = NULL;
	 	f_mc = new TFile(filename_mc_run3b_rhc.c_str());  
	  	tree_mc = (TTree*)f_mc->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_mc(tree_mc, _utility); 	

	  	// loop through events
	  	int n_entries_mc = tree_mc->GetEntries();
	  	std::cout << "Initial number events [Run 3b RHC Nu Overlay]: " << n_entries_mc << std::endl;

	  	for (int e = 0; e < n_entries_mc; e++) {
	  		
	    	tree_mc->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_mc >= 10) &&  (e % (n_entries_mc/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_mc/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_mc, _BDTTool, Utility::kMC, Utility::kRun3b);
		    if (!passSelection) continue;

		    // select which events to remove, needs to match taken from from nue overlay mc
		    if (((_event_mc.classification == Utility::kCCNue1piXp || _event_mc.classification == Utility::kCCNueNpi || _event_mc.classification == Utility::kCCNuepizero ||
    				_event_mc.classification == Utility::kCCNueNp || _event_mc.classification == Utility::kCCNueOther))) continue;

		    // fill histogram
		    _histStack.Fill(_event_mc.classification, _event_mc.BDTScoreElectronPhoton, pot_weight_mc_run3b_rhc * _event_mc.weight_cv);

		    //if (_event_mc.primaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.primaryTrackBDTScorePionProton, pot_weight_mc_run3b_rhc * _event_mc.weight_cv);
	        //else if (_event_mc.secondaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.secondaryTrackBDTScorePionProton, pot_weight_mc_run3b_rhc * _event_mc.weight_cv);
	  	    //else _histStack.Fill(_event_mc.classification, _event_mc.tertiaryTrackBDTScorePionProton, pot_weight_mc_run3b_rhc * _event_mc.weight_cv);

		}

		delete f_mc;
		
		// --- Dirt Overlay MC ---
		// read file
		TFile *f_dirt = NULL;
	  	TTree *tree_dirt = NULL;
	 	f_dirt = new TFile(filename_dirt_run3b_rhc.c_str());  
	  	tree_dirt = (TTree*)f_dirt->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_dirt(tree_dirt, _utility); 	

	  	// loop through events
	  	int n_entries_dirt = tree_dirt->GetEntries();
	  	std::cout << "Initial number events [Run 3b RHC Dirt Overlay]: " << n_entries_dirt << std::endl;

	  	for (int e = 0; e < n_entries_dirt; e++) {

	    	tree_dirt->GetEntry(e);

		    if ( (e != 0) && (n_entries_dirt >= 10) &&  (e % (n_entries_dirt/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_dirt/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_dirt, _BDTTool, Utility::kDirt, Utility::kRun3b);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_dirt.classification, _event_dirt.BDTScoreElectronPhoton, pot_weight_dirt_run3b_rhc * _event_dirt.weight_cv);

		    //if (_event_dirt.primaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.primaryTrackBDTScorePionProton, pot_weight_dirt_run3b_rhc * _event_dirt.weight_cv);
	        //else if (_event_dirt.secondaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.secondaryTrackBDTScorePionProton, pot_weight_dirt_run3b_rhc * _event_dirt.weight_cv);
	  	    //else _histStack.Fill(_event_dirt.classification, _event_dirt.tertiaryTrackBDTScorePionProton, pot_weight_dirt_run3b_rhc * _event_dirt.weight_cv);  
		}

		delete f_dirt;

		// --- Beam Off ---
		// read file
		TFile *f_beamoff = NULL;
	  	TTree *tree_beamoff = NULL;
	 	f_beamoff = new TFile(filename_beamoff_run3b_rhc.c_str());  
	  	tree_beamoff = (TTree*)f_beamoff->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_beamoff(tree_beamoff, _utility); 	

	  	// loop through events
	  	int n_entries_beamoff = tree_beamoff->GetEntries();
	  	std::cout << "Initial number events [Run 3b RHC Beam Off]: " << n_entries_beamoff << std::endl;

	  	for (int e = 0; e < n_entries_beamoff; e++) {

	    	tree_beamoff->GetEntry(e);

		    if ( (e != 0) && (n_entries_beamoff >= 10) &&  (e % (n_entries_beamoff/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_beamoff/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_beamoff, _BDTTool, Utility::kEXT, Utility::kRun3b);
		    if (!passSelection) continue;

		    // get correct normalisation depending on trigger threshold
		    double pot_weight_beamoff_run3b_rhc;
		    if (_event_beamoff.run < 16880) pot_weight_beamoff_run3b_rhc = pot_weight_beamoff_run3b_rhc_pre;
		    else pot_weight_beamoff_run3b_rhc = pot_weight_beamoff_run3b_rhc_post;
		    
		    // fill histogram
		    _histStack.Fill(_event_beamoff.classification, _event_beamoff.BDTScoreElectronPhoton, pot_weight_beamoff_run3b_rhc * _event_beamoff.weight_cv);

		    //if (_event_beamoff.primaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.primaryTrackBDTScorePionProton, pot_weight_beamoff_run3b_rhc * _event_beamoff.weight_cv);
	        //else if (_event_beamoff.secondaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.secondaryTrackBDTScorePionProton, pot_weight_beamoff_run3b_rhc * _event_beamoff.weight_cv);
	  	    //else _histStack.Fill(_event_beamoff.classification, _event_beamoff.tertiaryTrackBDTScorePionProton, pot_weight_beamoff_run3b_rhc * _event_beamoff.weight_cv);
		}

		delete f_beamoff;

	}
	*/

	
	// ----------------- Run 4 RHC ------------------
	{
		// --- Nue Overlay MC ---
		// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_test_run4_rhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 4 RHC Intrinsic Nue Overlay Test]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_intrinsic, _BDTTool, Utility::kIntrinsic, Utility::kRun4ab);
		    if (!passSelection) continue;

		    // select which events to keep, needs to match those removed from nu overlay mc
		    if (!((_event_intrinsic.classification == Utility::kCCNue1piXp || _event_intrinsic.classification == Utility::kCCNueNpi || _event_intrinsic.classification == Utility::kCCNuepizero ||
    				_event_intrinsic.classification == Utility::kCCNueNp || _event_intrinsic.classification == Utility::kCCNueOther))) continue;

		    // fill histogram
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.BDTScoreElectronPhoton, pot_weight_intrinsic_test_run4_rhc * _event_intrinsic.weight_cv);

		    //if (_event_intrinsic.primaryTrackPionlikeLoose) _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.primaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run4_rhc * _event_intrinsic.weight_cv);
	        //else if (_event_intrinsic.secondaryTrackPionlikeLoose) _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.secondaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run4_rhc * _event_intrinsic.weight_cv);
	  	    //else _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.tertiaryTrackBDTScorePionProton, pot_weight_intrinsic_test_run4_rhc * _event_intrinsic.weight_cv);
		
		}

		delete f_intrinsic;

		// --- Nu Overlay MC ---	
		// read file
		TFile *f_mc = NULL;
	  	TTree *tree_mc = NULL;
	 	f_mc = new TFile(filename_mc_run4_rhc.c_str());  
	  	tree_mc = (TTree*)f_mc->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_mc(tree_mc, _utility); 	

	  	// loop through events
	  	int n_entries_mc = tree_mc->GetEntries();
	  	std::cout << "Initial number events [Run 4 RHC Nu Overlay]: " << n_entries_mc << std::endl;

	  	for (int e = 0; e < n_entries_mc; e++) {
	  		
	    	tree_mc->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_mc >= 10) &&  (e % (n_entries_mc/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_mc/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_mc, _BDTTool, Utility::kMC, Utility::kRun4ab);
		    if (!passSelection) continue;

		    // select which events to remove, needs to match taken from from nue overlay mc
		    if (((_event_mc.classification == Utility::kCCNue1piXp || _event_mc.classification == Utility::kCCNueNpi || _event_mc.classification == Utility::kCCNuepizero ||
    				_event_mc.classification == Utility::kCCNueNp || _event_mc.classification == Utility::kCCNueOther))) continue;

		    // fill histogram
		    _histStack.Fill(_event_mc.classification, _event_mc.BDTScoreElectronPhoton, pot_weight_mc_run4_rhc * _event_mc.weight_cv);

		    //if (_event_mc.primaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.primaryTrackBDTScorePionProton, pot_weight_mc_run4_rhc * _event_mc.weight_cv);
	        //else if (_event_mc.secondaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.secondaryTrackBDTScorePionProton, pot_weight_mc_run4_rhc * _event_mc.weight_cv);
	  	    //else _histStack.Fill(_event_mc.classification, _event_mc.tertiaryTrackBDTScorePionProton, pot_weight_mc_run4_rhc * _event_mc.weight_cv);

		}

		delete f_mc;
		
		// --- Dirt Overlay MC ---
		// read file
		TFile *f_dirt = NULL;
	  	TTree *tree_dirt = NULL;
	 	f_dirt = new TFile(filename_dirt_run4_rhc.c_str());  
	  	tree_dirt = (TTree*)f_dirt->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_dirt(tree_dirt, _utility); 	

	  	// loop through events
	  	int n_entries_dirt = tree_dirt->GetEntries();
	  	std::cout << "Initial number events [Run 4 RHC Dirt Overlay]: " << n_entries_dirt << std::endl;

	  	for (int e = 0; e < n_entries_dirt; e++) {

	    	tree_dirt->GetEntry(e);

		    if ( (e != 0) && (n_entries_dirt >= 10) &&  (e % (n_entries_dirt/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_dirt/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_dirt, _BDTTool, Utility::kDirt, Utility::kRun4ab);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_dirt.classification, _event_dirt.BDTScoreElectronPhoton, pot_weight_dirt_run4_rhc * _event_dirt.weight_cv);

		    //if (_event_dirt.primaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.primaryTrackBDTScorePionProton, pot_weight_dirt_run4_rhc * _event_dirt.weight_cv);
	        //else if (_event_dirt.secondaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.secondaryTrackBDTScorePionProton, pot_weight_dirt_run4_rhc * _event_dirt.weight_cv);
	  	    //else _histStack.Fill(_event_dirt.classification, _event_dirt.tertiaryTrackBDTScorePionProton, pot_weight_dirt_run4_rhc * _event_dirt.weight_cv);  
		}

		delete f_dirt;

		// --- Beam Off ---
		// read file
		TFile *f_beamoff = NULL;
	  	TTree *tree_beamoff = NULL;
	 	f_beamoff = new TFile(filename_beamoff_run4_rhc.c_str());  
	  	tree_beamoff = (TTree*)f_beamoff->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_beamoff(tree_beamoff, _utility); 	

	  	// loop through events
	  	int n_entries_beamoff = tree_beamoff->GetEntries();
	  	std::cout << "Initial number events [Run 4 RHC Beam Off]: " << n_entries_beamoff << std::endl;

	  	for (int e = 0; e < n_entries_beamoff; e++) {

	    	tree_beamoff->GetEntry(e);

		    if ( (e != 0) && (n_entries_beamoff >= 10) &&  (e % (n_entries_beamoff/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_beamoff/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_beamoff, _BDTTool, Utility::kEXT, Utility::kRun4ab);
		    if (!passSelection) continue;
		    
		    // fill histogram
		    _histStack.Fill(_event_beamoff.classification, _event_beamoff.BDTScoreElectronPhoton, pot_weight_beamoff_run4_rhc * _event_beamoff.weight_cv);

		    //if (_event_beamoff.primaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.primaryTrackBDTScorePionProton, pot_weight_beamoff_run4_rhc * _event_beamoff.weight_cv);
	        //else if (_event_beamoff.secondaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.secondaryTrackBDTScorePionProton, pot_weight_beamoff_run4_rhc * _event_beamoff.weight_cv);
	  	    //else _histStack.Fill(_event_beamoff.classification, _event_beamoff.tertiaryTrackBDTScorePionProton, pot_weight_beamoff_run4_rhc * _event_beamoff.weight_cv);
		}

		delete f_beamoff;

	}
	
	
	// print event integrals
	_histStack.PrintEventIntegrals();

	TCanvas *canv = new TCanvas("canv", "canv", 1080, 1080);
  	_histStack.DrawStack(canv, Utility::kRHC);
  	canv->Print("plot_RHC.root");

  	//_histStack.DrawStack(canv, Utility::kElectronNeutralPionBDT);
  	//canv->Print("plot_electronPhoton_BDTScore_RHC.root");

  	//_histStack.DrawStack(canv, Utility::kPionProtonBDT);
  	//canv->Print("plot_pionProton_BDTScore_RHC.root");
}

// ------------------------------------------------------------------------------


// Run BDT selection on FHC detector variations
void SelectionDriver::runBDTSelectionDetVarFHC() {

	StackedHistTool _histStack_CV("", "", 1, 0, 10, _utility);
	StackedHistTool _histStack_SCE("", "", 1, 0, 10, _utility);
	StackedHistTool _histStack_Recombination("", "", 1, 0, 10, _utility);
	StackedHistTool _histStack_WireModX("", "", 1, 0, 10, _utility);
	StackedHistTool _histStack_WireModYZ("", "", 1, 0, 10, _utility);
	StackedHistTool _histStack_WireModThetaYZ("", "", 1, 0, 10, _utility);
	
	BDTTool _BDTTool(true, true, true, true,  _utility);
	Selection _selection(_utility);


	// ----------------- Run 1 FHC CV ------------------
	{
		// --- CV ---	
		// read file
		TFile *f_detvar = NULL;
	  	TTree *tree_detvar = NULL;
	 	f_detvar = new TFile(filename_detvar_CV_run1_fhc.c_str());  
	  	tree_detvar = (TTree*)f_detvar->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_detvar(tree_detvar, _utility); 	

	  	// loop through events
	  	int n_entries_detvar = tree_detvar->GetEntries();
	  	std::cout << "Initial number events [Run 1 FHC DetVar CV]: " << n_entries_detvar << std::endl;

	  	for (int e = 0; e < n_entries_detvar; e++) {
	  	//for (int e = 0; e < 10000; e++) {
	  		
	    	tree_detvar->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_detvar >= 10) &&  (e % (n_entries_detvar/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_detvar/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_detvar, _BDTTool, Utility::kDetVar, Utility::kRun1a);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack_CV.Fill(_event_detvar.classification, _event_detvar.shr2_pfpgeneration, pot_weight_detvar_CV_run1_fhc * _event_detvar.weight_cv);

		    //if (_event_mc.primaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.primaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
	        //else if (_event_mc.secondaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.secondaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
	  	    //else if (_event_mc.tertiaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.tertiaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
		}

		delete f_detvar;
	}

	/*
	// ----------------- Run 1 FHC SCE ------------------
	{
		// --- SCE ---	
		// read file
		TFile *f_detvar = NULL;
	  	TTree *tree_detvar = NULL;
	 	f_detvar = new TFile(filename_detvar_SCE_run1_fhc.c_str());  
	  	tree_detvar = (TTree*)f_detvar->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_detvar(tree_detvar, _utility); 	

	  	// loop through events
	  	int n_entries_detvar = tree_detvar->GetEntries();
	  	std::cout << "Initial number events [Run 1 FHC DetVar SCE]: " << n_entries_detvar << std::endl;

	  	for (int e = 0; e < n_entries_detvar; e++) {
	  	//for (int e = 0; e < 10000; e++) {
	  		
	    	tree_detvar->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_detvar >= 10) &&  (e % (n_entries_detvar/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_detvar/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_detvar, _BDTTool, Utility::kMC, Utility::kRun1a);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack_SCE.Fill(_event_detvar.classification, _event_detvar.shr2_pfpgeneration, pot_weight_detvar_SCE_run1_fhc * _event_detvar.weight_cv);

		    //if (_event_mc.primaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.primaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
	        //else if (_event_mc.secondaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.secondaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
	  	    //else if (_event_mc.tertiaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.tertiaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
		}

		delete f_detvar;
	}

	// ----------------- Run 1 FHC Recombination ------------------
	{
		// --- Recombination ---	
		// read file
		TFile *f_detvar = NULL;
	  	TTree *tree_detvar = NULL;
	 	f_detvar = new TFile(filename_detvar_Recombination_run1_fhc.c_str());  
	  	tree_detvar = (TTree*)f_detvar->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_detvar(tree_detvar, _utility); 	

	  	// loop through events
	  	int n_entries_detvar = tree_detvar->GetEntries();
	  	std::cout << "Initial number events [Run 1 FHC DetVar Recombination]: " << n_entries_detvar << std::endl;

	  	for (int e = 0; e < n_entries_detvar; e++) {
	  	//for (int e = 0; e < 10000; e++) {
	  		
	    	tree_detvar->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_detvar >= 10) &&  (e % (n_entries_detvar/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_detvar/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_detvar, _BDTTool, Utility::kMC, Utility::kRun1a);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack_Recombination.Fill(_event_detvar.classification, _event_detvar.shr2_pfpgeneration, pot_weight_detvar_Recombination_run1_fhc * _event_detvar.weight_cv);

		    //if (_event_mc.primaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.primaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
	        //else if (_event_mc.secondaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.secondaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
	  	    //else if (_event_mc.tertiaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.tertiaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
		}

		delete f_detvar;
	}

	// ----------------- Run 1 FHC WireModX ------------------
	{
		// --- WireModX ---	
		// read file
		TFile *f_detvar = NULL;
	  	TTree *tree_detvar = NULL;
	 	f_detvar = new TFile(filename_detvar_WireModX_run1_fhc.c_str());  
	  	tree_detvar = (TTree*)f_detvar->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_detvar(tree_detvar, _utility); 	

	  	// loop through events
	  	int n_entries_detvar = tree_detvar->GetEntries();
	  	std::cout << "Initial number events [Run 1 FHC DetVar WireModX]: " << n_entries_detvar << std::endl;

	  	for (int e = 0; e < n_entries_detvar; e++) {
	  	//for (int e = 0; e < 10000; e++) {
	  		
	    	tree_detvar->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_detvar >= 10) &&  (e % (n_entries_detvar/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_detvar/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_detvar, _BDTTool, Utility::kMC, Utility::kRun1a);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack_WireModX.Fill(_event_detvar.classification, _event_detvar.shr2_pfpgeneration, pot_weight_detvar_WireModX_run1_fhc * _event_detvar.weight_cv);

		    //if (_event_mc.primaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.primaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
	        //else if (_event_mc.secondaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.secondaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
	  	    //else if (_event_mc.tertiaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.tertiaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
		}

		delete f_detvar;
	}

	// ----------------- Run 1 FHC WireModYZ ------------------
	{
		// --- WireModYZ ---	
		// read file
		TFile *f_detvar = NULL;
	  	TTree *tree_detvar = NULL;
	 	f_detvar = new TFile(filename_detvar_WireModYZ_run1_fhc.c_str());  
	  	tree_detvar = (TTree*)f_detvar->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_detvar(tree_detvar, _utility); 	

	  	// loop through events
	  	int n_entries_detvar = tree_detvar->GetEntries();
	  	std::cout << "Initial number events [Run 1 FHC DetVar WireModYZ]: " << n_entries_detvar << std::endl;

	  	for (int e = 0; e < n_entries_detvar; e++) {
	  	//for (int e = 0; e < 10000; e++) {
	  		
	    	tree_detvar->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_detvar >= 10) &&  (e % (n_entries_detvar/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_detvar/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_detvar, _BDTTool, Utility::kMC, Utility::kRun1a);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack_WireModYZ.Fill(_event_detvar.classification, _event_detvar.shr2_pfpgeneration, pot_weight_detvar_WireModYZ_run1_fhc * _event_detvar.weight_cv);

		    //if (_event_mc.primaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.primaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
	        //else if (_event_mc.secondaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.secondaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
	  	    //else if (_event_mc.tertiaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.tertiaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
		}

		delete f_detvar;
	}

	// ----------------- Run 1 FHC WireModThetaYZ ------------------
	{
		// --- WireModThetaYZ ---	
		// read file
		TFile *f_detvar = NULL;
	  	TTree *tree_detvar = NULL;
	 	f_detvar = new TFile(filename_detvar_WireModThetaYZ_run1_fhc.c_str());  
	  	tree_detvar = (TTree*)f_detvar->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_detvar(tree_detvar, _utility); 	

	  	// loop through events
	  	int n_entries_detvar = tree_detvar->GetEntries();
	  	std::cout << "Initial number events [Run 1 FHC DetVar WireModThetaYZ]: " << n_entries_detvar << std::endl;

	  	for (int e = 0; e < n_entries_detvar; e++) {
	  	//for (int e = 0; e < 10000; e++) {
	  		
	    	tree_detvar->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_detvar >= 10) &&  (e % (n_entries_detvar/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_detvar/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_detvar, _BDTTool, Utility::kMC, Utility::kRun1a);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack_WireModThetaYZ.Fill(_event_detvar.classification, _event_detvar.shr2_pfpgeneration, pot_weight_detvar_WireModThetaYZ_run1_fhc * _event_detvar.weight_cv);

		    //if (_event_mc.primaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.primaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
	        //else if (_event_mc.secondaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.secondaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
	  	    //else if (_event_mc.tertiaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.tertiaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
		}

		delete f_detvar;
	}
	*/

	// print event integrals
	std::cout << "DetVar CV:" << std::endl;
	_histStack_CV.PrintEventIntegrals();

	std::cout << "DetVar SCE:" << std::endl;
	_histStack_SCE.PrintEventIntegrals();

	std::cout << "DetVar Recombination:" << std::endl;
	_histStack_Recombination.PrintEventIntegrals();

	std::cout << "DetVar WireModX:" << std::endl;
	_histStack_WireModX.PrintEventIntegrals();

	std::cout << "DetVar WireModYZ:" << std::endl;
	_histStack_WireModYZ.PrintEventIntegrals();

	std::cout << "DetVar WireModThetaYZ:" << std::endl;
	_histStack_WireModThetaYZ.PrintEventIntegrals();

}

// ------------------------------------------------------------------------------


// Run BDT selection on RHC detector variations
void SelectionDriver::runBDTSelectionDetVarRHC() {

	StackedHistTool _histStack_CV("", "", 20, 0, 1.001, _utility);
	StackedHistTool _histStack_WireModX("", "", 20, 0, 1.001, _utility);
	
	BDTTool _BDTTool(true, true, true, true,  _utility);
	Selection _selection(_utility);


	// ----------------- Run 3 RHC CV ------------------
	{
		// --- CV ---	
		// read file
		TFile *f_detvar = NULL;
	  	TTree *tree_detvar = NULL;
	 	f_detvar = new TFile(filename_detvar_CV_run3b_rhc.c_str());  
	  	tree_detvar = (TTree*)f_detvar->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_detvar(tree_detvar, _utility); 	

	  	// loop through events
	  	int n_entries_detvar = tree_detvar->GetEntries();
	  	std::cout << "Initial number events [Run 3b RHC DetVar CV]: " << n_entries_detvar << std::endl;

	  	for (int e = 0; e < n_entries_detvar; e++) {
	  	//for (int e = 0; e < 10000; e++) {
	  		
	    	tree_detvar->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_detvar >= 10) &&  (e % (n_entries_detvar/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_detvar/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_detvar, _BDTTool, Utility::kDetVar, Utility::kRun3b);
		    if (!passSelection) continue;

		    // fill histogram
		    //_histStack_CV.Fill(_event_detvar.classification, _event_detvar.BDTScoreElectronPhoton, pot_weight_detvar_CV_run3b_rhc * _event_detvar.weight_cv);

		    if (_event_detvar.primaryTrackPionlikeLoose) _histStack_CV.Fill(_event_detvar.classification, _event_detvar.primaryTrackBDTScorePionProton, pot_weight_detvar_CV_run3b_rhc * _event_detvar.weight_cv);
	        else if (_event_detvar.secondaryTrackPionlikeLoose) _histStack_CV.Fill(_event_detvar.classification, _event_detvar.secondaryTrackBDTScorePionProton, pot_weight_detvar_CV_run3b_rhc * _event_detvar.weight_cv);
	  	    else if (_event_detvar.tertiaryTrackPionlikeLoose) _histStack_CV.Fill(_event_detvar.classification, _event_detvar.tertiaryTrackBDTScorePionProton, pot_weight_detvar_CV_run3b_rhc * _event_detvar.weight_cv);
		}

		delete f_detvar;
	}

	// ----------------- Run 3 RHC WireModX ------------------
	{
		// --- WireModX ---	
		// read file
		TFile *f_detvar = NULL;
	  	TTree *tree_detvar = NULL;
	 	f_detvar = new TFile(filename_detvar_WireModX_run3b_rhc.c_str());  
	  	tree_detvar = (TTree*)f_detvar->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_detvar(tree_detvar, _utility); 	

	  	// loop through events
	  	int n_entries_detvar = tree_detvar->GetEntries();
	  	std::cout << "Initial number events [Run 3b FHC DetVar WireModX]: " << n_entries_detvar << std::endl;

	  	for (int e = 0; e < n_entries_detvar; e++) {
	  	//for (int e = 0; e < 10000; e++) {
	  		
	    	tree_detvar->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_detvar >= 10) &&  (e % (n_entries_detvar/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_detvar/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_detvar, _BDTTool, Utility::kMC, Utility::kRun3b);
		    if (!passSelection) continue;

		    // fill histogram
		    //_histStack_WireModX.Fill(_event_detvar.classification, _event_detvar.BDTScoreElectronPhoton, pot_weight_detvar_WireModX_run3b_rhc * _event_detvar.weight_cv);

		    if (_event_detvar.primaryTrackPionlikeLoose) _histStack_WireModX.Fill(_event_detvar.classification, _event_detvar.primaryTrackBDTScorePionProton, pot_weight_detvar_WireModX_run3b_rhc * _event_detvar.weight_cv);
	        else if (_event_detvar.secondaryTrackPionlikeLoose) _histStack_WireModX.Fill(_event_detvar.classification, _event_detvar.secondaryTrackBDTScorePionProton, pot_weight_detvar_WireModX_run3b_rhc * _event_detvar.weight_cv);
	  	    else if (_event_detvar.tertiaryTrackPionlikeLoose) _histStack_WireModX.Fill(_event_detvar.classification, _event_detvar.tertiaryTrackBDTScorePionProton, pot_weight_detvar_WireModX_run3b_rhc * _event_detvar.weight_cv);
		}

		delete f_detvar;
	}

	// print event integrals
	std::cout << "DetVar CV:" << std::endl;
	_histStack_CV.PrintEventIntegrals();

	std::cout << "DetVar WireModX:" << std::endl;
	_histStack_WireModX.PrintEventIntegrals();

	TCanvas *canv_1 = new TCanvas("canv_1", "canv_1", 1080, 1080);
	canv_1->cd();
  	_histStack_CV.DrawStack(canv_1, Utility::kRHC);
  	canv_1->Print("plot_RHC_CV.root");

  	TCanvas *canv_2 = new TCanvas("canv_2", "canv_2", 1080, 1080);
  	canv_2->cd();
  	_histStack_WireModX.DrawStack(canv_2, Utility::kRHC);
  	canv_2->Print("plot_RHC_WireModX.root");

}

// ------------------------------------------------------------------------------

// Create Training Tree for electron-photon BDT FHC
void SelectionDriver::createElectronPhotonBDTTrainingTreeFHC() {

	StackedHistTool _histStack("", "", 20, 0, 1.001, _utility);
	Selection _selection(_utility);
	CreateTrainingTree _trainingTree(Utility::kElectronPhoton);

	
	// ----------------- Run 1 FHC ------------------
	{
		
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_train_run1_fhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 1 FHC Intrinsic Nue Overlay Train]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyElectronPhotonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun1a);
		    if (!passSelection) continue;

		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_train_run1_fhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
		    // electron-photon
		    if (_event_intrinsic.classification == Utility::kCCNue1piXp) _trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;


		// --- CC/NC Pi Zero Overlay ---

		// read file
		TFile *f_ccncpizero = NULL;
	  	TTree *tree_ccncpizero = NULL;
	 	f_ccncpizero = new TFile(filename_ccncpizero_run1_fhc.c_str());  
	  	tree_ccncpizero = (TTree*)f_ccncpizero->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_ccncpizero(tree_ccncpizero, _utility); 	

	  	// loop through events
	  	int n_entries_ccncpizero = tree_ccncpizero->GetEntries();
	  	std::cout << "Initial number events [Run 1 FHC CC/NC Pi0 Overlay Train]: " << n_entries_ccncpizero << std::endl;
	  	
	  	for (int e = 0; e < n_entries_ccncpizero; e++) {

	    	tree_ccncpizero->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_ccncpizero >= 10) &&  (e % (n_entries_ccncpizero/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_ccncpizero/10));
		    }

		    bool passSelection = _selection.ApplyElectronPhotonBDTTrainingSelection(_event_ccncpizero, Utility::kCCNCPiZero, Utility::kRun1a);
		    if (!passSelection) continue;
		     
		     // fill histogram
		    _histStack.Fill(_event_ccncpizero.classification, _event_ccncpizero.shr_energyFraction, pot_weight_ccncpizero_run1_fhc * _event_ccncpizero.weight_cv);	 
			
		    // add event to training tree
		    if (_event_ccncpizero.classification == Utility::kCCNuepizero || _event_ccncpizero.classification == Utility::kCCNumupizero || _event_ccncpizero.classification == Utility::kNCpizero ) {
				_trainingTree.addEvent(_event_ccncpizero, _event_ccncpizero.classification);
			}
		}

		delete f_ccncpizero;
	}
	

	// ----------------- Run 2a FHC ------------------
	{
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_train_run2a_fhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 2a FHC Intrinsic Nue Overlay Train]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyElectronPhotonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun2a);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_train_run2a_fhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
		    // electron-photon
		    if (_event_intrinsic.classification == Utility::kCCNue1piXp
		    	) _trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;
	}

	// ----------------- Run 4 FHC ------------------
	{
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_train_run4_fhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 4 FHC Intrinsic Nue Overlay Train]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyElectronPhotonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun4cd);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_train_run4_fhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
		    // electron-photon
		    if (_event_intrinsic.classification == Utility::kCCNue1piXp
		    	) _trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;
	}

	// ----------------- Run 5 FHC ------------------
	{
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_train_run5_fhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 5 FHC Intrinsic Nue Overlay Train]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyElectronPhotonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun5);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_train_run5_fhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
		    // electron-photon
		    if (_event_intrinsic.classification == Utility::kCCNue1piXp
		    	) _trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;


		// --- CC/NC Pi Zero Overlay ---

		// read file
		TFile *f_ccncpizero = NULL;
	  	TTree *tree_ccncpizero = NULL;
	 	f_ccncpizero = new TFile(filename_ccncpizero_run5_fhc.c_str());  
	  	tree_ccncpizero = (TTree*)f_ccncpizero->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_ccncpizero(tree_ccncpizero, _utility); 	

	  	// loop through events
	  	int n_entries_ccncpizero = tree_ccncpizero->GetEntries();
	  	std::cout << "Initial number events [Run 5 FHC CC/NC Pi0 Overlay Train]: " << n_entries_ccncpizero << std::endl;
	  	
	  	for (int e = 0; e < n_entries_ccncpizero; e++) {

	    	tree_ccncpizero->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_ccncpizero >= 10) &&  (e % (n_entries_ccncpizero/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_ccncpizero/10));
		    }

		    bool passSelection = _selection.ApplyElectronPhotonBDTTrainingSelection(_event_ccncpizero, Utility::kCCNCPiZero, Utility::kRun5);
		    if (!passSelection) continue;
		     
		     // fill histogram
		    _histStack.Fill(_event_ccncpizero.classification, _event_ccncpizero.shr_energyFraction, pot_weight_ccncpizero_run5_fhc * _event_ccncpizero.weight_cv);	 
			
		    // add event to training tree
		    if (_event_ccncpizero.classification == Utility::kCCNuepizero || _event_ccncpizero.classification == Utility::kCCNumupizero || _event_ccncpizero.classification == Utility::kNCpizero ) {
				_trainingTree.addEvent(_event_ccncpizero, _event_ccncpizero.classification);
			}
		}

		delete f_ccncpizero;
	}

	// print event integrals
	_histStack.PrintEventIntegrals();

	// write training tree
	_trainingTree.writeOutputFile();
}


// ------------------------------------------------------------------------------

// Create Training Tree for electron-photon BDT RHC
void SelectionDriver::createElectronPhotonBDTTrainingTreeRHC() {

	StackedHistTool _histStack("", "", 20, 0, 1.001, _utility);
	Selection _selection(_utility);
	CreateTrainingTree _trainingTree(Utility::kElectronPhoton);
	

	
	// ----------------- Run 1 RHC ------------------
	{
		
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_train_run1_rhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 1 RHC Intrinsic Nue Overlay Train]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyElectronPhotonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun1b);
		    if (!passSelection) continue;

		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_train_run1_rhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
		    // electron-photon
		    if (_event_intrinsic.classification == Utility::kCCNue1piXp
		    	) _trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;
	}

	// ----------------- Run 2b RHC ------------------
	{
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_train_run2b_rhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 2b RHC Intrinsic Nue Overlay Train]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyElectronPhotonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun2b);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_train_run2b_rhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
		    // electron-photon
		    if (_event_intrinsic.classification == Utility::kCCNue1piXp
		    	) _trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;
	}

	// ----------------- Run 3b RHC ------------------
	{
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_train_run3b_rhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 3b RHC Intrinsic Nue Overlay Train]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyElectronPhotonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun3b);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_train_run3b_rhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
		    // electron-photon
		    if (_event_intrinsic.classification == Utility::kCCNue1piXp
		    	) _trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;

		// --- CC/NC Pi Zero Overlay ---

		// read file
		TFile *f_ccncpizero = NULL;
	  	TTree *tree_ccncpizero = NULL;
	 	f_ccncpizero = new TFile(filename_ccncpizero_run3b_rhc.c_str());  
	  	tree_ccncpizero = (TTree*)f_ccncpizero->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_ccncpizero(tree_ccncpizero, _utility); 	

	  	// loop through events
	  	int n_entries_ccncpizero = tree_ccncpizero->GetEntries();
	  	std::cout << "Initial number events [Run 3b RHC CC/NC Pi0 Overlay Train]: " << n_entries_ccncpizero << std::endl;
	  	
	  	for (int e = 0; e < n_entries_ccncpizero; e++) {

	    	tree_ccncpizero->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_ccncpizero >= 10) &&  (e % (n_entries_ccncpizero/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_ccncpizero/10));
		    }

		    bool passSelection = _selection.ApplyElectronPhotonBDTTrainingSelection(_event_ccncpizero, Utility::kCCNCPiZero, Utility::kRun3b);
		    if (!passSelection) continue;
 
		    _histStack.Fill(_event_ccncpizero.classification, _event_ccncpizero.contained_fraction, pot_weight_ccncpizero_run3b_rhc * _event_ccncpizero.weight_cv);	 
			
		    // add event to training tree
		    if (_event_ccncpizero.classification == Utility::kCCNuepizero || _event_ccncpizero.classification == Utility::kCCNumupizero || _event_ccncpizero.classification == Utility::kNCpizero ) {
				_trainingTree.addEvent(_event_ccncpizero, _event_ccncpizero.classification);
			}
		}

		delete f_ccncpizero;
	}

	// ----------------- Run 4 RHC ------------------
	{
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_train_run4_rhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 4 RHC Intrinsic Nue Overlay Train]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyElectronPhotonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun4ab);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_train_run4_rhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
		    // electron-photon
		    if (_event_intrinsic.classification == Utility::kCCNue1piXp 
		    	) _trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;
	}

	// print event integrals
	_histStack.PrintEventIntegrals();

	// write training tree
	_trainingTree.writeOutputFile();
}

// ------------------------------------------------------------------------------

// Create training tree for pion-proton BDT FHC
void SelectionDriver::createPionProtonBDTTrainingTreeFHC() {
	
	StackedHistTool _histStack("", "", 20, 0, 1.001, _utility);
	BDTTool _BDTTool(true, true, true, true,  _utility);
	Selection _selection(_utility);
	CreateTrainingTree _trainingTree(Utility::kPionProton);

	// ----------------- Run 1 FHC ------------------
	{
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_train_run1_fhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 1 FHC Intrinsic Nue Overlay Train]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun1a);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_train_run1_fhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
			_trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;
	}

	// ----------------- Run 2a FHC ------------------
	{
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_train_run2a_fhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 2a FHC Intrinsic Nue Overlay Train]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun2a);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_train_run2a_fhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
			_trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;
	}

	// ----------------- Run 4 FHC ------------------
	{
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_train_run4_fhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 4 FHC Intrinsic Nue Overlay Train]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun4cd);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_train_run4_fhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
			_trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;
	}

	// ----------------- Run 5 FHC ------------------
	{
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_train_run5_fhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 5 FHC Intrinsic Nue Overlay Train]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun5);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_train_run5_fhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
			_trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;
	}

	// print event integrals
	_histStack.PrintEventIntegrals();

	// write training tree
	_trainingTree.writeOutputFile();
}

// ------------------------------------------------------------------------------

// Create training tree for pion-proton BDT RHC
void SelectionDriver::createPionProtonBDTTrainingTreeRHC() {
	
	StackedHistTool _histStack("", "", 20, 0, 1.001, _utility);
	BDTTool _BDTTool(true, true, true, true,  _utility);
	Selection _selection(_utility);
	CreateTrainingTree _trainingTree(Utility::kPionProton);

	// ----------------- Run 1 RHC ------------------
	{
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_train_run1_rhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 1 RHC Intrinsic Nue Overlay Train]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun1b);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_train_run1_rhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
			_trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;
	}

	// ----------------- Run 2b RHC ------------------
	{
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_train_run2b_rhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 2b RHC Intrinsic Nue Overlay Train]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun2b);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_train_run2b_rhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
			_trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;
	}

	// ----------------- Run 3b RHC ------------------
	{
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_train_run3b_rhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 3b RHC Intrinsic Nue Overlay Train]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun3b);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_train_run3b_rhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
			_trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;
	}

	// ----------------- Run 4 RHC ------------------
	{
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_train_run4_rhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 4 RHC Intrinsic Nue Overlay Train]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun4ab);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_train_run4_rhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
			_trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;
	}

	// print event integrals
	_histStack.PrintEventIntegrals();

	// write training tree
	_trainingTree.writeOutputFile();
}

