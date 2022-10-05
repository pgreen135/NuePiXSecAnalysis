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
	if(!ApplyCosmicImpactParameterCut(_evt.CosmicIPAll3D)) return false;			// cosmic impact parameter
	if(!ApplyShowerScoreCut(_evt.shr_score)) return false;							// shower score
	if(!ApplyShowerHitRatioCut(_evt.hits_ratio)) return false;						// shower hits ratio
	if(!ApplyMoliereAverageCut(_evt.shrmoliereavg)) return false;					// shower moliere average
	
	float dEdxMax = GetdEdxMax(_evt.shr_tkfit_nhits_Y, _evt.shr_tkfit_nhits_V, _evt.shr_tkfit_nhits_U,
								_evt.shr_tkfit_dedx_Y, _evt.shr_tkfit_dedx_V, _evt.shr_tkfit_dedx_U);
	if(!ApplyNeutralPionRejectionCut(dEdxMax, _evt.shr_distance)) return false;		// neutral pion rejection: shower dE/dx and vertex separation
	if(!ApplyTrackLengthCut(_evt.trk_len)) return false;							// longest track length
	
	return true;
}

// ------------------------------------------------------------------------------

bool Selection::ApplyPionSelection(const EventContainer &_evt) {

	if (_evt.trk_len >= 5 && _evt.trk_distance <= 5 && _evt.trk_bragg_pion > 0.2 && _evt.trk_bragg_p < 0.2) return true;
	else return false;

	/*
	int numberSelectedPions = 0;

	// loop through tracks
	for (int i = 0; i < _evt.n_tracks; i++) {

		// Track Containment
		bool isStartContained = _utility.inFV(_evt.trk_sce_start_x_v->at(i), _evt.trk_sce_start_y_v->at(i), _evt.trk_sce_start_z_v->at(i));
		bool isEndContained = _utility.inFV(_evt.trk_sce_end_x_v->at(i), _evt.trk_sce_end_y_v->at(i), _evt.trk_sce_end_z_v->at(i));

		if(!(isStartContained && isEndContained)) continue;

		// Track Length
		if(_evt.trk_len_v->at(i) < 10) continue;

		// Track Vertex Distance
		//if(_evt.trk_distance_v->at(i) >= 5) continue;

		// Track Score
		//if(_evt.trk_score_v->at(i) < 0.8) continue;

		// LLR PID
		if (_evt.trk_llr_pid_score_v->at(i) < 0.2) continue;

		numberSelectedPions++;
	}

	if (numberSelectedPions >= 1) return true;
	else return false;
	*/
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

// Electron + Pion candidate: minimum 1 track and 1 shower ( // add less than 3 showers)
bool Selection::ApplyElectronPionCanidateCut(int n_showers, int n_tracks){
	if (n_tracks >= 1 && n_showers >= 1 && n_showers < 3) return true;
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

// Cosmic impact parameter
bool Selection::ApplyCosmicImpactParameterCut(float CosmicIPAll3D) {
	if (CosmicIPAll3D > 15) return true;
	else return false;
}

// Shower score
bool Selection::ApplyShowerScoreCut(float shr_score){
	if (shr_score <= 0.1) return true; 
	else return false;
}

// Shower hit ratio
bool Selection::ApplyShowerHitRatioCut(float hits_ratio){
	if (hits_ratio >= 0.5) return true;
	else return false;
}

// Leading shower Moliere average
bool Selection::ApplyMoliereAverageCut(float shrmoliereavg){
	if(shrmoliereavg <= 15) return true;
	else return false;
}

// Neutral pion rejection: shower dE/dx and vertex distance
// get dE/dx on plane with the most hits
float Selection::GetdEdxMax(unsigned int shr_tkfit_nhits_Y, unsigned int shr_tkfit_nhits_V, unsigned int shr_tkfit_nhits_U,
					float shr_tkfit_dedx_Y, float shr_tkfit_dedx_V, float shr_tkfit_dedx_U) {

	float dedx_max = -1;

    // We want to also use the dedx when it is defined properly. Sometimes, the plane can have hits but an undefined dedx
    // use the dedx where we get the max number of hits and the dedx > 0
    // int temp_shr_hits_u_tot = shr_hits_u_tot;
    // int temp_shr_hits_v_tot = shr_hits_v_tot;
    // int temp_shr_hits_y_tot = shr_hits_y_tot;

    int temp_shr_hits_u_tot = shr_tkfit_nhits_U; // These variables give a bigger difference in run 1 and run 3
    int temp_shr_hits_v_tot = shr_tkfit_nhits_V;
    int temp_shr_hits_y_tot = shr_tkfit_nhits_Y;

    // If the dedx is undefined, set the hits to zero
    if (shr_tkfit_dedx_U <= 0) temp_shr_hits_u_tot = 0;
    if (shr_tkfit_dedx_V <= 0) temp_shr_hits_v_tot = 0;
    if (shr_tkfit_dedx_Y <= 0) temp_shr_hits_y_tot = 0;

    // Collection plane is the largest
    if (temp_shr_hits_y_tot > temp_shr_hits_u_tot && temp_shr_hits_y_tot > temp_shr_hits_v_tot ){
        dedx_max = shr_tkfit_dedx_Y;
    }
    // V Plane is the largest
    else if (temp_shr_hits_v_tot > temp_shr_hits_u_tot && temp_shr_hits_v_tot > temp_shr_hits_y_tot) {
        dedx_max = shr_tkfit_dedx_V;        
    }
    // U Plane is the largest
    else if (temp_shr_hits_u_tot > temp_shr_hits_v_tot && temp_shr_hits_u_tot > temp_shr_hits_y_tot){
        dedx_max = shr_tkfit_dedx_U;
    }
    // One plane was equal, so need to prioritise planes in preference of y, v, u
    else {

        // If y == any other plane, then y wins
        if (temp_shr_hits_y_tot == temp_shr_hits_u_tot || temp_shr_hits_y_tot == temp_shr_hits_v_tot ){
            dedx_max = shr_tkfit_dedx_Y;           
        }
        // U == V, ALL Y cases have been used up, so default to v
        else if (temp_shr_hits_u_tot == temp_shr_hits_v_tot ){
            dedx_max = shr_tkfit_dedx_V;            
        }
        else {
            dedx_max = shr_tkfit_dedx_U;
        }
    }

    if (dedx_max == -1) {
        std::cout << shr_tkfit_dedx_U << " " << shr_tkfit_dedx_V << " " << shr_tkfit_dedx_Y<< std::endl;
        std::cout << "Error [Selection.h]: Edge case of dEdx comparisons." << std::endl;
    }

    return dedx_max;
}
// apply 2D cut
bool Selection::ApplyNeutralPionRejectionCut(float dEdxMax, float shr_distance) {

    if (dEdxMax <= 0) {
    	return false;
    }
    else if (dEdxMax > 0 && dEdxMax < 1.75){
        if (shr_distance > 3 ) return false;
        else return true;
    }
    else if (dEdxMax >= 1.75 && dEdxMax < 2.5){ 
        if (shr_distance > 12 ) return false;
        else return true;
    }
    else if (dEdxMax >= 2.5 && dEdxMax < 3.5){
        if (shr_distance > 3 ) return false;
        else return true;
    }
    else if (dEdxMax >= 3.5 && dEdxMax < 4.7){
        if (shr_distance > 0 ) return false;
        else return true;
    }
    else if (dEdxMax >= 4.7){
        if (shr_distance > 3 ) return false;
        else return true;
    }
    else{
        std::cout << "Error: [Selection.h] Uncaught dEdx values." << std::endl;
        return false;
    }
}

// Track Length
bool Selection::ApplyTrackLengthCut(float trk_len) {
	if (trk_len >= 10) return true;
	else return false;
} 		




