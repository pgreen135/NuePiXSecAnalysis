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
		if(!ApplyCommonOpticalFilterPECut(_evt.opfilter_pe_beam)) return false;		    // common optical filter (beam) [MC only]	(should this be applied?)
		if(!ApplyCommonOpticalFilterMichelCut(_evt.opfilter_pe_veto)) return false;	    // common optical filter (michel veto) [MC only]  (should this be applied?)
	}	

	if(!ApplySliceIDCut(_evt.nslice)) return false;									// slice ID
	
	if(!ApplyElectronPionCanidateCut(_evt.n_showers, _evt.n_tracks)) return false;	// electron + pion candidate
	
	if(!ApplyVertexFVCut(_evt.reco_nu_vtx_sce_x, _evt.reco_nu_vtx_sce_y, _evt.reco_nu_vtx_sce_z)) return false;	// neutrino vertex in fiducial volume
	
	if(!ApplyContainedFractionCut(_evt.contained_fraction)) return false; 			// contained fraction
	
	return true;
}

bool Selection::ApplyReconstructionCompletenessCheck(const EventContainer &_evt) {

	if(!ApplyAssociatedHitsFractionCut(_evt.associated_hits_fraction)) return false;	// fraction of hits associated with tracks/showers

	return true;
}

// ------------------------------------------------------------------------------

bool Selection::ApplyElectronSelection(const EventContainer &_evt) {

	if(!ApplyShowerScoreCut(_evt.shr_score)) return false;							// shower score

	if(!ApplyShowerHitRatioCut(_evt.hits_ratio)) return false;						// shower hits ratio

	return true;
}

// ------------------------------------------------------------------------------

bool Selection::ApplyPionSelection(EventContainer &_evt, Utility::FileTypeEnums type) {

	bool primaryTrackPasses = false;
	bool secondaryTrackPasses = false;

	// primary track
	if (ApplyTrackLengthCut(_evt.trk_len) && 
		ApplyTrackScoreCut(_evt.trk_score) &&
		ApplyTrackVertexDistanceCut(_evt.trk_distance) &&
		//ApplyTrackContainmentCut(_evt.trk_sce_end_x, _evt.trk_sce_end_y, _evt.trk_sce_end_z) &&
		ApplyTrackShowerOpeningAngleCut(_evt.tksh_angle)) primaryTrackPasses = true;			  										// track length, score, distance, containment, track-shower opening angle

	// secondary track - not available for Run 1 Dirt, and tksh_angle not available 	
	if (type == Utility::kMC || type == Utility::kEXT) {	
		if (ApplyTrackLengthCut(_evt.trk2_len) && 
			ApplyTrackScoreCut(_evt.trk2_score) &&
			//ApplyTrackContainmentCut(_evt.trk2_sce_end_x, _evt.trk2_sce_end_y, _evt.trk2_sce_end_z) &&
			ApplyTrackVertexDistanceCut(_evt.trk2_distance)) secondaryTrackPasses = true;		// track length, score, distance, containment
	}

	// update selection status variables in event for use later
	_evt.primaryTrackValid = primaryTrackPasses;
	_evt.secondaryTrackValid = secondaryTrackPasses;

	if (primaryTrackPasses || secondaryTrackPasses) return true;
	else return false;
}

// ------------------------------------------------------------------------------

bool Selection::ApplyCosmicRejection(const EventContainer &_evt) {

	if(!ApplyTopologicalScoreCut(_evt.topological_score)) return false;				// topological score

	if(!ApplyCosmicImpactParameterCut(_evt.CosmicIPAll3D)) return false;			// cosmic impact parameter

	return true;
}

// ------------------------------------------------------------------------------

bool Selection::ApplyNeutralPionRejection(const EventContainer &_evt){

	if(!ApplyNeutralPionRejectionCut(_evt.shr_trkfit_gap10_dedx_max, _evt.shr_distance)) return false;		// neutral pion rejection: shower dE/dx and vertex separation

	if(!ApplyMoliereAverageCut(_evt.shrmoliereavg)) return false;					// shower moliere average
	
	if(!ApplyLeadingShowerEnergyFractionCut(_evt.shr_energyFraction)) return false;	// leading shower energy fraction

	if(!ApplySecondShowerClusterCut(_evt.secondshower_U_nhit, _evt.secondshower_V_nhit, _evt.secondshower_Y_nhit,
							 		_evt.secondshower_U_vtxdist, _evt.secondshower_V_vtxdist, _evt.secondshower_Y_vtxdist,
							 		_evt.secondshower_U_anglediff, _evt.secondshower_V_anglediff, _evt.secondshower_Y_anglediff)) return false; // second shower cluster tagger

	return true;
}

// ------------------------------------------------------------------------------

bool Selection::ApplyProtonRejection(EventContainer &_evt, Utility::FileTypeEnums type) {

	
	bool primaryTrackPasses = false;
	bool secondaryTrackPasses = false;

	// primary track - some variables only available for MC
	if (_evt.primaryTrackValid) {
		if (ApplyLLRPIDScoreCut(_evt.trk_llr_pid_score) &&
	        ApplyTrackTrunkdEdxCut(_evt.trk_dEdx_trunk_max) 
	        ) primaryTrackPasses = true;
	}

	// secondary track, not available for Dirt + some variables only available for MC
	if (_evt.secondaryTrackValid) {
		if (type == Utility::kMC || type == Utility::kEXT) {
			if (ApplyLLRPIDScoreCut(_evt.trk2_llr_pid_score) && 
				ApplyTrackTrunkdEdxCut(_evt.trk2_dEdx_trunk_max) 
				) secondaryTrackPasses = true;
		}
	}

	// update selection status variables in event for use later
	_evt.primaryTrackPionlike = primaryTrackPasses;
	_evt.secondaryTrackPionlike = secondaryTrackPasses;	
	
	if (primaryTrackPasses || secondaryTrackPasses) return true;
	else return false;
	
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

// Fraction of hits associated with tracks and showers
bool Selection::ApplyAssociatedHitsFractionCut(float associated_hits_fraction) {
	if(associated_hits_fraction >= 0.75) return true;
	else return false;
}

// Shower score
bool Selection::ApplyShowerScoreCut(float shr_score){
	if (shr_score <= 0.1 && shr_score >= -0.1) return true; // >= -0.1  to check is defined, rather than default value
	else return false;
}

// Shower hit ratio
bool Selection::ApplyShowerHitRatioCut(float hits_ratio){
	if (hits_ratio >= 0.5) return true;
	else return false;
}

// Pandora topological score
bool Selection::ApplyTopologicalScoreCut(float topological_score){
	if(topological_score > 0.4 || topological_score <= 0.01) return true;
	else return false;
}

// Cosmic impact parameter
bool Selection::ApplyCosmicImpactParameterCut(float CosmicIPAll3D) {
	if (CosmicIPAll3D > 15) return true;
	else return false;
}

// Leading shower Moliere average
bool Selection::ApplyMoliereAverageCut(float shrmoliereavg){
	if(shrmoliereavg <= 10) return true;
	else return false;
}

// Leading shower energy fraction
bool Selection::ApplyLeadingShowerEnergyFractionCut(float shr_energyFraction){
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
        if (shr_distance > 1.5 ) return false;
        else return true;
    }
    else if (dEdxMax >= 1.5 && dEdxMax < 2.5){ 
        if (shr_distance > 3.5 ) return false;
        else return true;
    }
    else if (dEdxMax >= 2.5 && dEdxMax < 3.5){
        if (shr_distance > 1.5 ) return false;
        else return true;
    }
    else if (dEdxMax >= 3.5 && dEdxMax < 5){
        return false;
    }
    else if (dEdxMax >= 5){
        if (shr_distance > 1 ) return false;
        else return true;
    }
    else{
        std::cout << "Error: [Selection.h] Uncaught dEdx values." << std::endl;
        return false;
    }
}

// Neutral pion rejection: second shower tagger
// To do: optimize
// Only using Y plane - increased noise etc, causing issues with other planes
bool Selection::ApplySecondShowerClusterCut(int secondshower_U_nhit, int secondshower_V_nhit, int secondshower_Y_nhit, 
											float secondshower_U_vtxdist, float secondshower_V_vtxdist, float secondshower_Y_vtxdist, 
											float secondshower_U_anglediff, float secondshower_V_anglediff, float secondshower_Y_anglediff) {
	//if (secondshower_U_nhit > 25 && secondshower_U_vtxdist < 100 && secondshower_U_anglediff > 10 && secondshower_U_anglediff != 9999) return false;
	//if (secondshower_V_nhit > 25 && secondshower_V_vtxdist < 100 && secondshower_V_anglediff > 10 && secondshower_V_anglediff != 9999) return false;
	if (secondshower_Y_nhit > 25 && secondshower_Y_vtxdist < 100 && secondshower_Y_anglediff > 10 && secondshower_Y_anglediff != 9999) return false;
	return true;
}

// Track Length
bool Selection::ApplyTrackLengthCut(float trk_len) {
	if (trk_len >= 10) return true;
	else return false;
}

// Track Vertex Distance
bool Selection::ApplyTrackVertexDistanceCut(float trk_distance) {
	if (trk_distance <= 4) return true;
	else return false;
}

// Track Score
bool Selection::ApplyTrackScoreCut(float trk_score) {
	if(trk_score >= 0.7 && trk_score <= 1.1) return true;
	else return false;
}

// Track Containment
bool Selection::ApplyTrackContainmentCut(float trk_sce_end_x, float trk_sce_end_y, float trk_sce_end_z) {
	bool isExiting = _utility.isExiting(trk_sce_end_x, trk_sce_end_y, trk_sce_end_z);
	return isExiting;
}

// Track Shower Opening Angle (remove back-to-back tracks)
bool Selection::ApplyTrackShowerOpeningAngleCut(float tksh_angle) {
	if(std::acos(tksh_angle) * 180 / 3.14159 < 160) return true;
	else return false;
}

// LLR PID Score
bool Selection::ApplyLLRPIDScoreCut(float trk_llr_pid_score) {	
	if(trk_llr_pid_score > 0 && trk_llr_pid_score < 1.1) return true;
	else return false;
}

// Proton Bragg Peak Score
bool Selection::ApplyProtonBraggPeakScoreCut(float trk_bragg_p) {
	if(trk_bragg_p <= 0.225) return true;
	else return false;
}

// Pion Bragg Peak Score
bool Selection::ApplyPionBraggPeakScoreCut(float trk_bragg_pion) {
	if(trk_bragg_pion >= 0.225) return true;
	else return false;
}

// Track Trunk dE/dx
bool Selection::ApplyTrackTrunkdEdxCut(float trk_dEdx_trunk) {
	if(trk_dEdx_trunk <= 3.5 || trk_dEdx_trunk == 9999) return true;
	else return false;
}		




