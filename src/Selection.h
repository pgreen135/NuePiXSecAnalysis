#ifndef SELECTION_H
#define SELECTION_H

// class containing selection cuts and tools to run selection on an event

#include "Utility.h"
#include "EventContainer.h"

class Selection {

public:	
	// ----------------------------------
	// Constructor
	Selection(const Utility &util);

	// Destructor
	~Selection(){};

	// Selection
	// Pre-selection
	bool ApplyPreSelection(const EventContainer &_evt, Utility::FileTypeEnums type);
	bool ApplyReconstructionCompletenessCheck(const EventContainer &_evt);

	// Candidate Identification
	bool ApplyGoodShowerSelection(const EventContainer &_evt);
	bool ApplyGoodTrackSelection(EventContainer &_evt, Utility::FileTypeEnums type);

	// Background rejection
	bool ApplyReconstructionFailureChecks(const EventContainer &_evt, Utility::FileTypeEnums type);
	bool ApplyCosmicRejection(const EventContainer &_evt);
	bool ApplyNeutralPionRejection(const EventContainer &_evt);
	bool ApplyProtonRejection(EventContainer &_evt, Utility::FileTypeEnums type);
	
	// ----------------------------------


protected:

	const Utility _utility;

	// Passes software trigger [MC only, already applied to data]
	bool ApplySWTriggerCut(int swtrig);	

	// Common Optical Filter [MC only,  already applied to data]
	bool ApplyCommonOpticalFilterPECut(float opfilter_pe_beam);
	bool ApplyCommonOpticalFilterMichelCut(float opfilter_pe_veto);

	// Passes Pandora slice ID
	bool ApplySliceIDCut(int nslice);

	// Electron + Pion candidate cut
	bool ApplySignalCanidateCut(int n_showers, int n_tracks);

	// Vertex within fiducial volume
	bool ApplyVertexFVCut(float reco_nu_vtx_sce_x, float reco_nu_vtx_sce_y, float reco_nu_vtx_sce_z);

	// Fraction of PFP hits contained within fiducial volume
	bool ApplyContainedFractionCut(float contained_fraction);

	// Fraction of hits associated with tracks and showers
	bool ApplyAssociatedHitsFractionCut(float associated_hits_fraction);

	// Leading shower energy
	bool ApplyShowerEnergyCut(float shr_energy);

	// Leading shower score
	bool ApplyShowerScoreCut(float shr_score);

	// Leading shower hit ratio
	bool ApplyShowerHitRatioCut(float hits_ratio);

	// Pandora topological score
	bool ApplyTopologicalScoreCut(float topological_score);

	// Cosmic impact parameter
	bool ApplyCosmicImpactParameterCut(float CosmicIPAll3D);

	// Leading shower Moliere average
	bool ApplyMoliereAverageCut(float shrmoliereavg);

	// Leading shower subclusters 
	bool ApplyShowerSubclustersCut(unsigned int shrsubclusters);

	// Leading shower energy fraction
	bool ApplyLeadingShowerEnergyFractionCut(float shr_energyFraction);

	// Leading shower fraction of energy in 1cm cylinder from shower center [see PeLEE]
	bool ApplyShowerCylFractionCut(float CylFrac2h_1cm);

	// Number of showers
    bool ApplyNumberShowersCut(int n_showers_contained);
	
	// Neutral pion rejection: dE/dx and vertex distance	
	bool ApplyNeutralPionRejectionCut(float dEdxMax, float shr_distance);

	// Neutral pion rejection: second shower tagger
	bool ApplySecondShowerClusterCut(int secondshower_Y_nhit, float secondshower_Y_vtxdist, float secondshower_Y_anglediff);

	// Track Length
	bool ApplyTrackLengthCut(float trk_len);

	// Track Vertex Distance
	bool ApplyTrackVertexDistanceCut(float trk_distance);

	// Track Score
	bool ApplyTrackScoreCut(float trk_score);

	// Track Containment
	bool ApplyTrackContainmentCut(float trk_sce_end_x, float trk_sce_end_y, float trk_sce_end_z);

	// Track Shower Opening Angle
	bool ApplyTrackShowerOpeningAngleCut(float tksh_angle);

	// LLR PID Score
	bool ApplyLLRPIDScoreCut(float trk_llr_pid_score);

	// Track Trunk dE/dx
	bool ApplyTrackTrunkdEdxCut(float trk_trunk_dEdx);

	// Track Bragg Peak Score
	bool ApplyTrackBraggPeakScoreCut(float trk_bragg_mip, float trk_bragg_pion); 

	// Shower Track Fit
	bool ApplyShrTrackFitCut(float trkfit);	

	// Shower Track Fit Length
	bool ApplyShrTrackLengthCut(float shr_trk_len);							

};

#endif