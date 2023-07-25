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
	// Run 4c FHC:  1.21e+20 POT, 2374195.0 triggers
	// Run 4d FHC: 	2e20 POT ---- NOT CORRECT!!! just for testing
	// Run 5 FHC:   2e20 POT ---- NOT CORRECT!!! just for testing

	// Beam Off
	std::string filename_beamoff_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run1.root"; // Triggers FHC: 4582248.27
	std::string filename_beamoff_run1_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run1.root"; // Triggers RHC: 6425820.55
	std::string filename_beamoff_run2a_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run2a_fhc.root"; // Triggers FHC:	18785678.975
	std::string filename_beamoff_run2b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run2b_rhc.root"; // Triggers RHC: 12202588.125
	std::string filename_beamoff_run3b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run3b_rhc.root"; // Triggers RHC: Pre: 18512803.475, Post: 14136286.5 
	std::string filename_beamoff_run4c_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run4c.root"; // Triggers FHC:  8060024.70
	std::string filename_beamoff_run4d_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/beam_off/numi_beam_off_pion_ntuples_run4d.root"; // Triggers FHC: 17057035.80 [warning, missing runs]
	
	// Nu Overlay
	std::string filename_mc_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay/numi_nu_overlay_pion_ntuples_run1_fhc_slim.root"; // POT: 2.37912e+21
	std::string filename_mc_run1_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay/numi_nu_overlay_pion_ntuples_run1_rhc_slim.root"; // POT: 1.10485e+21
	std::string filename_mc_run2a_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay/numi_nu_overlay_pion_ntuples_run2a_fhc_slim.root"; // POT: 1.1207e+21
	std::string filename_mc_run2b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay/numi_nu_overlay_pion_ntuples_run2b_rhc_slim.root"; // POT: 1.12006e+21
	std::string filename_mc_run3b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay/numi_nu_overlay_pion_ntuples_run3b_rhc_slim.root"; // POT: 2.01629e+21
	std::string filename_mc_run4c_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay/numi_nu_overlay_pion_ntuples_run4c_fhc_slim.root"; // POT: 8.65945e+20
	std::string filename_mc_run4d_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay/numi_nu_overlay_pion_ntuples_run4d_fhc_slim.root"; // POT: 1.2933e+21
	std::string filename_mc_run5_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nu_overlay/numi_nu_overlay_pion_ntuples_run5_fhc_slim.root"; // POT: 1.76489e+21 
	
	// Dirt Overlay
	std::string filename_dirt_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run1_fhc_slim.root"; // POT: 1.68389e+21
	std::string filename_dirt_run1_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run1_rhc_slim.root"; // POT: 2.30452e+20
	std::string filename_dirt_run2a_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run2a_fhc_slim.root"; // POT: 1.51487e+20
	std::string filename_dirt_run2b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run2b_rhc_slim.root"; // POT: 1.25429e+20
	std::string filename_dirt_run3b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run3b_rhc_slim.root"; // POT: 1.04239e+21
	std::string filename_dirt_run4c_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run4c_fhc_slim.root"; // POT: 1.54423e+20
	std::string filename_dirt_run4d_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run4d_fhc_slim.root"; // POT: 2.44273e+20
	std::string filename_dirt_run5_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/dirt_overlay/numi_dirt_overlay_pion_ntuples_run5_fhc_slim.root"; // POT: 3.60484e+20
	
	// Intrinsic Nue Overlay
	std::string filename_intrinsic_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run1_fhc_slim.root"; // POT: 2.42248e+22
	std::string filename_intrinsic_run1_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run1_rhc_slim.root"; // POT: 4.10999e+22
	std::string filename_intrinsic_run2a_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run2a_fhc_slim.root"; // POT: 8.11203e+22
	std::string filename_intrinsic_run2b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run2b_rhc_slim.root"; // POT: 8.51696e+22
	std::string filename_intrinsic_run3b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/nue_overlay/numi_nue_overlay_pion_ntuples_run3b_rhc_slim.root"; // POT: 2.53921e+22

	// CCNCPi0 Overlay
	std::string filename_ccncpizero_run1_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/ccncpi0_overlay/numi_ccncpi0_overlay_pion_ntuples_run1_fhc_slim.root"; // POT: 1.31412e+22
	std::string filename_ccncpizero_run3b_rhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/ccncpi0_overlay/numi_ccncpi0_overlay_pion_ntuples_run3b_rhc_slim.root"; // POT: 2.0829e+22
	std::string filename_ccncpizero_run5_fhc = "/Users/patrick/Data/MicroBooNE/CrossSections/customPeLeeNTuples/ccncpi0_overlay/numi_ccncpi0_overlay_pion_ntuples_run5_fhc_slim.root"; // POT: 8.84556e+21

	// --- POT Weights ---
	// Beam On
	// Beam Off
    double pot_weight_beamoff_run1_fhc = 1.149664; // 4582248.27
    double pot_weight_beamoff_run1_rhc = 0.228918; // 6425820.55
    double pot_weight_beamoff_run2a_fhc = 0.445603; // 18785678.975
    double pot_weight_beamoff_run2b_rhc = 0.259572; // 12202588.125
    double pot_weight_beamoff_run3b_rhc_pre = 0.460669; // pre: 18512803.475
    double pot_weight_beamoff_run3b_rhc_post = 0.130546; // post: 14136286.5
    double pot_weight_beamoff_run4c_fhc = 0.294564; // 8060024.70
    double pot_weight_beamoff_run4d_fhc = 1; // 17057035.80 [warning, missing runs]

	// Nu Overlay
	double pot_weight_mc_run1_fhc = 0.084065; // 2.37912e+21
	double pot_weight_mc_run1_rhc = 0.055274; // 1.10485e+21
	double pot_weight_mc_run2a_fhc = 0.295797; // 1.1207e+21
	double pot_weight_mc_run2b_rhc = 0.119101; // 1.12006e+21
	double pot_weight_mc_run3b_rhc = 0.248625; // 2.01629e+21
	double pot_weight_mc_run4c_fhc = 0.139829; // 8.65945e+20
	double pot_weight_mc_run4d_fhc = 0.154653; // 1.2933e+21    // placeholder
	double pot_weight_mc_run5_fhc = 0.113322; // 1.76489e21    // placeholder

	// Dirt Overlay
	double pot_weight_dirt_run1_fhc = 0.118773; // 1.68389e+21
	double pot_weight_dirt_run1_rhc = 0.265044; // 2.30452e+20
	double pot_weight_dirt_run2a_fhc = 2.18831; // 1.51487e+20
	double pot_weight_dirt_run2b_rhc = 1.06355; // 1.25429e+20
	double pot_weight_dirt_run3b_rhc = 0.480914; // 1.04239e+21
	double pot_weight_dirt_run4c_fhc = 0.783562; // 1.54423e+20
	double pot_weight_dirt_run4d_fhc = 0.818756; // 2.44273e+20
	double pot_weight_dirt_run5_fhc = 0.554810; // 3.60484e+20

	// Intrinsic Nue Overlay
	double pot_weight_intrinsic_run1_fhc = 0.008256; // 2.42248e+22
	double pot_weight_intrinsic_run1_rhc = 0.001459; // 4.10999e+22
	double pot_weight_intrinsic_run2a_fhc = 0.002465; // 8.11203e+22
	double pot_weight_intrinsic_run2b_rhc = 0.001566; // 8.51696e+22
	double pot_weight_intrinsic_run3b_rhc = 0.019742; // 2.53921e+22

	// CCNCPi0 Overlay
	double pot_weight_ccncpizero_run1_fhc = 0.015219; // 1.31412e+22
	double pot_weight_ccncpizero_run3b_rhc = 0.024067; // 2.0829e+22
	double pot_weight_ccncpizero_run5_fhc = 0.022610; // 8.84556e+21


};

#endif