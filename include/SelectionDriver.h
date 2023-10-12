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

	// Run BDT selection on all samples
    void runBDTSelectionFull();

	// Run BDT selection on detector variations
	void runBDTSelectionDetVarFHC();
	void runBDTSelectionDetVarRHC();

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
	// Using newly processed ntuple files
	// Run 1 FHC:  2.192e+20 POT, 5748692.0 triggers
	// Run 1 RHC:  6.053e+19 POT, 1458253.0 triggers
	// Run 2 FHC:  1.268e+20 POT, 3535129.0 triggers
	// Run 2 RHC:  2.591e+20 POT, 5422907.0 triggers
	// Run 3 RHC:  5.003e+20 POT, 10349610.0 triggers [8504401.0 Pre, 1847097.0 Post]
	// Run 4a RHC: 8.209e+18 POT, 328921.0 triggers
	// Run 4 FHC: 2.075e+20 POT, 4131149.0 triggers
	// Run 5 FHC: 2.231e+20 POT, 5154196.0 triggers	

	// Beam On
	// Run 1 FHC: 	2e20 POT, 5268046.0 triggers
	// Run 1 RHC: 	6.107e19 POT, 1470984.0 triggers
	// Run 2a FHC:	3.315e20 POT, 8370956.0 triggers
	// Run 2b RHC:  1.334e20 POT, 3167451.0 triggers
	// Run 3 RHC:  5.013e+20 POT, 10371821.0 triggers [8528271.0 pre, 1845438.0 post]
	// Run 4 RHC:  (4a) + 2.205e+20 POT, 4730492.0 triggers [~85% of sample, to be updated] (4b) + 1.683e+19 POT, 333034.0 triggers (4c) = 2.37e20 POT, 5063526 triggers (to be updated)
	// Run 4 FHC:  1.259e+20 POT, 2470668.0 triggers (4c) + 8.374e+19 POT, 1702903.0 triggers (4d)  = 2.0964e+20 POT, 4173571 triggers
	// Run 5 FHC:   2.183e+20 POT, 5042362.0 triggers [Note -- needs to be updated once final makeup jobs run with newer version]
	
	// Beam Off
	std::string filename_beamoff_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run1_fhc.root"; // Triggers FHC: 4582248.27
	std::string filename_beamoff_run1_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run1_rhc.root"; // Triggers RHC: 6425820.55
	std::string filename_beamoff_run2a_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run2_fhc.root"; // Triggers FHC: 10021551.40
	std::string filename_beamoff_run2b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run2_rhc.root"; // Triggers RHC: 20966715.70
	std::string filename_beamoff_run3b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run3b_rhc.root"; // Triggers RHC: Pre: 18512803.475, Post: 14136286.5
	std::string filename_beamoff_run4_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run4_rhc.root";   // Triggers RHC:  17395694.925 (4a, 4b, 4c)
	std::string filename_beamoff_run4_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run4_fhc.root";   // Triggers FHC:  8060024.70 (4c) + 17432345.70 (4d)
	std::string filename_beamoff_run5_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run5_fhc.root";   // Triggers FHC:  19256341.475
	
	// Nu Overlay
	std::string filename_mc_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay_ppfxfix/numi_nu_overlay_pion_ntuples_run1_fhc_slim.root"; // POT: 2.22804e+21
	std::string filename_mc_run1_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay_ppfxfix/numi_nu_overlay_pion_ntuples_run1_rhc_slim.root"; // POT: 1.08998e+21
	std::string filename_mc_run2a_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay_ppfxfix/numi_nu_overlay_pion_ntuples_run2_fhc_slim.root"; // POT: 1.94607e+21
	std::string filename_mc_run2b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay_ppfxfix/numi_nu_overlay_pion_ntuples_run2_rhc_slim.root"; // POT: 1.44501e+21
	std::string filename_mc_run3b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay_ppfxfix/numi_nu_overlay_pion_ntuples_run3_rhc_slim.root"; // POT: 1.94144e+21
	std::string filename_mc_run4_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay_ppfxfix/numi_nu_overlay_pion_ntuples_run4_rhc_slim.root"; // POT: 2.08854e+21 (4b, 4b)
	std::string filename_mc_run4_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay_ppfxfix/numi_nu_overlay_pion_ntuples_run4_fhc_slim.root"; // POT: 2.02283e+21 (4c, 4d)
	std::string filename_mc_run5_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay_ppfxfix/numi_nu_overlay_pion_ntuples_run5_fhc_slim.root"; // POT: 1.92994e+21
	
	// Dirt Overlay
	std::string filename_dirt_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run1_fhc_slim.root"; // POT: 1.68389e+21
	std::string filename_dirt_run1_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run1_rhc_slim.root"; // POT: 2.30452e+20
	std::string filename_dirt_run2a_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run2a_fhc_slim.root"; // POT: 1.51487e+20
	std::string filename_dirt_run2b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run2b_rhc_slim.root"; // POT: 1.25429e+20
	std::string filename_dirt_run3b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run3b_rhc_slim.root"; // POT: 1.04239e+21
	std::string filename_dirt_run4_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run4_rhc_slim.root"; // POT: 3.42645e+20
	std::string filename_dirt_run4_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run4_fhc_slim.root"; // POT: 1.54423e+20 (4c) + 2.44273e+20 (4d)
	std::string filename_dirt_run5_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run5_fhc_slim.root"; // POT: 3.61101e+20
	
	// Intrinsic Nue Overlay -- Testing/Validation/Analysis samples
	std::string filename_intrinsic_test_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay_ppfxfix/numi_nue_overlay_pion_ntuples_run1_fhc_test_slim.root"; // POT: 1.25378e+22
	std::string filename_intrinsic_test_run1_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay_ppfxfix/numi_nue_overlay_pion_ntuples_run1_rhc_test_slim.root"; // POT: 2.25504e+22
	std::string filename_intrinsic_test_run2a_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay_ppfxfix/numi_nue_overlay_pion_ntuples_run2_fhc_test_slim.root"; // POT: 3.81712e+22
	std::string filename_intrinsic_test_run2b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay_ppfxfix/numi_nue_overlay_pion_ntuples_run2_rhc_test_slim.root"; // POT: 4.22458e+22
	std::string filename_intrinsic_test_run3b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay_ppfxfix/numi_nue_overlay_pion_ntuples_run3_rhc_test_slim.root"; // POT: 1.22077e+22
    std::string filename_intrinsic_test_run4_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay_ppfxfix/numi_nue_overlay_pion_ntuples_run4_rhc_test_slim.root"; // POT: 2.45255e+22 (4a, 4b)
	std::string filename_intrinsic_test_run4_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay_ppfxfix/numi_nue_overlay_pion_ntuples_run4_fhc_test_slim.root"; // POT: 2.84875e+22 (4c, 4d)
	std::string filename_intrinsic_test_run5_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay_ppfxfix/numi_nue_overlay_pion_ntuples_run5_fhc_test_slim.root"; // POT: 2.10906e+22

	// Intrinsic Nue Overlay -- Training samples
	std::string filename_intrinsic_train_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run1_fhc_slim_train.root"; 
	std::string filename_intrinsic_train_run1_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run1_rhc_slim_train.root"; 
	std::string filename_intrinsic_train_run2a_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run2a_fhc_slim_train_goodruns.root";
	std::string filename_intrinsic_train_run2b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run2b_rhc_slim_train_goodruns.root";
	std::string filename_intrinsic_train_run3b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run3b_rhc_slim_train.root";
	std::string filename_intrinsic_train_run4_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run4b_rhc_slim_train.root";
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
    // Run 3 RHC
    std::string filename_detvar_CV_run3b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/detvars/rhc/numi_detvars_pion_ntuples_run3_rhc_CV_slim.root"; // POT: 2.47981e+21
    std::string filename_detvar_WireModX_run3b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/detvars/rhc/numi_detvars_pion_ntuples_run3_rhc_WireModX_slim.root"; // POT: 2.3453e+21 

	// --- POT Weights ---
	// Beam On
	// Beam Off
    double pot_weight_beamoff_run1_fhc = 1.254557; // 4582248.27 -- final
    double pot_weight_beamoff_run1_rhc = 0.226936; // 6425820.55 -- final
    double pot_weight_beamoff_run2a_fhc = 0.352753; // 10021551.40 -- final
    double pot_weight_beamoff_run2b_rhc = 0.258644; // 20966715.70 -- final
    double pot_weight_beamoff_run3b_rhc = 1; // placeholder fudge for code!
    double pot_weight_beamoff_run3b_rhc_pre = 0.459379;  // pre: 18512803.475 -- final
    double pot_weight_beamoff_run3b_rhc_post = 0.130664; // post: 14136286.5 -- final 
    double pot_weight_beamoff_run4_rhc = 0.291080; // 17395694.925 -- temp scaling
    double pot_weight_beamoff_run4_fhc = 0.162054; // 8060024.70 + 17432345.70 -- final
    double pot_weight_beamoff_run5_fhc = 0.267659; // 19256341.475 -- final

	// Nu Overlay
	double pot_weight_mc_run1_fhc = 0.098382; // 2.22804e+21 -- ppfxfix, final
	double pot_weight_mc_run1_rhc = 0.056029; // 1.08998e+21 -- ppfxfix, final
	double pot_weight_mc_run2a_fhc = 0.065157; // 1.94607e+21 -- ppfxfix, final
	double pot_weight_mc_run2b_rhc = 0.175154; // 1.44501e+21 -- ppfxfix, final
	double pot_weight_mc_run3b_rhc = 0.257695; // 1.94144e+21 -- ppfxfix, final
	double pot_weight_mc_run4_rhc = 0.113476; // 2.08854e+21 -- ppfxfix -- temp scaling
	double pot_weight_mc_run4_fhc = 0.102579; // 2.02283e+21 -- ppfxfix, final
	double pot_weight_mc_run5_fhc = 0.115599; // 1.92994e+21 -- ppfxfix, final 

	// Dirt Overlay
	double pot_weight_dirt_run1_fhc = 0.130175; // 1.68389e+21 -- final
	double pot_weight_dirt_run1_rhc = 0.265000; // 2.30452e+20 -- final
	double pot_weight_dirt_run2a_fhc = 0.837036; // 1.51487e+20 -- final
	double pot_weight_dirt_run2b_rhc = 2.017875; // 1.25429e+20 -- final
	double pot_weight_dirt_run3b_rhc = 0.479955; // 1.04239e+21 -- final
	double pot_weight_dirt_run4_rhc = 0.691678; // 3.42645e+20 -- temp scaling
	double pot_weight_dirt_run4_fhc = 0.520446; // 1.54423e+20 + 2.44273e+20 -- final
	double pot_weight_dirt_run5_fhc = 0.617833; // 3.61101e+20 -- final

	// Intrinsic Nue Overlay -- Testing/Validation/Analysis samples
	double pot_weight_intrinsic_test_run1_fhc = 0.017483; // 1.25378e+22 -- ppfxfix, final
	double pot_weight_intrinsic_test_run1_rhc = 0.002708; // 2.25504e+22 -- ppfxfix, final
	double pot_weight_intrinsic_test_run2a_fhc = 0.003322; // 3.81712e+22 -- ppfxfix, final
	double pot_weight_intrinsic_test_run2b_rhc = 0.005991; // 4.22458e+22 -- ppfxfix, final
	double pot_weight_intrinsic_test_run3b_rhc = 0.040982; // 1.22077e+22 -- ppfxfix, final
	double pot_weight_intrinsic_test_run4_rhc = 0.009663; // 2.45255e+22 -- ppfxfix, temp scaling
	double pot_weight_intrinsic_test_run4_fhc = 0.007284; // 2.84875e+22 -- ppfxfix, final
	double pot_weight_intrinsic_test_run5_fhc = 0.010578; // 2.10906e+22 -- ppfxfix, final 

	// Intrinsic Nue Overlay -- Training samples
	double pot_weight_intrinsic_train_run1_fhc = 1;
	double pot_weight_intrinsic_train_run1_rhc = 1;
	double pot_weight_intrinsic_train_run2a_fhc = 1;
	double pot_weight_intrinsic_train_run2b_rhc = 1;
	double pot_weight_intrinsic_train_run3b_rhc = 1;
	double pot_weight_intrinsic_train_run4_rhc = 1;
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
    // Run 3 RHC
    double pot_weight_detvar_CV_run3b_rhc = 0.202152; // 2.47981e+21
    double pot_weight_detvar_WireModX_run3b_rhc = 0.213746; 

};

#endif