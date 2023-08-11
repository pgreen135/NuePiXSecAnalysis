#ifndef SELECTIONDRIVER_H
#define SELECTIONDRIVER_H

// class to run selections on datasets

#include <string>

#include "../include/Utility.h"


class SelectionDriver {

public:	

	// ----------------------------------
	// Constructor
	SelectionDriver();

	// Destructor
	~SelectionDriver(){};

	// Run Selection BDT FHC
	void runBDTSelectionFHC();

	// Run Selection BDT RHC
	void runBDTSelectionRHC();

	// Run BDT selection on FHC detector variations
	void runBDTSelectionDetVarFHC();

	// Create training tree for electron-photon BDT FHC
	void createElectronPhotonBDTTrainingTreeFHC();

	// Create training tree for electron-photon BDT RHC
	void createElectronPhotonBDTTrainingTreeRHC();

	// Create training tree for pion-proton BDT FHC
	void createPionProtonBDTTrainingTreeFHC();

	// Create training tree for pion-proton BDT RHC
	void createPionProtonBDTTrainingTreeRHC();

	// ----------------------------------


protected:

	// classes
	Utility _utility;
  
	// --- NTuple Files ---
	// Beam On
	// Run 1 FHC: 	2e20 POT, 5268046.0 triggers
	// Run 1 RHC: 	6.107e19 POT, 1470984.0 triggers
	// Run 2a FHC:	3.315e20 POT, 8370956.0 triggers
	// Run 2b RHC:  1.334e20 POT, 3167451.0 triggers
	// Run 3b RHC:  5.013e+20 POT, 10371821.0 triggers [8528271.0 pre, 1845438.0 post]
	// Run 4c RHC:  1.613e+19 POT, 319286.0 triggers
	// Run 4 FHC:  1.21e+20 POT, 2374195.0 triggers (4c) + 8.374e+19 POT, 1702903.0 triggers (4d) --- Warning, potentially issues; need to recaculate once samples finalised
	// Run 5 FHC:   2e20 POT, 5268046.0 triggers ---- NOT CORRECT!!! just for testing

	// Beam Off
	std::string filename_beamoff_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run1_fhc.root"; // Triggers FHC: 4582248.27
	std::string filename_beamoff_run1_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run1_rhc.root"; // Triggers RHC: 6425820.55
	std::string filename_beamoff_run2a_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run2a_fhc.root"; // Triggers FHC:	18785678.975
	std::string filename_beamoff_run2b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run2b_rhc.root"; // Triggers RHC: 12202588.125
	std::string filename_beamoff_run3b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run3b_rhc.root"; // Triggers RHC: Pre: 18512803.475, Post: 14136286.5
	std::string filename_beamoff_run4_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run4_fhc.root";   // Triggers FHC:  8060024.70 (4c) + 17432345.70 (4d)
	std::string filename_beamoff_run5_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run5_fhc.root";   // Triggers FHC:  19256341.475
	
	// Nu Overlay
	std::string filename_mc_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay/numi_nu_overlay_pion_ntuples_run1_fhc_slim.root"; // POT: 2.37912e+21
	std::string filename_mc_run1_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay/numi_nu_overlay_pion_ntuples_run1_rhc_slim.root"; // POT: 1.10485e+21
	std::string filename_mc_run2a_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay/numi_nu_overlay_pion_ntuples_run2a_fhc_slim.root"; // POT: 1.1207e+21
	std::string filename_mc_run2b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay/numi_nu_overlay_pion_ntuples_run2b_rhc_slim.root"; // POT: 1.12006e+21
	std::string filename_mc_run3b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay/numi_nu_overlay_pion_ntuples_run3b_rhc_slim.root"; // POT: 2.01629e+21
	std::string filename_mc_run4_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay/numi_nu_overlay_pion_ntuples_run4_fhc_slim.root"; // POT: 8.65945e+20 (4c) + 1.2933e+21 (4d)
	std::string filename_mc_run5_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay/numi_nu_overlay_pion_ntuples_run5_fhc_slim.root"; // POT: 1.76941e+21
	
	// Dirt Overlay
	std::string filename_dirt_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run1_fhc_slim.root"; // POT: 1.68389e+21
	std::string filename_dirt_run1_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run1_rhc_slim.root"; // POT: 2.30452e+20
	std::string filename_dirt_run2a_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run2a_fhc_slim.root"; // POT: 1.51487e+20
	std::string filename_dirt_run2b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run2b_rhc_slim.root"; // POT: 1.25429e+20
	std::string filename_dirt_run3b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run3b_rhc_slim.root"; // POT: 1.04239e+21
	std::string filename_dirt_run4_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run4_fhc_slim.root"; // POT: 1.54423e+20 (4c) + 2.44273e+20 (4d)
	std::string filename_dirt_run5_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run5_fhc_slim.root"; // POT: 3.61101e+20
	
	// Intrinsic Nue Overlay -- Testing/Validation/Analysis samples
	std::string filename_intrinsic_test_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run1_fhc_slim_test.root"; // POT: 1.27481e+22
	std::string filename_intrinsic_test_run1_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run1_rhc_slim_test.root"; // POT: 2.26176e+22
	std::string filename_intrinsic_test_run2a_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run2a_fhc_slim_test.root"; // POT: 3.86831e+22
	std::string filename_intrinsic_test_run2b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run2b_rhc_slim_test.root"; // POT: 4.22611e+22
	std::string filename_intrinsic_test_run3b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run3b_rhc_slim_test.root"; // POT: 1.22077e+22

	std::string filename_intrinsic_test_run4_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run4_fhc_slim_test.root"; // POT: 2.90568e+22
	std::string filename_intrinsic_test_run5_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run5_fhc_slim_test.root"; // POT: 1.88098e+22

	// Intrinsic Nue Overlay -- Training samples
	std::string filename_intrinsic_train_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run1_fhc_slim_train.root"; 
	std::string filename_intrinsic_train_run1_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run1_rhc_slim_train.root"; 
	std::string filename_intrinsic_train_run2a_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run2a_fhc_slim_train.root";
	std::string filename_intrinsic_train_run2b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run2b_rhc_slim_train.root";
	std::string filename_intrinsic_train_run3b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run3b_rhc_slim_train.root";

	std::string filename_intrinsic_train_run4_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run4_fhc_slim_train.root";
	std::string filename_intrinsic_train_run5_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run5_fhc_slim_train.root";

	// CCNCPi0 Overlay
	std::string filename_ccncpizero_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/ccncpi0_overlay/numi_ccncpi0_overlay_pion_ntuples_run1_fhc_slim.root"; // POT: 1.31412e+22
	std::string filename_ccncpizero_run3b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/ccncpi0_overlay/numi_ccncpi0_overlay_pion_ntuples_run3b_rhc_slim.root"; // POT: 2.0829e+22
	std::string filename_ccncpizero_run5_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/ccncpi0_overlay/numi_ccncpi0_overlay_pion_ntuples_run5_fhc_slim.root"; // POT: 8.84556e+21

    // Detector Variations
    // Run 1 FHC
    std::string filename_detvar_CV_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/detvars/numi_detvars_pion_ntuples_run1_fhc_CV_slim.root"; // POT: 7.63091e+20
    std::string filename_detvar_SCE_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/detvars/numi_detvars_pion_ntuples_run1_fhc_SCE_slim.root"; // POT: 7.53234e+20
    std::string filename_detvar_Recombination_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/detvars/numi_detvars_pion_ntuples_run1_fhc_Recombination_slim.root"; // POT: 7.53761e+20
    std::string filename_detvar_WireModX_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/detvars/numi_detvars_pion_ntuples_run1_fhc_WireModX_slim.root"; // POT: 7.60069e+20
    std::string filename_detvar_WireModYZ_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/detvars/numi_detvars_pion_ntuples_run1_fhc_WireModYZ_slim.root"; // POT: 7.50974e+20
    std::string filename_detvar_WireModThetaYZ_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/detvars/numi_detvars_pion_ntuples_run1_fhc_WireModThetaYZ_slim.root"; // POT: 7.65315e+20


	// --- POT Weights ---
	// Beam On
	// Beam Off
    double pot_weight_beamoff_run1_fhc = 1.149664; // 4582248.27
    double pot_weight_beamoff_run1_rhc = 0.228918; // 6425820.55
    double pot_weight_beamoff_run2a_fhc = 0.445603; // 18785678.975
    double pot_weight_beamoff_run2b_rhc = 0.259572; // 12202588.125
    double pot_weight_beamoff_run3b_rhc_pre = 0.460669; // pre: 18512803.475
    double pot_weight_beamoff_run3b_rhc_post = 0.130546; // post: 14136286.5
    double pot_weight_beamoff_run4_fhc = 0.159934; // 8060024.70 + 17432345.70 // check
    double pot_weight_beamoff_run5_fhc = 0.273575; // 19256341.475 // placeholder

	// Nu Overlay
	double pot_weight_mc_run1_fhc = 0.084065; // 2.37912e+21
	double pot_weight_mc_run1_rhc = 0.055274; // 1.10485e+21
	double pot_weight_mc_run2a_fhc = 0.295797; // 1.1207e+21
	double pot_weight_mc_run2b_rhc = 0.119101; // 1.12006e+2
	double pot_weight_mc_run3b_rhc = 0.248625; // 2.01629e+21
	double pot_weight_mc_run4_fhc = 0.094820; // 8.65945e+20 + 1.2933e+21 // check
	double pot_weight_mc_run5_fhc = 0.113933; // 1.76941e+21    // placeholder

	// Dirt Overlay
	double pot_weight_dirt_run1_fhc = 0.118773; // 1.68389e+21
	double pot_weight_dirt_run1_rhc = 0.265044; // 2.30452e+20
	double pot_weight_dirt_run2a_fhc = 2.18831; // 1.51487e+20
	double pot_weight_dirt_run2b_rhc = 1.06355; // 1.25429e+20
	double pot_weight_dirt_run3b_rhc = 0.480914; // 1.04239e+21
	double pot_weight_dirt_run4_fhc = 0.513524; // 1.54423e+20  + 2.44273e+20  // check
	double pot_weight_dirt_run5_fhc = 0.553862; // 3.61101e+20 // placeholder

	// Intrinsic Nue Overlay -- Testing/Validation/Analysis samples
	double pot_weight_intrinsic_test_run1_fhc = 0.015689; // 1.27481e+22
	double pot_weight_intrinsic_test_run1_rhc = 0.002700; // 2.26176e+22
	double pot_weight_intrinsic_test_run2a_fhc = 0.008570; // 3.86831e+22
	double pot_weight_intrinsic_test_run2b_rhc = 0.003157; // 4.22611e+22
	double pot_weight_intrinsic_test_run3b_rhc = 0.041064; // 1.22077e+22
	double pot_weight_intrinsic_test_run4_fhc = 0.007046; // 2.90568e+22  // check
	double pot_weight_intrinsic_test_run5_fhc = 0.010633; // 1.88098e+22 // placeholder

	// Intrinsic Nue Overlay -- Training samples
	double pot_weight_intrinsic_train_run1_fhc = 1;
	double pot_weight_intrinsic_train_run1_rhc = 1;
	double pot_weight_intrinsic_train_run2a_fhc = 1;
	double pot_weight_intrinsic_train_run2b_rhc = 1;
	double pot_weight_intrinsic_train_run3b_rhc = 1;
	double pot_weight_intrinsic_train_run4_fhc = 1;
	double pot_weight_intrinsic_train_run5_fhc = 1;

	// CCNCPi0 Overlay Training samples
	double pot_weight_ccncpizero_run1_fhc = 1; // 1.31412e+22
	double pot_weight_ccncpizero_run3b_rhc = 1; // 2.0829e+22
	double pot_weight_ccncpizero_run5_fhc = 1; // 8.84556e+21

	// Detector Variations
    // Run 1 FHC
    double pot_weight_detvar_CV_run1_fhc = 0.262092; // 7.63091e+20
    double pot_weight_detvar_SCE_run1_fhc = 0.265522; // 7.53234e+20
    double pot_weight_detvar_Recombination_run1_fhc = 0.265336; // 7.53761e+20
    double pot_weight_detvar_WireModX_run1_fhc = 0.263134; // 7.60069e+20
    double pot_weight_detvar_WireModYZ_run1_fhc = 0.266321; // 7.50974e+20
    double pot_weight_detvar_WireModThetaYZ_run1_fhc = 0.261330; // 7.65315e+20

};

#endif