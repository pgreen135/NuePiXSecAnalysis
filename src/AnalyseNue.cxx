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
    std::string filename_mc = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1_reprocessed/neutrinoselection_filt_run1_overlay_integration.root";
	//std::string filename_mc = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1/neutrinoselection_filt_run1_overlay.root";
	std::string filename_dirt = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1/neutrinoselection_filt_run1_dirt_overlay.root";
	std::string filename_beamoff = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1/neutrinoselection_filt_run1_beamoff.root";

	// Weights [Run 1]
	//double weight_mc = 1;		// POT_beam-on / POT_mc
	double weight_mc = 0.0855;			// POT_beam-on / POT_mc   // Re-processed files, POT 2.33827e+21 [new]
	//double weight_mc = 0.0856;		// POT_beam-on / POT_mc   // Krishan's files, POT 2.33652e+21
	double weight_dirt = 0.1407;	// POT_beam-on / POT_dirt
	double weight_beamoff = 0.5612; // 0.98 * HW_beam-on / HW_beam-off

	// Initialise Classes
  	Utility _utility;
  	Selection _selection(_utility);
  	StackedHistTool histStack("", "", 24, -0.1, 1.1, _utility);

  	// Testing histogram
  	TH1F *hist_sig = new TH1F("", "", 20, 0, 20);
  	TH1F *hist_bg = new TH1F("", "", 20, 0, 20);
  	
  	TH2F *hist2D = new TH2F("", "", 20, 0, 10, 15, 0, 15);
  	TH2F *hist2D_bg = new TH2F("", "", 20, 0, 10, 15, 0, 15);
	
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

	    // populate derived variables [not in ntuples]
	    _event_mc.populateDerivedVariables(Utility::kMC);

	    // reconstruction completeness (separated out from pre-selection to avoid calculating derived variables for all events)
	    bool passReconstructionCompletenessCheck = _selection.ApplyReconstructionCompletenessCheck(_event_mc);
	    if(!passReconstructionCompletenessCheck) continue;

	    // electron selection
	    bool passElectronSelection = _selection.ApplyElectronSelection(_event_mc);
	    if(!passElectronSelection) continue;

	    // apply pion selection
	    bool passPionSelection = _selection.ApplyPionSelection(_event_mc, Utility::kMC);
	    if(!passPionSelection) continue;

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

	    /*
		// fill testing plot 
	    if(classification == Utility::kCCNue1piNp || classification == Utility::kCCNue1pi0p) {
	    	hist2D->Fill(_event_mc.shr_trkfit_gap10_dedx_max, _event_mc.shr_distance);
	    }
	    else if (classification == Utility::kCCNumupizero || classification == Utility::kNCpizero) {
	    	hist2D_bg->Fill(_event_mc.shr_trkfit_gap10_dedx_max, _event_mc.shr_distance);
	    }
	    */

	    // fill histogram
	    //if (_event_mc.trk2_llr_pid_score == 9999)  histStack.Fill(classification, _event_mc.trk_llr_pid_score, weight_mc);
	    //else if (_event_mc.trk2_llr_pid_score > _event_mc.trk_llr_pid_score && _event_mc.trk2_len >= 10 && _event_mc.trk2_distance <= 5 && _event_mc.trk2_score >= 0.8 && _event_mc.trk2_score <= 1.1) histStack.Fill(classification, _event_mc.trk2_llr_pid_score, weight_mc);
	    //else histStack.Fill(classification, _event_mc.trk_llr_pid_score, weight_mc);

	    // fill histograms
	    // primary track
	    // muon
	    //if ((_event_mc.trk_bkt_pdg == 13 || _event_mc.trk_bkt_pdg == -13) && _event_mc.primaryTrackValid) hist2D_bg->Fill(_event_mc.trk_avg_deflection_separation_mean, _event_mc.trk_avg_deflection_mean);
	    // proton
	    if (_event_mc.trk_bkt_pdg == 2212 && _event_mc.primaryTrackValid) hist_bg->Fill(_event_mc.trk_dEdx_trunk_max);
	    // pion
	    if ((_event_mc.trk_bkt_pdg == 211 || _event_mc.trk_bkt_pdg == -211) && _event_mc.primaryTrackValid) hist_sig->Fill(_event_mc.trk_dEdx_trunk_max);
	    //if ((_event_mc.trk_bkt_pdg == 211 || _event_mc.trk_bkt_pdg == -211) && _event_mc.primaryTrackValid) hist2D->Fill(_event_mc.trk_avg_deflection_separation_mean, _event_mc.trk_avg_deflection_mean);
	    
	    // secondary track
	    // proton
	    if (_event_mc.trk2_bkt_pdg == 2212 && _event_mc.secondaryTrackValid) hist_bg->Fill(_event_mc.trk2_dEdx_trunk_max);
	    // pion
	    if ((_event_mc.trk2_bkt_pdg == 211 || _event_mc.trk2_bkt_pdg == -211) && _event_mc.secondaryTrackValid) hist_sig->Fill(_event_mc.trk2_dEdx_trunk_max);
	  	
	  	//if (_event_mc.secondshower_V_nhit > 50 && _event_mc.secondshower_V_vtxdist < 100 && _event_mc.secondshower_V_anglediff != 9999) {
		histStack.Fill(classification, _event_mc.associated_hits_fraction_u, weight_mc);
		//    std::cout << "Passing Event: Run " << _event_mc.run << ", Subrun " << _event_mc.sub << ", Event " << _event_mc.evt << " --- Topology: " << histStack.topologyenum2str(classification) << std::endl;
	    //	
		//	std::cout << _event_mc.secondshower_V_anglediff << std::endl;
		//}
	  	
	  	//if (_event_mc.primaryTrackPionlike) histStack.Fill(classification, _event_mc.trk_dEdx_trunk_max, weight_mc);
	  	//else histStack.Fill(classification, _event_mc.trk2_dEdx_trunk_max, weight_mc);

	    
	   	/*
	    if (_event_mc.classification == Utility::kCCNue1pi0p || _event_mc.classification == Utility::kCCNue1piNp) {
	    	std::cout << "Passing Event: Run " << _event_mc.run << ", Subrun " << _event_mc.sub << ", Event " << _event_mc.evt << " --- Topology: " << histStack.topologyenum2str(classification) << std::endl;
	    	std::cout << "Number Pions: " << _event_mc.npion << ", Energies: " << std::endl;
	    	for (unsigned int i = 0; i < (_event_mc.mc_pdg_v)->size(); i++) {
	    		if ((_event_mc.mc_pdg_v)->at(i) == 211 || (_event_mc.mc_pdg_v)->at(i) == -211) std::cout << (_event_mc.mc_E_v)->at(i) << std::endl; 
	    	}
		}
		*/

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

	    // apply selection
	    // pre-selection
	    bool passPreSelection = _selection.ApplyPreSelection(_event_beamoff, Utility::kEXT);
	    if(!passPreSelection) continue;

	    // populate derived variables [not in ntuple]
	    _event_beamoff.populateDerivedVariables(Utility::kEXT);

	    // reconstruction completeness (separated out from pre-selection to avoid calculating derived variables for all events)
	    bool passReconstructionCompletenessCheck = _selection.ApplyReconstructionCompletenessCheck(_event_beamoff);
	    if(!passReconstructionCompletenessCheck) continue;

	    // electron identification
	    bool passElectronIdentification = _selection.ApplyElectronSelection(_event_beamoff);
	    if(!passElectronIdentification) continue;

	    // apply pion selection
	    bool passPionSelection = _selection.ApplyPionSelection(_event_beamoff, Utility::kEXT);
	    if(!passPionSelection) continue;

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
	    histStack.Fill(classification, _event_beamoff.associated_hits_fraction, weight_beamoff);

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

	    // populate derived variables [not in ntuple]
	    _event_dirt.populateDerivedVariables(Utility::kDirt);

	    // reconstruction completeness (separated out from pre-selection to avoid calculating derived variables for all events)
	    bool passReconstructionCompletenessCheck = _selection.ApplyReconstructionCompletenessCheck(_event_dirt);
	    if(!passReconstructionCompletenessCheck) continue;

	    // electron identification
	    bool passElectronIdentification = _selection.ApplyElectronSelection(_event_dirt);
	    if(!passElectronIdentification) continue;

	    // apply pion selection
	    bool passPionSelection = _selection.ApplyPionSelection(_event_dirt, Utility::kDirt);
	    if(!passPionSelection) continue;	    

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
	    histStack.Fill(classification, _event_dirt.associated_hits_fraction, weight_dirt);

	}
	
	*/
	
	
	histStack.PrintEventIntegrals();

	TCanvas *canv = new TCanvas("canv", "canv", 1080, 1080);
  	histStack.DrawStack(canv, Utility::kAssociatedHitsFraction);
  	//histStack.PrintEventIntegrals();

  	
  	//canv->Print("plot_postCosmicImpactParameter_ShowerScore.root");
  	//canv->Print("plot_postShowerScore_HitRatio.root");
  	//canv->Print("plot_postHitRatio_LeadingShowerEnergy.root");
  	//canv->Print("plot_postNeutralPionRejection_MoliereAverage.root");
  	//canv->Print("plot_postTrackLength_TrackDistance.root");
  	canv->Print("plot_Contained.root");

  	
  	/*
  	TCanvas *c1 = new TCanvas("c1","",200,10,1080,1080);
  	c1->cd();
  	gStyle->SetOptStat(0);
  	//hist2D->Draw("COLZ");
  	
  	hist2D_bg->GetXaxis()->SetTitle("Shower dE/dx [MeV/cm]");
	hist2D_bg->GetYaxis()->SetTitle("Shower Distance [cm]");

	//hist2D->GetYaxis()->SetTitle("Mean Wiggliness [deg]");
	//hist2D->GetXaxis()->SetTitle("Mean Spacepoint Separation [cm]");
	
	
  	//hist2D->GetXaxis()->SetTitleSize(0.045);
  	//hist2D->GetYaxis()->SetTitleSize(0.045);

  	//hist2D->SetTitle("Muons");

  	hist2D_bg->SetFillColor(kBlue);
  	hist2D_bg->Draw("BOX");

  	c1->Modified();
  	
  	hist2D->SetFillColor(kRed);
  	hist2D->Draw("BOX same");

  	c1->Modified();

  	TLegend *leg = new TLegend(0.6,0.7,0.9,0.9, NULL,"brNDC");
	leg->AddEntry(hist2D,"Electron","f");
	leg->AddEntry(hist2D_bg,"Photon","f"); 
	leg->Draw("same");

	c1->Modified();

	gStyle->SetOptStat(0);

  	//c1->Print("PhotonRejection_gap10_forward.root");
	*/


  	
	// normalise
	//hist_bg->Scale(1/hist_bg->GetEntries());
	//hist_sig->Scale(1/hist_sig->GetEntries());

  	
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
	

	return 0;
}