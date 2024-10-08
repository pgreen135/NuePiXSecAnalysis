#include "../include/BDTTool.h"

#include <iostream>

BDTTool::BDTTool(bool loadElectronPhotonBDTFHC, bool loadElectronPhotonBDTRHC, bool loadPionProtonBDTFHC, bool loadPionProtonBDTRHC, const Utility &utility): _utility{ utility } {

	std::cout << "Initialising BDT Tool Class" << std::endl;

	// load BDTs
	loadBDTs(loadElectronPhotonBDTFHC, loadElectronPhotonBDTRHC, loadPionProtonBDTFHC, loadPionProtonBDTRHC);

}

BDTTool::~BDTTool(){

	if (loadedElectronPhotonBDTFHC) {
		int xgreturn = -1;
	    xgreturn = XGBoosterFree(boosterElectronPhotonFHC);
	    assert(xgreturn == 0);
	}
	if (loadedElectronPhotonBDTRHC) {
		int xgreturn = -1;
	    xgreturn = XGBoosterFree(boosterElectronPhotonRHC);
	    assert(xgreturn == 0);
	}
	if (loadedPionProtonBDTFHC) {
		int xgreturn = -1;
	    xgreturn = XGBoosterFree(boosterPionProtonFHC);
	    assert(xgreturn == 0);
	}
	if (loadedPionProtonBDTRHC) {
		int xgreturn = -1;
	    xgreturn = XGBoosterFree(boosterPionProtonRHC);
	    assert(xgreturn == 0);
	}

}


void BDTTool::loadBDTs(bool loadElectronPhotonBDTFHC, bool loadElectronPhotonBDTRHC, bool loadPionProtonBDTFHC, bool loadPionProtonBDTRHC){

	// Electron Photon BDT FHC
	if(loadElectronPhotonBDTFHC) {

		std::cout << "Loading electron-photon separation FHC BDT model." << std::endl;

	    int xgreturn = -1;
	    xgreturn = XGBoosterCreate(NULL, 0, &boosterElectronPhotonFHC);
	    xgreturn = XGBoosterLoadModel(boosterElectronPhotonFHC, BDTFileElectronPhotonFHC.c_str());
	    assert(xgreturn == 0);

		loadedElectronPhotonBDTFHC = true;
	}

	// Electron Photon BDT RHC
	if(loadElectronPhotonBDTRHC) {

		std::cout << "Loading electron-photon separation RHC BDT model." << std::endl;

	    int xgreturn = -1;
	    xgreturn = XGBoosterCreate(NULL, 0, &boosterElectronPhotonRHC);
	    xgreturn = XGBoosterLoadModel(boosterElectronPhotonRHC, BDTFileElectronPhotonRHC.c_str());
	    assert(xgreturn == 0);

		loadedElectronPhotonBDTRHC = true;
	}

	// Pion Proton BDT FHC
	if(loadPionProtonBDTFHC) {

		std::cout << "Loading pion-proton separation FHC BDT model." << std::endl;

	    int xgreturn = -1;
	    xgreturn = XGBoosterCreate(NULL, 0, &boosterPionProtonFHC);
	    xgreturn = XGBoosterLoadModel(boosterPionProtonFHC, BDTFilePionProtonFHC.c_str());
	    assert(xgreturn == 0);

		loadedPionProtonBDTFHC = true;
	}

	// Pion Proton BDT RHC
	if(loadPionProtonBDTRHC) {

		std::cout << "Loading pion-proton separation RHC BDT model." << std::endl;

	    int xgreturn = -1;
	    xgreturn = XGBoosterCreate(NULL, 0, &boosterPionProtonRHC);
	    xgreturn = XGBoosterLoadModel(boosterPionProtonRHC, BDTFilePionProtonRHC.c_str());
	    assert(xgreturn == 0);

		loadedPionProtonBDTRHC = true;
	}
}

void BDTTool::dumpBDTModel() {

    // dump model [testing]
    const int dump_format = 0; // 0: text format, 1: json format
    const char** out_str;
    bst_ulong dump_size;
    XGBoosterDumpModel(boosterPionProtonFHC, "", dump_format, &dump_size, &out_str);
    
    std::cout << dump_size << std::endl;
    for (int i = 0; i < 1000; i++) {
    	std::cout << i << std::endl;
    	std::cout << out_str[i] << std::endl;
    }

    std::free(out_str);
    
}


// BDT evaluation
// electron-photon separation
double BDTTool::evaluateElectronPhotonBDTScoreFHC(EventContainer &_evt) const {

	// --- electron-photon separation BDT ---
	int xgreturn = -1;

	// sanitize input
	if (_evt.shr_trkfit_gap10_dedx_max  < 0 || !_utility.isNumber(_evt.shr_trkfit_gap10_dedx_max)) _evt.shr_trkfit_gap10_dedx_max = 9999;
	if (_evt.shr_trkfit_2cm_dedx_max < 0 || !_utility.isNumber(_evt.shr_trkfit_2cm_dedx_max)) _evt.shr_trkfit_2cm_dedx_max = 9999;
	if (_evt.shrmoliereavg < 0 || !_utility.isNumber(_evt.shrmoliereavg) ) _evt.shrmoliereavg = 9999;
	
	if (_evt.shrPCA1CMed_5cm < 0 || !_utility.isNumber(_evt.shrPCA1CMed_5cm)) _evt.shrPCA1CMed_5cm = 9999;
	if (_evt.CylFrac2h_1cm < 0 || !_utility.isNumber(_evt.CylFrac2h_1cm)) _evt.CylFrac2h_1cm = 9999;
	if (_evt.DeltaRMS2h < 0 || !_utility.isNumber(_evt.DeltaRMS2h)) _evt.DeltaRMS2h = 9999;
	if (_evt.shrMCSMom < 0 || !_utility.isNumber(_evt.shrMCSMom)) _evt.shrMCSMom = 9999;

	if (_evt.shr_energy_second_cali <= 0 || !_utility.isNumber(_evt.shr_energy_second_cali)) {
		_evt.shr_energy_second_cali = 9999;
		_evt.shr2_distance = 9999;
		_evt.shr12_p1_dstart = 9999;
		_evt.shr2_trackEndProximity = 9999;
		_evt.shr2_pfpgeneration = 9999;
	}
	if (_evt.shr2_pfpgeneration == 0 || !_utility.isNumber(_evt.shr2_pfpgeneration)) _evt.shr2_pfpgeneration = 9999;

	if (_evt.secondshower_Y_nhit < 0 || !_utility.isNumber(_evt.secondshower_Y_nhit)) _evt.secondshower_Y_nhit = 9999;
	if (_evt.secondshower_Y_vtxdist < 0 || !_utility.isNumber(_evt.secondshower_Y_vtxdist)) _evt.secondshower_Y_vtxdist = 9999;
	if (_evt.secondshower_Y_dot < 0 || !_utility.isNumber(_evt.secondshower_Y_dot)) _evt.secondshower_Y_dot = 9999;
	if (_evt.secondshower_Y_anglediff < 0 || !_utility.isNumber(_evt.secondshower_Y_anglediff)) _evt.secondshower_Y_anglediff = 9999;
	if (_evt.secondshower_U_nhit < 0 || !_utility.isNumber(_evt.secondshower_U_nhit)) _evt.secondshower_U_nhit = 9999;
	if (_evt.secondshower_U_vtxdist < 0 || !_utility.isNumber(_evt.secondshower_U_vtxdist)) _evt.secondshower_U_vtxdist = 9999;
	if (_evt.secondshower_U_dot < 0 || !_utility.isNumber(_evt.secondshower_U_dot)) _evt.secondshower_U_dot = 9999;
	if (_evt.secondshower_U_anglediff < 0 || !_utility.isNumber(_evt.secondshower_U_anglediff)) _evt.secondshower_U_anglediff = 9999;
	if (_evt.secondshower_V_nhit < 0 || !_utility.isNumber(_evt.secondshower_V_nhit)) _evt.secondshower_V_nhit = 9999;
	if (_evt.secondshower_V_vtxdist < 0 || !_utility.isNumber(_evt.secondshower_V_vtxdist)) _evt.secondshower_V_vtxdist = 9999;
	if (_evt.secondshower_V_dot < 0 || !_utility.isNumber(_evt.secondshower_V_dot)) _evt.secondshower_V_dot = 9999;
	if (_evt.secondshower_V_anglediff < 0 || !_utility.isNumber(_evt.secondshower_V_anglediff)) _evt.secondshower_V_anglediff = 9999;

    // Aug 10, pions, split training sample
    //["shr_trkfit_gap10_dedx_max",
    //"shr_trkfit_2cm_dedx_max",
    //"shr2_trackEndProximity",
    //"shrmoliereavg",
    //"shrsubclusters",
    //"secondshower_U_nhit",
    //"shr12_p1_dstart",
    //"shr2_pfpgeneration",
    //"secondshower_Y_anglediff",
    //"secondshower_V_vtxdist",
    //"secondshower_Y_dot",
    //"secondshower_V_dot",
    //"shrMCSMom",
    //"shr_energy_second_cali",
    //"shrPCA1CMed_5cm",
    //"secondshower_Y_vtxdist",
    //"n_showers_contained",
    //"shr_distance",
    //"shr2_distance",
    //"CylFrac2h_1cm",
    //"secondshower_U_anglediff",
    //"shr_energyFraction",
    //"DeltaRMS2h",
    //"secondshower_V_nhit",
    //"secondshower_U_vtxdist",
    //"secondshower_Y_nhit",
    //"secondshower_V_anglediff",
    //"secondshower_U_dot"]
	/*
	std::vector<float> data {_evt.shr_trkfit_gap10_dedx_max, _evt.shr_trkfit_2cm_dedx_max, _evt.shr2_trackEndProximity, _evt.shrmoliereavg, static_cast<float>(_evt.shrsubclusters), static_cast<float>(_evt.secondshower_U_nhit),
							 _evt.shr12_p1_dstart, static_cast<float>(_evt.shr2_pfpgeneration), _evt.secondshower_Y_anglediff, _evt.secondshower_V_vtxdist, _evt.secondshower_Y_dot, _evt.secondshower_V_dot, _evt.shrMCSMom,
							 _evt.shr_energy_second_cali, _evt.shrPCA1CMed_5cm, _evt.secondshower_Y_vtxdist, static_cast<float>(_evt.n_showers_contained), _evt.shr_distance, _evt.shr2_distance, _evt.CylFrac2h_1cm,
							 _evt.secondshower_U_anglediff, _evt.shr_energyFraction, _evt.DeltaRMS2h, static_cast<float>(_evt.secondshower_V_nhit), _evt.secondshower_U_vtxdist, static_cast<float>(_evt.secondshower_Y_nhit),
							 _evt.secondshower_V_anglediff, _evt.secondshower_U_dot };
	*/

	// Nov 2023 model
	//["shr2_distance",
	//"shr_distance",
	//"shrsubclusters",
	//"secondshower_U_nhit",
	//"secondshower_Y_dot",
	//"secondshower_U_vtxdist",
	//"DeltaRMS2h",
	//"shrmoliereavg",
	//"shr12_p1_dstart",
	//"CylFrac2h_1cm",
	//"shr_trkfit_2cm_dedx_max",
	//"secondshower_Y_vtxdist",
	//"secondshower_U_dot",
	//"shrMCSMom",
	//"secondshower_V_anglediff",
	//"n_showers_contained",
	//"shr_energyFraction",
	//"secondshower_V_nhit",
	//"secondshower_Y_anglediff",
	//"secondshower_V_dot",
	//"secondshower_U_anglediff",
	//"shr2_trackEndProximity",
	//"shr2_pfpgeneration",
	//"secondshower_V_vtxdist",
	//"shr_trkfit_gap10_dedx_max",
	//"shr_energy_second_cali",
	//"secondshower_Y_nhit",
	//"shrPCA1CMed_5cm"]	

	std::vector<float> data { _evt.shr2_distance, _evt.shr_distance, static_cast<float>(_evt.shrsubclusters), static_cast<float>(_evt.secondshower_U_nhit), _evt.secondshower_Y_dot, _evt.secondshower_U_vtxdist, _evt.DeltaRMS2h,
							  _evt.shrmoliereavg, _evt.shr12_p1_dstart, _evt.CylFrac2h_1cm, _evt.shr_trkfit_2cm_dedx_max, _evt.secondshower_Y_vtxdist, _evt.secondshower_U_dot, _evt.shrMCSMom, _evt.secondshower_V_anglediff,
							  static_cast<float>(_evt.n_showers_contained), _evt.shr_energyFraction, static_cast<float>(_evt.secondshower_V_nhit), _evt.secondshower_Y_anglediff, _evt.secondshower_V_dot, _evt.secondshower_U_anglediff,
							  _evt.shr2_trackEndProximity, static_cast<float>(_evt.shr2_pfpgeneration), _evt.secondshower_V_vtxdist, _evt.shr_trkfit_gap10_dedx_max, _evt.shr_energy_second_cali, 
							  static_cast<float>(_evt.secondshower_Y_nhit), _evt.shrPCA1CMed_5cm };	

	// Combined Model (May 2024)
	//["shrMCSMom",
	//"DeltaRMS2h",
	//"shr_distance",
	//"secondshower_V_vtxdist",
	//"shr_trkfit_gap10_dedx_max",
	//"secondshower_V_anglediff",
	//"secondshower_V_dot",
	//"shr2_trackEndProximity",
	//"secondshower_V_nhit",
	//"shrmoliereavg",
	//"shrsubclusters",
	//"secondshower_U_dot",
	//"secondshower_U_anglediff",
	//"secondshower_U_nhit",
	//"shr_energy_second_cali",
	//"shr12_p1_dstart",
	//"shr_energyFraction",
	//"shrPCA1CMed_5cm",
	//"secondshower_Y_anglediff",
	//"CylFrac2h_1cm",
	//"n_showers_contained",
	//"shr2_pfpgeneration",
	//"shr2_distance",
	//"shr_trkfit_2cm_dedx_max",
	//"secondshower_Y_vtxdist",
	//"secondshower_Y_dot",
	//"secondshower_Y_nhit",
	//"secondshower_U_vtxdist"]
	/*
	std::vector<float> data {_evt.shrMCSMom, _evt.DeltaRMS2h, _evt.shr_distance, _evt.secondshower_V_vtxdist, _evt.shr_trkfit_gap10_dedx_max, _evt.secondshower_V_anglediff,
							 _evt.secondshower_V_dot, _evt.shr2_trackEndProximity, static_cast<float>(_evt.secondshower_V_nhit), _evt.shrmoliereavg, static_cast<float>(_evt.shrsubclusters),
							 _evt.secondshower_U_dot, _evt.secondshower_U_anglediff, static_cast<float>(_evt.secondshower_U_nhit), _evt.shr_energy_second_cali, _evt.shr12_p1_dstart,
							 _evt.shr_energyFraction, _evt.shrPCA1CMed_5cm, _evt.secondshower_Y_anglediff, _evt.CylFrac2h_1cm, static_cast<float>(_evt.n_showers_contained),
							 static_cast<float>(_evt.shr2_pfpgeneration), _evt.shr2_distance, _evt.shr_trkfit_2cm_dedx_max, _evt.secondshower_Y_vtxdist, _evt.secondshower_Y_dot,
							 static_cast<float>(_evt.secondshower_Y_nhit), _evt.secondshower_U_vtxdist};
	*/	
	
    DMatrixHandle matrix_electronPhoton;
    xgreturn = XGDMatrixCreateFromMat(data.data(), 1, data.size(), 9999, &matrix_electronPhoton);

    // make prediction
	char const config[] =
		"{\"training\": false, \"type\": 0, "
		"\"iteration_begin\": 0, \"iteration_end\": 0, \"strict_shape\": false}";

	uint64_t const* out_shape;
	uint64_t out_dim;
	float const* out_result = NULL;

	xgreturn = XGBoosterPredictFromDMatrix(boosterElectronPhotonFHC, matrix_electronPhoton, config, &out_shape, &out_dim, &out_result);

    // free memory
    xgreturn = XGDMatrixFree(matrix_electronPhoton);
    
    // check return code
    assert(xgreturn == 0);

    return *out_result;
}

// BDT evaluation
// electron-photon separation RHC
double BDTTool::evaluateElectronPhotonBDTScoreRHC(EventContainer &_evt) const {

	// --- electron-photon separation BDT ---
	int xgreturn = -1;
	
	// sanitize input
	if (_evt.shr_trkfit_gap10_dedx_max  < 0 || !_utility.isNumber(_evt.shr_trkfit_gap10_dedx_max)) _evt.shr_trkfit_gap10_dedx_max = 9999;
	if (_evt.shr_trkfit_2cm_dedx_max < 0 || !_utility.isNumber(_evt.shr_trkfit_2cm_dedx_max)) _evt.shr_trkfit_2cm_dedx_max = 9999;
	if (_evt.shrmoliereavg < 0 || !_utility.isNumber(_evt.shrmoliereavg) ) _evt.shrmoliereavg = 9999;
	
	if (_evt.shrPCA1CMed_5cm < 0 || !_utility.isNumber(_evt.shrPCA1CMed_5cm)) _evt.shrPCA1CMed_5cm = 9999;
	if (_evt.CylFrac2h_1cm < 0 || !_utility.isNumber(_evt.CylFrac2h_1cm)) _evt.CylFrac2h_1cm = 9999;
	if (_evt.DeltaRMS2h < 0 || !_utility.isNumber(_evt.DeltaRMS2h)) _evt.DeltaRMS2h = 9999;
	if (_evt.shrMCSMom < 0 || !_utility.isNumber(_evt.shrMCSMom)) _evt.shrMCSMom = 9999;

	if (_evt.shr_energy_second_cali <= 0 || !_utility.isNumber(_evt.shr_energy_second_cali)) {
		_evt.shr_energy_second_cali = 9999;
		_evt.shr2_distance = 9999;
		_evt.shr12_p1_dstart = 9999;
		_evt.shr2_trackEndProximity = 9999;
		_evt.shr2_pfpgeneration = 9999;
	}
	if (_evt.shr2_pfpgeneration == 0 || !_utility.isNumber(_evt.shr2_pfpgeneration)) _evt.shr2_pfpgeneration = 9999;

	if (_evt.secondshower_Y_nhit < 0 || !_utility.isNumber(_evt.secondshower_Y_nhit)) _evt.secondshower_Y_nhit = 9999;
	if (_evt.secondshower_Y_vtxdist < 0 || !_utility.isNumber(_evt.secondshower_Y_vtxdist)) _evt.secondshower_Y_vtxdist = 9999;
	if (_evt.secondshower_Y_dot < 0 || !_utility.isNumber(_evt.secondshower_Y_dot)) _evt.secondshower_Y_dot = 9999;
	if (_evt.secondshower_Y_anglediff < 0 || !_utility.isNumber(_evt.secondshower_Y_anglediff)) _evt.secondshower_Y_anglediff = 9999;
	if (_evt.secondshower_U_nhit < 0 || !_utility.isNumber(_evt.secondshower_U_nhit)) _evt.secondshower_U_nhit = 9999;
	if (_evt.secondshower_U_vtxdist < 0 || !_utility.isNumber(_evt.secondshower_U_vtxdist)) _evt.secondshower_U_vtxdist = 9999;
	if (_evt.secondshower_U_dot < 0 || !_utility.isNumber(_evt.secondshower_U_dot)) _evt.secondshower_U_dot = 9999;
	if (_evt.secondshower_U_anglediff < 0 || !_utility.isNumber(_evt.secondshower_U_anglediff)) _evt.secondshower_U_anglediff = 9999;
	if (_evt.secondshower_V_nhit < 0 || !_utility.isNumber(_evt.secondshower_V_nhit)) _evt.secondshower_V_nhit = 9999;
	if (_evt.secondshower_V_vtxdist < 0 || !_utility.isNumber(_evt.secondshower_V_vtxdist)) _evt.secondshower_V_vtxdist = 9999;
	if (_evt.secondshower_V_dot < 0 || !_utility.isNumber(_evt.secondshower_V_dot)) _evt.secondshower_V_dot = 9999;
	if (_evt.secondshower_V_anglediff < 0 || !_utility.isNumber(_evt.secondshower_V_anglediff)) _evt.secondshower_V_anglediff = 9999;

	// Aug 17, pions, split training sample
    //"secondshower_Y_anglediff",
    //"secondshower_U_dot",
    //"n_showers_contained",
    //"shr_distance",
    //"CylFrac2h_1cm",
    //"secondshower_V_anglediff",
    //"secondshower_Y_dot",
    //"shr2_distance",
    //"shr2_trackEndProximity",
    //"shr2_pfpgeneration",
    //"secondshower_V_vtxdist",
    //"DeltaRMS2h",
    //"secondshower_Y_nhit",
    //"shrMCSMom",
    //"shrsubclusters",
    //"secondshower_Y_vtxdist",
    //"secondshower_V_nhit",
    //"shr_trkfit_2cm_dedx_max",
    //"shr_energyFraction",
    //"shr_energy_second_cali",
    //"shrmoliereavg",
    //"secondshower_U_vtxdist",
    //"secondshower_U_nhit",
    //"secondshower_V_dot",
    //"shrPCA1CMed_5cm",
    //"secondshower_U_anglediff",
    //"shr12_p1_dstart",
    //"shr_trkfit_gap10_dedx_max"
	/*
	std::vector<float> data {_evt.secondshower_Y_anglediff, _evt.secondshower_U_dot, static_cast<float>(_evt.n_showers_contained), _evt.shr_distance, _evt.CylFrac2h_1cm, _evt.secondshower_V_anglediff, _evt.secondshower_Y_dot, _evt.shr2_distance,
							 _evt.shr2_trackEndProximity, static_cast<float>(_evt.shr2_pfpgeneration), _evt.secondshower_V_vtxdist, _evt.DeltaRMS2h, static_cast<float>(_evt.secondshower_Y_nhit), _evt.shrMCSMom, static_cast<float>(_evt.shrsubclusters),
							 _evt.secondshower_Y_vtxdist, static_cast<float>(_evt.secondshower_V_nhit), _evt.shr_trkfit_2cm_dedx_max, _evt.shr_energyFraction, _evt.shr_energy_second_cali, _evt.shrmoliereavg, _evt.secondshower_U_vtxdist,
							 static_cast<float>(_evt.secondshower_U_nhit), _evt.secondshower_V_dot, _evt.shrPCA1CMed_5cm, _evt.secondshower_U_anglediff, _evt.shr12_p1_dstart, _evt.shr_trkfit_gap10_dedx_max };					 
	*/

	// Nov 2023 model
	//"shr_distance",
	//"shr_trkfit_2cm_dedx_max",
	//"secondshower_U_nhit",
	//"shrPCA1CMed_5cm",
	//"secondshower_Y_nhit",
	//"DeltaRMS2h",
	//"shrsubclusters",
	//"shr_energyFraction",
	//"shr2_distance",
	//"secondshower_Y_anglediff",
	//"n_showers_contained",
	//"shr2_pfpgeneration",
	//"secondshower_V_vtxdist",
	//"shrMCSMom",
	//"secondshower_U_dot",
	//"secondshower_U_anglediff",
	//"shrmoliereavg",
	//"shr2_trackEndProximity",
	//"secondshower_Y_dot",
	//"secondshower_V_nhit",
	//"CylFrac2h_1cm",
	//"shr12_p1_dstart",
	//"secondshower_V_anglediff",
	//"secondshower_U_vtxdist",
	//"shr_trkfit_gap10_dedx_max",
	//"secondshower_V_dot",
	//"secondshower_Y_vtxdist",
	//"shr_energy_second_cali"]
	
	std::vector<float> data {_evt.shr_distance, _evt.shr_trkfit_2cm_dedx_max, static_cast<float>(_evt.secondshower_U_nhit), _evt.shrPCA1CMed_5cm, static_cast<float>(_evt.secondshower_Y_nhit), _evt.DeltaRMS2h, static_cast<float>(_evt.shrsubclusters),
							 _evt.shr_energyFraction, _evt.shr2_distance, _evt.secondshower_Y_anglediff, static_cast<float>(_evt.n_showers_contained), static_cast<float>(_evt.shr2_pfpgeneration), _evt.secondshower_V_vtxdist, _evt.shrMCSMom,
							 _evt.secondshower_U_dot, _evt.secondshower_U_anglediff, _evt.shrmoliereavg, _evt.shr2_trackEndProximity, _evt.secondshower_Y_dot, static_cast<float>(_evt.secondshower_V_nhit), _evt.CylFrac2h_1cm, _evt.shr12_p1_dstart,
							 _evt.secondshower_V_anglediff, _evt.secondshower_U_vtxdist, _evt.shr_trkfit_gap10_dedx_max, _evt.secondshower_V_dot, _evt.secondshower_Y_vtxdist, _evt.shr_energy_second_cali };						 
	
    // Combined Model (May 2024)
	//["shrMCSMom",
	//"DeltaRMS2h",
	//"shr_distance",
	//"secondshower_V_vtxdist",
	//"shr_trkfit_gap10_dedx_max",
	//"secondshower_V_anglediff",
	//"secondshower_V_dot",
	//"shr2_trackEndProximity",
	//"secondshower_V_nhit",
	//"shrmoliereavg",
	//"shrsubclusters",
	//"secondshower_U_dot",
	//"secondshower_U_anglediff",
	//"secondshower_U_nhit",
	//"shr_energy_second_cali",
	//"shr12_p1_dstart",
	//"shr_energyFraction",
	//"shrPCA1CMed_5cm",
	//"secondshower_Y_anglediff",
	//"CylFrac2h_1cm",
	//"n_showers_contained",
	//"shr2_pfpgeneration",
	//"shr2_distance",
	//"shr_trkfit_2cm_dedx_max",
	//"secondshower_Y_vtxdist",
	//"secondshower_Y_dot",
	//"secondshower_Y_nhit",
	//"secondshower_U_vtxdist"]
	/*
	std::vector<float> data {_evt.shrMCSMom, _evt.DeltaRMS2h, _evt.shr_distance, _evt.secondshower_V_vtxdist, _evt.shr_trkfit_gap10_dedx_max, _evt.secondshower_V_anglediff,
							 _evt.secondshower_V_dot, _evt.shr2_trackEndProximity, static_cast<float>(_evt.secondshower_V_nhit), _evt.shrmoliereavg, static_cast<float>(_evt.shrsubclusters),
							 _evt.secondshower_U_dot, _evt.secondshower_U_anglediff, static_cast<float>(_evt.secondshower_U_nhit), _evt.shr_energy_second_cali, _evt.shr12_p1_dstart,
							 _evt.shr_energyFraction, _evt.shrPCA1CMed_5cm, _evt.secondshower_Y_anglediff, _evt.CylFrac2h_1cm, static_cast<float>(_evt.n_showers_contained),
							 static_cast<float>(_evt.shr2_pfpgeneration), _evt.shr2_distance, _evt.shr_trkfit_2cm_dedx_max, _evt.secondshower_Y_vtxdist, _evt.secondshower_Y_dot,
							 static_cast<float>(_evt.secondshower_Y_nhit), _evt.secondshower_U_vtxdist};
	*/

    DMatrixHandle matrix_electronPhoton;
    xgreturn = XGDMatrixCreateFromMat(data.data(), 1, data.size(), 9999, &matrix_electronPhoton);

    // make prediction
	char const config[] =
		"{\"training\": false, \"type\": 0, "
		"\"iteration_begin\": 0, \"iteration_end\": 0, \"strict_shape\": false}";

	uint64_t const* out_shape;
	uint64_t out_dim;
	float const* out_result = NULL;

	xgreturn = XGBoosterPredictFromDMatrix(boosterElectronPhotonRHC, matrix_electronPhoton, config, &out_shape, &out_dim, &out_result);

    // free memory
    xgreturn = XGDMatrixFree(matrix_electronPhoton);
    
    // check return code
    assert(xgreturn == 0);

    return *out_result;
}

// BDT evaluation
// pion-proton separation FHC
double BDTTool::evaluatePionProtonBDTScoreFHC(const EventContainer &_evt, int trackID) const {

	// --- pion-proton separation BDT ---
	int xgreturn = -1;

	// create DMatrix, note: order is not the same as in training -- order in .json

	// Aug 10, pions, split training sample
	//["trk_bragg_mip_max",
	//"trk_dEdx_trunk_max",
	//"trk_llr_pid_score",
	//"trk_score",
	//"trk_daughters",
	//"trk_end_spacepoints",
	//"trk_bragg_pion_max"]
	/*
	std::vector<float> data;
	if (trackID == 1) {
		std::vector<float> data_init {_evt.trk_bragg_mip_max,  _evt.trk_dEdx_trunk_max, _evt.trk_llr_pid_score, _evt.trk_score, static_cast<float>(_evt.trk_daughters), static_cast<float>(_evt.trk_end_spacepoints), _evt.trk_bragg_pion_max}; 
		data = data_init;
	}
	else if (trackID == 2) {
		std::vector<float> data_init {_evt.trk2_bragg_mip_max,  _evt.trk2_dEdx_trunk_max, _evt.trk2_llr_pid_score, _evt.trk2_score, static_cast<float>(_evt.trk2_daughters), static_cast<float>(_evt.trk2_end_spacepoints), _evt.trk2_bragg_pion_max};
		data = data_init;
	}
	else if (trackID == 3) {
		std::vector<float> data_init {_evt.trk3_bragg_mip_max,  _evt.trk3_dEdx_trunk_max, _evt.trk3_llr_pid_score, _evt.trk3_score, static_cast<float>(_evt.trk3_daughters), static_cast<float>(_evt.trk3_end_spacepoints), _evt.trk3_bragg_pion_max};
		data = data_init;
	}
	else {
		std::cout << "BDT Tool: invalid trackID provided." << std::endl;
		exit(1);
	}
	*/

	// Nov 2023, pions, more conservative
	//["trk_dEdx_trunk_max",
	//"trk_daughters",
	//"trk_score",
	//"trk_end_spacepoints",
	//"trk_bragg_pion_max",
	//"trk_bragg_mip_max",
	//"trk_llr_pid_score"]
	
	std::vector<float> data;
	if (trackID == 1) {
		std::vector<float> data_init { _evt.trk_dEdx_trunk_max, static_cast<float>(_evt.trk_daughters), _evt.trk_score, static_cast<float>(_evt.trk_end_spacepoints), _evt.trk_bragg_pion_max, _evt.trk_bragg_mip_max, _evt.trk_llr_pid_score };
		data = data_init;
	}
	else if (trackID == 2) {
		std::vector<float> data_init { _evt.trk2_dEdx_trunk_max, static_cast<float>(_evt.trk2_daughters), _evt.trk2_score, static_cast<float>(_evt.trk2_end_spacepoints), _evt.trk2_bragg_pion_max, _evt.trk2_bragg_mip_max, _evt.trk2_llr_pid_score };
		data = data_init;
	}
	else if (trackID == 3) {
		std::vector<float> data_init { _evt.trk3_dEdx_trunk_max, static_cast<float>(_evt.trk3_daughters), _evt.trk3_score, static_cast<float>(_evt.trk3_end_spacepoints), _evt.trk3_bragg_pion_max, _evt.trk3_bragg_mip_max, _evt.trk3_llr_pid_score };
		data = data_init;
	}
	else {
		std::cout << "BDT Tool: invalid trackID provided." << std::endl;
		exit(1);
	}

	// Combined model
	//["trk_daughters",
	//"trk_bragg_mip_max",
	//"trk_llr_pid_score",
	//"trk_end_spacepoints",
	//"trk_dEdx_trunk_max",
	//"trk_score",
	//"trk_bragg_pion_max"]
	/*
	std::vector<float> data;
	if (trackID == 1) {
		std::vector<float> data_init { static_cast<float>(_evt.trk_daughters), _evt.trk_bragg_mip_max, _evt.trk_llr_pid_score, static_cast<float>(_evt.trk_end_spacepoints), _evt.trk_dEdx_trunk_max, _evt.trk_score, _evt.trk_bragg_pion_max  };
		data = data_init;
	}
	else if (trackID == 2) {
		std::vector<float> data_init { static_cast<float>(_evt.trk2_daughters), _evt.trk2_bragg_mip_max, _evt.trk2_llr_pid_score, static_cast<float>(_evt.trk2_end_spacepoints), _evt.trk2_dEdx_trunk_max, _evt.trk2_score, _evt.trk2_bragg_pion_max };
		data = data_init;
	}
	else if (trackID == 3) {
		std::vector<float> data_init { static_cast<float>(_evt.trk3_daughters), _evt.trk3_bragg_mip_max, _evt.trk3_llr_pid_score, static_cast<float>(_evt.trk3_end_spacepoints), _evt.trk3_dEdx_trunk_max, _evt.trk3_score, _evt.trk3_bragg_pion_max };
		data = data_init;
	}
	else {
		std::cout << "BDT Tool: invalid trackID provided." << std::endl;
		exit(1);
	}
	*/
	
    DMatrixHandle matrix_pionProton;
    xgreturn = XGDMatrixCreateFromMat(data.data(), 1, data.size(), 9999, &matrix_pionProton);

    // make prediction
	char const config[] =
		"{\"training\": false, \"type\": 0, "
		"\"iteration_begin\": 0, \"iteration_end\": 0, \"strict_shape\": false}";

	uint64_t const* out_shape;
	uint64_t out_dim;
	float const* out_result = NULL;

	xgreturn = XGBoosterPredictFromDMatrix(boosterPionProtonFHC, matrix_pionProton, config, &out_shape, &out_dim, &out_result);

    // free memory
    xgreturn = XGDMatrixFree(matrix_pionProton);
    
    // check return code
    assert(xgreturn == 0);

    return *out_result;
}

// BDT evaluation
// pion-proton separation RHC
double BDTTool::evaluatePionProtonBDTScoreRHC(const EventContainer &_evt, int trackID) const {

	// --- pion-proton separation BDT ---
	int xgreturn = -1;
	
	// create DMatrix, note: order is not the same as in training -- order in .json

	// Aug 17, pions, split training sample
	//["trk_score",
	//"trk_dEdx_trunk_max",
	//"trk_bragg_mip_max",
	//"trk_daughters",
	//"trk_llr_pid_score",
	//"trk_end_spacepoints",
	//"trk_bragg_pion_max"]

	/*
	std::vector<float> data;
	if (trackID == 1) {
		std::vector<float> data_init { _evt.trk_score, _evt.trk_dEdx_trunk_max, _evt.trk_bragg_mip_max, static_cast<float>(_evt.trk_daughters), _evt.trk_llr_pid_score, static_cast<float>(_evt.trk_end_spacepoints), _evt.trk_bragg_pion_max};
		data = data_init;
	}
	else if (trackID == 2) {
		std::vector<float> data_init { _evt.trk2_score, _evt.trk2_dEdx_trunk_max, _evt.trk2_bragg_mip_max, static_cast<float>(_evt.trk2_daughters), _evt.trk2_llr_pid_score, static_cast<float>(_evt.trk2_end_spacepoints), _evt.trk2_bragg_pion_max};
		data = data_init;
	}
	else if (trackID == 3) {
		std::vector<float> data_init { _evt.trk3_score, _evt.trk3_dEdx_trunk_max, _evt.trk3_bragg_mip_max, static_cast<float>(_evt.trk3_daughters), _evt.trk3_llr_pid_score, static_cast<float>(_evt.trk3_end_spacepoints), _evt.trk3_bragg_pion_max};
		data = data_init;
	}
	else {
		std::cout << "BDT Tool: invalid trackID provided." << std::endl;
		exit(1);
	}
	*/

	// Nov 2023, pions, more conservative
    //["trk_end_spacepoints",
    //"trk_bragg_pion_max",
    //"trk_daughters",
    //"trk_score",
    //"trk_llr_pid_score",
    //"trk_bragg_mip_max",
    //"trk_dEdx_trunk_max"]
	
	std::vector<float> data;
	if (trackID == 1) {
		std::vector<float> data_init { static_cast<float>(_evt.trk_end_spacepoints), _evt.trk_bragg_pion_max, static_cast<float>(_evt.trk_daughters), _evt.trk_score, _evt.trk_llr_pid_score, _evt.trk_bragg_mip_max, _evt.trk_dEdx_trunk_max };
		data = data_init;
	}
	else if (trackID == 2) {
		std::vector<float> data_init { static_cast<float>(_evt.trk2_end_spacepoints), _evt.trk2_bragg_pion_max, static_cast<float>(_evt.trk2_daughters), _evt.trk2_score, _evt.trk2_llr_pid_score, _evt.trk2_bragg_mip_max, _evt.trk2_dEdx_trunk_max };
		data = data_init;
	}
	else if (trackID == 3) {
		std::vector<float> data_init { static_cast<float>(_evt.trk3_end_spacepoints), _evt.trk3_bragg_pion_max, static_cast<float>(_evt.trk3_daughters), _evt.trk3_score, _evt.trk3_llr_pid_score, _evt.trk3_bragg_mip_max, _evt.trk3_dEdx_trunk_max };
		data = data_init;
	}
	else {
		std::cout << "BDT Tool: invalid trackID provided." << std::endl;
		exit(1);
	}
	

	// Combined model
	//["trk_daughters",
	//"trk_bragg_mip_max",
	//"trk_llr_pid_score",
	//"trk_end_spacepoints",
	//"trk_dEdx_trunk_max",
	//"trk_score",
	//"trk_bragg_pion_max"]
	/*
	std::vector<float> data;
	if (trackID == 1) {
		std::vector<float> data_init { static_cast<float>(_evt.trk_daughters), _evt.trk_bragg_mip_max, _evt.trk_llr_pid_score, static_cast<float>(_evt.trk_end_spacepoints), _evt.trk_dEdx_trunk_max, _evt.trk_score, _evt.trk_bragg_pion_max  };
		data = data_init;
	}
	else if (trackID == 2) {
		std::vector<float> data_init { static_cast<float>(_evt.trk2_daughters), _evt.trk2_bragg_mip_max, _evt.trk2_llr_pid_score, static_cast<float>(_evt.trk2_end_spacepoints), _evt.trk2_dEdx_trunk_max, _evt.trk2_score, _evt.trk2_bragg_pion_max };
		data = data_init;
	}
	else if (trackID == 3) {
		std::vector<float> data_init { static_cast<float>(_evt.trk3_daughters), _evt.trk3_bragg_mip_max, _evt.trk3_llr_pid_score, static_cast<float>(_evt.trk3_end_spacepoints), _evt.trk3_dEdx_trunk_max, _evt.trk3_score, _evt.trk3_bragg_pion_max };
		data = data_init;
	}
	else {
		std::cout << "BDT Tool: invalid trackID provided." << std::endl;
		exit(1);
	}
	*/
	
    DMatrixHandle matrix_pionProton;
    xgreturn = XGDMatrixCreateFromMat(data.data(), 1, data.size(), 9999, &matrix_pionProton);

    // make prediction
	char const config[] =
		"{\"training\": false, \"type\": 0, "
		"\"iteration_begin\": 0, \"iteration_end\": 0, \"strict_shape\": false}";

	uint64_t const* out_shape;
	uint64_t out_dim;
	float const* out_result = NULL;

	xgreturn = XGBoosterPredictFromDMatrix(boosterPionProtonRHC, matrix_pionProton, config, &out_shape, &out_dim, &out_result);

    // free memory
    xgreturn = XGDMatrixFree(matrix_pionProton);
    
    // check return code
    assert(xgreturn == 0);

    return *out_result;
}

