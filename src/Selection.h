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
	bool ApplyPreSelection(const EventContainer &evt, Utility::FileTypeEnums type);
	bool ApplyCosmicRejection(const EventContainer &evt);

	bool ApplyElectronSelection(const EventContainer &_evt);
	bool ApplyPionSelection(const EventContainer &evt);

	bool ApplyNeutralPionRejection(const EventContainer &_evt);
	bool ApplyProtonRejection(const EventContainer &_evt);
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

	// Pandora topological score
	bool ApplyTopologicalScoreCut(float topological_score);

	// Cosmic impact parameter
	bool ApplyCosmicImpactParameterCut(float CosmicIPAll3D);

	// Leading shower score
	bool ApplyShowerScoreCut(float shr_score);

	// Leading shower hit ratio
	bool ApplyShowerHitRatioCut(float hits_ratio);

	// Leading shower Moliere average
	bool ApplyMoliereAverageCut(float shrmoliereavg);

	// Leading shower energy fraction
	bool ApplyLeadingShowerEnergyFractionCut(float shr_energyFraction);

	// Neutral pion rejection: dE/dx and vertex distance	
	bool ApplyNeutralPionRejectionCut(float dEdxMax, float shr_distance);

	// Track Length
	bool ApplyTrackLengthCut(float trk_len);

	// Track Vertex Distance
	bool ApplyTrackVertexDistanceCut(float trk_distance);

	// Track Score
	bool ApplyTrackScoreCut(float trk_score);

	// Track Shower Opening Angle
	bool ApplyTrackShowerOpeningAngleCut(float tksh_angle);

	// LLR PID Score
	bool ApplyLLRPIDScoreCut(float trk_llr_pid_score);

	// Proton Bragg peak score
	bool ApplyProtonBraggPeakScoreCut(float trk_bragg_p); 								

};

#endif