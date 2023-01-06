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
#include <TStyle.h>

#include <TSystem.h>


int main() {
	
	// Files [Run 1]
    //std::string filename_mc = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1_reprocessed/neutrinoselection_filt_run1_overlay_integration.root";
    std::string filename_mc = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1_reprocessed/neutrinoselection_filt_run1_overlay_integration_thirdtrack_new.root";
	//std::string filename_mc = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1/neutrinoselection_filt_run1_overlay.root";
	std::string filename_dirt = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1/neutrinoselection_filt_run1_dirt_overlay.root";
	std::string filename_beamoff = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1/neutrinoselection_filt_run1_beamoff.root";

	// Weights [Run 1]
	//double weight_mc = 1;		// POT_beam-on / POT_mc
	double weight_mc = 0.08564; 	// 2.33543e+21 [third track, new]
	//double weight_mc = 0.0858;			// POT_beam-on / POT_mc   // Re-processed files, POT 2.3307e+21 [third track]
	//double weight_mc = 0.0855;		// POT_beam-on / POT_mc   // Re-processed files, POT 2.33827e+21
	//double weight_mc = 0.0856;		// POT_beam-on / POT_mc   // Krishan's files, POT 2.33652e+21
	double weight_dirt = 0.1407;	// POT_beam-on / POT_dirt
	double weight_beamoff = 0.5612; // 0.98 * HW_beam-on / HW_beam-off

	// Initialise Classes
  	Utility _utility;
  	Selection _selection(_utility);
  	StackedHistTool histStack("", "", 60, 0, 3, _utility);

  	// Testing histogram
  	TH1F *hist_sig = new TH1F("", "", 50, 0, 10);
  	TH1F *hist_bg = new TH1F("", "", 50, 0, 10);
  	
  	//TH2F *hist2D = new TH2F("", "", 20, 0, 10, 15, 0, 15);
  	//TH2F *hist2D_bg = new TH2F("", "", 20, 0, 10, 15, 0, 15);
  	
  	TH2F *hist2D = new TH2F("", "", 20, 0, 10, 30, 0, 15);
  	TH2F *hist2D_bg = new TH2F("", "", 20, 0, 10, 30, 0, 15);
	
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
	    bool passPreSelection = _selection.ApplyPreSelection(_event_mc, Utility::kMC);
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
	    if (!passReconstructionFailureChecks) continue;

	    // cosmic rejection
	    bool passCosmicRejection = _selection.ApplyCosmicRejection(_event_mc);
	    if(!passCosmicRejection) continue;	   	    

	    // neutral pion rejection
	    bool passNeutralPionRejection = _selection.ApplyNeutralPionRejection(_event_mc);
	    if(!passNeutralPionRejection) continue;	

	    // proton rejection
	    bool passProtonRejection = _selection.ApplyProtonRejection(_event_mc, Utility::kMC);
	    if(!passProtonRejection) continue;

	    // get event classification
	    Utility::ClassificationEnums classification = _event_mc.getEventClassification(Utility::kMC);


		//// fill testing plot 
	    if(classification == Utility::kCCNue1piNp || classification == Utility::kCCNue1pi0p) {
	    	hist2D->Fill(_event_mc.shr_trkfit_gap10_dedx_max, _event_mc.tksh_distance);
	    }
	    else if (classification == Utility::kCCNumupizero || classification == Utility::kNCpizero) {
	    	hist2D_bg->Fill(_event_mc.shr_trkfit_gap10_dedx_max, _event_mc.tksh_distance);
	    }
	    

	    // fill testing plot
	    /*
	    // primary
	    if (_event_mc.trk_bkt_pdg == 2212 && _event_mc.primaryTrackPionlike) {
	    	hist2D_bg->Fill(_event_mc.trk_bragg_pion_max, _event_mc.trk_bragg_mip_max);
	    }
	    if ((_event_mc.trk_bkt_pdg == 211 || _event_mc.trk_bkt_pdg == -211) && _event_mc.primaryTrackPionlike) {
	    	hist2D->Fill(_event_mc.trk_bragg_pion_max, _event_mc.trk_bragg_mip_max);
	    }
	    // secondary
	    if (_event_mc.trk2_bkt_pdg == 2212 && _event_mc.secondaryTrackPionlike) {
	    	hist2D_bg->Fill(_event_mc.trk2_bragg_pion_max, _event_mc.trk2_bragg_mip_max);
	    }
	    if ((_event_mc.trk2_bkt_pdg == 211 || _event_mc.trk2_bkt_pdg == -211) && _event_mc.secondaryTrackPionlike) {
	    	hist2D->Fill(_event_mc.trk2_bragg_pion_max, _event_mc.trk2_bragg_mip_max);
	    }
	    // tertiary
	    if (_event_mc.trk3_bkt_pdg == 2212 && _event_mc.tertiaryTrackPionlike) {
	    	hist2D_bg->Fill(_event_mc.trk3_bragg_pion_max, _event_mc.trk3_bragg_mip_max);
	    }
	    if ((_event_mc.trk3_bkt_pdg == 211 || _event_mc.trk3_bkt_pdg == -211) && _event_mc.secondaryTrackPionlike) {
	    	hist2D->Fill(_event_mc.trk3_bragg_pion_max, _event_mc.trk3_bragg_mip_max);
	    }
	    */
	    
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
	  	
	    
	    //if (_event_mc.n_showers_contained > 1 && _event_mc.shr2_energy > 0.07 && _event_mc.shr1shr2_angle < 90 && _event_mc.shr2_distance < 100 && _event_mc.shr2_energy != 9999) 

	    //if (_event_mc.n_showers_contained > 1 && !_event_mc.hasSplitPrimaryShower && _event_mc.shr2_energy != 9999) 

	    histStack.Fill(classification, _event_mc.shr2_energy, weight_mc);
	     	
	  	//if (_event_mc.primaryTrackPionlike) histStack.Fill(classification, _event_mc.trk_dEdx_trunk_max, weight_mc);
	    //else if (_event_mc.secondaryTrackPionlike) histStack.Fill(classification, _event_mc.trk2_dEdx_trunk_max, weight_mc);
	  	//else histStack.Fill(classification, _event_mc.trk3_dEdx_trunk_max, weight_mc);

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

	    // populate derived variables [not in ntuple]
	    _event_beamoff.populateDerivedVariables(Utility::kEXT);

	    // apply reconstruction recovery algorithms
	    _event_beamoff.applyEventRecoveryAlgorithms(Utility::kEXT);

	    // apply selection
	    // pre-selection
	    bool passPreSelection = _selection.ApplyPreSelection(_event_beamoff, Utility::kEXT);
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
	    if (!passReconstructionFailureChecks) continue;

	    // cosmic rejection
	    bool passCosmicRejection = _selection.ApplyCosmicRejection(_event_beamoff);
	    if(!passCosmicRejection) continue;  	    
	    
	    // neutral pion rejection
	    bool passNeutralPionRejection = _selection.ApplyNeutralPionRejection(_event_beamoff);
	    if(!passNeutralPionRejection) continue;

	    // proton rejection
	    bool passProtonRejection = _selection.ApplyProtonRejection(_event_beamoff, Utility::kEXT);
	    if(!passProtonRejection) continue;

	    // get event classification
	    Utility::ClassificationEnums classification = _event_beamoff.getEventClassification(Utility::kEXT);

	    // fill histogram
	    histStack.Fill(classification, _event_beamoff.trkfit, weight_beamoff);

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
	    bool passPreSelection = _selection.ApplyPreSelection(_event_dirt, Utility::kDirt);
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
	    if (!passReconstructionFailureChecks) continue;	    

	    // cosmic rejection
	    bool passCosmicRejection = _selection.ApplyCosmicRejection(_event_dirt);
	    if(!passCosmicRejection) continue;

	    // neutral pion rejection
	    bool passNeutralPionRejection = _selection.ApplyNeutralPionRejection(_event_dirt);
	    if(!passNeutralPionRejection) continue;

	    // proton rejection
	    bool passProtonRejection = _selection.ApplyProtonRejection(_event_dirt, Utility::kDirt);
	    if(!passProtonRejection) continue;

	    // get event classification
	    Utility::ClassificationEnums classification = _event_dirt.getEventClassification(Utility::kDirt);

	    // fill histogram
	    histStack.Fill(classification, _event_dirt.trkfit, weight_dirt);

	}
		
	
	
	
	histStack.PrintEventIntegrals();

	TCanvas *canv = new TCanvas("canv", "canv", 1080, 1080);
  	histStack.DrawStack(canv, Utility::kContainedFraction);
  	//histStack.PrintEventIntegrals();

  	
  	//canv->Print("plot_postCosmicImpactParameter_ShowerScore.root");
  	//canv->Print("plot_postShowerScore_HitRatio.root");
  	//canv->Print("plot_postHitRatio_LeadingShowerEnergy.root");
  	//canv->Print("plot_postNeutralPionRejection_MoliereAverage.root");
  	//canv->Print("plot_postTrackLength_TrackDistance.root");
  	canv->Print("plot_Contained.root");

  	
	
  	TCanvas *c1 = new TCanvas("c1","",200,10,1080,1080);
  	c1->cd();
  	gStyle->SetOptStat(0);
  	hist2D->Draw("COLZ");
  	
  	hist2D_bg->GetXaxis()->SetTitle("Shower dE/dx [MeV/cm]");
	hist2D_bg->GetYaxis()->SetTitle("Shower Distance [cm]");

	//hist2D_bg->GetXaxis()->SetTitle("Pion Bragg Peak Score");
	//hist2D_bg->GetYaxis()->SetTitle("MIP Bragg Peak Score");


	//hist2D->GetYaxis()->SetTitle("Mean Wiggliness [deg]");
	//hist2D->GetXaxis()->SetTitle("Mean Spacepoint Separation [cm]");
	
	
  	//hist2D->GetXaxis()->SetTitleSize(0.045);
  	//hist2D->GetYaxis()->SetTitleSize(0.045);

  	//hist2D->SetTitle("Muons");
	hist2D_bg->SetFillColor(kBlue);
  	hist2D->SetFillColor(kRed);


  	hist2D_bg->Draw("BOX");

  	c1->Modified();
  	
  	hist2D->Draw("BOX same");

  	c1->Modified();
  	
  	TLegend *leg = new TLegend(0.6,0.7,0.9,0.9, NULL,"brNDC");
	leg->AddEntry(hist2D,"Electron","f");
	leg->AddEntry(hist2D_bg,"Photon","f"); 
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