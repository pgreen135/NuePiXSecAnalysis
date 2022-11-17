// Driver script to launch nue analysis code

#include "Utility.h"
#include "EventContainer.h"
#include "Selection.h"
#include "StackedHistTool.h"

#include <iostream>
#include <string>

#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>


int main() {

	// Files [Run 1]
	//std::string filename_mc = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1_reprocessed/neutrinoselection_filt_run1_overlay_llrpid.root";
	std::string filename_mc = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1/neutrinoselection_filt_run1_overlay.root";
	std::string filename_dirt = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1/neutrinoselection_filt_run1_dirt_overlay.root";
	std::string filename_beamoff = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1/neutrinoselection_filt_run1_beamoff.root";

	// Weights [Run 1]
	//double weight_mc = 1;		// POT_beam-on / POT_mc
	double weight_mc = 0.0856;		// POT_beam-on / POT_mc
	double weight_dirt = 0.1407;	// POT_beam-on / POT_dirt
	double weight_beamoff = 0.5612; // 0.98 * HW_beam-on / HW_beam-off

	// Initialise Classes
  	Utility _utility;
  	Selection _selection(_utility);
  	StackedHistTool histStack("", "", 19, 0, 190, _utility);

  	// Testing histogram
  	TH1F *hist = new TH1F("", "", 25, 0, 10);
  	TH2F *hist2D = new TH2F("", "", 20, 0, 10, 40, 0, 20);
	
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

	    ///if(classification == Utility::kCCNue1pi) {
	    	//hist->Fill(_event_mc.elec_e);
	    	//std::cout << "Electron energy: " << _event_mc.elec_e << ", Pion Energy: " << _event_mc.pion_e << std::endl;
	    //}

	    // apply selection
	    // pre-selection
	    bool passPreSelection = _selection.ApplyPreSelection(_event_mc, Utility::kMC);
	    if(!passPreSelection) continue;

	    // cosmic rejection
	    bool passCosmicRejection = _selection.ApplyCosmicRejection(_event_mc);
	    if(!passCosmicRejection) continue;

	    // electron selection
	    bool passElectronSelection = _selection.ApplyElectronSelection(_event_mc);
	    if(!passElectronSelection) continue;

	     // apply pion selection
	    bool passPionSelection = _selection.ApplyPionSelection(_event_mc);
	    if(!passPionSelection) continue;	    

	    // populate derived variables [not in ntuple]
	    _event_mc.populateDerivedVariables();

	    // neutral pion rejection
	    bool passNeutralPionRejection = _selection.ApplyNeutralPionRejection(_event_mc);
	    if(!passNeutralPionRejection) continue;	

	    // proton rejection
	    bool passProtonRejection = _selection.ApplyProtonRejection(_event_mc);
	    if(!passProtonRejection) continue;

	    // get event classification
	    Utility::ClassificationEnums classification = _event_mc.getEventClassification(Utility::kMC);

		// fill testing plot 
	    if(classification == Utility::kCCNue1piNp) {
	    //if(classification == Utility::kCCNuepizero || classification == Utility::kCCNumupizero || classification == Utility::kNCpizero) {
	    	hist2D->Fill(_event_mc.shr_trkfit_dedx_max, _event_mc.shr_distance);
	    	//std::cout << "Primary Track Backtracked PDG: " << _event_mc.trk_bkt_pdg << ", LLR PID Score: " << _event_mc.trk_llr_pid_score << std::endl;
	    }

	    // fill histogram
	    histStack.Fill(classification, std::acos(_event_mc.tksh_angle) * 180 / 3.14, weight_mc);

	    //std::cout << "Passing Event: Run " << _event_mc.run << ", Subrun " << _event_mc.sub << ", Event " << _event_mc.evt << " --- Topology: " << histStack.topologyenum2str(classification) << std::endl;

	}

	
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

	    // apply selection
	    // pre-selection
	    bool passPreSelection = _selection.ApplyPreSelection(_event_beamoff, Utility::kEXT);
	    if(!passPreSelection) continue;

	    // cosmic rejection
	    bool passCosmicRejection = _selection.ApplyCosmicRejection(_event_beamoff);
	    if(!passCosmicRejection) continue;

	    // electron identification
	    bool passElectronIdentification = _selection.ApplyElectronSelection(_event_beamoff);
	    if(!passElectronIdentification) continue;

	     // apply pion selection
	    bool passPionSelection = _selection.ApplyPionSelection(_event_beamoff);
	    if(!passPionSelection) continue;	    

	    // populate derived variables [not in ntuple]
	    _event_beamoff.populateDerivedVariables();
	    
	    // neutral pion rejection
	    bool passNeutralPionRejection = _selection.ApplyNeutralPionRejection(_event_beamoff);
	    if(!passNeutralPionRejection) continue;

	    // proton rejection
	    bool passProtonRejection = _selection.ApplyProtonRejection(_event_beamoff);
	    if(!passProtonRejection) continue;

	    // get event classification
	    Utility::ClassificationEnums classification = _event_beamoff.getEventClassification(Utility::kEXT);

	    // fill histogram
	    histStack.Fill(classification, std::acos(_event_beamoff.tksh_angle) * 180 / 3.14, weight_beamoff);

	    //std::cout << "Passing Event: Run " << _event_beamoff.run << ", Subrun " << _event_beamoff.sub << ", Event " << _event_beamoff.evt << " --- Topology: " << histStack.topologyenum2str(classification) << std::endl;
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

	    // apply selection
	    // pre-selection
	    bool passPreSelection = _selection.ApplyPreSelection(_event_dirt, Utility::kDirt);
	    if(!passPreSelection) continue;

	    // cosmic rejection
	    bool passCosmicRejection = _selection.ApplyCosmicRejection(_event_dirt);
	    if(!passCosmicRejection) continue;

	    // electron identification
	    bool passElectronIdentification = _selection.ApplyElectronSelection(_event_dirt);
	    if(!passElectronIdentification) continue;

	    // apply pion selection
	    bool passPionSelection = _selection.ApplyPionSelection(_event_dirt);
	    if(!passPionSelection) continue;	    

	     // populate derived variables [not in ntuple]
	    _event_dirt.populateDerivedVariables();

	    // neutral pion rejection
	    bool passNeutralPionRejection = _selection.ApplyNeutralPionRejection(_event_dirt);
	    if(!passNeutralPionRejection) continue;

	    // proton rejection
	    bool passProtonRejection = _selection.ApplyProtonRejection(_event_dirt);
	    if(!passProtonRejection) continue;

	    // get event classification
	    Utility::ClassificationEnums classification = _event_dirt.getEventClassification(Utility::kDirt);

	    // fill histogram
	    histStack.Fill(classification, std::acos(_event_dirt.tksh_angle) * 180 / 3.14, weight_dirt);

	    //std::cout << "Passing Event: Run " << _event_dirt.run << ", Subrun " << _event_dirt.sub << ", Event " << _event_dirt.evt << " --- Topology: " << histStack.topologyenum2str(classification) << std::endl;
	}
	
	histStack.PrintEventIntegrals();

	TCanvas *canv = new TCanvas("canv", "canv", 1080, 1080);
  	histStack.DrawStack(canv, Utility::kTrackShowerAngle);
  	//histStack.PrintEventIntegrals();

  	
  	//canv->Print("plot_postCosmicImpactParameter_ShowerScore.root");
  	//canv->Print("plot_postShowerScore_HitRatio.root");
  	//canv->Print("plot_postHitRatio_LeadingShowerEnergy.root");
  	//canv->Print("plot_postNeutralPionRejection_MoliereAverage.root");
  	//canv->Print("plot_postTrackLength_TrackDistance.root");
  	canv->Print("plot_TrkShrAngle.root");

  	//canv->Print("plot_trkID.root");

  	TCanvas *c1 = new TCanvas("c1","",200,10,1080,1080);
  	c1->cd();
  	hist2D->Draw("BOX");
  	
  	hist2D->GetXaxis()->SetTitle("Shower dE/dx [MeV/cm]");
	hist2D->GetYaxis()->SetTitle("Shower Distance [cm]");
	
  	hist2D->GetXaxis()->SetTitleSize(0.045);
  	hist2D->GetYaxis()->SetTitleSize(0.045);

  	c1->Modified();
  	//c1->Print("NeutralPionRejection_background.root");



	return 0;
}