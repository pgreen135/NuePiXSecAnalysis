#include "../include/CreateTrainingTree.h"

#include <iostream>

CreateTrainingTree::CreateTrainingTree() {
	
	std::cout << "Initialising Training Tree Creation Class" << std::endl;

	// create file
	outputFile = new TFile("TrainingTree_ElectronPhotonSeparation_withLooseCuts.root", "RECREATE", "Output File");
	if (outputFile->IsOpen()) std::cout << "Output file created successfully." << std::endl;
	else {
		std::cout << "Output file could not be opened, check file name is valid." << std::endl << std::endl;
		exit(1);
	}

	// create tree
	electronPhotonSeparationTree = new TTree("electronPhotonSeparationTree", "electronPhotonSeparationTree");

	// create branches
	electronPhotonSeparationTree->Branch("isSignal", &isSignal);
	electronPhotonSeparationTree->Branch("n_showers_contained", &n_showers_contained);
	electronPhotonSeparationTree->Branch("shr_distance", &shr_distance);
	electronPhotonSeparationTree->Branch("shr_trkfit_gap10_dedx_max", &shr_trkfit_gap10_dedx_max);
	electronPhotonSeparationTree->Branch("shr_trkfit_2cm_dedx_max", &shr_trkfit_2cm_dedx_max);
	electronPhotonSeparationTree->Branch("shrmoliereavg", &shrmoliereavg);
	electronPhotonSeparationTree->Branch("shr_energyFraction", &shr_energyFraction);
	electronPhotonSeparationTree->Branch("CylFrac2h_1cm", &CylFrac2h_1cm);
	electronPhotonSeparationTree->Branch("shrsubclusters", &shrsubclusters);
	electronPhotonSeparationTree->Branch("secondshower_Y_nhit", &secondshower_Y_nhit);
	electronPhotonSeparationTree->Branch("secondshower_Y_vtxdist", &secondshower_Y_vtxdist);
	electronPhotonSeparationTree->Branch("secondshower_Y_anglediff", &secondshower_Y_anglediff);
}

CreateTrainingTree::~CreateTrainingTree(){
	delete outputFile;
}

// ------------------------------------------

void CreateTrainingTree::addEvent(const EventContainer &_evt, Utility::ClassificationEnums classification) {

	// populate variables, sanitising values
	n_showers_contained = _evt.n_showers_contained;

	shr_distance = _evt.shr_distance;

	if (_evt.shr_trkfit_gap10_dedx_max >= 0) shr_trkfit_gap10_dedx_max = _evt.shr_trkfit_gap10_dedx_max;
	else return;
	if (_evt.shr_trkfit_2cm_dedx_max >= 0) shr_trkfit_2cm_dedx_max = _evt.shr_trkfit_2cm_dedx_max;
	else return;

	if (_evt.shrmoliereavg >= 0) shrmoliereavg = _evt.shrmoliereavg;
	else shrmoliereavg = 9999;
	shr_energyFraction = _evt.shr_energyFraction;
	CylFrac2h_1cm = _evt.CylFrac2h_1cm;
	shrsubclusters = _evt.shrsubclusters;

	secondshower_Y_nhit = _evt.secondshower_Y_nhit;
	if (_evt.secondshower_Y_vtxdist >= 0 && _evt.secondshower_Y_vtxdist < 9000) secondshower_Y_vtxdist = _evt.secondshower_Y_vtxdist;
	else secondshower_Y_vtxdist = 9999;
	if (_evt.secondshower_Y_anglediff >= 0 && _evt.secondshower_Y_anglediff < 9000) secondshower_Y_anglediff = _evt.secondshower_Y_anglediff;
	else secondshower_Y_anglediff = 9999;

	// determine whether signal or background, and save
	if (classification == Utility::kCCNue1pi0p || classification == Utility::kCCNue1piNp || classification == Utility::kCCNueNpi) {
		isSignal = 1;
		electronPhotonSeparationTree->Fill();
	}
	else if (classification == Utility::kCCNuepizero || classification == Utility::kCCNumupizero || classification == Utility::kNCpizero) {
		isSignal = 0;
		electronPhotonSeparationTree->Fill();
	}
	else {
		return;
	}
}

// --------------------------------------------

void CreateTrainingTree::writeOutputFile() { 
	outputFile->Write(); 
}



