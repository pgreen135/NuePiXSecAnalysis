#include "../include/BDTTool.h"

#include <iostream>

BDTTool::BDTTool(bool loadElectronPhotonBDT, bool loadPionProtonBDT, bool loadPionProtonBDTAlternate) {

	std::cout << "Initialising BDT Tool Class" << std::endl;

	// load BDTs
	loadBDTs(loadElectronPhotonBDT, loadPionProtonBDT, loadPionProtonBDTAlternate);

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


void BDTTool::loadBDTs(bool loadElectronPhotonBDT, bool loadPionProtonBDT, bool loadPionProtonBDTAlternate){

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

	// Pion Proton BDT Alternate
	if(loadPionProtonBDTAlternate) {

		std::cout << "Loading alternate pion-proton separation BDT model." << std::endl;

	    int xgreturn = -1;
	    xgreturn = XGBoosterCreate(NULL, 0, &boosterPionProtonAlternate);
	    xgreturn = XGBoosterLoadModel(boosterPionProtonAlternate, BDTFilePionProtonAlternate.c_str());
	    assert(xgreturn == 0);

		loadedPionProtonBDTAlternate = true;
	}
}

void BDTTool::dumpBDTModel() {

    // dump model [testing]
    const int dump_format = 0; // 0: text format, 1: json format
    const char** out_str;
    bst_ulong dump_size;
    XGBoosterDumpModel(boosterPionProtonAlternate, "", dump_format, &dump_size, &out_str);
    
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
	
	// create DMatrix, note: order is not the same as in training -- must dump model to determine order:
	// new model
	//["secondshower_U_nhit",
	//	"shr3_distance",
	//	"shr2_distance",
	//	"shr12_p1_dstart",
	//	"shr_trkfit_gap10_dedx_max",
	//	"shrmoliereavg",
	//	"shr13_p1_dstart",
	//	"shr_distance",
	//	"shr_energy_third_cali",
	//	"secondshower_U_vtxdist",
	//	"secondshower_U_anglediff",
	//	"secondshower_Y_vtxdist",
	//	"shr_trkfit_2cm_dedx_max",
	//	"secondshower_Y_anglediff",
	//	"secondshower_V_vtxdist",
	//	"shr_energyFraction",
	//	"secondshower_Y_nhit",
	//	"shr_energy_second_cali",
	//	"secondshower_V_nhit",
	//	"n_showers_contained",
	//	"shrsubclusters",
	//	"secondshower_V_anglediff"]

	std::vector<float> data {static_cast<float>(_evt.secondshower_U_nhit), _evt.shr3_distance, _evt.shr2_distance, _evt.shr12_p1_dstart,
							 _evt.shr_trkfit_gap10_dedx_max, _evt.shrmoliereavg, _evt.shr13_p1_dstart, _evt.shr_distance, _evt.shr_energy_third_cali,
							 _evt.secondshower_U_vtxdist, _evt.secondshower_U_anglediff, _evt.secondshower_Y_vtxdist, _evt.shr_trkfit_2cm_dedx_max,
							 _evt.secondshower_Y_anglediff, _evt.secondshower_V_vtxdist, _evt.shr_energyFraction, static_cast<float>(_evt.secondshower_Y_nhit),  
							 _evt.shr_energy_second_cali, static_cast<float>(_evt.secondshower_V_nhit), static_cast<float>(_evt.n_showers_contained),
							 static_cast<float>(_evt.shrsubclusters), _evt.secondshower_V_anglediff};
	
    DMatrixHandle matrix_electronPhoton;
    xgreturn = XGDMatrixCreateFromMat(data.data(), 1, data.size(), 9999, &matrix_electronPhoton);

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
double BDTTool::evaluatePionProtonBDTScore(const EventContainer &_evt, int trackID) const {

	// --- pion-proton separation BDT ---
	int xgreturn = -1;
	
	// create DMatrix, note: order is not the same as in training -- must dump model to determine order:

	// f0 = trk_bragg_mip_max
	// f1 = trk_daughters
	// f2 = trk_dEdx_trunk_max
	// f3 = trk_bragg_pion_max
	// f4 = trk_end_spacepoints
	// f5 = trk_llr_pid_score

	std::vector<float> data;
	if (trackID == 1) {
		std::vector<float> data_init {_evt.trk_bragg_mip_max, static_cast<float>(_evt.trk_daughters), _evt.trk_dEdx_trunk_max, _evt.trk_bragg_pion_max, static_cast<float>(_evt.trk_end_spacepoints), _evt.trk_llr_pid_score};
		data = data_init;
	}
	else if (trackID == 2) {
		std::vector<float> data_init {_evt.trk2_bragg_mip_max, static_cast<float>(_evt.trk2_daughters), _evt.trk2_dEdx_trunk_max, _evt.trk2_bragg_pion_max, static_cast<float>(_evt.trk2_end_spacepoints), _evt.trk2_llr_pid_score};
		data = data_init;
	}
	else if (trackID == 3) {
		std::vector<float> data_init {_evt.trk3_bragg_mip_max, static_cast<float>(_evt.trk3_daughters), _evt.trk3_dEdx_trunk_max, _evt.trk3_bragg_pion_max, static_cast<float>(_evt.trk3_end_spacepoints), _evt.trk3_llr_pid_score};
		data = data_init;
	}
	else {
		std::cout << "BDT Tool: invalid trackID provided." << std::endl;
		exit(1);
	}
	
    DMatrixHandle matrix_pionProton;
    xgreturn = XGDMatrixCreateFromMat(data.data(), 1, data.size(), 9999, &matrix_pionProton);

    // make prediction
	char const config[] =
		"{\"training\": false, \"type\": 0, "
		"\"iteration_begin\": 0, \"iteration_end\": 0, \"strict_shape\": false}";

	uint64_t const* out_shape;
	uint64_t out_dim;
	float const* out_result = NULL;

	xgreturn = XGBoosterPredictFromDMatrix(boosterPionProton, matrix_pionProton, config, &out_shape, &out_dim, &out_result);

    // free memory
    xgreturn = XGDMatrixFree(matrix_pionProton);
    
    // check return code
    assert(xgreturn == 0);

    return *out_result;
}

// BDT evaluation
// pion-proton separation alternate
double BDTTool::evaluatePionProtonBDTScoreAlternate(const EventContainer &_evt) const {

	// --- pion-proton separation BDT ---
	int xgreturn = -1;
	
	// create DMatrix, note: order is not the same as in training -- must dump model to determine order:
	// get event information 
	float trk_llr_pid_score = _evt.trk_llr_pid_score;
	float trk_bragg_mip_max = _evt.trk_bragg_mip_max;
	float trk_bragg_pion_max = _evt.trk_bragg_pion_max;
	float trk_dEdx_trunk_max = _evt.trk_dEdx_trunk_max;
	float trk_daughters = _evt.trk_daughters;
	float trk_end_spacepoints = _evt.trk_end_spacepoints;

	float trk2_llr_pid_score = _evt.trk2_llr_pid_score;
	float trk2_bragg_mip_max = _evt.trk2_bragg_mip_max;
	float trk2_bragg_pion_max = _evt.trk2_bragg_pion_max;
	float trk2_dEdx_trunk_max = _evt.trk2_dEdx_trunk_max;
	float trk2_daughters = _evt.trk2_daughters;
	float trk2_end_spacepoints = _evt.trk2_end_spacepoints;
	
	float trk3_llr_pid_score = _evt.trk3_llr_pid_score;
	float trk3_bragg_mip_max = _evt.trk3_bragg_mip_max;
	float trk3_bragg_pion_max = _evt.trk3_bragg_pion_max;
	float trk3_dEdx_trunk_max = _evt.trk3_dEdx_trunk_max;
	float trk3_daughters = _evt.trk3_daughters;
	float trk3_end_spacepoints = _evt.trk3_end_spacepoints;

		
	// set non-passing tracks to missing values
	if (_evt.primaryTrackPionlikeLoose == false) {
		trk_llr_pid_score = 9999;
     	trk_bragg_mip_max = 9999;
     	trk_bragg_pion_max = 9999;
     	trk_dEdx_trunk_max = 9999;
     	trk_daughters = 9999;
     	trk_end_spacepoints = 9999;
	}
	if (_evt.secondaryTrackPionlikeLoose == false) {
		trk2_llr_pid_score = 9999;
     	trk2_bragg_mip_max = 9999;
     	trk2_bragg_pion_max = 9999;
     	trk2_dEdx_trunk_max = 9999;
     	trk2_daughters = 9999;
     	trk2_end_spacepoints = 9999;
	}
	if (_evt.tertiaryTrackPionlikeLoose == false) {
		trk3_llr_pid_score = 9999;
     	trk3_bragg_mip_max = 9999;
     	trk3_bragg_pion_max = 9999;
     	trk3_dEdx_trunk_max = 9999;
     	trk3_daughters = 9999;
     	trk3_end_spacepoints = 9999;
	}

	//["trk2_end_spacepoints",
	//"trk3_dEdx_trunk_max",
	//"trk3_bragg_pion_max",
	//"trk3_daughters",
	//"trk2_llr_pid_score",
	//"trk2_dEdx_trunk_max",
	//"trk_bragg_pion_max",
	//"trk3_llr_pid_score",
	//"trk3_end_spacepoints",
	//"trk_bragg_mip_max",
	//"trk_dEdx_trunk_max",
	//"trk_end_spacepoints",
	//"trk2_bragg_mip_max",
	//"trk2_bragg_pion_max",
	///"trk_daughters",
	//"trk_llr_pid_score",
	//"trk3_bragg_mip_max",
	//"trk2_daughters"]

	// initialise
	std::vector<float> data {static_cast<float>(trk2_end_spacepoints), trk3_dEdx_trunk_max, trk3_bragg_pion_max, static_cast<float>(trk3_daughters), trk2_llr_pid_score,
							trk2_dEdx_trunk_max, trk_bragg_pion_max, trk3_llr_pid_score, static_cast<float>(trk3_end_spacepoints), trk_bragg_mip_max, trk_dEdx_trunk_max,
							static_cast<float>(trk_end_spacepoints), trk2_bragg_mip_max, trk2_bragg_pion_max, static_cast<float>(trk_daughters), trk_llr_pid_score,
							trk3_bragg_mip_max, static_cast<float>(trk2_daughters)};    

	//std::vector<float> data {trk2_bragg_pion_max, trk2_dEdx_trunk_max, static_cast<float>(trk2_end_spacepoints), static_cast<float>(trk3_end_spacepoints), trk2_bragg_mip_max, trk_llr_pid_score, trk3_dEdx_trunk_max,
	//						trk3_bragg_mip_max, trk_dEdx_trunk_max, static_cast<float>(trk3_daughters), trk3_llr_pid_score, trk_bragg_pion_max, trk2_llr_pid_score, trk3_bragg_pion_max,
	//						trk_bragg_mip_max, static_cast<float>(trk_daughters), static_cast<float>(trk2_daughters), static_cast<float>(trk_end_spacepoints)};

    DMatrixHandle matrix_pionProton;
    xgreturn = XGDMatrixCreateFromMat(data.data(), 1, data.size(), 9999, &matrix_pionProton);

    // make prediction
	char const config[] =
		"{\"training\": false, \"type\": 0, "
		"\"iteration_begin\": 0, \"iteration_end\": 0, \"strict_shape\": false}";

	uint64_t const* out_shape;
	uint64_t out_dim;
	float const* out_result = NULL;

	xgreturn = XGBoosterPredictFromDMatrix(boosterPionProtonAlternate, matrix_pionProton, config, &out_shape, &out_dim, &out_result);

    // free memory
    xgreturn = XGDMatrixFree(matrix_pionProton);
    
    // check return code
    assert(xgreturn == 0);

    return *out_result;
}


