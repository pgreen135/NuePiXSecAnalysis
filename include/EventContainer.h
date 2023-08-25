#ifndef EVENTCONTAINER_H
#define EVENTCONTAINER_H

// class to read and contain events from the pandora ntuples
// event information can then be passed as required to other parts of the analysis code
// variables public for ease of access

#include <string>
#include <vector>
#include <map>

#include <TTree.h>
#include <TVector3.h>

#include "../include/Utility.h"

class EventContainer {

public:
	
	// ----------------------------------
	
	// Constructor
	EventContainer(TTree *tree, const Utility &utility);

	// Destructor
	~EventContainer();

	// Functions to classify the event
	void EventClassifier(Utility::FileTypeEnums type);
	Utility::ClassificationEnums getEventClassification(Utility::FileTypeEnums type);

    // Functions to calculation event weight
    void calculateCVEventWeight(Utility::FileTypeEnums type, Utility::RunPeriodEnums runPeriod);
    void calculateBeamlineVariationWeights();
    float checkWeight(float weight);

	// Functions to recover reconstruction failures
	void applyEventRecoveryAlgorithms();
	void failureRecoverySplitShowers();
	void failureRecoverySpuriousTrack();
	void failureRecoverySplitTrackShower();
	void failureRecoverySecondShowerProton(); 

	// Functions to populate derived event variables
	void populateDerivedVariables(Utility::FileTypeEnums type);
	void GetSecondShowerClusterAngleDiff();
	void GetdEdxMax(bool includeGap);
	void isAlongWire(unsigned int trackID, bool &isAlongWire_u, bool &isAlongWire_v, bool &isAlongWire_y);
	float GetTrackTrunkdEdxBestPlane(unsigned int trackID);
	float GetTrackBraggPionBestPlane(unsigned int trackID);
	float GetTrackBraggMIPBestPlane(unsigned int trackID);
    float CalculatePionEnergyRange(float R);
    float GetShowerTrackEndProximity(unsigned int shrID);
    double GetNuMIAngle(double px, double py, double pz, std::string direction);

 
    // ----------------------------------

    // --- Utility ---
    Utility _utility;

	// --- Event classification ---
	Utility::ClassificationEnums classification;

    // --- Event weight ---
    // CV weight, before POT scaling
    float weight_cv; 

	// --- Reconstruction failures information ---
	bool hasSplitPrimaryShower;
	bool hasSpuriousLeadingTrack;
	bool hasSplitTrackShower;
	bool hasSecondShowerProton;

	// --- Selection Information ---
	bool primaryTrackValid;
    bool secondaryTrackValid;
    bool tertiaryTrackValid;

    bool primaryTrackPionlike;
    bool secondaryTrackPionlike;
    bool tertiaryTrackPionlike;

    bool primaryTrackPionlikeLoose;
    bool secondaryTrackPionlikeLoose;
    bool tertiaryTrackPionlikeLoose;

    // --- BDT Scores ---
    double BDTScoreElectronPhoton;
    double primaryTrackBDTScorePionProton;
    double secondaryTrackBDTScorePionProton;
    double tertiaryTrackBDTScorePionProton;
    double BDTScorePionProtonAlternate;

    // --- Variables for STV Tree ---
    bool is_mc_;
    bool mc_is_signal_;
    bool sel_NueCC1piXp_;
    int  category_;
    
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
    float pi0_e;
  	
  	int nproton; 				// Truth: number of protons
  	float proton_e;				// Truth: proton energy

  	// truth neutrino interaction vertex
  	float true_nu_vtx_sce_x;     // True Neutrino Vtx Space Charge x
  	float true_nu_vtx_sce_y;     // True Neutrino Vtx Space Charge y
  	float true_nu_vtx_sce_z;     // True Neutrino Vtx Space Charge z

    // truth neutrino momentum
    float true_nu_px;            // True Neutrino Px
    float true_nu_py;            // True Neutrino Py
    float true_nu_pz;            // True Neutrino Pz

  	// --- Software trigger [MC only] ---
  	int swtrig;     			// Software Trigger
    int swtrig_pre;     		// Software Trigger before change -- Run 1
    int swtrig_post;     		// Software Trigger after change

    // --- Common optical filter [MC only] ---
    float opfilter_pe_beam; // Common Optical Filter (beam window)
    float opfilter_pe_veto; // Common Optical Filter (michel veto)

    // --- Event weight ---
    // CV
    float weightSplineTimesTune;    // Weight from Genie, spline * tune
    float weightSpline;
    float weightTune; 
    float ppfx_cv;                  // Weight from PPFX CV
    float normalisation_weight;     // NuMI normalisation weights (beam off, dirt)
    
    // systematic universes
    std::map<std::string, std::vector<double>> *mc_weights_map_ = nullptr;
    std::map<std::string, std::vector<double>*> mc_weights_ptr_map_;

    // beamline variations
    bool beamlineVarWeightsPresent;
    // true nu angle from numi beamline 
    float nu_angle;
    // variations
    std::vector<double> Horn_2kA;
    std::vector<double> Horn1_x_3mm;
    std::vector<double> Horn1_y_3mm;
    std::vector<double> Beam_spot_1_1mm;
    std::vector<double> Beam_spot_1_5mm;
    std::vector<double> Horn2_x_3mm;
    std::vector<double> Horn2_y_3mm;
    std::vector<double> Horns_0mm_water;
    std::vector<double> Horns_2mm_water;
    std::vector<double> Beam_shift_x_1mm;
    std::vector<double> Beam_shift_y_1mm;
    std::vector<double> Target_z_7mm;

  	// --- Slice information ---
  	// number
  	int nslice;		// Reco - Slice: number of neutrino slices identified by the SliceID. Values are 0 or 1.
    int n_tracks;   // Reco - Slice: number of tracks identified with a track score cut
    int n_showers;  // Reco - Slice: number of showers with a shower score cut
    unsigned int n_showers_contained; // Reco - Slice: number of showers contained
    unsigned int n_tracks_contained;  // Reco - Slice: number of tracks contained
    int n_showers_alt;
    int n_showers_above_threshold; 

    // neutrino PID
    int slpdg; // Reco? -- Pandora people say don't use, crude variable

  	// slice quality
  	float nu_purity_from_pfp;   // Truth: Neutrino Purity from PFP (how many out of all the hits are the neutrino)

  	// total hits (all planes)
  	unsigned int shr_hits_tot;	// all showers
  	unsigned int trk_hits_tot;	// all tracks
  	unsigned int trk_hits_max; 	// primary track
  	unsigned int trk_hits_2nd;  // second track

  	// reconstruction completeness
  	unsigned int total_hits_y;		// Reco - Slice: total number hits on collection plane in neutrino slice
  	unsigned int shr_hits_y_tot;    // Reco - Shower: total number hits on collection plane in neutrino slice associated with showers
    unsigned int trk_hits_y_tot;    // Reco - Track: total number hits on collection plane in neutrino slice associated with tracks

  	unsigned int shr_hits_u_tot;    // Reco - Shower: total number hits on collection plane in neutrino slice associated with showers
    unsigned int trk_hits_u_tot;    // Reco - Track: total number hits on collection plane in neutrino slice associated with tracks

  	unsigned int shr_hits_v_tot;    // Reco - Shower: total number hits on collection plane in neutrino slice associated with showers
    unsigned int trk_hits_v_tot;    // Reco - Track: total number hits on collection plane in neutrino slice associated with tracks

    float associated_hits_fraction; // Reco - Slice: fraction of hits on collection plane in neutrino slice associated with tracks and showers (derived variable)
    float extra_energy_y;			// Reco - Slice: deposited energy in neutrino slice not associated with tracks or showers

    // CRT veto
    int crtveto;

  	// --- Neutrino Reconstruction ---
  	// reconstructed neutrino vertex, space charge corrected
  	float reco_nu_vtx_sce_x;    // Reco - Neutrino: neutrino Vtx Space Charge x
    float reco_nu_vtx_sce_y;    // Reco - Neutrino: neutrino Vtx Space Charge y
    float reco_nu_vtx_sce_z;    // Reco - Neutrino: neutrino Vtx Space Charge z

    float contained_fraction;   // Reco: hits in PFParticles contained in the fiducial volume over the total number of clustered hits in the slice

    // --- Cosmic Reconstruction ---
    float topological_score;  	// Reco - cosmic: topological Score
    float CosmicIPAll3D;        // Reco - cosmic: 3D distance of shower start from closest spacepoint of any pfp not in the neutrino slice
    float CosmicDirAll3D;		// Reco - cosmic: cosmic impact direction 3D

    // -- Shower Reconstruction ---
    // Primary Shower
    unsigned int shr_id;		// Reco - shower: Primary shower ID
    float shr_distance;         // Reco - shower: distance between leading shower vertex and reconstructed neutrino vertex
    float shr_score;            // Reco - shower: Pandora track score for the leading shower
    float shr_energy_cali;		// Reco - shower: Energy of the shower with the largest number of hits (in GeV) (calibrated)
    float shrmoliereavg;        // Reco - shower: average angle between the shower’s direction and its 3D spacepoints
    float shr_start_x;
    float shr_start_y;
    float shr_start_z;
    float shr_dir_x;
    float shr_dir_y;
    float shr_dir_z;

    float shr_llrpid_dedx;		// Reco - shower: LLR PID score, shower electron-photon separation

    // Track fit
    float trkfit;				// Fraction of charge inlcuded when shower is fitted under track hypothesis
    float shr_trk_len;			// length of shower track fit
    float shr_trk_sce_start_x;
    float shr_trk_sce_start_y;
    float shr_trk_sce_start_z;
    float shr_trk_sce_end_x;
    float shr_trk_sce_end_y;
    float shr_trk_sce_end_z;

    unsigned int shr_tkfit_nhits_Y;     // Reco - shower: number of hits in the 1x4 cm box on the Y plane with the track fitting
    unsigned int shr_tkfit_nhits_V;     // Reco - shower: number of hits in the 1x4 cm box on the V plane with the track fitting
    unsigned int shr_tkfit_nhits_U;     // Reco - shower: number of hits in the 1x4 cm box on the U plane with the track fitting

    unsigned int shr_tkfit_gap05_nhits_Y; 	// Reco - shower: number of hits in the 1x4 cm box on the Y plane with the track fitting, gap 5mm from start
    unsigned int shr_tkfit_gap05_nhits_V;   // Reco - shower: number of hits in the 1x4 cm box on the V plane with the track fitting, gap 5mm from start
    unsigned int shr_tkfit_gap05_nhits_U;   // Reco - shower: number of hits in the 1x4 cm box on the U plane with the track fitting, gap 5mm from start

    unsigned int shr_tkfit_gap10_nhits_Y; 	// Reco - shower: number of hits in the 1x4 cm box on the Y plane with the track fitting, gap 10mm from start
    unsigned int shr_tkfit_gap10_nhits_V;   // Reco - shower: number of hits in the 1x4 cm box on the V plane with the track fitting, gap 10mm from start
    unsigned int shr_tkfit_gap10_nhits_U;   // Reco - shower: number of hits in the 1x4 cm box on the U plane with the track fitting, gap 10mm from start

    unsigned int shr_tkfit_2cm_nhits_Y;   // Reco - shower: number of hits in the 1x2 cm box on the Y plane with the track fitting, first 2cm only 
    unsigned int shr_tkfit_2cm_nhits_V;   // Reco - shower: number of hits in the 1x2 cm box on the V plane with the track fitting, first 2cm only
    unsigned int shr_tkfit_2cm_nhits_U;   // Reco - shower: number of hits in the 1x2 cm box on the U plane with the track fitting, first 2cm only

    unsigned int trk2_tkfit_nhits_u;
    unsigned int trk2_tkfit_nhits_v;
    unsigned int trk2_tkfit_nhits_y;

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

    float shr_tkfit_2cm_dedx_Y;      // Reco - shower: dE/dx of the leading shower on the Y plane with the track fitting, first 2cm only 
    float shr_tkfit_2cm_dedx_V;      // Reco - shower: dE/dx of the leading shower on the V plane with the track fitting, first 2cm only
    float shr_tkfit_2cm_dedx_U;      // Reco - shower: dE/dx of the leading shower on the U plane with the track fitting, first 2cm only
    float shr_trkfit_2cm_dedx_max;   // Reco - shower: dE/dx of the leading shower on plane with the most hits (derived variable), first 2cm only

    float trk2_tkfit_dedx_u;
    float trk2_tkfit_dedx_v;
    float trk2_tkfit_dedx_y;
    
    float shrclusdir0; 	// direction of shower cluster on U plane
    float shrclusdir1; 	// direction of shower cluster on V plane
    float shrclusdir2; 	// direction of shower cluster on Y plane

    unsigned int shrsubclusters; 	// total number of clusters summed across all planes
    unsigned int shrsubclusters0;	// number of clusters shower can be broken into, U plane
    unsigned int shrsubclusters1;   // number of clusters shower can be broken into, V plane
    unsigned int shrsubclusters2;   // number of clusters shower can be broken into, Y plane

    float shrPCA1CMed_5cm;			// metric of shower linearity
    float CylFrac1h_1cm;            // fraction of shower energy within cyclinder 1cm radius from track direction, first half only - low for showers, high for tracks, very low for misreconstructed pi0
    float CylFrac2h_1cm; 			// fraction of shower energy within cyclinder 1cm radius from track direction, second half only - low for showers, high for tracks, very low for misreconstructed pi0
    float DeltaRMS2h;
    float shrMCSMom;

    int shr_planehits_U;
    int shr_planehits_V;
    int shr_planehits_Y;

    int shr_pfpgeneration;

    // Primary Shower Truth
    float shr_bkt_E;            // backtracked energy of the MCParticle matched to the leading shower

    // Seconary Shower
    unsigned int shr2_id;		// Reco - shower: Secondary shower ID
    float shr2_energy;			// Reco - shower: energy of second shower (in GeV), note - not calibrated variable as missing from ntuples
    float shr_energy_second_cali;
    float shr2_score;
    float shr2_start_x;
    float shr2_start_y;
    float shr2_start_z;
    float shr2_dir_x;
    float shr2_dir_y;
    float shr2_dir_z;
    float shr2_distance;
    float shr2moliereavg;

    float shr12_p1_dstart;		// Reco - shower: opening angle between direction of primary shower and vector between primary and secondary shower vertices
    int shr2subclusters;
    float shr1shr2moliereavg; 	// Shower moliere average including second shower
    float shr1trk2moliereavg;
    float tk1sh2_distance;		// Second shower distance from primary track
    float tk1tk2_distance; 		// Distance between primary and secondary track
    float tk2sh1_angle;			// Angle between primary shower and secondary track
    float tk1tk2_angle;			// Angle between primary and secondary track
    float shr2pid; 				// second shower LLR PID, treating as track-like (mis-reconstructed)

    float shr2_trackEndProximity;   // second shower start proximity to nearest track end
    
    int shr2_pfpgeneration;


    // Tertiary shower
    unsigned int shr3_id;
    float shr3_energy;
    float shr_energy_third_cali;
    float shr3_start_x;
    float shr3_start_y;
    float shr3_start_z;
    float shr3_distance;
    int shr3subclusters;
   
    float shr13_p1_dstart;
    float tk1sh3_distance;

    float shr3_trackEndProximity;   // tertiary shower start proximity to nearest track end 

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
    float secondshower_U_dot;   // Reco - shower: dot product of second shower cluster from neutrino vertex, U plane
    float secondshower_V_dot;   // Reco - shower: dot product of second shower cluster from neutrino vertex, V plane
    float secondshower_Y_dot;   // Reco - shower: dot product of second shower cluster from neutrino vertex, Y plane
	float secondshower_U_dir;	// Reco - shower: direction of second shower cluster relative to wire direction, U plane
	float secondshower_V_dir;	// Reco - shower: direction of second shower cluster relative to wire direction, V plane
	float secondshower_Y_dir;	// Reco - shower: direction of second shower cluster relative to wire direction, Y plane


	float secondshower_U_anglediff;	// Reco - shower: opening angle between primary shower and second shower tagged cluster, U plane [derived variable]
	float secondshower_V_anglediff;	// Reco - shower: opening angle between primary shower and second shower tagged cluster, V plane [derived variable]
	float secondshower_Y_anglediff;	// Reco - shower: opening angle between primary shower and second shower tagged cluster, Y plane [derived variable]

    // --- Track Reconstruction ---
   	// Primary track
    unsigned int trk_id;		// Reco - track: primary track ID
    float trk_len;			// Reco - track: Length of the longest track
    float trk_distance;		// Reco - track: Distance between longest track start and reconstructed neutrino vertex
    float trk_score;		// Reco - track: Pandora track score for the longest track
    float trk_theta;        // Reco - track: Reconstructed theta angle for the longest track
    float trk_phi;          // Reco - track: Reconstructed phi angle for the longest track
    float trk_start_x;
    float trk_start_y;
    float trk_start_z;
    float trk_end_x;
    float trk_end_y;
    float trk_end_z;
    float trk_sce_end_x;
    float trk_sce_end_y;
    float trk_sce_end_z;
    float trk_dir_x;
    float trk_dir_y;
    float trk_dir_z;
    unsigned int trk_daughters; 		// Reco - track: number of daughters
    float trk_calo_energy;
    float trk_energy_proton;
    float trk_energy_muon;
    float trk_energy_pion;
   
    int trk_bkt_pdg;      // Backtracker - track: Backtrack PDG

    float trk_bragg_pion; 	// Reco - track: Track Bragg Likelihood Pion
    float trk_bragg_pion_max; 	// Reco - track: Track Bragg Likelihood Pion, best plane    
    float trk_bragg_p;		// Reco - track: Track Bragg Likelihood Proton
    float trk_bragg_mu;		// Reco - track: Track Bragg Likelihood Muon
    float trk_bragg_mip;	// Reco - track: Track Bragg Likelihood MIP
    float trk_bragg_mip_max;	// Reco - track: Track Bragg Likelihood MIP, best plane
    float trk_llr_pid_score;	// Reco - track: LLR PID longest track
    float trk_dEdx_trunk_max;   // Reco - track: average dE/dx of first third of track, best plane [Requires re-run NTuples]

    int trk_end_spacepoints;

    int trk_planehits_U;
    int trk_planehits_V;
    int trk_planehits_Y;

    int trk_pfpgeneration;

    // Seconary track
    unsigned int trk2_id;	// Reco - track: secondary track ID
    float trk2_len;			// Reco - track: Length of the second longest track
    float trk2_distance;	// Reco - track: Distance between second longest track start and reconstructed neutrino vertex
    float trk2_score;		// Reco - track: Pandora track score for the second longest track
    float trk2_start_x;
    float trk2_start_y;
    float trk2_start_z;
    float trk2_end_x;
    float trk2_end_y;
    float trk2_end_z;
    float trk2_sce_end_x;
    float trk2_sce_end_y;
    float trk2_sce_end_z;
    float trk2_dir_x;
    float trk2_dir_y;
    float trk2_dir_z;
    unsigned int trk2_daughters;		// Reco - track: number of daughters
    float trk2_calo_energy;
    float trk2_energy_proton;
    float trk2_energy_muon;
    float trk2_energy_pion;
    
    int trk2_bkt_pdg;			// Backtracker - track: Backtrack PDG
    
    float trk2_bragg_p;			// Reco - track: Track Bragg Likelihood Proton
    float trk2_bragg_mu;		// Reco - track: Track Bragg Likelihood Muon
    float trk2_bragg_pion;		// Reco - track: Track Bragg Likelihood Pion
    float trk2_bragg_pion_max;	// Reco - track: Track Bragg Likelihood Pion, best plane
    float trk2_bragg_mip;		// Reco - track: Track Bragg Likelihood MIP
    float trk2_bragg_mip_max; 	// Reco - track: Track Bragg Likelihood MIP, best plane
    float trk2_llr_pid_score;	// Reco - track: LLR PID second longest track
    float trk2_dEdx_trunk_max;	// Reco - track: average dE/dx of first third of track, best plane [Requires re-run NTuples]

    unsigned int trk2subclusters0;
    unsigned int trk2subclusters1;
    unsigned int trk2subclusters2;

    int trk2_end_spacepoints;

    int trk2_planehits_U;
    int trk2_planehits_V;
    int trk2_planehits_Y;

    int trk2_pfpgeneration;

    // tertiary track
    unsigned int trk3_id;	// Reco - track: secondary track ID
    float trk3_len;			// Reco - track: Length of the second longest track
    float trk3_distance;	// Reco - track: Distance between second longest track start and reconstructed neutrino vertex
    float trk3_score;		// Reco - track: Pandora track score for the second longest track
    float trk3_end_x;
    float trk3_end_y;
    float trk3_end_z;
    float trk3_sce_end_x;
    float trk3_sce_end_y;
    float trk3_sce_end_z;
    
    unsigned int trk3_daughters;		// Reco - track: number of daughters
    int trk3_bkt_pdg;			// Backtracker - track: Backtrack PDG
    float trk3_calo_energy;
    float trk3_energy_proton;
    float trk3_energy_muon;
    float trk3_energy_pion;
    
    float trk3_bragg_p;			// Reco - track: Track Bragg Likelihood Proton
    float trk3_bragg_mu;		// Reco - track: Track Bragg Likelihood Muon
    float trk3_bragg_pion;		// Reco - track: Track Bragg Likelihood Pion
    float trk3_bragg_pion_max;	// Reco - track: Track Bragg Likelihood Pion, best plane
    float trk3_bragg_mip;		// Reco - track: Track Bragg Likelihood MIP
    float trk3_bragg_mip_max; 	// Reco - track: Track Bragg Likelihood MIP, best plane
    float trk3_llr_pid_score;	// Reco - track: LLR PID second longest track
    float trk3_dEdx_trunk_max;	// Reco - track: average dE/dx of first third of track, best plane [Requires re-run NTuples]

    int trk3_end_spacepoints;

    int trk3_planehits_U;
    int trk3_planehits_V;
    int trk3_planehits_Y;

    int trk3_pfpgeneration;

    // Angle and distance between primary track and primary shower
    float tksh_distance;        // Reco: Distance between leading shower vertex and longest track vertex
    float tksh_angle;           // Reco: Angle between leading shower vertex and longest track vertex 

    // Pi0 reconstruction
    float pi0_mass_U; 			// Reco: reconstructed pi0 mass (two highest-energy showers)

    // --- Full PFP vectors ---

    // hits on each plane
    std::vector<int> *pfnplanehits_U = nullptr; // number of hits in pfp plane U
    std::vector<int> *pfnplanehits_V = nullptr; // number of hits in pfp plane V
    std::vector<int> *pfnplanehits_Y = nullptr; // number of hits in pfp plane Y

    // generation
    std::vector<unsigned int> *pfp_generation_v = nullptr; // generation of pfp

    // Full Track vectors 
    std::vector<float> *trk_score_v       = nullptr; // PFP track score
    std::vector<float> *trk_start_x_v = nullptr;
    std::vector<float> *trk_start_y_v = nullptr;
    std::vector<float> *trk_start_z_v = nullptr;
    std::vector<float> *trk_end_x_v = nullptr;
    std::vector<float> *trk_end_y_v = nullptr;
    std::vector<float> *trk_end_z_v = nullptr;
    std::vector<float> *trk_sce_start_x_v = nullptr;
    std::vector<float> *trk_sce_start_y_v = nullptr;
    std::vector<float> *trk_sce_start_z_v = nullptr;
    std::vector<float> *trk_sce_end_x_v   = nullptr;
    std::vector<float> *trk_sce_end_y_v   = nullptr;
    std::vector<float> *trk_sce_end_z_v   = nullptr;
    std::vector<float> *trk_dir_x_v 	= nullptr;
    std::vector<float> *trk_dir_y_v 	= nullptr;
    std::vector<float> *trk_dir_z_v 	= nullptr;
    std::vector<float> *trk_len_v         = nullptr;
    std::vector<float> *trk_distance_v    = nullptr;
    std::vector<float> *trk_calo_energy_y_v = nullptr;
    std::vector<float> *trk_energy_proton_v = nullptr;
    std::vector<float> *trk_energy_muon_v = nullptr;
     

    std::vector<float> *trk_bragg_p_v     	= nullptr;
    std::vector<float> *trk_bragg_pion_v   	= nullptr;
    std::vector<float> *trk_bragg_pion_u_v   	= nullptr;
    std::vector<float> *trk_bragg_pion_v_v   	= nullptr;
    std::vector<float> *trk_bragg_mu_v    	= nullptr;
    std::vector<float> *trk_bragg_mip_v    	= nullptr;
    std::vector<float> *trk_bragg_mip_u_v    	= nullptr;
    std::vector<float> *trk_bragg_mip_v_v    	= nullptr;
    std::vector<float> *trk_llr_pid_score_v = nullptr; // LLR PID - Muon/Proton separation

    std::vector<int> *all_trk_hits = nullptr;

    // Full Shower vectors 
    std::vector<float> *all_shr_energies    = nullptr;
    std::vector<float> *shr_energy_u_v      = nullptr;
    std::vector<float> *shr_energy_v_v      = nullptr;
    std::vector<float> *shr_energy_y_v      = nullptr;
    std::vector<float> *shr_px_v            = nullptr;
    std::vector<float> *shr_py_v            = nullptr;
    std::vector<float> *shr_pz_v            = nullptr;
    std::vector<float> *shr_dist_v          = nullptr;
    std::vector<float> *shr_moliere_avg_v   = nullptr;
    
    std::vector<float> *shr_start_x_v = nullptr;
    std::vector<float> *shr_start_y_v = nullptr;
    std::vector<float> *shr_start_z_v = nullptr;

    std::vector<float> *shr_tkfit_dedx_u_v = nullptr;
    std::vector<float> *shr_tkfit_dedx_v_v = nullptr;
    std::vector<float> *shr_tkfit_dedx_y_v = nullptr;
    std::vector<float> *shr_tkfit_dedx_nhits_u_v = nullptr;
    std::vector<float> *shr_tkfit_dedx_nhits_v_v = nullptr;
    std::vector<float> *shr_tkfit_dedx_nhits_y_v = nullptr;

    // Full daughter vectors
    std::vector<unsigned int> *pfp_trk_daughters_v = nullptr;
    std::vector<unsigned int> *pfp_shr_daughters_v = nullptr;

    // Track end spacepoints
    std::vector<unsigned int> *trk_end_spacepoints_v = nullptr;

    // Full subcluster vectors
    std::vector<int> *pfpplanesubclusters_U_v = nullptr;
    std::vector<int> *pfpplanesubclusters_V_v = nullptr;
    std::vector<int> *pfpplanesubclusters_Y_v = nullptr;

    // Backtracker information vectors
    std::vector<int> *backtracked_pdg_v = nullptr;        // PDG code of backtracked particle

    // track trunk dE/dx  [ Requires re-run NTuples]
    std::vector<int> *trk_nhits_u_v = nullptr;
    std::vector<int> *trk_nhits_v_v = nullptr;
    std::vector<int> *trk_nhits_y_v = nullptr;    
    
    std::vector<float> *trk_trunk_dEdx_u_v = nullptr;
    std::vector<float> *trk_trunk_dEdx_v_v = nullptr; 
    std::vector<float> *trk_trunk_dEdx_y_v = nullptr;    

    // --- Full MC truth vectors ---
    std::vector<int>   *mc_pdg_v  = nullptr;  // True: Vector of all MC particles
    std::vector<float> *mc_E_v    = nullptr;

};

#endif

