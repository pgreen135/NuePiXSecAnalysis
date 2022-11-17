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
	void populateDerivedVariables();
	void GetdEdxMax(bool includeGap);
	void GetTrackdEdx();
    
    
    // ----------------------------------

    // -- Utility --
    Utility _utility;


	// --- Event classification ---
	Utility::ClassificationEnums classification;


	// --- Event information
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
  	int nslice;		// Reco: number of neutrino slices identified by the SliceID. Values are 0 or 1.
    int n_tracks;   // Reco: number of tracks identified with a track score cut
    int n_showers;  // Reco: number of showers with a shower score cut

  	// slice quality
  	float nu_purity_from_pfp;   // Neutrino Purity from PFP (how many out of all the hits are the neutrino)

  	// --- Neutrino Reconstruction ---
  	// reconstructed neutrino vertex, space charge corrected
  	float reco_nu_vtx_sce_x;    // Reco: neutrino Vtx Space Charge x
    float reco_nu_vtx_sce_y;    // Reco: neutrino Vtx Space Charge y
    float reco_nu_vtx_sce_z;    // Reco: neutrino Vtx Space Charge z

    float contained_fraction;   // Reco: hits in PFParticles contained in the fiducial volume over the total number of clustered hits in the slice

    // --- Cosmic Reconstruction
    float topological_score;  	// Reco: topological Score
    float CosmicIPAll3D;        // Reco: 3D distance of shower start from closest spacepoint of any pfp not in the neutrino slice

    // -- Shower Reconstruction
    unsigned int shr_id;
    float shr_distance;         // Reco: distance between leading shower vertex and reconstructed neutrino vertex
    float shr_score;            // Reco: Pandora track score for the leading shower
    float shr_energy_cali;			// Reco: Energy of the shower with the largest number of hits (in GeV) (calibrated)
    float shr_energy_tot_cali;        // Shower: the energy of the showers (in GeV) (calibrated)
    float hits_ratio;           // Reco: ratio between hits from showers and total number of hits in the slice
    float shrmoliereavg;        // Reco: average angle between the shower’s direction and its 3D spacepoints

    unsigned int shr_tkfit_nhits_Y;     // Reco: number of hits in the 1x4 cm box on the Y plane with the track fitting
    unsigned int shr_tkfit_nhits_V;     // Reco: number of hits in the 1x4 cm box on the V plane with the track fitting
    unsigned int shr_tkfit_nhits_U;     // Reco: number of hits in the 1x4 cm box on the U plane with the track fitting

    unsigned int shr_tkfit_gap10_nhits_Y;     // Reco: number of hits in the 1x4 cm box on the Y plane with the track fitting
    unsigned int shr_tkfit_gap10_nhits_V;     // Reco: number of hits in the 1x4 cm box on the V plane with the track fitting
    unsigned int shr_tkfit_gap10_nhits_U;     // Reco: number of hits in the 1x4 cm box on the U plane with the track fitting

    float shr_tkfit_dedx_Y;      // Reco: dE/dx of the leading shower on the Y plane with the track fitting
    float shr_tkfit_dedx_V;      // Reco: dE/dx of the leading shower on the V plane with the track fitting
    float shr_tkfit_dedx_U;      // Reco: dE/dx of the leading shower on the U plane with the track fitting
    float shr_trkfit_dedx_max;	 // Reco: dE/dx of the leading shower on plane with the most hits (derived variable)

    float shr_tkfit_gap10_dedx_Y;      // Reco: dE/dx of the leading shower on the Y plane with the track fitting
    float shr_tkfit_gap10_dedx_V;      // Reco: dE/dx of the leading shower on the V plane with the track fitting
    float shr_tkfit_gap10_dedx_U;      // Reco: dE/dx of the leading shower on the U plane with the track fitting
    float shr_trkfit_gap10_dedx_max;	 // Reco: dE/dx of the leading shower on plane with the most hits (derived variable)

    // Track Reconstruction
    unsigned int trk_id;
    unsigned int trk2_id;
    float trk_len;		// Track: Length of the longest track
    float trk_distance;	// Track: Distance between longest track start and reconstructed neutrino vertex
    float trk_score;	// Track: Pandora track score for the longest track
    float trk_theta;            // Track: Reconstructed theta angle for the longest track
    float trk_phi;              // Track: Reconstructed phi angle for the longest track
    int   trk_bkt_pdg;          // Track: Backtrack PDG

    float trk_bragg_pion; // Track Bragg Likelihood Pion
    float trk_bragg_p;	// Track Bragg Likelihood Proton
    float trk_bragg_mu;

    // Angle and distance between primary track and primary shower
    float tksh_distance;        // Distance between leading shower vertex and longest track vertex
    float tksh_angle;           // Angle between leading shower vertex and longest track vertex 

    // Pi0 reconstruction
    float pi0_mass_U; 	// reconstructed pi0 mass (two highest-energy showers)

    // Track and shower vectors
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
    std::vector<float> *trk_bragg_mu_v    	= nullptr;
    std::vector<float> *trk_llr_pid_score_v = nullptr; // LLR PID - Muon/Proton separation

    std::vector<float> *trk_llr_pid_score_5cm_v = nullptr; // LLR PID - Muon/Proton separation - 5cm gap

    std::vector<float> *all_shr_energies    = nullptr;
    std::vector<float> *shr_energy_u_v      = nullptr;
    std::vector<float> *shr_energy_v_v      = nullptr;
    std::vector<float> *shr_energy_y_v      = nullptr;
    std::vector<float> *shr_px_v            = nullptr;
    std::vector<float> *shr_py_v            = nullptr;
    std::vector<float> *shr_pz_v            = nullptr;

    // dE/dx of leading track
    int trk_nhits_u;
    int trk_nhits_v;
    int trk_nhits_y;
    std::vector<float> *trk_dedx_u_v = nullptr;
    std::vector<float> *trk_dedx_v_v = nullptr;
    std::vector<float> *trk_dedx_y_v = nullptr;
    std::vector<float> *trk_rr_u_v = nullptr;
    std::vector<float> *trk_rr_v_v = nullptr;
    std::vector<float> *trk_rr_y_v = nullptr;

    float trk_llr_pid_score;
    float trk_llr_pid_score_5cm;
    
    float trk2_len;
    float trk2_llr_pid_score;
    float trk2_llr_pid_score_5cm;

    float shr_energyFraction;

    float trk_dEdx_5cm_max;


    float neutralPionInvariantMassDifference;
};

#endif

