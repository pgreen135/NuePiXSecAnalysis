#include "../include/BDTTool.h"

#include <iostream>

BDTTool::BDTTool(bool loadElectronPhotonBDT, bool loadPionProtonBDT) {

	std::cout << "Initialising BDT Tool Class" << std::endl;

	// load BDTs
	loadBDTs(loadElectronPhotonBDT, loadPionProtonBDT);

}

BDTTool::~BDTTool(){

	if (loadedElectronPhotonBDT) {
		int xgreturn = -1;
	    xgreturn = XGBoosterFree(boosterElectronPhoton);
	    assert(xgreturn == 0);
	}
	if (loadedPionProtonBDT) {
		int xgreturn = -1;
	    xgreturn = XGBoosterFree(boosterPionProton);
	    assert(xgreturn == 0);
	}

}


void BDTTool::loadBDTs(bool loadElectronPhotonBDT, bool loadPionProtonBDT){

	// Electron Photon BDT
	if(loadElectronPhotonBDT) {

		std::cout << "Loading electron-photon separation BDT model." << std::endl;

	    int xgreturn = -1;
	    xgreturn = XGBoosterCreate(NULL, 0, &boosterElectronPhoton);
	    xgreturn = XGBoosterLoadModel(boosterElectronPhoton, BDTFileElectronPhoton.c_str());
	    assert(xgreturn == 0);

		loadedElectronPhotonBDT = true;
	}

	// Pion Proton BDT
	if(loadPionProtonBDT) {

		std::cout << "Loading pion-proton separation BDT model." << std::endl;

	    int xgreturn = -1;
	    xgreturn = XGBoosterCreate(NULL, 0, &boosterPionProton);
	    xgreturn = XGBoosterLoadModel(boosterPionProton, BDTFilePionProton.c_str());
	    assert(xgreturn == 0);

		loadedPionProtonBDT = true;
	}
}

void BDTTool::dumpBDTModel() {

    // dump model [testing]
    const int dump_format = 0; // 0: text format, 1: json format
    const char** out_str;
    bst_ulong dump_size;
    XGBoosterDumpModel(boosterElectronPhoton, "", dump_format, &dump_size, &out_str);
    
    std::cout << dump_size << std::endl;
    for (int i = 0; i < 1000; i++) {
    	std::cout << i << std::endl;
    	std::cout << out_str[i] << std::endl;
    }

    std::free(out_str);
    
}


// BDT evaluation
// electron-photon separation
double BDTTool::evaluateElectronPhotonBDTScore(const EventContainer &_evt) const {

	// --- electron-photon separation BDT ---
	int xgreturn = -1;
	
	// create DMatrix, note: order is not the same as in trainig -- must dump model to determine order:

	// case with nue pi0
	// f0 = shr_energyFraction
	// f1 = n_showers_contained
	// f2 = secondshower_Y_nhit
	// f3 = shr_distance
	// f4 = shrmoliereavg
	// f5 = shr_trkfit_2cm_dedx_max
	// f6 = shr_trkfit_gap10_dedx_max
	// f7 = shrsubclusters
	// f8 = secondshower_Y_vtxdist
	// f9 = secondshower_Y_anglediff	

	std::vector<float> data {_evt.shr_energyFraction, static_cast<float>(_evt.n_showers_contained), static_cast<float>(_evt.secondshower_Y_nhit), _evt.shr_distance, _evt.shrmoliereavg,
							 _evt.shr_trkfit_2cm_dedx_max, _evt.shr_trkfit_gap10_dedx_max, static_cast<float>(_evt.shrsubclusters), _evt.secondshower_Y_vtxdist, _evt.secondshower_Y_anglediff};

	
    DMatrixHandle matrix_electronPhoton;
    xgreturn = XGDMatrixCreateFromMat(data.data(), 1, data.size(), 0, &matrix_electronPhoton);

    // make prediction
	char const config[] =
		"{\"training\": false, \"type\": 0, "
		"\"iteration_begin\": 0, \"iteration_end\": 0, \"strict_shape\": false}";

	uint64_t const* out_shape;
	uint64_t out_dim;
	float const* out_result = NULL;

	xgreturn = XGBoosterPredictFromDMatrix(boosterElectronPhoton, matrix_electronPhoton, config, &out_shape, &out_dim, &out_result);

    // free memory
    xgreturn = XGDMatrixFree(matrix_electronPhoton);
    
    // check return code
    assert(xgreturn == 0);

    return *out_result;
}

// BDT evaluation
// pion-proton separation
double BDTTool::evaluatePionProtonBDTScore(const EventContainer &_evt) const {

	// To be implemented 
	return 0;

}



