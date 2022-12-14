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
	bool ApplyElectronSelection(const EventContainer &_evt);
	bool ApplyPionSelection(EventContainer &_evt, Utility::FileTypeEnums type);

	// Background rejection
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
	bool ApplyElectronPionCanidateCut(int n_showers, int n_tracks);

	// Vertex within fiducial volume
	bool ApplyVertexFVCut(float reco_nu_vtx_sce_x, float reco_nu_vtx_sce_y, float reco_nu_vtx_sce_z);

	// Fraction of PFP hits contained within fiducial volume
	bool ApplyContainedFractionCut(float contained_fraction);

	// Fraction of hits associated with tracks and showers
	bool ApplyAssociatedHitsFractionCut(float associated_hits_fraction);

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

	// Leading shower energy fraction
	bool ApplyLeadingShowerEnergyFractionCut(float shr_energyFraction);

	// Neutral pion rejection: dE/dx and vertex distance	
	bool ApplyNeutralPionRejectionCut(float dEdxMax, float shr_distance);

	// Neutral pion rejection: second shower tagger
	bool ApplySecondShowerClusterCut(int secondshower_U_nhit, int secondshower_V_nhit, int secondshower_Y_nhit, 
							  		 float secondshower_U_vtxdist, float secondshower_V_vtxdist, float secondshower_Y_vtxdist, 
							  		 float secondshower_U_anglediff, float secondshower_V_anglediff, float secondshower_Y_anglediff);

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

	// Proton Bragg peak score
	bool ApplyProtonBraggPeakScoreCut(float trk_bragg_p);

	// Pion Bragg Peak Score
	bool ApplyPionBraggPeakScoreCut(float trk_bragg_pion);

	// Track Trunk dE/dx
	bool ApplyTrackTrunkdEdxCut(float trk_trunk_dEdx); 								

};

#endif