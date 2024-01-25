// Driver script to launch nue analysis code

#include "../include/Utility.h"
#include "../include/EventContainer.h"
#include "../include/Selection.h"
#include "../include/SelectionDriver.h"
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
#include <TEfficiency.h>
#include <TGraphAsymmErrors.h>

#include <TSystem.h>


int main() {
	
	SelectionDriver _selectionDriver;
	
    _selectionDriver.runBDTSelectionFull();
    //_selectionDriver.runBDTSelectionFHC();
	//_selectionDriver.runBDTSelectionRHC();

	//_selectionDriver.optimiseBDTSelection();

	//_selectionDriver.runBDTSelectionDetVarFHC();
	//_selectionDriver.runBDTSelectionDetVarRHC();
	
	//_selectionDriver.createElectronPhotonBDTTrainingTreeFHC();
	//_selectionDriver.createElectronPhotonBDTTrainingTreeRHC();

	//_selectionDriver.createPionProtonBDTTrainingTreeFHC();
	//_selectionDriver.createPionProtonBDTTrainingTreeRHC();
	
	return 0;
}