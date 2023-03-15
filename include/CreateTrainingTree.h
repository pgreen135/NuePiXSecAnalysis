#ifndef CREATETRAININGTREE_H
#define CREATETRAININGTREE_H

// class for creating root trees used for BDT training
// selects required sanitized variables from event and writes to flat root file

#include "../include/Utility.h"
#include "../include/EventContainer.h"

#include <TFile.h>
#include <TTree.h>

class CreateTrainingTree {

public:	

	// ----------------------------------
	// Constructor
	CreateTrainingTree();

	// Destructor
	~CreateTrainingTree();

	// Function to add an event
	void addEvent(const EventContainer &_evt, Utility::ClassificationEnums classification);

	// Function to write output file
	void writeOutputFile();

	// ----------------------------------

private:

	// output file
	TFile *outputFile;

	// trees
	TTree *electronPhotonSeparationTree;

	// branches

	// --- electron-photon separation tree ---
	bool isSignal;
	
	unsigned int n_showers_contained;
	
	float shr_distance;
	float shr_trkfit_gap10_dedx_max;
	float shr_trkfit_2cm_dedx_max;

	float shrmoliereavg;
	float shr_energyFraction;
	float CylFrac2h_1cm;
	float shrsubclusters;

	float secondshower_Y_nhit;
	float secondshower_Y_vtxdist;
	float secondshower_Y_anglediff;

}; 

#endif