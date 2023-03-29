#include "../include/CreateTrainingTree.h"

#include <iostream>

CreateTrainingTree::CreateTrainingTree(Utility::BDTEnums type) {
	
	std::cout << "Initialising Training Tree Creation Class" << std::endl;

	if (type == Utility::kElectronPhoton) {
		
		std::cout << "Creating electron photon separation BDT training tree." << std::endl;
		BDTType = Utility::kElectronPhoton;

		// create file
		outputFile = new TFile("TrainingTree_ElectronPhotonSeparation.root", "RECREATE", "Output File");
		if (outputFile->IsOpen()) std::cout << "Output file created successfully." << std::endl;
		else {
			std::cout << "Training Tree: output file could not be opened, check file name is valid." << std::endl << std::endl;
			exit(1);
		}

		// create tree
		trainingTree = new TTree("trainingTree", "trainingTree");

		// create branches
		trainingTree->Branch("isSignal", &isSignal);
		trainingTree->Branch("n_showers_contained", &n_showers_contained);
		trainingTree->Branch("shr_distance", &shr_distance);
		trainingTree->Branch("shr_trkfit_gap10_dedx_max", &shr_trkfit_gap10_dedx_max);
		trainingTree->Branch("shr_trkfit_2cm_dedx_max", &shr_trkfit_2cm_dedx_max);
		trainingTree->Branch("shrmoliereavg", &shrmoliereavg);
		trainingTree->Branch("shr_energyFraction", &shr_energyFraction);
		trainingTree->Branch("shrsubclusters", &shrsubclusters);
		trainingTree->Branch("secondshower_Y_nhit", &secondshower_Y_nhit);
		trainingTree->Branch("secondshower_Y_vtxdist", &secondshower_Y_vtxdist);
		trainingTree->Branch("secondshower_Y_anglediff", &secondshower_Y_anglediff);
		trainingTree->Branch("secondshower_U_nhit", &secondshower_U_nhit);
		trainingTree->Branch("secondshower_U_vtxdist", &secondshower_U_vtxdist);
		trainingTree->Branch("secondshower_U_anglediff", &secondshower_U_anglediff);
		trainingTree->Branch("secondshower_V_nhit", &secondshower_V_nhit);
		trainingTree->Branch("secondshower_V_vtxdist", &secondshower_V_vtxdist);
		trainingTree->Branch("secondshower_V_anglediff", &secondshower_V_anglediff);

	}
	else if (type == Utility::kPionProton) {
		
		std::cout << "Creating pion proton separation BDT training tree." << std::endl;
		BDTType = Utility::kPionProton;

		// create file
		outputFile = new TFile("TrainingTree_PionProtonSeparation.root", "RECREATE", "Output File");
		if (outputFile->IsOpen()) std::cout << "Output file created successfully." << std::endl;
		else {
			std::cout << "Training Tree: output file could not be opened, check file name is valid." << std::endl << std::endl;
			exit(1);
		}

		// create tree
		trainingTree = new TTree("trainingTree", "trainingTree");

		// create branches
		trainingTree->Branch("isSignal", &isSignal);
		trainingTree->Branch("trk_llr_pid_score", &trk_llr_pid_score);
		trainingTree->Branch("trk_bragg_mip_max", &trk_bragg_mip_max);
		trainingTree->Branch("trk_bragg_pion_max", &trk_bragg_pion_max);
		trainingTree->Branch("trk_dEdx_trunk_max", &trk_dEdx_trunk_max);
		trainingTree->Branch("trk_daughters", &trk_daughters);

	}
	else {
		std::cout << "Training Tree: invalid BDT type provided." << std::endl << std::endl;
		exit(1);
	}
}

CreateTrainingTree::~CreateTrainingTree(){
	delete trainingTree;
	delete outputFile;
}

// ------------------------------------------

void CreateTrainingTree::addEvent(const EventContainer &_evt, Utility::ClassificationEnums classification) {

	if (BDTType == Utility::kElectronPhoton) {

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
		shrsubclusters = _evt.shrsubclusters;

		secondshower_Y_nhit = _evt.secondshower_Y_nhit;
		if (_evt.secondshower_Y_vtxdist >= 0 && _evt.secondshower_Y_vtxdist < 9000) secondshower_Y_vtxdist = _evt.secondshower_Y_vtxdist;
		else secondshower_Y_vtxdist = 9999;
		if (_evt.secondshower_Y_anglediff >= 0 && _evt.secondshower_Y_anglediff < 9000) secondshower_Y_anglediff = _evt.secondshower_Y_anglediff;
		else secondshower_Y_anglediff = 9999;

		secondshower_U_nhit = _evt.secondshower_U_nhit;
		if (_evt.secondshower_U_vtxdist >= 0 && _evt.secondshower_U_vtxdist < 9000) secondshower_U_vtxdist = _evt.secondshower_U_vtxdist;
		else secondshower_U_vtxdist = 9999;
		if (_evt.secondshower_U_anglediff >= 0 && _evt.secondshower_U_anglediff < 9000) secondshower_U_anglediff = _evt.secondshower_U_anglediff;
		else secondshower_U_anglediff = 9999;

		secondshower_V_nhit = _evt.secondshower_V_nhit;
		if (_evt.secondshower_V_vtxdist >= 0 && _evt.secondshower_V_vtxdist < 9000) secondshower_V_vtxdist = _evt.secondshower_V_vtxdist;
		else secondshower_V_vtxdist = 9999;
		if (_evt.secondshower_V_anglediff >= 0 && _evt.secondshower_V_anglediff < 9000) secondshower_V_anglediff = _evt.secondshower_V_anglediff;
		else secondshower_V_anglediff = 9999;

		// determine whether signal or background, and save
		if (classification == Utility::kCCNue1pi0p || classification == Utility::kCCNue1piNp || classification == Utility::kCCNueNpi) {
			isSignal = 1;
			trainingTree->Fill();
			return;
		}
		else if (classification == Utility::kCCNuepizero || classification == Utility::kCCNumupizero || classification == Utility::kNCpizero) {
			isSignal = 0;
			trainingTree->Fill();
			return;
		}
		else {
			return;
		}
	}
	else if (BDTType == Utility::kPionProton) {

		// primary track
		if (_evt.primaryTrackPionlikeLoose) {

			// populate variables 
			trk_llr_pid_score = _evt.trk_llr_pid_score;
			trk_bragg_mip_max = _evt.trk_bragg_mip_max;
			trk_bragg_pion_max = _evt.trk_bragg_pion_max;
			trk_dEdx_trunk_max = _evt.trk_dEdx_trunk_max;
			trk_daughters = _evt.trk_daughters;

			// determine whether signal or background, and save
			if (_evt.trk_bkt_pdg == 211 || _evt.trk_bkt_pdg == -211) {
				isSignal = 1;
				trainingTree->Fill();
			}
			else if (_evt.trk_bkt_pdg == 2212) {
				isSignal = 0;
				trainingTree->Fill();
			}

			// otherwise don't fill
		}
		// secondary track
		if (_evt.secondaryTrackPionlikeLoose) {

			// populate variables 
			trk_llr_pid_score = _evt.trk2_llr_pid_score;
			trk_bragg_mip_max = _evt.trk2_bragg_mip_max;
			trk_bragg_pion_max = _evt.trk2_bragg_pion_max;
			trk_dEdx_trunk_max = _evt.trk2_dEdx_trunk_max;
			trk_daughters = _evt.trk2_daughters;

			// determine whether signal or background, and save
			if (_evt.trk2_bkt_pdg == 211 || _evt.trk2_bkt_pdg == -211) {
				isSignal = 1;
				trainingTree->Fill();
			}
			else if (_evt.trk2_bkt_pdg == 2212) {
				isSignal = 0;
				trainingTree->Fill();
			}

			// otherwise don't fill
		}
		// tertiary track
		if (_evt.tertiaryTrackPionlikeLoose) {

			// populate variables 
			trk_llr_pid_score = _evt.trk3_llr_pid_score;
			trk_bragg_mip_max = _evt.trk3_bragg_mip_max;
			trk_bragg_pion_max = _evt.trk3_bragg_pion_max;
			trk_dEdx_trunk_max = _evt.trk3_dEdx_trunk_max;
			trk_daughters = _evt.trk3_daughters;

			// determine whether signal or background, and save
			if (_evt.trk3_bkt_pdg == 211 || _evt.trk3_bkt_pdg == -211) {
				isSignal = 1;
				trainingTree->Fill();
			}
			else if (_evt.trk3_bkt_pdg == 2212) {
				isSignal = 0;
				trainingTree->Fill();
			}

			// otherwise don't fill
		}

		return;
	}
}

// --------------------------------------------

void CreateTrainingTree::writeOutputFile() { 
	outputFile->Write(); 
}

