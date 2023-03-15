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

#include <TSystem.h>


int main() {
	
	// Files [Run 1]
    std::string filename_intrinsic = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1_slim/neutrinoselection_filt_run1_intrinsic_slim.root";
    std::string filename_mc = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1_slim/neutrinoselection_filt_run1_overlay_slim.root";
	std::string filename_dirt = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1_slim/neutrinoselection_filt_run1_dirt_slim.root";
	std::string filename_beamoff = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1_slim/neutrinoselection_filt_run1_beamoff_slim.root";

	// Files [Run 3b]
	//std::string filename_mc = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run3b_slim/neutrinoselection_filt_run3b_overlay_slim.root";

	// Weights [Run 1]
	//double weight_mc = 1;		// POT_beam-on / POT_mc
	double weight_intrinsic = 0.008405127 * 0.9502;	// intrinsic nue 2.3795e+22 [slim]  2.3795e+22
	double weight_mc = 0.08569; 	// 2.33391e+21 [slim]
	double weight_dirt = 0.12245; 	// 1.63329e+21 [slim]
	double weight_beamoff = 0.5612; // 0.98 * HW_beam-on / HW_beam-off

	// Weights [Run 3b]
	//double weight_mc = 0.25081; // 1.99351e+21 [slim]

	// Initialise Classes
  	Utility _utility;
  	Selection _selection(_utility);
  	StackedHistTool _histStack("", "", 6, 0, 6, _utility);
  	BDTTool _BDTTool(true, false);
  	//CreateTrainingTree _trainingTree;

  	// Testing histogram
  	TH1F *hist_sig = new TH1F("", "", 50, 0, 10);
  	TH1F *hist_bg = new TH1F("", "", 50, 0, 10);
  	
  	TH2F *hist2D = new TH2F("", "", 22, 0, 1.1, 22, 0, 1.1);
  	TH2F *hist2D_bg = new TH2F("", "", 22, 0, 1.1, 22, 0, 1.1);
  	
  	//TH2F *hist2D = new TH2F("", "", 20, 0, 10, 30, 0, 15);
  	//TH2F *hist2D_bg = new TH2F("", "", 20, 0, 10, 30, 0, 15);
	
  	
  	/*
	// --- Intrinsic Nue MC -- 
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

  	//for (int e = 0; e < n_entries_intrinsic; e++) {
  	for (int e = 0; e < 70000; e++) {
  		
    	tree_intrinsic->GetEntry(e);    	

	    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
	      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
	    }

	    // populate derived variables [not in ntuples]
	    _event_intrinsic.populateDerivedVariables(Utility::kIntrinsic);

	    // apply reconstruction recovery algorithms
	    _event_intrinsic.applyEventRecoveryAlgorithms(Utility::kIntrinsic);

	    // apply selection
	    // pre-selection
	    bool passPreSelection = _selection.ApplyPreSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun1);
	    if(!passPreSelection) continue;	    

	    // reconstruction completeness (separated out from pre-selection to avoid calculating derived variables for all events)
	    bool passReconstructionCompletenessCheck = _selection.ApplyReconstructionCompletenessCheck(_event_intrinsic);
	    if(!passReconstructionCompletenessCheck) continue;

	    // good shower selection
	    bool passGoodShowerIdentification = _selection.ApplyGoodShowerSelection(_event_intrinsic);
	    if(!passGoodShowerIdentification) continue;

	    // good track selection
	    bool passGoodTrackSelection = _selection.ApplyGoodTrackSelection(_event_intrinsic, Utility::kIntrinsic);
	    //if(!passGoodTrackSelection) continue;

	    // reconstruction failure checks
	    bool passReconstructionFailureChecks = _selection.ApplyReconstructionFailureChecks(_event_intrinsic, Utility::kIntrinsic);
	    if(!passReconstructionFailureChecks) continue;

	    // cosmic rejection
	    bool passCosmicRejection = _selection.ApplyCosmicRejection(_event_intrinsic);
	    if(!passCosmicRejection) continue;

	    // evaluate BDTs
	    ///_event_intrinsic.evaluateBDTs();		   	    

	    // neutral pion rejection
	    bool passNeutralPionRejection = _selection.ApplyNeutralPionRejectionBDT(_event_intrinsic);
	    if(!passNeutralPionRejection) continue;	

	    // proton rejection
	    bool passProtonRejection = _selection.ApplyProtonRejection(_event_intrinsic, Utility::kIntrinsic);
	    //if(!passProtonRejection) continue;

	    // get event classification
	    Utility::ClassificationEnums classification = _event_intrinsic.getEventClassification(Utility::kIntrinsic);

	    
	    if(classification == Utility::kCCNue1piNp || classification == Utility::kCCNue1pi0p) {
	    	hist2D->Fill(_event_intrinsic.shr_trkfit_gap10_dedx_max, _event_intrinsic.shr_distance, weight_intrinsic);
	    }

	    // fill stacked histogram, selected topologies only
	    if (classification == Utility::kCCNue1pi0p || classification == Utility::kCCNue1piNp || classification == Utility::kCCNueNpi || classification == Utility::kCCNuepizero || 
	    	classification == Utility::kCCNue1p || classification == Utility::kCCNueNp || classification == Utility::kCCNueOther || 
	    	classification == Utility::kCCNue1piNp ){
	    	
	    	_histStack.Fill(classification, _event_intrinsic.bdtscore_electronPhoton, weight_intrinsic);

	    	
		    // fill testing plot
		    // primary
		    if (_event_intrinsic.trk_bkt_pdg == 2212 && _event_intrinsic.primaryTrackPionlike) {
		    	hist2D_bg->Fill(_event_intrinsic.trk_bragg_pion_max, _event_intrinsic.trk_bragg_mip_max, weight_intrinsic);
		    }
		    if ((_event_intrinsic.trk_bkt_pdg == 211 || _event_intrinsic.trk_bkt_pdg == -211) && _event_intrinsic.primaryTrackPionlike) {
		    	hist2D->Fill(_event_intrinsic.trk_bragg_pion_max, _event_intrinsic.trk_bragg_mip_max, weight_intrinsic);
		    }
		    // secondary
		    if (_event_intrinsic.trk2_bkt_pdg == 2212 && _event_intrinsic.secondaryTrackPionlike) {
		    	hist2D_bg->Fill(_event_intrinsic.trk2_bragg_pion_max, _event_intrinsic.trk2_bragg_mip_max, weight_intrinsic);
		    }
		    if ((_event_intrinsic.trk2_bkt_pdg == 211 || _event_intrinsic.trk2_bkt_pdg == -211) && _event_intrinsic.secondaryTrackPionlike) {
		    	hist2D->Fill(_event_intrinsic.trk2_bragg_pion_max, _event_intrinsic.trk2_bragg_mip_max, weight_intrinsic);
		    }
		    // tertiary
		    if (_event_intrinsic.trk3_bkt_pdg == 2212 && _event_intrinsic.tertiaryTrackPionlike) {
		    	hist2D_bg->Fill(_event_intrinsic.trk3_bragg_pion_max, _event_intrinsic.trk3_bragg_mip_max, weight_intrinsic);
		    }
		    if ((_event_intrinsic.trk3_bkt_pdg == 211 || _event_intrinsic.trk3_bkt_pdg == -211) && _event_intrinsic.tertiaryTrackPionlike) {
		    	hist2D->Fill(_event_intrinsic.trk3_bragg_pion_max, _event_intrinsic.trk3_bragg_mip_max, weight_intrinsic);
		    }
		    

	    	//if (_event_intrinsic.primaryTrackValid) _histStack.Fill(classification, _event_intrinsic.trk_len, weight_intrinsic);
			//else if (_event_intrinsic.secondaryTrackValid) _histStack.Fill(classification, _event_intrinsic.trk2_len, weight_intrinsic);
			//else if (_event_intrinsic.tertiaryTrackValid) _histStack.Fill(classification, _event_intrinsic.trk3_len, weight_intrinsic);

		}
		

	    // add event to training tree (if required)
	    if(classification == Utility::kCCNuepizero && e > 12500) continue; 	// prevent excess of nue pi0
		_trainingTree.addEvent(_event_intrinsic, classification);

	}
	*/
	

	// --- Overlay MC ---	
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
  	//for (int e = 0; e < 50000; e++) {
  		
    	tree_mc->GetEntry(e);    	

	    if ( (e != 0) && (n_entries_mc >= 10) &&  (e % (n_entries_mc/10) == 0) ) {
	      std::cout << Form("%i0%% Completed...\n", e / (n_entries_mc/10));
	    }

	    // populate derived variables [not in ntuples]
	    _event_mc.populateDerivedVariables(Utility::kMC);

	    // apply reconstruction recovery algorithms
	    _event_mc.applyEventRecoveryAlgorithms(Utility::kMC);

	    // apply selection
	    // pre-selection
	    bool passPreSelection = _selection.ApplyPreSelection(_event_mc, Utility::kMC, Utility::kRun1);
	    if(!passPreSelection) continue;	    

	    // reconstruction completeness (separated out from pre-selection to avoid calculating derived variables for all events)
	    bool passReconstructionCompletenessCheck = _selection.ApplyReconstructionCompletenessCheck(_event_mc);
	    if(!passReconstructionCompletenessCheck) continue;

	    // good shower selection
	    bool passGoodShowerIdentification = _selection.ApplyGoodShowerSelection(_event_mc);
	    if(!passGoodShowerIdentification) continue;

	    // good track selection
	    bool passGoodTrackSelection = _selection.ApplyGoodTrackSelection(_event_mc, Utility::kMC);
	    if(!passGoodTrackSelection) continue;

	    // reconstruction failure checks
	    bool passReconstructionFailureChecks = _selection.ApplyReconstructionFailureChecks(_event_mc, Utility::kMC);
	    if(!passReconstructionFailureChecks) continue;

	    // cosmic rejection
	    bool passCosmicRejection = _selection.ApplyCosmicRejection(_event_mc);
	    if(!passCosmicRejection) continue;

	    // neutral pion rejection
	    //bool passNeutralPionRejection = _selection.ApplyNeutralPionRejection(_event_mc);
	    bool passNeutralPionRejection = _selection.ApplyNeutralPionRejectionBDT(_event_mc, _BDTTool);
	    if(!passNeutralPionRejection) continue;	

	    // proton rejection
	    bool passProtonRejection = _selection.ApplyProtonRejection(_event_mc, Utility::kMC);
	    if(!passProtonRejection) continue;

	    // get event classification
	    Utility::ClassificationEnums classification = _event_mc.getEventClassification(Utility::kMC);

		//// fill testing plot 
	    if(classification == Utility::kCCNue1piNp || classification == Utility::kCCNue1pi0p) {
	    	hist2D->Fill(_event_mc.shr_trkfit_gap10_dedx_max, _event_mc.shr_distance, weight_mc);
	    }
	    
	    if (classification == Utility::kCCNumupizero || classification == Utility::kNCpizero) {
	    	hist2D_bg->Fill(_event_mc.shr_trkfit_gap10_dedx_max, _event_mc.shr_distance, weight_mc);
	    }
	    
	    
	 
	    
	    
	    
	    //if (_event_mc.npion == 1 && (_event_mc.trk_bkt_pdg == 211 || _event_mc.trk_bkt_pdg == -211)) {
	    //	hist2D->Fill(_event_mc.pion_e - (139.57/1000), _event_mc.trk_len);
	    //}

	   

	    
	    // fill histograms
	    // primary track
	    // muon
	    //if ((_event_mc.trk_bkt_pdg == 13 || _event_mc.trk_bkt_pdg == -13) && _event_mc.primaryTrackValid) hist2D_bg->Fill(_event_mc.trk_avg_deflection_separation_mean, _event_mc.trk_avg_deflection_mean);
	    // proton
	    //if (_event_mc.trk_bkt_pdg == 2212 && _event_mc.primaryTrackPionlike) hist_bg->Fill(_event_mc.trk_dEdx_trunk_max);
	    // pion
	    //if ((_event_mc.trk_bkt_pdg == 211 || _event_mc.trk_bkt_pdg == -211) && _event_mc.primaryTrackPionlike) hist_sig->Fill(_event_mc.trk_dEdx_trunk_max);
	    //if ((_event_mc.trk_bkt_pdg == 211 || _event_mc.trk_bkt_pdg == -211) && _event_mc.primaryTrackValid) hist2D->Fill(_event_mc.trk_avg_deflection_separation_mean, _event_mc.trk_avg_deflection_mean);
	    
	    // secondary track
	    // proton
	    //if (_event_mc.trk2_bkt_pdg == 2212 && _event_mc.secondaryTrackPionlike) hist_bg->Fill(_event_mc.trk2_dEdx_trunk_max);
	    // pion
	    //if ((_event_mc.trk2_bkt_pdg == 211 || _event_mc.trk2_bkt_pdg == -211) && _event_mc.secondaryTrackPionlike) hist_sig->Fill(_event_mc.trk2_dEdx_trunk_max);
	  	
	    // do not add nues in training, use intrinsic simulation instead [comment out when testing with actual sample]
	    //if (classification == Utility::kCCNue1pi0p || classification == Utility::kCCNue1piNp || classification == Utility::kCCNueNpi || classification == Utility::kCCNuepizero || 
	    //	classification == Utility::kCCNue1p || classification == Utility::kCCNueNp || classification == Utility::kCCNueOther || 
	    //	classification == Utility::kCCNue1piNp ) continue;
	    	
	    
	    // fill testing plot
	    // primary
	    if (_event_mc.trk_bkt_pdg == 2212 && _event_mc.primaryTrackPionlike) {
	    	hist2D_bg->Fill(_event_mc.trk_bragg_pion_max, _event_mc.trk_bragg_mip_max, weight_mc);
	    }
	    if ((_event_mc.trk_bkt_pdg == 211 || _event_mc.trk_bkt_pdg == -211) && _event_mc.primaryTrackPionlike) {
	    	hist2D->Fill(_event_mc.trk_bragg_pion_max, _event_mc.trk_bragg_mip_max, weight_mc);
	    }
	    // secondary
	    if (_event_mc.trk2_bkt_pdg == 2212 && _event_mc.secondaryTrackPionlike) {
	    	hist2D_bg->Fill(_event_mc.trk2_bragg_pion_max, _event_mc.trk2_bragg_mip_max, weight_mc);
	    }
	    if ((_event_mc.trk2_bkt_pdg == 211 || _event_mc.trk2_bkt_pdg == -211) && _event_mc.secondaryTrackPionlike) {
	    	hist2D->Fill(_event_mc.trk2_bragg_pion_max, _event_mc.trk2_bragg_mip_max, weight_mc);
	    }
	    // tertiary
	    if (_event_mc.trk3_bkt_pdg == 2212 && _event_mc.tertiaryTrackPionlike) {
	    	hist2D_bg->Fill(_event_mc.trk3_bragg_pion_max, _event_mc.trk3_bragg_mip_max, weight_mc);
	    }
	    if ((_event_mc.trk3_bkt_pdg == 211 || _event_mc.trk3_bkt_pdg == -211) && _event_mc.tertiaryTrackPionlike) {
	    	hist2D->Fill(_event_mc.trk3_bragg_pion_max, _event_mc.trk3_bragg_mip_max, weight_mc);
	    }
	    

	    //_histStack.Fill(classification, _event_mc.n_showers_contained, weight_mc);
		
		if (_event_mc.primaryTrackValid) _histStack.Fill(classification, _event_mc.trk_daughters, weight_mc);
		else if (_event_mc.secondaryTrackValid) _histStack.Fill(classification, _event_mc.trk2_daughters, weight_mc);
		else if (_event_mc.tertiaryTrackValid) _histStack.Fill(classification, _event_mc.trk3_daughters, weight_mc);

	  	//if (_event_mc.primaryTrackPionlike) _histStack.Fill(classification, _event_mc.trk_llr_pid_score, weight_mc);
	    //else if (_event_mc.secondaryTrackPionlike) _histStack.Fill(classification, _event_mc.trk2_llr_pid_score, weight_mc);
	  	//else _histStack.Fill(classification, _event_mc.trk3_llr_pid_score, weight_mc);

	  	// add event to training tree (if required)
	  	//_trainingTree.addEvent(_event_mc, classification);


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
  	//for (int e = 0; e < 50000; e++) {

    	tree_beamoff->GetEntry(e);

	    if ( (e != 0) && (n_entries_beamoff >= 10) &&  (e % (n_entries_beamoff/10) == 0) ) {
	      std::cout << Form("%i0%% Completed...\n", e / (n_entries_beamoff/10));
	    }

	    // populate derived variables [not in ntuple]
	    _event_beamoff.populateDerivedVariables(Utility::kEXT);

	    // apply reconstruction recovery algorithms
	    _event_beamoff.applyEventRecoveryAlgorithms(Utility::kEXT);

	    // apply selection
	    // pre-selection
	    bool passPreSelection = _selection.ApplyPreSelection(_event_beamoff, Utility::kEXT, Utility::kRun1);
	    if(!passPreSelection) continue;

	    // reconstruction completeness (separated out from pre-selection to avoid calculating derived variables for all events)
	    bool passReconstructionCompletenessCheck = _selection.ApplyReconstructionCompletenessCheck(_event_beamoff);
	    if(!passReconstructionCompletenessCheck) continue;

	    // good shower identification
	    bool passGoodShowerIdentification = _selection.ApplyGoodShowerSelection(_event_beamoff);
	    if(!passGoodShowerIdentification) continue;

	    // good track selection
	    bool passGoodTrackSelection = _selection.ApplyGoodTrackSelection(_event_beamoff, Utility::kEXT);
	    if(!passGoodTrackSelection) continue;

	    // reconstruction failure checks
	    bool passReconstructionFailureChecks = _selection.ApplyReconstructionFailureChecks(_event_beamoff, Utility::kEXT);
	    if(!passReconstructionFailureChecks) continue;

	    // cosmic rejection
	    bool passCosmicRejection = _selection.ApplyCosmicRejection(_event_beamoff);
	    if(!passCosmicRejection) continue;

	    // evaluate BDTs
	    //_event_beamoff.evaluateBDTs();  	    
	    
	    // neutral pion rejection
	    bool passNeutralPionRejection = _selection.ApplyNeutralPionRejection(_event_beamoff);
	    if(!passNeutralPionRejection) continue;

	    // proton rejection
	    bool passProtonRejection = _selection.ApplyProtonRejection(_event_beamoff, Utility::kEXT);
	    if(!passProtonRejection) continue;

	    // get event classification
	    Utility::ClassificationEnums classification = _event_beamoff.getEventClassification(Utility::kEXT);

	    // fill histogram
	    _histStack.Fill(classification, _event_beamoff.n_showers_contained, weight_beamoff);

	    //if (_event_beamoff.primaryTrackValid) _histStack.Fill(classification, _event_beamoff.trk_len, weight_beamoff);
		//else if (_event_beamoff.secondaryTrackValid) _histStack.Fill(classification, _event_beamoff.trk2_len, weight_beamoff);
		//else if (_event_beamoff.tertiaryTrackValid) _histStack.Fill(classification, _event_beamoff.trk3_len, weight_beamoff);


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
  	//for (int e = 0; e < 50000; e++) {

    	tree_dirt->GetEntry(e);

	    if ( (e != 0) && (n_entries_dirt >= 10) &&  (e % (n_entries_dirt/10) == 0) ) {
	      std::cout << Form("%i0%% Completed...\n", e / (n_entries_dirt/10));
	    }

	    // populate derived variables [not in ntuple]
	    _event_dirt.populateDerivedVariables(Utility::kDirt);

	    // apply reconstruction recovery algorithms
	    _event_dirt.applyEventRecoveryAlgorithms(Utility::kDirt);

	    // apply selection
	    // pre-selection
	    bool passPreSelection = _selection.ApplyPreSelection(_event_dirt, Utility::kDirt, Utility::kRun1);
	    if(!passPreSelection) continue;

	    // reconstruction completeness (separated out from pre-selection to avoid calculating derived variables for all events)
	    bool passReconstructionCompletenessCheck = _selection.ApplyReconstructionCompletenessCheck(_event_dirt);
	    if(!passReconstructionCompletenessCheck) continue;

	    // good shower identification
	    bool passGoodShowerIdentification = _selection.ApplyGoodShowerSelection(_event_dirt);
	    if(!passGoodShowerIdentification) continue;

	    // good track selection
	    bool passGoodTrackSelection = _selection.ApplyGoodTrackSelection(_event_dirt, Utility::kDirt);
	    if(!passGoodTrackSelection) continue;

	    // reconstruction failure checks
	    bool passReconstructionFailureChecks = _selection.ApplyReconstructionFailureChecks(_event_dirt, Utility::kDirt);
	    if(!passReconstructionFailureChecks) continue;	    

	    // cosmic rejection
	    bool passCosmicRejection = _selection.ApplyCosmicRejection(_event_dirt);
	    if(!passCosmicRejection) continue;

	    // evaluate BDTs
	    //_event_dirt.evaluateBDTs();  	 

	    // neutral pion rejection
	    bool passNeutralPionRejection = _selection.ApplyNeutralPionRejection(_event_dirt);
	    if(!passNeutralPionRejection) continue;

	    // proton rejection
	    bool passProtonRejection = _selection.ApplyProtonRejection(_event_dirt, Utility::kDirt);
	    if(!passProtonRejection) continue;

	    // get event classification
	    Utility::ClassificationEnums classification = _event_dirt.getEventClassification(Utility::kDirt);

	    // fill histogram
	    _histStack.Fill(classification, _event_dirt.n_showers_contained, weight_dirt);

	    //if (_event_dirt.primaryTrackValid) _histStack.Fill(classification, _event_dirt.trk_len, weight_dirt);
		//else if (_event_dirt.secondaryTrackValid) _histStack.Fill(classification, _event_dirt.trk2_len, weight_dirt);
		//else if (_event_dirt.tertiaryTrackValid) _histStack.Fill(classification, _event_dirt.trk3_len, weight_dirt);

	}
	*/
	

	// write training tree
	//_trainingTree.writeOutputFile();
	
	
	_histStack.PrintEventIntegrals();

	TCanvas *canv = new TCanvas("canv", "canv", 1080, 1080);
  	_histStack.DrawStack(canv, Utility::kNShower);
  	//_histStack.PrintEventIntegrals();

  	
  	//canv->Print("plot_postCosmicImpactParameter_ShowerScore.root");
  	//canv->Print("plot_postShowerScore_HitRatio.root");
  	//canv->Print("plot_postHitRatio_LeadingShowerEnergy.root");
  	//canv->Print("plot_postNeutralPionRejection_MoliereAverage.root");
  	//canv->Print("plot_postTrackLength_TrackDistance.root");
  	canv->Print("plot_NShowers.root");

  	
	
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
	


  	
	// normalise
	//hist_bg->Scale(1/hist_bg->GetEntries());
	//hist_sig->Scale(1/hist_sig->GetEntries());

  	/*
	TCanvas *c1 = new TCanvas("c1","",200,10,1080,1080);
  	c1->cd();
  	gStyle->SetOptStat(0);
  	hist_bg->Draw("HIST");
  	
  	hist_bg->GetXaxis()->SetTitle("Track Trunk dE/dx [MeV/cm]");
	
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

  	c1->Print("ProtonRejection_trackTrunkdEdx.root");
	*/

	return 0;
}