#include "../include/SelectionDriver.h"

#include <iostream>
#include <string>

#include <TFile.h>
#include <TTree.h>

#include "../include/EventContainer.h"
#include "../include/CreateTrainingTree.h"
#include "../include/Selection.h"
#include "../include/StackedHistTool.h"
#include "../include/BDTTool.h"


// Constructor
SelectionDriver::SelectionDriver(): _utility() {
	
	std::cout << "Initialising Selection Driver Class" << std::endl;

}

// ------------------------------------------------------------------------------

// Draw stacked histogram


// ------------------------------------------------------------------------------

// Run BDT selection on FHC samples
void SelectionDriver::runBDTSelectionFHC() {

	//StackedHistTool _histStack("", "", 10, 0, 1.001, _utility);
	StackedHistTool _histStack("", "", 5, 0, 5, _utility);
	BDTTool _BDTTool(true, true, true, true);
	Selection _selection(_utility);

	// ----------------- Run 1 FHC ------------------
	{
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

		    // fill histogram
		    _histStack.Fill(_event_mc.classification, _event_mc.shr2_pfpgeneration, pot_weight_mc_run1_fhc * _event_mc.weight_cv);

		    //if (_event_mc.primaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.primaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
	        //else if (_event_mc.secondaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.secondaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
	  	    //else if (_event_mc.tertiaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.tertiaryTrackBDTScorePionProton, pot_weight_mc_run1_fhc * _event_mc.weight_cv);
	  	    //else {
	  	    //	std::cout << "HERE" << std::endl;
	  	    //}

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
		    _histStack.Fill(_event_dirt.classification, _event_dirt.shr2_pfpgeneration, pot_weight_dirt_run1_fhc * _event_dirt.weight_cv);

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

		    if (_event_beamoff.run > 6748) continue; // FHC era only

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_beamoff, _BDTTool, Utility::kEXT, Utility::kRun1a);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_beamoff.classification, _event_beamoff.shr2_pfpgeneration, pot_weight_beamoff_run1_fhc * _event_beamoff.weight_cv);

		    //if (_event_beamoff.primaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.primaryTrackBDTScorePionProton, pot_weight_beamoff_run1_fhc * _event_beamoff.weight_cv);
	        //else if (_event_beamoff.secondaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.secondaryTrackBDTScorePionProton, pot_weight_beamoff_run1_fhc * _event_beamoff.weight_cv);
	  	    //else _histStack.Fill(_event_beamoff.classification, _event_beamoff.tertiaryTrackBDTScorePionProton, pot_weight_beamoff_run1_fhc * _event_beamoff.weight_cv);
		}

		delete f_beamoff;
	}
	
	/*
	// ----------------- Run 2a FHC ------------------
	{
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

		    // fill histogram
		    _histStack.Fill(_event_mc.classification, _event_mc.shr2_pfpgeneration, pot_weight_mc_run2a_fhc * _event_mc.weight_cv);

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
		    _histStack.Fill(_event_dirt.classification, _event_dirt.shr2_pfpgeneration, pot_weight_dirt_run2a_fhc * _event_dirt.weight_cv); 

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
		    _histStack.Fill(_event_beamoff.classification, _event_beamoff.shr2_pfpgeneration, pot_weight_beamoff_run2a_fhc * _event_beamoff.weight_cv);

		    //if (_event_beamoff.primaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.primaryTrackBDTScorePionProton, pot_weight_beamoff_run2a_fhc * _event_beamoff.weight_cv);
	        //else if (_event_beamoff.secondaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.secondaryTrackBDTScorePionProton, pot_weight_beamoff_run2a_fhc * _event_beamoff.weight_cv);
	  	    //else _histStack.Fill(_event_beamoff.classification, _event_beamoff.tertiaryTrackBDTScorePionProton, pot_weight_beamoff_run2a_fhc * _event_beamoff.weight_cv);
		}

		delete f_beamoff;
	}
	
	// ----------------- Run 4c FHC ------------------
	{
		// --- Nu Overlay MC ---	
		// read file
		TFile *f_mc = NULL;
	  	TTree *tree_mc = NULL;
	 	f_mc = new TFile(filename_mc_run4c_fhc.c_str());  
	  	tree_mc = (TTree*)f_mc->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_mc(tree_mc, _utility); 	

	  	// loop through events
	  	int n_entries_mc = tree_mc->GetEntries();
	  	std::cout << "Initial number events [Run 4c FHC Nu Overlay]: " << n_entries_mc << std::endl;

	  	for (int e = 0; e < n_entries_mc; e++) {
	  		
	    	tree_mc->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_mc >= 10) &&  (e % (n_entries_mc/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_mc/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_mc, _BDTTool, Utility::kMC, Utility::kRun4c);
		    if (!passSelection) continue;	    	

		    // fill histogram
		    _histStack.Fill(_event_mc.classification, _event_mc.shr2_pfpgeneration, pot_weight_mc_run4c_fhc * _event_mc.weight_cv);

		    //if (_event_mc.primaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.primaryTrackBDTScorePionProton, pot_weight_mc_run4c_fhc * _event_mc.weight_cv);
	        //else if (_event_mc.secondaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.secondaryTrackBDTScorePionProton, pot_weight_mc_run4c_fhc * _event_mc.weight_cv);
	  	    //else _histStack.Fill(_event_mc.classification, _event_mc.tertiaryTrackBDTScorePionProton, pot_weight_mc_run4c_fhc * _event_mc.weight_cv);

		}

		delete f_mc;

		// --- Dirt Overlay MC ---
		// read file
		TFile *f_dirt = NULL;
	  	TTree *tree_dirt = NULL;
	 	f_dirt = new TFile(filename_dirt_run4c_fhc.c_str());  
	  	tree_dirt = (TTree*)f_dirt->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_dirt(tree_dirt, _utility); 	

	  	// loop through events
	  	int n_entries_dirt = tree_dirt->GetEntries();
	  	std::cout << "Initial number events [Run 4c FHC Dirt Overlay]: " << n_entries_dirt << std::endl;

	  	for (int e = 0; e < n_entries_dirt; e++) {

	    	tree_dirt->GetEntry(e);

		    if ( (e != 0) && (n_entries_dirt >= 10) &&  (e % (n_entries_dirt/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_dirt/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_dirt, _BDTTool, Utility::kDirt, Utility::kRun4c);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_dirt.classification, _event_dirt.shr2_pfpgeneration, pot_weight_dirt_run4c_fhc * _event_dirt.weight_cv); 

		    //if (_event_dirt.primaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.primaryTrackBDTScorePionProton, pot_weight_dirt_run4c_fhc * _event_dirt.weight_cv);
	        //else if (_event_dirt.secondaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.secondaryTrackBDTScorePionProton, pot_weight_dirt_run4c_fhc * _event_dirt.weight_cv);
	  	    //else _histStack.Fill(_event_dirt.classification, _event_dirt.tertiaryTrackBDTScorePionProton, pot_weight_dirt_run4c_fhc * _event_dirt.weight_cv);
		}

		delete f_dirt;
	
		// --- Beam Off ---
		// read file
		TFile *f_beamoff = NULL;
	  	TTree *tree_beamoff = NULL;
	 	f_beamoff = new TFile(filename_beamoff_run4c_fhc.c_str());  
	  	tree_beamoff = (TTree*)f_beamoff->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_beamoff(tree_beamoff, _utility); 	

	  	// loop through events
	  	int n_entries_beamoff = tree_beamoff->GetEntries();
	  	std::cout << "Initial number events [Run 4c FHC Beam Off]: " << n_entries_beamoff << std::endl;

	  	for (int e = 0; e < n_entries_beamoff; e++) {

	    	tree_beamoff->GetEntry(e);

		    if ( (e != 0) && (n_entries_beamoff >= 10) &&  (e % (n_entries_beamoff/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_beamoff/10));
		    }

		    if (_event_beamoff.run < 21411) continue; // FHC part only

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_beamoff, _BDTTool, Utility::kEXT, Utility::kRun4c);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_beamoff.classification, _event_beamoff.shr2_pfpgeneration, pot_weight_beamoff_run4c_fhc * _event_beamoff.weight_cv);

		    //if (_event_beamoff.primaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.primaryTrackBDTScorePionProton, pot_weight_beamoff_run4c_fhc * _event_beamoff.weight_cv);
	        //else if (_event_beamoff.secondaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.secondaryTrackBDTScorePionProton, pot_weight_beamoff_run4c_fhc * _event_beamoff.weight_cv);
	  	    //else _histStack.Fill(_event_beamoff.classification, _event_beamoff.tertiaryTrackBDTScorePionProton, pot_weight_beamoff_run4c_fhc * _event_beamoff.weight_cv);
		}

		delete f_beamoff;
	}
	*/

	/*
	// ----------------- Run 4d FHC ------------------
	{
		// --- Nu Overlay MC ---	
		// read file
		TFile *f_mc = NULL;
	  	TTree *tree_mc = NULL;
	 	f_mc = new TFile(filename_mc_run4d_fhc.c_str());  
	  	tree_mc = (TTree*)f_mc->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_mc(tree_mc, _utility); 	

	  	// loop through events
	  	int n_entries_mc = tree_mc->GetEntries();
	  	std::cout << "Initial number events [Run 4d FHC Nu Overlay]: " << n_entries_mc << std::endl;

	  	for (int e = 0; e < n_entries_mc; e++) {
	  		
	    	tree_mc->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_mc >= 10) &&  (e % (n_entries_mc/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_mc/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_mc, _BDTTool, Utility::kMC, Utility::kRun4d);
		    if (!passSelection) continue;	    	

		    // fill histogram
		    _histStack.Fill(_event_mc.classification, _event_mc.BDTScoreElectronPhoton, pot_weight_mc_run4d_fhc * _event_mc.weight_cv);

		}

		delete f_mc;

		// --- Dirt Overlay MC ---
		// read file
		TFile *f_dirt = NULL;
	  	TTree *tree_dirt = NULL;
	 	f_dirt = new TFile(filename_dirt_run4d_fhc.c_str());  
	  	tree_dirt = (TTree*)f_dirt->Get("nuselection/NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_dirt(tree_dirt, _utility); 	

	  	// loop through events
	  	int n_entries_dirt = tree_dirt->GetEntries();
	  	std::cout << "Initial number events [Run 4d FHC Dirt Overlay]: " << n_entries_dirt << std::endl;

	  	for (int e = 0; e < n_entries_dirt; e++) {

	    	tree_dirt->GetEntry(e);

		    if ( (e != 0) && (n_entries_dirt >= 10) &&  (e % (n_entries_dirt/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_dirt/10));
		    }

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_dirt, _BDTTool, Utility::kDirt, Utility::kRun4d);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_dirt.classification, _event_dirt.BDTScoreElectronPhoton, pot_weight_dirt_run4d_fhc * _event_dirt.weight_cv); 
		}

		delete f_dirt;
	}
	*/
	
	/*
	// ----------------- Run 5 FHC ------------------
	{
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

		    if (_event_mc.run >= 25447 && _event_mc.run <= 25512) continue; // run 5 zero lifetime period

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_mc, _BDTTool, Utility::kMC, Utility::kRun5);
		    if (!passSelection) continue;	    	

		    // fill histogram
		    _histStack.Fill(_event_mc.classification, _event_mc.BDTScoreElectronPhoton, pot_weight_mc_run5_fhc * _event_mc.weight_cv);

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

		    if (_event_dirt.run >= 25447 && _event_dirt.run <= 25512) continue; // run 5 zero lifetime period

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_dirt, _BDTTool, Utility::kDirt, Utility::kRun5);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_dirt.classification, _event_dirt.BDTScoreElectronPhoton, pot_weight_dirt_run5_fhc * _event_dirt.weight_cv); 
		}

		delete f_dirt;
	}
	*/
	

	// print event integrals
	_histStack.PrintEventIntegrals();

	TCanvas *canv = new TCanvas("canv", "canv", 1080, 1080);
  	//_histStack.DrawStack(canv, Utility::kElectronNeutralPionBDT);
  	//canv->Print("plot_electronPhoton_BDTScore_FHC.root");

  	_histStack.DrawStack(canv, Utility::kSecondShowerPFPGeneration);
  	canv->Print("plot_SecondShowerPFPGeneration.root");
}

// ------------------------------------------------------------------------------

// Run BDT selection on RHC samples
void SelectionDriver::runBDTSelectionRHC() {

	StackedHistTool _histStack("", "", 10, 0, 1.001, _utility);
	//StackedHistTool _histStack("", "", 2, 0, 2, _utility);
	//StackedHistTool _histStack("", "", 20, 0, 100, _utility);
	BDTTool _BDTTool(true, true, true, true);
	Selection _selection(_utility);

	
	// ----------------- Run 1 RHC ------------------
	{
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

		    // fill histogram
		    //_histStack.Fill(_event_mc.classification, _event_mc.BDTScoreElectronPhoton, pot_weight_mc_run1_rhc * _event_mc.weight_cv);

		    if (_event_mc.primaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.primaryTrackBDTScorePionProton, pot_weight_mc_run1_rhc * _event_mc.weight_cv);
	        else if (_event_mc.secondaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.secondaryTrackBDTScorePionProton, pot_weight_mc_run1_rhc * _event_mc.weight_cv);
	  	    else if (_event_mc.tertiaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.tertiaryTrackBDTScorePionProton, pot_weight_mc_run1_rhc * _event_mc.weight_cv);
	  	    else std::cout << "HERE" << std::endl;	

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
		    //_histStack.Fill(_event_dirt.classification, _event_dirt.BDTScoreElectronPhoton, pot_weight_dirt_run1_rhc * _event_dirt.weight_cv);

		    if (_event_dirt.primaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.primaryTrackBDTScorePionProton, pot_weight_dirt_run1_rhc * _event_dirt.weight_cv);
	        else if (_event_dirt.secondaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.secondaryTrackBDTScorePionProton, pot_weight_dirt_run1_rhc * _event_dirt.weight_cv);
	  	    else _histStack.Fill(_event_dirt.classification, _event_dirt.tertiaryTrackBDTScorePionProton, pot_weight_dirt_run1_rhc * _event_dirt.weight_cv); 
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

		    if (_event_beamoff.run <= 6748) continue; // RHC era only

		    bool passSelection = _selection.ApplyBDTBasedSelection(_event_beamoff, _BDTTool, Utility::kEXT, Utility::kRun1b);
		    if (!passSelection) continue;

		    // fill histogram
		    //_histStack.Fill(_event_beamoff.classification, _event_beamoff.BDTScoreElectronPhoton, pot_weight_beamoff_run1_rhc * _event_beamoff.weight_cv);

		    if (_event_beamoff.primaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.primaryTrackBDTScorePionProton, pot_weight_beamoff_run1_rhc * _event_beamoff.weight_cv);
	        else if (_event_beamoff.secondaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.secondaryTrackBDTScorePionProton, pot_weight_beamoff_run1_rhc * _event_beamoff.weight_cv);
	  	    else _histStack.Fill(_event_beamoff.classification, _event_beamoff.tertiaryTrackBDTScorePionProton, pot_weight_beamoff_run1_rhc * _event_beamoff.weight_cv);
		}
		

		delete f_beamoff;
		

	}
	

	
	// ----------------- Run 2b RHC ------------------
	{
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

		    // fill histogram
		    //_histStack.Fill(_event_mc.classification, _event_mc.BDTScoreElectronPhoton, pot_weight_mc_run2b_rhc * _event_mc.weight_cv);

		    if (_event_mc.primaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.primaryTrackBDTScorePionProton, pot_weight_mc_run2b_rhc * _event_mc.weight_cv);
	        else if (_event_mc.secondaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.secondaryTrackBDTScorePionProton, pot_weight_mc_run2b_rhc * _event_mc.weight_cv);
	  	    else _histStack.Fill(_event_mc.classification, _event_mc.tertiaryTrackBDTScorePionProton, pot_weight_mc_run2b_rhc * _event_mc.weight_cv);

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
		    //_histStack.Fill(_event_dirt.classification, _event_dirt.BDTScoreElectronPhoton, pot_weight_dirt_run2b_rhc * _event_dirt.weight_cv);

		    if (_event_dirt.primaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.primaryTrackBDTScorePionProton, pot_weight_dirt_run2b_rhc * _event_dirt.weight_cv);
	        else if (_event_dirt.secondaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.secondaryTrackBDTScorePionProton, pot_weight_dirt_run2b_rhc * _event_dirt.weight_cv);
	  	    else _histStack.Fill(_event_dirt.classification, _event_dirt.tertiaryTrackBDTScorePionProton, pot_weight_dirt_run2b_rhc * _event_dirt.weight_cv); 
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
		    //_histStack.Fill(_event_beamoff.classification, _event_beamoff.BDTScoreElectronPhoton, pot_weight_beamoff_run2b_rhc * _event_beamoff.weight_cv);

		    if (_event_beamoff.primaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.primaryTrackBDTScorePionProton, pot_weight_beamoff_run2b_rhc * _event_beamoff.weight_cv);
	        else if (_event_beamoff.secondaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.secondaryTrackBDTScorePionProton, pot_weight_beamoff_run2b_rhc * _event_beamoff.weight_cv);
	  	    else _histStack.Fill(_event_beamoff.classification, _event_beamoff.tertiaryTrackBDTScorePionProton, pot_weight_beamoff_run2b_rhc * _event_beamoff.weight_cv);
		}

		delete f_beamoff;
		
	}
	
	
	
	// ----------------- Run 3b RHC ------------------
	{
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

		    // fill histogram
		    //_histStack.Fill(_event_mc.classification, _event_mc.BDTScoreElectronPhoton, pot_weight_mc_run3b_rhc * _event_mc.weight_cv);

		    if (_event_mc.primaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.primaryTrackBDTScorePionProton, pot_weight_mc_run3b_rhc * _event_mc.weight_cv);
	        else if (_event_mc.secondaryTrackPionlikeLoose) _histStack.Fill(_event_mc.classification, _event_mc.secondaryTrackBDTScorePionProton, pot_weight_mc_run3b_rhc * _event_mc.weight_cv);
	  	    else _histStack.Fill(_event_mc.classification, _event_mc.tertiaryTrackBDTScorePionProton, pot_weight_mc_run3b_rhc * _event_mc.weight_cv);

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
		    //_histStack.Fill(_event_dirt.classification, _event_dirt.BDTScoreElectronPhoton, pot_weight_dirt_run3b_rhc * _event_dirt.weight_cv);

		    if (_event_dirt.primaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.primaryTrackBDTScorePionProton, pot_weight_dirt_run3b_rhc * _event_dirt.weight_cv);
	        else if (_event_dirt.secondaryTrackPionlikeLoose) _histStack.Fill(_event_dirt.classification, _event_dirt.secondaryTrackBDTScorePionProton, pot_weight_dirt_run3b_rhc * _event_dirt.weight_cv);
	  	    else _histStack.Fill(_event_dirt.classification, _event_dirt.tertiaryTrackBDTScorePionProton, pot_weight_dirt_run3b_rhc * _event_dirt.weight_cv);  
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
		    //_histStack.Fill(_event_beamoff.classification, _event_beamoff.BDTScoreElectronPhoton, pot_weight_beamoff_run3b_rhc * _event_beamoff.weight_cv);

		    if (_event_beamoff.primaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.primaryTrackBDTScorePionProton, pot_weight_beamoff_run3b_rhc * _event_beamoff.weight_cv);
	        else if (_event_beamoff.secondaryTrackPionlikeLoose) _histStack.Fill(_event_beamoff.classification, _event_beamoff.secondaryTrackBDTScorePionProton, pot_weight_beamoff_run3b_rhc * _event_beamoff.weight_cv);
	  	    else _histStack.Fill(_event_beamoff.classification, _event_beamoff.tertiaryTrackBDTScorePionProton, pot_weight_beamoff_run3b_rhc * _event_beamoff.weight_cv);
		}

		delete f_beamoff;

	}
	
	
	
	
	// print event integrals
	_histStack.PrintEventIntegrals();

	TCanvas *canv = new TCanvas("canv", "canv", 1080, 1080);
  	//_histStack.DrawStack(canv, Utility::kPionProtonBDT);
  	//canv->Print("plot_pionProton_BDTScore_RHC.root");
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
	 	f_intrinsic = new TFile(filename_intrinsic_run1_fhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 1 FHC Intrinsic Nue Overlay]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyElectronPhotonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun1a);
		    if (!passSelection) continue;

		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_run1_fhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
		    // electron-photon
		    if (_event_intrinsic.classification == Utility::kCCNue1pi0p || _event_intrinsic.classification == Utility::kCCNue1piNp 
		    	//|| _event_intrinsic.classification == Utility::kCCNueNpi || _event_intrinsic.classification == Utility::kCCNueNp
		    	) _trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
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
	  	std::cout << "Initial number events [Run 1 FHC CC/NC Pi0 Overlay]: " << n_entries_ccncpizero << std::endl;
	  	
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
	 	f_intrinsic = new TFile(filename_intrinsic_run2a_fhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 2a FHC Intrinsic Nue Overlay]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyElectronPhotonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun2a);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_run2a_fhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
		    // electron-photon
		    if (_event_intrinsic.classification == Utility::kCCNue1pi0p || _event_intrinsic.classification == Utility::kCCNue1piNp 
		    	//|| _event_intrinsic.classification == Utility::kCCNueNpi || _event_intrinsic.classification == Utility::kCCNueNp
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
	 	f_intrinsic = new TFile(filename_intrinsic_run1_rhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 1 RHC Intrinsic Nue Overlay]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyElectronPhotonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun1b);
		    if (!passSelection) continue;

		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_run1_rhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
		    // electron-photon
		    if (_event_intrinsic.classification == Utility::kCCNue1pi0p || _event_intrinsic.classification == Utility::kCCNue1piNp 
		    	//|| _event_intrinsic.classification == Utility::kCCNueNpi || _event_intrinsic.classification == Utility::kCCNueNp
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
	 	f_intrinsic = new TFile(filename_intrinsic_run2b_rhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 2b RHC Intrinsic Nue Overlay]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyElectronPhotonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun2b);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_run2b_rhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
		    // electron-photon
		    if (_event_intrinsic.classification == Utility::kCCNue1pi0p || _event_intrinsic.classification == Utility::kCCNue1piNp 
		    	//|| _event_intrinsic.classification == Utility::kCCNueNpi || _event_intrinsic.classification == Utility::kCCNueNp
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
	 	f_intrinsic = new TFile(filename_intrinsic_run3b_rhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 3b RHC Intrinsic Nue Overlay]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyElectronPhotonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun3b);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_run3b_rhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
		    // electron-photon
		    if (_event_intrinsic.classification == Utility::kCCNue1pi0p || _event_intrinsic.classification == Utility::kCCNue1piNp 
		    	//|| _event_intrinsic.classification == Utility::kCCNueNpi || _event_intrinsic.classification == Utility::kCCNueNp
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
	  	std::cout << "Initial number events [Run 3b RHC CC/NC Pi0 Overlay]: " << n_entries_ccncpizero << std::endl;
	  	
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

	// print event integrals
	_histStack.PrintEventIntegrals();

	// write training tree
	_trainingTree.writeOutputFile();
}

// ------------------------------------------------------------------------------

// Create training tree for pion-proton BDT FHC
void SelectionDriver::createPionProtonBDTTrainingTreeFHC() {
	
	StackedHistTool _histStack("", "", 20, 0, 1.001, _utility);
	BDTTool _BDTTool(true, true, true, true);
	Selection _selection(_utility);
	CreateTrainingTree _trainingTree(Utility::kPionProton);

	// ----------------- Run 1 FHC ------------------
	{
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_run1_fhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 1 FHC Intrinsic Nue Overlay]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun1a);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_run1_fhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
			_trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;

		/*
		// --- Nu Overlay MC --
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
	  		
	    	tree_mc->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_mc >= 10) &&  (e % (n_entries_mc/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_mc/10));
		    }

		    bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_mc, Utility::kMC, Utility::kRun1a);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_mc.classification, _event_mc.contained_fraction, pot_weight_mc_run1_fhc * _event_mc.weight_cv);

	    	// muon neutrinos without pi0 only to avoid bias 
	    	if ((_event_mc.nu_pdg == 14 || _event_mc.nu_pdg == -14) && _event_mc.npi0 == 0) _trainingTree.addEvent(_event_mc, _event_mc.classification);
		}

		delete f_mc;
		*/

	}

	// ----------------- Run 2a FHC ------------------
	{
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_run2a_fhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 2a FHC Intrinsic Nue Overlay]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun2a);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_run2a_fhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
			_trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;

		/*
		// --- Nu Overlay MC --
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

		    bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_mc, Utility::kMC, Utility::kRun2a);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_mc.classification, _event_mc.contained_fraction, pot_weight_mc_run2a_fhc * _event_mc.weight_cv);

	    	// muon neutrinos without pi0 only to avoid bias 
	    	if ((_event_mc.nu_pdg == 14 || _event_mc.nu_pdg == -14) && _event_mc.npi0 == 0) _trainingTree.addEvent(_event_mc, _event_mc.classification);
		}

		delete f_mc;
		*/

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
	BDTTool _BDTTool(true, true, true, true);
	Selection _selection(_utility);
	CreateTrainingTree _trainingTree(Utility::kPionProton);

	// ----------------- Run 1 RHC ------------------
	{
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_run1_rhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 1 RHC Intrinsic Nue Overlay]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun1b);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_run1_rhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
			_trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;

		/*
		// --- Nu Overlay MC --
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

		    bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_mc, Utility::kMC, Utility::kRun1b);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_mc.classification, _event_mc.contained_fraction, pot_weight_mc_run1_rhc * _event_mc.weight_cv);

	    	// muon neutrinos without pi0 only to avoid bias 
	    	if ((_event_mc.nu_pdg == 14 || _event_mc.nu_pdg == -14) && _event_mc.npi0 == 0) _trainingTree.addEvent(_event_mc, _event_mc.classification);
		}

		delete f_mc;
		*/
	}

	// ----------------- Run 2b RHC ------------------
	{
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_run2b_rhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 2b RHC Intrinsic Nue Overlay]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun2b);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_run2b_rhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
			_trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;

		/*
		// --- Nu Overlay MC --
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

		    bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_mc, Utility::kMC, Utility::kRun2b);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_mc.classification, _event_mc.contained_fraction, pot_weight_mc_run2b_rhc * _event_mc.weight_cv);

	    	// muon neutrinos without pi0 only to avoid bias 
	    	if ((_event_mc.nu_pdg == 14 || _event_mc.nu_pdg == -14) && _event_mc.npi0 == 0) _trainingTree.addEvent(_event_mc, _event_mc.classification);
		}

		delete f_mc;
		*/
	}

	// ----------------- Run 3b RHC ------------------
	{
		// --- Intrinsic Nue Overlay MC -- 
	  	// read file
		TFile *f_intrinsic = NULL;
	  	TTree *tree_intrinsic = NULL;
	 	f_intrinsic = new TFile(filename_intrinsic_run3b_rhc.c_str());  
	  	tree_intrinsic = (TTree*)f_intrinsic->Get("NeutrinoSelectionFilter");
	  	
	  	// initialise event container
	  	EventContainer _event_intrinsic(tree_intrinsic, _utility); 	

	  	// loop through events
	  	int n_entries_intrinsic = tree_intrinsic->GetEntries();
	  	std::cout << "Initial number events [Run 3b RHC Intrinsic Nue Overlay]: " << n_entries_intrinsic << std::endl;

	  	for (int e = 0; e < n_entries_intrinsic; e++) {
	  		
	    	tree_intrinsic->GetEntry(e);    	

		    if ( (e != 0) && (n_entries_intrinsic >= 10) &&  (e % (n_entries_intrinsic/10) == 0) ) {
		      std::cout << Form("%i0%% Completed...\n", e / (n_entries_intrinsic/10));
		    }

		    bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_intrinsic, Utility::kIntrinsic, Utility::kRun3b);
		    if (!passSelection) continue;
		    
		    _histStack.Fill(_event_intrinsic.classification, _event_intrinsic.contained_fraction, pot_weight_intrinsic_run3b_rhc * _event_intrinsic.weight_cv);
		    
		    // add event to training tree
			_trainingTree.addEvent(_event_intrinsic, _event_intrinsic.classification);
		}

		delete f_intrinsic;

		/*
		// --- Nu Overlay MC --
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

		    bool passSelection = _selection.ApplyPionProtonBDTTrainingSelection(_event_mc, Utility::kMC, Utility::kRun3b);
		    if (!passSelection) continue;

		    // fill histogram
		    _histStack.Fill(_event_mc.classification, _event_mc.contained_fraction, pot_weight_mc_run3b_rhc * _event_mc.weight_cv);

	    	// muon neutrinos without pi0 only to avoid bias 
	    	if ((_event_mc.nu_pdg == 14 || _event_mc.nu_pdg == -14) && _event_mc.npi0 == 0) _trainingTree.addEvent(_event_mc, _event_mc.classification);
		}

		delete f_mc;
		*/
	}

	// print event integrals
	_histStack.PrintEventIntegrals();

	// write training tree
	_trainingTree.writeOutputFile();
}

