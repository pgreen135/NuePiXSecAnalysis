#include "../include/Utility.h"

#include <iostream>
#include <numeric>
#include <string>
#include <sstream>

#include <TFile.h>

// Constructor
Utility::Utility() {
	
	std::cout << "Initialising Utilities Class" << std::endl;

	// load beamline variation histograms
	loadBeamLineVariationHistograms();

}

// ------------------------------------------------------------------------------

// Function to check if point is within FV
bool Utility::inFV(const double x, const double y, const double z) const {
	// check the point is in the boundary 										
	// NTuples definition
	if ( x   >= 10 && x <= 246
		 && y   >= -101 && y <= 101
	  	 && z   >= 10 && z <= 986  ) {
	  	return true;
	}
	else return false;
}

// ------------------------------------------------------------------------------

// Function to check whether a track is exiting
// Currently same definition as FV, but could be altered
bool Utility::isExiting(const double x, const double y, const double z) const {
	// NTuples definition
	//if ( x   >= 10 && x <= 246
	//	 && y   >= -101 && y <= 101
	//  	 && z   >= 10 && z <= 986  ) {
	//  	return true;
	//}
	// containment definition (10 cm from borders)
	if ( x   >= 10 && x <= 246
		 && y   >= -106 && y <= 106
	  	 && z   >= 10 && z <= 1026  ) {
	  	return true;
	}
	else return false;
}

// ------------------------------------------------------------------------------

// Function to check whether number is valid
bool Utility::isNumber(float input) {

	// infinite 
	if (std::isinf(input)) {
		return false;
	}

	// nan 
	if (std::isnan(input)) {
		return false;
	}

	return true;
}

// ------------------------------------------------------------------------------

// Functions to get beam line variation weights
void Utility::loadBeamLineVariationHistograms() {

	// load beamline variations TH2D
	TFile *beamlineVariationsFile = NULL;
	beamlineVariationsFile = new TFile("/Users/patrick/Documents/MicroBooNE/CrossSections/NuePiXSec_Analysis/NuMIBeamLineWeights/NuMI_Beamline_Variations_to_CV_Ratios.root");
	
	// loop over beamline variations
	for (int i = 1; i <= 20; i++) {
		// construct names
		std::stringstream name_nue_ss; name_nue_ss << "EnergyTheta2D/ratio_run" << i <<  "_FHC_nue_CV_AV_TPC_2D";
		std::stringstream name_nuebar_ss; name_nuebar_ss << "EnergyTheta2D/ratio_run" << i <<  "_FHC_nuebar_CV_AV_TPC_2D";
		std::stringstream name_numu_ss; name_numu_ss << "EnergyTheta2D/ratio_run" << i <<  "_FHC_numu_CV_AV_TPC_2D";
		std::stringstream name_numubar_ss; name_numubar_ss << "EnergyTheta2D/ratio_run" << i <<  "_FHC_numubar_CV_AV_TPC_2D";
		std::string name_nue = name_nue_ss.str();
		std::string name_nuebar = name_nuebar_ss.str();
		std::string name_numu = name_numu_ss.str();
		std::string name_numubar = name_numubar_ss.str();		

		// load histograms
		h_nue_fhc.push_back(*(TH2F*)beamlineVariationsFile->Get(name_nue.c_str()));
		h_nuebar_fhc.push_back(*(TH2F*)beamlineVariationsFile->Get(name_nuebar.c_str()));
		h_numu_fhc.push_back(*(TH2F*)beamlineVariationsFile->Get(name_numu.c_str()));
		h_numubar_fhc.push_back(*(TH2F*)beamlineVariationsFile->Get(name_numubar.c_str()));
	}

	beamlineVariationsFile->Close();
}

std::vector<double> Utility::getWeightsNue(float energy, float angle) {
	
	std::vector<double> weights; weights.reserve(20);

	for (int i = 0; i < h_nue_fhc.size(); i++) {
		int binx = h_nue_fhc[i].GetXaxis()->FindBin(energy);
		int biny = h_nue_fhc[i].GetYaxis()->FindBin(angle);
		float weight = h_nue_fhc[i].GetBinContent(binx,biny);
		weights.push_back(weight);
	}
	return weights;
}

std::vector<double> Utility::getWeightsNuebar(float energy, float angle) {
	
	std::vector<double> weights; weights.reserve(20);

	for (int i = 0; i < h_nue_fhc.size(); i++) {
		int binx = h_nuebar_fhc[i].GetXaxis()->FindBin(energy);
		int biny = h_nuebar_fhc[i].GetYaxis()->FindBin(angle);
		float weight = h_nuebar_fhc[i].GetBinContent(binx,biny);
		weights.push_back(weight);
	}
	return weights;
}

std::vector<double> Utility::getWeightsNumu(float energy, float angle) {
	
	std::vector<double> weights; weights.reserve(20);

	for (int i = 0; i < h_nue_fhc.size(); i++) {
		int binx = h_numu_fhc[i].GetXaxis()->FindBin(energy);
		int biny = h_numu_fhc[i].GetYaxis()->FindBin(angle);
		float weight = h_numu_fhc[i].GetBinContent(binx,biny);
		weights.push_back(weight);
	}
	return weights;
}

std::vector<double> Utility::getWeightsNumubar(float energy, float angle) {
	
	std::vector<double> weights; weights.reserve(20);

	for (int i = 0; i < h_nue_fhc.size(); i++) {
		int binx = h_numubar_fhc[i].GetXaxis()->FindBin(energy);
		int biny = h_numubar_fhc[i].GetYaxis()->FindBin(angle);
		float weight = h_numubar_fhc[i].GetBinContent(binx,biny);
		weights.push_back(weight);
	}
	return weights;
}

// ------------------------------------------------------------------------------
