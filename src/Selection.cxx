#include "Selection.h"

#include <iostream>

// Constructor
Selection::Selection(const Utility &util): _utility{ util } {
	
	std::cout << "Initialising Selection Class" << std::endl;

}

// ------------------------------------------------------------------------------

bool Selection::ApplySelection(const EventContainer &_evt) {
	if(!ApplySWTriggerCut(_evt.swtrig_pre)) return false;							// software trigger [MC only]
	//if(!ApplyCommonOpticalFilterPECut(evt.opfilter_pe_beam)) return false;		// common optical filter (beam) [MC only]	(not applied)
	//if(!ApplyCommonOpticalFilterMichelCut(evt.opfilter_pe_veto)) return false;	// common optical filter (michel) [MC only]  (not applied)
	if(!ApplySliceIDCut(_evt.nslice)) return false;									// slice ID
	if(!ApplyElectronPionCanidateCut(_evt.n_showers, _evt.n_tracks)) return false;	// electron + pion candidate
	if(!ApplyVertexFVCut(_evt.reco_nu_vtx_sce_x, _evt.reco_nu_vtx_sce_y, _evt.reco_nu_vtx_sce_z)) return false;	// neutrino vertex in fiducial volume
	if(!ApplyContainedFractionCut(_evt.contained_fraction)) return false; 			// contained fraction
	if(!ApplyTopologicalScoreCut(_evt.topological_score)) return false;				// topological score
	
	return true;
}

// ------------------------------------------------------------------------------
// Selection cuts
// Software Trigger [MC only]
bool Selection::ApplySWTriggerCut(int swtrig){
	return swtrig;
}

// Common Optical Filter PE [MC only]
bool Selection::ApplyCommonOpticalFilterPECut(float opfilter_pe_beam){
	if (opfilter_pe_beam >= 20) return true;
    else return false;
}

// Common Optical Filter Michel Veto [MC only]
bool Selection::ApplyCommonOpticalFilterMichelCut(float opfilter_pe_veto){
	if (opfilter_pe_veto < 20) return true;
    else return false;
}

// Slice ID
bool Selection::ApplySliceIDCut(int nslice){
	if (nslice == 1) return true;
	else return false;
}

// Electron + Pion candidate: minimum 1 track and 1 shower
bool Selection::ApplyElectronPionCanidateCut(int n_showers, int n_tracks){
	if (n_tracks >= 1 && n_showers >= 1) return true;
	else return false; 
}

// Vertex within fiducial volume
bool Selection::ApplyVertexFVCut(float reco_nu_vtx_sce_x, float reco_nu_vtx_sce_y, float reco_nu_vtx_sce_z){
	bool isInFV = _utility.inFV(reco_nu_vtx_sce_x, reco_nu_vtx_sce_y, reco_nu_vtx_sce_z);
	if (isInFV) return true;
	else return false;
}

// Contained fraction of hits
bool Selection::ApplyContainedFractionCut(float contained_fraction){
	if(contained_fraction >= 0.85) return true;
	else return false;
}

// Pandora topological score
bool Selection::ApplyTopologicalScoreCut(float topological_score){
	if(topological_score <= 0.01 || topological_score > 0.2) return true;
	else return false;
}