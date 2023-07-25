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
	BDTTool(bool loadElectronPhotonBDTFHC, bool loadElectronPhotonBDTRHC, bool loadPionProtonBDTFHC, bool loadPionProtonBDTRHC);

	// Destructor
	~BDTTool();

	// Function to load BDTs
	void loadBDTs(bool loadElectronPhotonBDTFHC, bool loadElectronPhotonBDTRHC, bool loadPionProtonBDTFHC, bool loadPionProtonBDTRHC);

	// Functions to evaluate BDT scores
	// Electron-photon separation
    double evaluateElectronPhotonBDTScoreFHC(EventContainer &_evt) const;
    double evaluateElectronPhotonBDTScoreRHC(EventContainer &_evt) const;
    // Pion-proton separation
    double evaluatePionProtonBDTScoreFHC(const EventContainer &_evt, int trackID) const;
    double evaluatePionProtonBDTScoreRHC(const EventContainer &_evt, int trackID) const;

    // Function to dump BDT models [for testing]
    void dumpBDTModel();

	// ----------------------------------

private:

	// --- BDTs ---
	bool loadedElectronPhotonBDTFHC; 
	std::string BDTFileElectronPhotonFHC = "/Users/patrick/Documents/MicroBooNE/CrossSections/NuePiXSec_Analysis/Selection/bdts/bdt_electronPhoton_FHC_Jul13.json";
	BoosterHandle boosterElectronPhotonFHC;

	bool loadedElectronPhotonBDTRHC; 
	std::string BDTFileElectronPhotonRHC = "/Users/patrick/Documents/MicroBooNE/CrossSections/NuePiXSec_Analysis/Selection/bdts/bdt_electronPhoton_RHC_Jul13.json";
	BoosterHandle boosterElectronPhotonRHC;
    
	bool loadedPionProtonBDTFHC; 
    std::string BDTFilePionProtonFHC = "/Users/patrick/Documents/MicroBooNE/CrossSections/NuePiXSec_Analysis/Selection/bdts/bdt_pionProton_FHC_Jul13.json";
    BoosterHandle boosterPionProtonFHC;

    bool loadedPionProtonBDTRHC; 
    std::string BDTFilePionProtonRHC = "/Users/patrick/Documents/MicroBooNE/CrossSections/NuePiXSec_Analysis/Selection/bdts/bdt_pionProton_RHC_Jul13.json";
    BoosterHandle boosterPionProtonRHC;    
};

#endif