#ifndef EVENTCONTAINER_H
#define EVENTCONTAINER_H

// class to read and contain events from the pandora ntuples
// event information can then be passed as required to other parts of the analysis code
// variables public for ease of access

#include <string>

#include <TTree.h>

#include "Utility.h"

class EventContainer {

public:
	
	// ----------------------------------
	
	// Constructor
	EventContainer(TTree *tree, const Utility &utility);

	// Destructor
	~EventContainer(){};

	// Functions to classify the event
	void  EventClassifier(Utility::FileTypeEnums type);
	Utility::ClassificationEnums getEventClassification(Utility::FileTypeEnums type);

	// Functions to populate derived event variables
	void populateDerivedVariables(Utility::FileTypeEnums type);
	void GetSecondShowerClusterAngleDiff();
	void GetdEdxMax(bool includeGap);
	float GetTrackTrunkdEdxMax(unsigned int trackID);
    
    
    // ----------------------------------

    // -- Utility --
    Utility _utility;

	// --- Event classification ---
	Utility::ClassificationEnums classification;

	// -- Selection Information ---
	bool primaryTrackValid;
    bool secondaryTrackValid;

    bool primaryTrackPionlike;
    bool secondaryTrackPionlike;

	// --- Event information ---
	int run, sub, evt;			// run, subrun, event numbers

	// --- MC Truth ---
	// truth interaction properties
	int nu_pdg;					// Truth: neutrino pdg
	int ccnc; 					// Truth: CC or NC interaction
	int interaction;			// Truth: interaction code from GENIE
	float nu_e;        			// Truth: Neutrino Energy [GeV]
  	
  	int nmuon; 					// Truth: number of muons
  	
  	int nelec; 					// Truth: number of electrons
  	float elec_e;				// Truth: electron energy
  	
  	int npion; 					// Truth: number of charged pions
  	float pion_e;				// Truth: pion energy

  	int npi0; 					// Truth: number of neutral pions
  	
  	int nproton; 				// Truth: number of protons
  	float proton_e;				// Truth: proton energy

  	// truth interaction vertex
  	float true_nu_vtx_sce_x;     // True Neutrino Vtx Space Charge x
  	float true_nu_vtx_sce_y;     // True Neutrino Vtx Space Charge y
  	float true_nu_vtx_sce_z;     // True Neutrino Vtx Space Charge z

  	// --- Software trigger [MC only] ---
  	int swtrig;     			// Software Trigger
    int swtrig_pre;     		// Software Trigger before change -- Run 1
    int swtrig_post;     		// Software Trigger after change

    // --- Common optical filter [MC only] ---
    float opfilter_pe_beam; // Common Optical Filter (beam window)
    float opfilter_pe_veto; // Common Optical Filter (michel veto)

  	// --- Slice information ---
  	// number
  	int nslice;		// Reco - Slice: number of neutrino slices identified by the SliceID. Values are 0 or 1.
    int n_tracks;   // Reco - Slice: number of tracks identified with a track score cut
    int n_showers;  // Reco - Slice: number of showers with a shower score cut
    unsigned int n_showers_contained; // Reco - Slice: number of showers contained
    int n_showers_alt;
    int n_showers_above_threshold; 

  	// slice quality
  	float nu_purity_from_pfp;   // Truth: Neutrino Purity from PFP (how many out of all the hits are the neutrino)

  	// reconstruction completeness
  	unsigned int total_hits_y;		// Reco - Slice: total number hits on collection plane in neutrino slice
  	unsigned int shr_hits_y_tot;    // Reco - Shower: total number hits on collection plane in neutrino slice associated with showers
    unsigned int trk_hits_y_tot;    // Reco - Track: total number hits on collection plane in neutrino slice associated with tracks

    float associated_hits_fraction; // Reco - Slice: fraction of hits on collection plane in neutrino slice associated with tracks and showers (derived variable)
    float associated_hits_fraction_u; // Reco - Slice: fraction of hits on U plane in neutrino slice associated with tracks and showers (derived variable)
    float associated_hits_fraction_v; // Reco - Slice: fraction of hits on V plane in neutrino slice associated with tracks and showers (derived variable)
    float extra_energy_y;			// Reco - Slice: deposited energy in neutrino slice not associated with tracks or showers

  	// --- Neutrino Reconstruction ---
  	// reconstructed neutrino vertex, space charge corrected
  	float reco_nu_vtx_sce_x;    // Reco - Neutrino: neutrino Vtx Space Charge x
    float reco_nu_vtx_sce_y;    // Reco - Neutrino: neutrino Vtx Space Charge y
    float reco_nu_vtx_sce_z;    // Reco - Neutrino: neutrino Vtx Space Charge z

    float contained_fraction;   // Reco: hits in PFParticles contained in the fiducial volume over the total number of clustered hits in the slice

    // --- Cosmic Reconstruction ---
    float topological_score;  	// Reco - cosmic: topological Score
    float CosmicIPAll3D;        // Reco - cosmic: 3D distance of shower start from closest spacepoint of any pfp not in the neutrino slice

    // -- Shower Reconstruction ---
    // Primary Shower
    unsigned int shr_id;		// Reco - shower: Primary shower ID
    float shr_distance;         // Reco - shower: distance between leading shower vertex and reconstructed neutrino vertex
    float shr_score;            // Reco - shower: Pandora track score for the leading shower
    float shr_energy_cali;		// Reco - shower: Energy of the shower with the largest number of hits (in GeV) (calibrated)
    float shrmoliereavg;        // Reco - shower: average angle between the shower’s direction and its 3D spacepoints

    float shr_llrpid_dedx;		// Reco - shower: LLR PID score, shower electron-photon separation

    unsigned int shr_tkfit_nhits_Y;     // Reco - shower: number of hits in the 1x4 cm box on the Y plane with the track fitting
    unsigned int shr_tkfit_nhits_V;     // Reco - shower: number of hits in the 1x4 cm box on the V plane with the track fitting
    unsigned int shr_tkfit_nhits_U;     // Reco - shower: number of hits in the 1x4 cm box on the U plane with the track fitting

    unsigned int shr_tkfit_gap05_nhits_Y; 	// Reco - shower: number of hits in the 1x4 cm box on the Y plane with the track fitting, gap 5mm from start
    unsigned int shr_tkfit_gap05_nhits_V;   // Reco - shower: number of hits in the 1x4 cm box on the V plane with the track fitting, gap 5mm from start
    unsigned int shr_tkfit_gap05_nhits_U;   // Reco - shower: number of hits in the 1x4 cm box on the U plane with the track fitting, gap 5mm from start

    unsigned int shr_tkfit_gap10_nhits_Y; 	// Reco - shower: number of hits in the 1x4 cm box on the Y plane with the track fitting, gap 10mm from start
    unsigned int shr_tkfit_gap10_nhits_V;   // Reco - shower: number of hits in the 1x4 cm box on the V plane with the track fitting, gap 10mm from start
    unsigned int shr_tkfit_gap10_nhits_U;   // Reco - shower: number of hits in the 1x4 cm box on the U plane with the track fitting, gap 10mm from start

    float shr_tkfit_dedx_Y;      // Reco - shower: dE/dx of the leading shower on the Y plane with the track fitting
    float shr_tkfit_dedx_V;      // Reco - shower: dE/dx of the leading shower on the V plane with the track fitting
    float shr_tkfit_dedx_U;      // Reco - shower: dE/dx of the leading shower on the U plane with the track fitting
    float shr_trkfit_dedx_max;	 // Reco - shower: dE/dx of the leading shower on plane with the most hits (derived variable)

    float shr_tkfit_gap05_dedx_Y;      // Reco - shower: dE/dx of the leading shower on the Y plane with the track fitting, gap 5mm from vertex
    float shr_tkfit_gap05_dedx_V;      // Reco - shower: dE/dx of the leading shower on the V plane with the track fitting, gap 5mm from vertex
    float shr_tkfit_gap05_dedx_U;      // Reco - shower: dE/dx of the leading shower on the U plane with the track fitting, gap 5mm from vertex
    float shr_trkfit_gap05_dedx_max;   // Reco - shower: dE/dx of the leading shower on plane with the most hits (derived variable), gap 5mm from vertex

    float shr_tkfit_gap10_dedx_Y;      // Reco - shower: dE/dx of the leading shower on the Y plane with the track fitting, gap 10mm from vertex
    float shr_tkfit_gap10_dedx_V;      // Reco - shower: dE/dx of the leading shower on the V plane with the track fitting, gap 10mm from vertex
    float shr_tkfit_gap10_dedx_U;      // Reco - shower: dE/dx of the leading shower on the U plane with the track fitting, gap 10mm from vertex
    float shr_trkfit_gap10_dedx_max;   // Reco - shower: dE/dx of the leading shower on plane with the most hits (derived variable), gap 10mm from vertex
    
    float shrclusdir0; 	// direction of shower cluster on U plane
    float shrclusdir1; 	// direction of shower cluster on V plane
    float shrclusdir2; 	// direction of shower cluster on Y plane

    // Seconary Shower
    unsigned int shr2_id;		// Reco - shower: Secondary shower ID
    float shr2_energy;			// Reco - shower: energy of second shower (in GeV), note - not calibrated variable as missing from ntuples
    
    // All showers
    float shr_energy_tot_cali;  // Reco - shower: the energy of the showers (in GeV) (calibrated)
    float hits_ratio;           // Reco - shower: ratio between hits from showers and total number of hits in the slice
	float shr_energyFraction;	// Reco - shower: fraction of energy in primary shower vs. all showers (derived variable)

	// Second shower tagger analysis
	int secondshower_U_nhit;	// Reco - shower: number of hits of largest cluster not included in primary shower, U plane
	int secondshower_V_nhit;	// Reco - shower: number of hits of largest cluster not included in primary shower, V plane
	int secondshower_Y_nhit;	// Reco - shower: number of hits of largest cluster not included in primary shower, Y plane
	float secondshower_U_vtxdist;	// Reco - shower: distance of second shower cluster from neutrino vertex, U plane
	float secondshower_V_vtxdist;	// Reco - shower: distance of second shower cluster from neutrino vertex, V plane
	float secondshower_Y_vtxdist;	// Reco - shower: distance of second shower cluster from neutrino vertex, Y plane
	float secondshower_U_dir;	// Reco - shower: direction of second shower cluster relative to wire direction, U plane
	float secondshower_V_dir;	// Reco - shower: direction of second shower cluster relative to wire direction, U plane
	float secondshower_Y_dir;	// Reco - shower: direction of second shower cluster relative to wire direction, U plane

	float secondshower_U_anglediff;	// Reco - shower: opening angle between primary shower and second shower tagged cluster, U plane [derived variable]
	float secondshower_V_anglediff;	// Reco - shower: opening angle between primary shower and second shower tagged cluster, V plane [derived variable]
	float secondshower_Y_anglediff;	// Reco - shower: opening angle between primary shower and second shower tagged cluster, Y plane [derived variable]

    // --- Track Reconstruction ---
   	// Primary track
    unsigned int trk_id;	// Reco - track: primary track ID
    float trk_len;			// Reco - track: Length of the longest track
    float trk_distance;		// Reco - track: Distance between longest track start and reconstructed neutrino vertex
    float trk_score;		// Reco - track: Pandora track score for the longest track
    float trk_theta;        // Reco - track: Reconstructed theta angle for the longest track
    float trk_phi;          // Reco - track: Reconstructed phi angle for the longest track
    float trk_avg_deflection_mean; 		// Reco - track: average deflections mean longest track
    float trk_avg_deflection_stdev; 	// Reco - track: average deflections stdev longest track
    float trk_avg_deflection_separation_mean;
    float trk_sce_end_x;
    float trk_sce_end_y;
    float trk_sce_end_z;
    unsigned int trk_daughters; 		// Reco - track: number of daughters
    int trk_end_spacepoints;

    int trk_bkt_pdg;      // Backtracker - track: Backtrack PDG

    float trk_bragg_pion; 	// Reco - track: Track Bragg Likelihood Pion
    float trk_bragg_p;		// Reco - track: Track Bragg Likelihood Proton
    float trk_bragg_mu;		// Reco - track: Track Bragg Likelihood Muon
    float trk_bragg_mip;	// Reco - track: Track Bragg Likelihood MIP
    float trk_llr_pid_score;	// Reco - track: LLR PID longest track
    float trk_dEdx_trunk_max;   // Reco - track: average dE/dx of first third of track, plane with maximum number of hits [Requires re-run NTuples]

    // Seconary track
    unsigned int trk2_id;	// Reco - track: secondary track ID
    float trk2_len;			// Reco - track: Length of the second longest track
    float trk2_distance;	// Reco - track: Distance between second longest track start and reconstructed neutrino vertex
    float trk2_score;		// Reco - track: Pandora track score for the second longest track
    float trk2_avg_deflection_mean; 	// Reco - track: average deflections mean second longest track
    float trk2_avg_deflection_stdev; 	// Reco - track: average deflections stdev second longest track
    float trk2_sce_end_x;
    float trk2_sce_end_y;
    float trk2_sce_end_z;
    unsigned int trk2_daughters;		// Reco - track: number of daughters
    int trk2_end_spacepoints;

    int trk2_bkt_pdg;			// Backtracker - track: Backtrack PDG
    
    float trk2_bragg_p;			// Reco - track: Track Bragg Likelihood Proton
    float trk2_bragg_mu;		// Reco - track: Track Bragg Likelihood Muon
    float trk2_bragg_pion;		// Reco - track: Track Bragg Likelihood Pion
    float trk2_bragg_mip;		// Reco - track: Track Bragg Likelihood MIP
    float trk2_llr_pid_score;	// Reco - track: LLR PID second longest track
    float trk2_dEdx_trunk_max;	// Reco - track: average dE/dx of first third of track, plane with maximum number of hits [Requires re-run NTuples]

    // Angle and distance between primary track and primary shower
    float tksh_distance;        // Reco: Distance between leading shower vertex and longest track vertex
    float tksh_angle;           // Reco: Angle between leading shower vertex and longest track vertex 

    // Pi0 reconstruction
    float pi0_mass_U; 			// Reco: reconstructed pi0 mass (two highest-energy showers)

    // --- Full PFP vectors ---

    // Full Track vectors 
    std::vector<float> *trk_score_v       = nullptr; // PFP track score
    std::vector<float> *trk_sce_start_x_v = nullptr;
    std::vector<float> *trk_sce_start_y_v = nullptr;
    std::vector<float> *trk_sce_start_z_v = nullptr;
    std::vector<float> *trk_sce_end_x_v   = nullptr;
    std::vector<float> *trk_sce_end_y_v   = nullptr;
    std::vector<float> *trk_sce_end_z_v   = nullptr;
    std::vector<float> *trk_len_v         = nullptr;
    std::vector<float> *trk_distance_v    = nullptr; 

    std::vector<float> *trk_bragg_p_v     	= nullptr;
    std::vector<float> *trk_bragg_pion_v   	= nullptr;
    std::vector<float> *trk_bragg_mu_v    	= nullptr;
    std::vector<float> *trk_bragg_mip_v    	= nullptr;
    std::vector<float> *trk_llr_pid_score_v = nullptr; // LLR PID - Muon/Proton separation

    // Full Shower vectors 
    std::vector<float> *all_shr_energies    = nullptr;
    std::vector<float> *shr_energy_u_v      = nullptr;
    std::vector<float> *shr_energy_v_v      = nullptr;
    std::vector<float> *shr_energy_y_v      = nullptr;
    std::vector<float> *shr_px_v            = nullptr;
    std::vector<float> *shr_py_v            = nullptr;
    std::vector<float> *shr_pz_v            = nullptr;
    
    std::vector<float> *shr_start_x_v = nullptr;
    std::vector<float> *shr_start_y_v = nullptr;
    std::vector<float> *shr_start_z_v = nullptr;

    // Full daughter vectors
    std::vector<unsigned int> *pfp_trk_daughters_v = nullptr;
    std::vector<unsigned int> *pfp_shr_daughters_v = nullptr;

    // Backtracker information vectors
    std::vector<int> *backtracked_pdg_v = nullptr;        // PDG code of backtracked particle

    // track trunk dE/dx  [ Requires re-run NTuples]
    std::vector<int> *trk_nhits_u_v = nullptr;
    std::vector<int> *trk_nhits_v_v = nullptr;
    std::vector<int> *trk_nhits_y_v = nullptr;    
    
    std::vector<float> *trk_trunk_dEdx_u_v = nullptr;
    std::vector<float> *trk_trunk_dEdx_v_v = nullptr; 
    std::vector<float> *trk_trunk_dEdx_y_v = nullptr;
    
    // track deflections [ Requires re-run NTuples]
    std::vector<float> *trk_avg_deflection_mean_v = nullptr;
    std::vector<float> *trk_avg_deflection_stdev_v = nullptr;
    std::vector<float> *trk_avg_deflection_separation_mean_v = nullptr;

    // track spacepoints [Requires re-run NTuples]
    std::vector<int> *trk_end_spacepoints_v = nullptr;    

    // --- Full MC truth vectors ---
    std::vector<int>   *mc_pdg_v  = nullptr;  // True: Vector of all MC particles
    std::vector<float> *mc_E_v    = nullptr;

};

#endif

