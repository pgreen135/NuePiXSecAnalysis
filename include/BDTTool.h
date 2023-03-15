#ifndef BDTTOOL_H
#define BDTTOOL_H

// class for interfacing with BDTs trained in Python

#include "../include/Utility.h"
#include "../include/EventContainer.h"

#include <xgboost/c_api.h>

class BDTTool {

public:	

	// ----------------------------------
	// Constructor
	BDTTool(bool loadElectronPhotonBDT, bool loadPionProtonBDT);

	// Destructor
	~BDTTool();

	// Function to load BDTs
	void loadBDTs(bool loadElectronPhotonBDT, bool loadPionProtonBDT);

	// Functions to evaluate BDT scores
	// Electron-photon separation
    double evaluateElectronPhotonBDTScore(const EventContainer &_evt) const;
    // Pion-proton separation
    double evaluatePionProtonBDTScore(const EventContainer &_evt) const;

    // Function to dump BDT models [for testing]
    void dumpBDTModel();

	// ----------------------------------

private:

	// --- BDTs ---
	bool loadedElectronPhotonBDT; 
	std::string BDTFileElectronPhoton = "/Users/patrick/Documents/MicroBooNE/CrossSections/NuePiXSec_Analysis/Selection/bdts/bdt_electronPhotonSeparation_withNue.model";
    BoosterHandle boosterElectronPhoton;
    
	bool loadedPionProtonBDT; 
    std::string BDTFilePionProton = "/Users/patrick/Documents/MicroBooNE/CrossSections/NuePiXSec_Analysis/Selection/bdts/bdt_TOBEADDED.model";
    BoosterHandle boosterPionProton;
    
};



#endif