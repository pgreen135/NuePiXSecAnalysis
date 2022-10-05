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

	bool ApplySelection(const EventContainer &evt);
	bool ApplyPionSelection(const EventContainer &evt);
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

	// Neutral pion rejection: dE/dx and vertex distance
	float GetdEdxMax(unsigned int shr_tkfit_nhits_Y, unsigned int shr_tkfit_nhits_V, unsigned int shr_tkfit_nhits_U,
						float shr_tkfit_dedx_Y, float shr_tkfit_dedx_V, float shr_tkfit_dedx_U);
	bool ApplyNeutralPionRejectionCut(float dEdxMax, float shr_distance);

	// Track Length
	bool ApplyTrackLengthCut(float trk_len);								

};

#endif