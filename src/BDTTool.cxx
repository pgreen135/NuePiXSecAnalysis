#include "../include/BDTTool.h"

#include <iostream>

BDTTool::BDTTool(bool loadElectronPhotonBDTFHC, bool loadElectronPhotonBDTRHC, bool loadPionProtonBDTFHC, bool loadPionProtonBDTRHC) {

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

	// Apr21 model
	//["DeltaRMS2h",
	//"shr_energyFraction",
	//"shr_trkfit_2cm_dedx_max",
	//"shr12_p1_dstart",
	//"shrsubclusters",
	//"secondshower_U_vtxdist",
	//"secondshower_U_nhit",
	//"secondshower_U_dot",
	//"shr_trkfit_gap10_dedx_max",
	//"secondshower_V_nhit",
	//"shr_energy_second_cali",
	//"shrMCSMom",
	//"secondshower_Y_anglediff",
	//"secondshower_V_vtxdist",
	//"secondshower_Y_dot",
	//"secondshower_Y_nhit",
	//"shr2_distance",
	//"n_showers_contained",
	//"secondshower_U_anglediff",
	//"shrPCA1CMed_5cm",
	//"secondshower_V_anglediff",
	//"shrmoliereavg",
	//"CylFrac2h_1cm",
	//"shr2_trackEndProximity",
	//"shr_distance",
	//"secondshower_V_dot",
	//"secondshower_Y_vtxdist"

	// sanitize input
	if (_evt.shr_trkfit_gap10_dedx_max  < 0) _evt.shr_trkfit_gap10_dedx_max = 9999;
	if (_evt.shr_trkfit_2cm_dedx_max < 0) _evt.shr_trkfit_2cm_dedx_max = 9999;
	if (_evt.shrmoliereavg < 0) _evt.shrmoliereavg = 9999;
	
	if (_evt.shrPCA1CMed_5cm < 0) _evt.shrPCA1CMed_5cm = 9999;
	if (_evt.CylFrac2h_1cm < 0) _evt.CylFrac2h_1cm = 9999;
	if (_evt.DeltaRMS2h < 0) _evt.DeltaRMS2h = 9999;
	if (_evt.shrMCSMom < 0) _evt.shrMCSMom = 9999;

	if (_evt.shr_energy_second_cali <= 0) {
		_evt.shr_energy_second_cali = 9999;
		_evt.shr2_distance = 9999;
		_evt.shr12_p1_dstart = 9999;
		_evt.shr2_trackEndProximity = 9999;
		_evt.shr2_pfpgeneration = 9999;
	}
	if (_evt.shr2_pfpgeneration == 0) _evt.shr2_pfpgeneration = 9999;

	if (_evt.secondshower_Y_nhit < 0) _evt.secondshower_Y_nhit = 9999;
	if (_evt.secondshower_Y_vtxdist < 0) _evt.secondshower_Y_vtxdist = 9999;
	if (_evt.secondshower_Y_dot < 0) _evt.secondshower_Y_dot = 9999;
	if (_evt.secondshower_Y_anglediff < 0) _evt.secondshower_Y_anglediff = 9999;
	if (_evt.secondshower_U_nhit < 0) _evt.secondshower_U_nhit = 9999;
	if (_evt.secondshower_U_vtxdist < 0) _evt.secondshower_U_vtxdist = 9999;
	if (_evt.secondshower_U_dot < 0) _evt.secondshower_U_dot = 9999;
	if (_evt.secondshower_U_anglediff < 0) _evt.secondshower_U_anglediff = 9999;
	if (_evt.secondshower_V_nhit < 0) _evt.secondshower_V_nhit = 9999;
	if (_evt.secondshower_V_vtxdist < 0) _evt.secondshower_V_vtxdist = 9999;
	if (_evt.secondshower_V_dot < 0) _evt.secondshower_V_dot = 9999;
	if (_evt.secondshower_V_anglediff < 0) _evt.secondshower_V_anglediff = 9999;

	//std::vector<float> data {_evt.DeltaRMS2h, _evt.shr_energyFraction, _evt.shr_trkfit_2cm_dedx_max, _evt.shr12_p1_dstart, static_cast<float>(_evt.shrsubclusters), _evt.secondshower_U_vtxdist,
	//						  static_cast<float>(_evt.secondshower_U_nhit), _evt.secondshower_U_dot, _evt.shr_trkfit_gap10_dedx_max, static_cast<float>(_evt.secondshower_V_nhit),
	//						  _evt.shr_energy_second_cali, _evt.shrMCSMom, _evt.secondshower_Y_anglediff, _evt.secondshower_V_vtxdist, _evt.secondshower_Y_dot, static_cast<float>(_evt.secondshower_Y_nhit), 
	//						  _evt.shr2_distance, static_cast<float>(_evt.n_showers_contained), _evt.secondshower_U_anglediff, _evt.shrPCA1CMed_5cm, _evt.secondshower_V_anglediff, _evt.shrmoliereavg, 
	//						  _evt.CylFrac2h_1cm, _evt.shr2_trackEndProximity, _evt.shr_distance, _evt.secondshower_V_dot, _evt.secondshower_Y_vtxdist }; 

	// Jul 13 model
    //"secondshower_U_dot",
    //"secondshower_V_vtxdist",
    //"shr_trkfit_gap10_dedx_max",
    //"secondshower_V_anglediff",
    //"shr12_p1_dstart",
    //"secondshower_U_anglediff",
    //"secondshower_V_dot",
    //"shrPCA1CMed_5cm",
    //"secondshower_Y_nhit",
    //"shr2_trackEndProximity",
    //"shr2_pfpgeneration",
    //"CylFrac2h_1cm",
    //"shr_trkfit_2cm_dedx_max",
    //"DeltaRMS2h",
    //"secondshower_U_nhit",
    //"secondshower_Y_anglediff",
    //"n_showers_contained",
    //"shrsubclusters",
    //"shr_energy_second_cali",
    //"secondshower_V_nhit",
    //"shr_distance",
    //"shr_energyFraction",
    //"secondshower_Y_dot",
    //"shr2_distance",
    //"shrmoliereavg",
    //"secondshower_Y_vtxdist",
    //"shrMCSMom",
    //"secondshower_U_vtxdist"
    
    std::vector<float> data {_evt.secondshower_U_dot, _evt.secondshower_V_vtxdist, _evt.shr_trkfit_gap10_dedx_max, _evt.secondshower_V_anglediff, _evt.shr12_p1_dstart, _evt.secondshower_U_anglediff, _evt.secondshower_V_dot,
    						 _evt.shrPCA1CMed_5cm, static_cast<float>(_evt.secondshower_Y_nhit), _evt.shr2_trackEndProximity, static_cast<float>(_evt.shr2_pfpgeneration), _evt.CylFrac2h_1cm, _evt.shr_trkfit_2cm_dedx_max,
    						 _evt.DeltaRMS2h, static_cast<float>(_evt.secondshower_U_nhit), _evt.secondshower_Y_anglediff, static_cast<float>(_evt.n_showers_contained), static_cast<float>(_evt.shrsubclusters),
    						 _evt.shr_energy_second_cali, static_cast<float>(_evt.secondshower_V_nhit), _evt.shr_distance, _evt.shr_energyFraction, _evt.secondshower_Y_dot, _evt.shr2_distance, _evt.shrmoliereavg,
    						 _evt.secondshower_Y_vtxdist, _evt.shrMCSMom, _evt.secondshower_U_vtxdist };


	// Jul 7 Model
	//["secondshower_V_dot",
	//"DeltaRMS2h",
	//"shr12_p1_dstart",
	//"secondshower_V_anglediff",
	//"secondshower_Y_dot",
	//"shrmoliereavg",
	//"shr_trkfit_gap10_dedx_max",
	//"shrMCSMom",
	//"secondshower_U_vtxdist",
	//"shr_energy_second_cali",
	//"shr2_trackEndProximity",
	//"secondshower_Y_nhit",
	//"n_showers_contained",
	//"secondshower_U_dot",
	//"shrsubclusters",
	//"secondshower_V_vtxdist",
	//"CylFrac2h_1cm",
	//"shr_trkfit_2cm_dedx_max",
	//"shrPCA1CMed_5cm",
	//"shr_energyFraction",
	//"secondshower_Y_anglediff",
	//"shr_distance",
	//"shr2_distance",
	//"secondshower_U_anglediff",
	//"secondshower_Y_vtxdist",
	//"secondshower_V_nhit",
	//"secondshower_U_nhit"]

	//std::vector<float> data {_evt.secondshower_V_dot, _evt.DeltaRMS2h, _evt.shr12_p1_dstart, _evt.secondshower_V_anglediff, _evt.secondshower_Y_dot, _evt.shrmoliereavg,
	//						 _evt.shr_trkfit_gap10_dedx_max, _evt.shrMCSMom, _evt.secondshower_U_vtxdist, _evt.shr_energy_second_cali, _evt.shr2_trackEndProximity, 
	//						 static_cast<float>(_evt.secondshower_Y_nhit), static_cast<float>(_evt.n_showers_contained), _evt.secondshower_U_dot, static_cast<float>(_evt.shrsubclusters),
	//						 _evt.secondshower_V_vtxdist, _evt.CylFrac2h_1cm, _evt.shr_trkfit_2cm_dedx_max, _evt.shrPCA1CMed_5cm, _evt.shr_energyFraction, _evt.secondshower_Y_anglediff,
	//						 _evt.shr_distance, _evt.shr2_distance, _evt.secondshower_U_anglediff, _evt.secondshower_Y_vtxdist, static_cast<float>(_evt.secondshower_V_nhit),
	//						 static_cast<float>(_evt.secondshower_U_nhit),                

	//						};
					 
	
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
	if (_evt.shr_trkfit_gap10_dedx_max  < 0) _evt.shr_trkfit_gap10_dedx_max = 9999;
	if (_evt.shr_trkfit_2cm_dedx_max < 0) _evt.shr_trkfit_2cm_dedx_max = 9999;
	if (_evt.shrmoliereavg < 0) _evt.shrmoliereavg = 9999;
	
	if (_evt.shrPCA1CMed_5cm < 0) _evt.shrPCA1CMed_5cm = 9999;
	if (_evt.CylFrac2h_1cm < 0) _evt.CylFrac2h_1cm = 9999;
	if (_evt.DeltaRMS2h < 0) _evt.DeltaRMS2h = 9999;
	if (_evt.shrMCSMom < 0) _evt.shrMCSMom = 9999;

	if (_evt.shr_energy_second_cali <= 0) {
		_evt.shr_energy_second_cali = 9999;
		_evt.shr2_distance = 9999;
		_evt.shr12_p1_dstart = 9999;
		_evt.shr2_trackEndProximity = 9999;
		_evt.shr2_pfpgeneration = 9999;
	}
	if (_evt.shr2_pfpgeneration == 0) _evt.shr2_pfpgeneration = 9999;

	if (_evt.secondshower_Y_nhit < 0) _evt.secondshower_Y_nhit = 9999;
	if (_evt.secondshower_Y_vtxdist < 0) _evt.secondshower_Y_vtxdist = 9999;
	if (_evt.secondshower_Y_dot < 0) _evt.secondshower_Y_dot = 9999;
	if (_evt.secondshower_Y_anglediff < 0) _evt.secondshower_Y_anglediff = 9999;
	if (_evt.secondshower_U_nhit < 0) _evt.secondshower_U_nhit = 9999;
	if (_evt.secondshower_U_vtxdist < 0) _evt.secondshower_U_vtxdist = 9999;
	if (_evt.secondshower_U_dot < 0) _evt.secondshower_U_dot = 9999;
	if (_evt.secondshower_U_anglediff < 0) _evt.secondshower_U_anglediff = 9999;
	if (_evt.secondshower_V_nhit < 0) _evt.secondshower_V_nhit = 9999;
	if (_evt.secondshower_V_vtxdist < 0) _evt.secondshower_V_vtxdist = 9999;
	if (_evt.secondshower_V_dot < 0) _evt.secondshower_V_dot = 9999;
	if (_evt.secondshower_V_anglediff < 0) _evt.secondshower_V_anglediff = 9999;


	// Jul11 model
	//["secondshower_V_anglediff",
	//"secondshower_V_nhit",
	//"CylFrac2h_1cm",
	//"shrPCA1CMed_5cm",
	//"secondshower_U_vtxdist",
	//"shrsubclusters",
	//"secondshower_V_vtxdist",
	//"secondshower_V_dot",
	//"shr2_distance",
	//"shr12_p1_dstart",
	//"secondshower_U_anglediff",
	//"shrMCSMom",
	//"shrmoliereavg",
	//"n_showers_contained",
	//"shr_energy_second_cali",
	//"secondshower_U_nhit",
	//"secondshower_Y_dot",
	//"shr_trkfit_2cm_dedx_max",
	//"secondshower_U_dot",
	//"secondshower_Y_vtxdist",
	//"secondshower_Y_nhit",
	//"secondshower_Y_anglediff",
	//"shr2_trackEndProximity",
	//"shr_energyFraction",
	//"shr_distance",
	//"DeltaRMS2h",
	//"shr_trkfit_gap10_dedx_max"]

	//std::vector<float> data {_evt.secondshower_V_anglediff, static_cast<float>(_evt.secondshower_V_nhit), _evt.CylFrac2h_1cm, _evt.shrPCA1CMed_5cm, _evt.secondshower_U_vtxdist, static_cast<float>(_evt.shrsubclusters), _evt.secondshower_V_vtxdist, _evt.secondshower_V_dot,
	//						 _evt.shr2_distance, _evt.shr12_p1_dstart, _evt.secondshower_U_anglediff, _evt.shrMCSMom, _evt.shrmoliereavg, static_cast<float>(_evt.n_showers_contained), _evt.shr_energy_second_cali, static_cast<float>(_evt.secondshower_U_nhit), _evt.secondshower_Y_dot,
	//						 _evt.shr_trkfit_2cm_dedx_max, _evt.secondshower_U_dot, _evt.secondshower_Y_vtxdist, static_cast<float>(_evt.secondshower_Y_nhit), _evt.secondshower_Y_anglediff, _evt.shr2_trackEndProximity, _evt.shr_energyFraction, _evt.shr_distance, _evt.DeltaRMS2h,
	//						 _evt.shr_trkfit_gap10_dedx_max };

    // Jul 13 model (pions training)
    //"shr_trkfit_2cm_dedx_max",
    //"secondshower_Y_dot",
    //"secondshower_U_anglediff",
    //"secondshower_Y_anglediff",
    //"secondshower_V_anglediff",
    //"secondshower_V_nhit",
    //"secondshower_U_dot",
    //"n_showers_contained",
    //"DeltaRMS2h",
    //"shrMCSMom",
    //"shr2_trackEndProximity",
    //"shr2_distance",
    //"secondshower_Y_nhit",
    //"secondshower_V_vtxdist",
    //"shr_trkfit_gap10_dedx_max",
    //"shr12_p1_dstart",
    //"secondshower_Y_vtxdist",
    //"secondshower_U_vtxdist",
    //"shr_energyFraction",
    //"shrPCA1CMed_5cm",
    //"shr_energy_second_cali",
    //"CylFrac2h_1cm",
    //"shrmoliereavg",
    //"shrsubclusters",
    //"secondshower_U_nhit",
    //"secondshower_V_dot",
    //"shr_distance",
    //"shr2_pfpgeneration"
	
	std::vector<float> data {_evt.shr_trkfit_2cm_dedx_max, _evt.secondshower_Y_dot, _evt.secondshower_U_anglediff, _evt.secondshower_Y_anglediff, _evt.secondshower_V_anglediff, static_cast<float>(_evt.secondshower_V_nhit),
							 _evt.secondshower_U_dot, static_cast<float>(_evt.n_showers_contained), _evt.DeltaRMS2h, _evt.shrMCSMom, _evt.shr2_trackEndProximity, _evt.shr2_distance, static_cast<float>(_evt.secondshower_Y_nhit),
							 _evt.secondshower_V_vtxdist, _evt.shr_trkfit_gap10_dedx_max, _evt.shr12_p1_dstart, _evt.secondshower_Y_vtxdist, _evt.secondshower_U_vtxdist, _evt.shr_energyFraction, _evt.shrPCA1CMed_5cm,
							 _evt.shr_energy_second_cali, _evt.CylFrac2h_1cm, _evt.shrmoliereavg, static_cast<float>(_evt.shrsubclusters), static_cast<float>(_evt.secondshower_U_nhit), _evt.secondshower_V_dot,
							 _evt.shr_distance, static_cast<float>(_evt.shr2_pfpgeneration) };
	
	
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
	
	// Apr 19, with track score

	//["trk_score",
	//	"trk_llr_pid_score",
	//	"trk_daughters",
	//	"trk_end_spacepoints",
	//	"trk_bragg_pion_max",
	//	"trk_bragg_mip_max",
	//	"trk_dEdx_trunk_max"]
	
	/*
	std::vector<float> data;
	if (trackID == 1) {
		std::vector<float> data_init {_evt.trk_score, _evt.trk_llr_pid_score, static_cast<float>(_evt.trk_daughters), static_cast<float>(_evt.trk_end_spacepoints), _evt.trk_bragg_pion_max, _evt.trk_bragg_mip_max, _evt.trk_dEdx_trunk_max};
		data = data_init;
	}
	else if (trackID == 2) {
		std::vector<float> data_init {_evt.trk2_score, _evt.trk2_llr_pid_score, static_cast<float>(_evt.trk2_daughters), static_cast<float>(_evt.trk2_end_spacepoints), _evt.trk2_bragg_pion_max, _evt.trk2_bragg_mip_max, _evt.trk2_dEdx_trunk_max};
		data = data_init;
	}
	else if (trackID == 3) {
		std::vector<float> data_init {_evt.trk3_score, _evt.trk3_llr_pid_score, static_cast<float>(_evt.trk3_daughters), static_cast<float>(_evt.trk3_end_spacepoints), _evt.trk3_bragg_pion_max, _evt.trk3_bragg_mip_max, _evt.trk3_dEdx_trunk_max};
		data = data_init;
	}
	else {
		std::cout << "BDT Tool: invalid trackID provided." << std::endl;
		exit(1);
	}
	*/

	// Jul 13, pions
    //"trk_llr_pid_score",
    //"trk_bragg_mip_max",
    //"trk_daughters",
    //"trk_end_spacepoints",
    //"trk_score",
    //"trk_dEdx_trunk_max",
    //"trk_bragg_pion_max"

	std::vector<float> data;
	if (trackID == 1) {
		std::vector<float> data_init {_evt.trk_llr_pid_score, _evt.trk_bragg_mip_max, static_cast<float>(_evt.trk_daughters), static_cast<float>(_evt.trk_end_spacepoints), _evt.trk_score, _evt.trk_dEdx_trunk_max, _evt.trk_bragg_pion_max};
		data = data_init;
	}
	else if (trackID == 2) {
		std::vector<float> data_init {_evt.trk2_llr_pid_score, _evt.trk2_bragg_mip_max, static_cast<float>(_evt.trk2_daughters), static_cast<float>(_evt.trk2_end_spacepoints), _evt.trk2_score, _evt.trk2_dEdx_trunk_max, _evt.trk2_bragg_pion_max};
		data = data_init;
	}
	else if (trackID == 3) {
		std::vector<float> data_init {_evt.trk3_llr_pid_score, _evt.trk3_bragg_mip_max, static_cast<float>(_evt.trk3_daughters), static_cast<float>(_evt.trk3_end_spacepoints), _evt.trk3_score, _evt.trk3_dEdx_trunk_max, _evt.trk3_bragg_pion_max};
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
	
	// Jul 11

	//["trk_bragg_pion_max",
	//"trk_bragg_mip_max",
	//"trk_end_spacepoints",
	//"trk_score",
	//"trk_daughters",
	//"trk_llr_pid_score",
	//"trk_dEdx_trunk_max"]
	/*
	std::vector<float> data;
	if (trackID == 1) {
		std::vector<float> data_init {_evt.trk_bragg_pion_max, _evt.trk_bragg_mip_max, static_cast<float>(_evt.trk_end_spacepoints), _evt.trk_score, static_cast<float>(_evt.trk_daughters),  _evt.trk_llr_pid_score, _evt.trk_dEdx_trunk_max};
		data = data_init;
	}
	else if (trackID == 2) {
		std::vector<float> data_init {_evt.trk2_bragg_pion_max, _evt.trk2_bragg_mip_max, static_cast<float>(_evt.trk2_end_spacepoints), _evt.trk2_score, static_cast<float>(_evt.trk2_daughters),  _evt.trk2_llr_pid_score, _evt.trk2_dEdx_trunk_max};
		data = data_init;
	}
	else if (trackID == 3) {
		std::vector<float> data_init {_evt.trk3_bragg_pion_max, _evt.trk3_bragg_mip_max, static_cast<float>(_evt.trk3_end_spacepoints), _evt.trk3_score, static_cast<float>(_evt.trk3_daughters),  _evt.trk3_llr_pid_score, _evt.trk3_dEdx_trunk_max};
		data = data_init;
	}
	else {
		std::cout << "BDT Tool: invalid trackID provided." << std::endl;
		exit(1);
	}
	*/

	// Jul 13
	//"trk_bragg_pion_max",
	//"trk_bragg_mip_max",
	//"trk_end_spacepoints",
	//"trk_score",
	//"trk_daughters",
	//"trk_llr_pid_score"
	//"trk_dEdx_trunk_max"

	std::vector<float> data;
	if (trackID == 1) {
		std::vector<float> data_init {_evt.trk_bragg_pion_max, _evt.trk_bragg_mip_max, static_cast<float>(_evt.trk_end_spacepoints), _evt.trk_score, static_cast<float>(_evt.trk_daughters),  _evt.trk_llr_pid_score, _evt.trk_dEdx_trunk_max};
		data = data_init;
	}
	else if (trackID == 2) {
		std::vector<float> data_init {_evt.trk2_bragg_pion_max, _evt.trk2_bragg_mip_max, static_cast<float>(_evt.trk2_end_spacepoints), _evt.trk2_score, static_cast<float>(_evt.trk2_daughters),  _evt.trk2_llr_pid_score, _evt.trk2_dEdx_trunk_max};
		data = data_init;
	}
	else if (trackID == 3) {
		std::vector<float> data_init {_evt.trk3_bragg_pion_max, _evt.trk3_bragg_mip_max, static_cast<float>(_evt.trk3_end_spacepoints), _evt.trk3_score, static_cast<float>(_evt.trk3_daughters),  _evt.trk3_llr_pid_score, _evt.trk3_dEdx_trunk_max};
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

	xgreturn = XGBoosterPredictFromDMatrix(boosterPionProtonRHC, matrix_pionProton, config, &out_shape, &out_dim, &out_result);

    // free memory
    xgreturn = XGDMatrixFree(matrix_pionProton);
    
    // check return code
    assert(xgreturn == 0);

    return *out_result;
}

