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

int main(int argc, char *argv[]) {

	// parse arguments
	if ( argc != 3 ) {
    	std::cout << "Usage: ProcessNTuple INPUT_PELEE_NTUPLE_FILE OUTPUT_FILE\n";
    	return 1;
  	}

  	std::string input_filename( argv[1] );
  	std::string output_filename( argv[2] );

  	std::cout << "Processing file: " << input_filename << std::endl;

	// Get the TTrees containing the event ntuples and subrun POT information
	// read file
	TFile *inputFile = NULL;
	TTree *eventsTree = NULL;
	TTree *subrunsTree = NULL;
	inputFile = new TFile(input_filename.c_str());  
	eventsTree = (TTree*)inputFile->Get("nuselection/NeutrinoSelectionFilter");
	subrunsTree = (TTree*)inputFile->Get("nuselection/SubRun");
    
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

	// initialise classes
	Utility _utility;
	Selection _selection(_utility);
	BDTTool _BDTTool(true, true, true, true);
	EventContainer _event(eventsTree, _utility);

	bool created_output_branches = false;
	
	// Event loop
	int n_entries = eventsTree->GetEntries();
  	std::cout << "Number events: " << n_entries << std::endl;

  	for (int e = 0; e < n_entries; e++) {
  	//for (int e = 0; e < 10000; e++) {
  		
  		// get current entry
    	eventsTree->GetEntry(e);    	

	    if ( (e != 0) && (n_entries >= 10) &&  (e % (n_entries/10) == 0) ) {
	      std::cout << Form("%i0%% Completed...\n", e / (n_entries/10));
	    }

	    // apply selection
	    // populates necessary variables to pass to stv tree
	    bool passSelection = _selection.ApplyBDTBasedSelection(_event, _BDTTool, Utility::kMC, Utility::kRun1a);	// need to figure out how to set file type and run

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
  	set_output_branch_address( out_tree, "mc_is_signal", &ev.mc_is_signal_, create, "mc_is_signal/O");

  	// MC event category
  	set_output_branch_address( out_tree, "category", &ev.category_, create, "category/I");

  	// CV Event weights
  	set_output_branch_address( out_tree, "weight_cv", &ev.weight_cv, create, "weight_cv/F");
  	
  	// If MC weights are available, store them in the output TTree
  	if ( ev.mc_weights_map_ ) {

	    // Make separate branches for the various sets of systematic variation
	    // weights in the map
	    for ( auto& pair : *ev.mc_weights_map_ ) {

			// Prepend "weight_" to the name of the vector of weights in the map
			std::string weight_branch_name = "weight_" + pair.first;

			// Store a pointer to the vector of weights (needed to set the branch
			// address properly) in the temporary map of pointers
			ev.mc_weights_ptr_map_[ weight_branch_name ] = &pair.second;

			// Set the branch address for this vector of weights
			set_object_output_branch_address< std::vector<double> >( out_tree, weight_branch_name, ev.mc_weights_ptr_map_.at(weight_branch_name), create);
	    }
  	}

  	// NueCC1piXp selection criteria
  	set_output_branch_address( out_tree, "sel_NueCC1piXp", &ev.sel_NueCC1piXp_, create, "sel_NueCC1piXp/O");

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


