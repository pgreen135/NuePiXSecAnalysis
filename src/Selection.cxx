#include "Selection.h"

#include <iostream>

// Constructor
Selection::Selection(const Utility &util): _utility{ util } {
	
	std::cout << "Initialising Selection Class" << std::endl;

}

// ------------------------------------------------------------------------------

bool Selection::ApplyPreSelection(const EventContainer &_evt, Utility::FileTypeEnums type) {
	
	// MC only cuts
	if (type == Utility::kMC || type == Utility::kDirt) {
		if(!ApplySWTriggerCut(_evt.swtrig_pre)) return false;							// software trigger [MC only]
		//if(!ApplyCommonOpticalFilterPECut(evt.opfilter_pe_beam)) return false;		// common optical filter (beam) [MC only]	(not applied)
		//if(!ApplyCommonOpticalFilterMichelCut(evt.opfilter_pe_veto)) return false;	// common optical filter (michel) [MC only]  (not applied)
	}	

	if(!ApplySliceIDCut(_evt.nslice)) return false;									// slice ID
	
	if(!ApplyElectronPionCanidateCut(_evt.n_showers, _evt.n_tracks)) return false;	// electron + pion candidate
	
	if(!ApplyVertexFVCut(_evt.reco_nu_vtx_sce_x, _evt.reco_nu_vtx_sce_y, _evt.reco_nu_vtx_sce_z)) return false;	// neutrino vertex in fiducial volume
	
	if(!ApplyContainedFractionCut(_evt.contained_fraction)) return false; 			// contained fraction
	
	return true;
}

// ------------------------------------------------------------------------------

bool Selection::ApplyCosmicRejection(const EventContainer &_evt) {

	if(!ApplyTopologicalScoreCut(_evt.topological_score)) return false;				// topological score
	
	if(!ApplyCosmicImpactParameterCut(_evt.CosmicIPAll3D)) return false;			// cosmic impact parameter

	return true;
}

// ------------------------------------------------------------------------------

bool Selection::ApplyElectronSelection(const EventContainer &_evt) {

	if(!ApplyShowerScoreCut(_evt.shr_score)) return false;							// shower score

	if(!ApplyShowerHitRatioCut(_evt.hits_ratio)) return false;						// shower hits ratio

	return true;
}

// ------------------------------------------------------------------------------

bool Selection::ApplyPionSelection(const EventContainer &_evt) {

	if(!ApplyTrackLengthCut(_evt.trk_len)) return false;							// longest track length

	if(!ApplyTrackVertexDistanceCut(_evt.trk_distance)) return false;				// track vertex separation distance

	if(!ApplyTrackScoreCut(_evt.trk_score)) return false;							// track score

	if(!ApplyTrackShowerOpeningAngleCut(_evt.tksh_angle)) return false;				// track-shower opening angle

	return true;
}

// ------------------------------------------------------------------------------

bool Selection::ApplyNeutralPionRejection(const EventContainer &_evt){

	if(!ApplyNeutralPionRejectionCut(_evt.shr_trkfit_gap10_dedx_max, _evt.shr_distance)) return false;		// neutral pion rejection: shower dE/dx and vertex separation

	if(!ApplyMoliereAverageCut(_evt.shrmoliereavg)) return false;					// shower moliere average
	
	if(!ApplyLeadingShowerEnergyFractionCut(_evt.shr_energyFraction)) return false;	// leading shower energy fraction
	
	return true;
}

// ------------------------------------------------------------------------------

bool Selection::ApplyProtonRejection(const EventContainer &_evt) {

	if(!ApplyLLRPIDScoreCut(_evt.trk_llr_pid_score)) return false;					// LLR PID score

	//if(!ApplyProtonBraggPeakScoreCut(_evt.trk_bragg_p)) return false;				// Proton Bragg peak score

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
	if(contained_fraction >= 0.9) return true;
	else return false;
}

// Pandora topological score
bool Selection::ApplyTopologicalScoreCut(float topological_score){
	if(topological_score > 0.4 || topological_score <= 0.01) return true;
	else return false;
}

// Cosmic impact parameter
bool Selection::ApplyCosmicImpactParameterCut(float CosmicIPAll3D) {
	if (CosmicIPAll3D > 20) return true;
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

// Leading shower energy fraction
bool Selection::ApplyLeadingShowerEnergyFractionCut(float shr_energyFraction){
	//std::cout << shr_energyFraction << std::endl;
	if(shr_energyFraction >= 0.8) return true;
	else return false;
}

// Neutral pion rejection: shower dE/dx and vertex distance
// apply 2D cut
bool Selection::ApplyNeutralPionRejectionCut(float dEdxMax, float shr_distance) {
	
	if (dEdxMax <= 0) {
    	return false;
    }
    else if (dEdxMax > 0 && dEdxMax < 1.5){
        if (shr_distance > 2 ) return false;
        else return true;
    }
    else if (dEdxMax >= 1.5 && dEdxMax < 2.5){ 
        if (shr_distance > 4 ) return false;
        else return true;
    }
    else if (dEdxMax >= 2.5 && dEdxMax < 3.75){
        if (shr_distance > 2 ) return false;
        else return true;
    }
    else if (dEdxMax >= 3.75 && dEdxMax < 4.5){
        if (shr_distance > 0 ) return false;
        else return true;
    }
    else if (dEdxMax >= 4.5){
        if (shr_distance > 1 ) return false;
        else return true;
    }
    else{
        std::cout << "Error: [Selection.h] Uncaught dEdx values." << std::endl;
        return false;
    }
    
	/*
    // ORIGINAL
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
    */
    
}

// Track Length
bool Selection::ApplyTrackLengthCut(float trk_len) {
	if (trk_len >= 10) return true;
	else return false;
}

// Track Vertex Distance
bool Selection::ApplyTrackVertexDistanceCut(float trk_distance) {
	if (trk_distance <= 5) return true;
	else return false;
}

// Track Score
bool Selection::ApplyTrackScoreCut(float trk_score) {
	if(trk_score >= 0.8 && trk_score <= 1) return true;
	else return false;
}

// Track Shower Opening Angle (remove back-to-back tracks)
bool Selection::ApplyTrackShowerOpeningAngleCut(float tksh_angle) {
	if(std::acos(tksh_angle) * 180 / 3.14159 < 160) return true;
	else return false;
}

// LLR PID Score
bool Selection::ApplyLLRPIDScoreCut(float trk_llr_pid_score) {
	if(trk_llr_pid_score > 0.5 && trk_llr_pid_score < 1.1) return true;
	else return false;
}

// Proton Bragg Peak Score
bool Selection::ApplyProtonBraggPeakScoreCut(float trk_bragg_p) {
	if(trk_bragg_p < 0.25) return true;
	else return false;
}		




