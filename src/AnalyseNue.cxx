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

int main() {

	

	// read file
	TFile *f = NULL;
  	TTree *tree = NULL;

  	std::string filename = "/Users/patrick/Data/MicroBooNE/CrossSections/samplesPandora/run1/neutrinoselection_filt_run1_overlay.root";

 	f = new TFile(filename.c_str());  
  	tree = (TTree*)f->Get("nuselection/NeutrinoSelectionFilter");

  	// initialise classes
  	Utility _utility;
  	EventContainer _event(tree, _utility);
  	Selection _selection(_utility);
  	StackedHistTool histStack("", "", 30, 0, 3, _utility);

  	// loop through events
  	int n_entries = tree->GetEntries();
  	std::cout << "Initial number events: " << n_entries << std::endl;

  	for (int e = 0; e < n_entries; e++) {
  	//for (int e = 0; e < 50000; e++) {

    	tree->GetEntry(e);

	    if ( (e != 0) && (n_entries >= 10) &&  (e % (n_entries/10) == 0) ) {
	      std::cout << Form("%i0%% Completed...\n", e / (n_entries/10));
	    }

	    // apply selection
	    bool selected = _selection.ApplySelection(_event);
	    if(!selected) continue;

	    // populate derived variables [not in ntuple]
	    //_event.populateDerivedVariables();

	    // apply pion selection
	    //bool pionselected = _selection.ApplyPionSelection(_event);
	    //if(!pionselected) continue;

	    // get event classification
	    Utility::ClassificationEnums classification = _event.getEventClassification();

	    //std::cout << _event.shr_energy << std::endl;

	    // fill histogram
	    histStack.Fill(classification, _event.shr_energy);
	}

	

	TCanvas *canv = new TCanvas("canv", "canv", 1080, 1080);
  	histStack.DrawStack(canv, Utility::kShowerEnergy);
  	histStack.PrintEventIntegrals();

  	
  	canv->Print("plot_postPionSelection_ShowerEnergy.root");


	return 0;
}