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
		trainingTree->Branch("shr_energy_second_cali", &shr_energy_second_cali);
		trainingTree->Branch("shr2_distance", &shr2_distance);
		trainingTree->Branch("shr12_p1_dstart", &shr12_p1_dstart);
		trainingTree->Branch("shr_energy_third_cali", &shr_energy_third_cali);
		trainingTree->Branch("shr3_distance", &shr3_distance);
		trainingTree->Branch("shr13_p1_dstart", &shr13_p1_dstart);
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
		trainingTree->Branch("trk_end_spacepoints", &trk_end_spacepoints);

	}
	else if (type == Utility::kPionProtonAlternate) {
		
		std::cout << "Creating alternate pion proton separation BDT training tree." << std::endl;
		BDTType = Utility::kPionProtonAlternate;

		// create file
		outputFile = new TFile("TrainingTree_PionProtonSeparation_Alternate.root", "RECREATE", "Output File");
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
		trainingTree->Branch("trk2_llr_pid_score", &trk2_llr_pid_score);
		trainingTree->Branch("trk3_llr_pid_score", &trk3_llr_pid_score);
		trainingTree->Branch("trk_bragg_mip_max", &trk_bragg_mip_max);
		trainingTree->Branch("trk2_bragg_mip_max", &trk2_bragg_mip_max);
		trainingTree->Branch("trk3_bragg_mip_max", &trk3_bragg_mip_max);
		trainingTree->Branch("trk_bragg_pion_max", &trk_bragg_pion_max);
		trainingTree->Branch("trk2_bragg_pion_max", &trk2_bragg_pion_max);
		trainingTree->Branch("trk3_bragg_pion_max", &trk3_bragg_pion_max);
		trainingTree->Branch("trk_dEdx_trunk_max", &trk_dEdx_trunk_max);
		trainingTree->Branch("trk2_dEdx_trunk_max", &trk2_dEdx_trunk_max);
		trainingTree->Branch("trk3_dEdx_trunk_max", &trk3_dEdx_trunk_max);
		trainingTree->Branch("trk_daughters", &trk_daughters);
		trainingTree->Branch("trk2_daughters", &trk2_daughters);
		trainingTree->Branch("trk3_daughters", &trk3_daughters);
		trainingTree->Branch("trk_end_spacepoints", &trk_end_spacepoints);
		trainingTree->Branch("trk2_end_spacepoints", &trk2_end_spacepoints);
		trainingTree->Branch("trk3_end_spacepoints", &trk3_end_spacepoints);

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

		if (_evt.shr_energy_second_cali > 0) {
			shr_energy_second_cali = _evt.shr_energy_second_cali;
			shr2_distance = _evt.shr2_distance;
			shr12_p1_dstart = _evt.shr12_p1_dstart;
		}
		else {
			shr_energy_second_cali = 9999;
			shr2_distance = 9999;
			shr12_p1_dstart = 9999;
		}

		if (_evt.shr_energy_third_cali > 0) {
			shr_energy_third_cali = _evt.shr_energy_third_cali;
			shr3_distance = _evt.shr3_distance;
			shr13_p1_dstart = _evt.shr13_p1_dstart;
		}
		else {
			shr_energy_third_cali = 9999;
			shr3_distance = 9999;
			shr13_p1_dstart = 9999;
		}		

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
		if (classification == Utility::kCCNue1pi0p || classification == Utility::kCCNue1piNp || classification == Utility::kCCNueNpi || 
			classification == Utility::kCCNue1p || classification == Utility::kCCNueNp) {
			isSignal = 1;
			trainingTree->Fill();
			return;
		}
		else if (classification == Utility::kCCNuepizero || classification == Utility::kCCNumupizero || classification == Utility::kNCpizero) {
		//else if (classification == Utility::kCCNumupizero || classification == Utility::kNCpizero) {
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
			trk_end_spacepoints = _evt.trk_end_spacepoints;

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
			trk_end_spacepoints = _evt.trk2_end_spacepoints;

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
			trk_end_spacepoints = _evt.trk3_end_spacepoints;

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
	}
	else if (BDTType == Utility::kPionProtonAlternate) {

		// primary track
		if (_evt.primaryTrackPionlikeLoose) {
			// populate variables 
			trk_llr_pid_score = _evt.trk_llr_pid_score;
			trk_bragg_mip_max = _evt.trk_bragg_mip_max;
			trk_bragg_pion_max = _evt.trk_bragg_pion_max;
			trk_dEdx_trunk_max = _evt.trk_dEdx_trunk_max;
			trk_daughters = _evt.trk_daughters;
			trk_end_spacepoints = _evt.trk_end_spacepoints;
		}
		else {
			// fill with missing value
			trk_llr_pid_score = 9999;
			trk_bragg_mip_max = 9999;
			trk_bragg_pion_max = 9999;
			trk_dEdx_trunk_max = 9999;
			trk_daughters = 9999;
			trk_end_spacepoints = 9999;
		}
		// secondary track
		if (_evt.secondaryTrackPionlikeLoose) {

			// populate variables 
			trk2_llr_pid_score = _evt.trk2_llr_pid_score;
			trk2_bragg_mip_max = _evt.trk2_bragg_mip_max;
			trk2_bragg_pion_max = _evt.trk2_bragg_pion_max;
			trk2_dEdx_trunk_max = _evt.trk2_dEdx_trunk_max;
			trk2_daughters = _evt.trk2_daughters;
			trk2_end_spacepoints = _evt.trk2_end_spacepoints;
		}
		else {
			// fill with missing value
			trk2_llr_pid_score = 9999;
			trk2_bragg_mip_max = 9999;
			trk2_bragg_pion_max = 9999;
			trk2_dEdx_trunk_max = 9999;
			trk2_daughters = 9999;
			trk2_end_spacepoints = 9999;
		}
		// tertiary track
		if (_evt.tertiaryTrackPionlikeLoose) {

			// populate variables 
			trk3_llr_pid_score = _evt.trk3_llr_pid_score;
			trk3_bragg_mip_max = _evt.trk3_bragg_mip_max;
			trk3_bragg_pion_max = _evt.trk3_bragg_pion_max;
			trk3_dEdx_trunk_max = _evt.trk3_dEdx_trunk_max;
			trk3_daughters = _evt.trk3_daughters;
			trk3_end_spacepoints = _evt.trk3_end_spacepoints;
		}
		else {
			// fill with missing value
			trk3_llr_pid_score = 9999;
			trk3_bragg_mip_max = 9999;
			trk3_bragg_pion_max = 9999;
			trk3_dEdx_trunk_max = 9999;
			trk3_daughters = 9999;
			trk3_end_spacepoints = 9999;
		}

		// determine whether signal or background, and save
		if (classification == Utility::kCCNue1pi0p || classification == Utility::kCCNue1piNp) {
			isSignal = 1;
			trainingTree->Fill();
			return;
		}
		else if (classification == Utility::kCCNue1p || classification == Utility::kCCNueNp) {
			isSignal = 0;
			trainingTree->Fill();
			return;
		}
		else {
			return;
		}

		return;
	}
}

// --------------------------------------------

void CreateTrainingTree::writeOutputFile() { 
	outputFile->Write(); 
}

