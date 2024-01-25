#include "../include/Selection.h"

#include <iostream>

// Constructor
Selection::Selection(const Utility &util): _utility{ util } {
	
	std::cout << "Initialising Selection Class" << std::endl;

}

// ------------------------------------------------------------------------------

bool Selection::ApplyCutBasedSelection(EventContainer &_evt, Utility::FileTypeEnums type, Utility::RunPeriodEnums runPeriod) {

    // populate derived variables
    _evt.populateDerivedVariables(type, runPeriod);

    // apply reconstruction recovery algorithms
    _evt.applyEventRecoveryAlgorithms();

	// trigger [impacts MC only]
	bool passTrigger = ApplyMCTrigger(_evt, type, runPeriod);
	if (!passTrigger) return false;

	// pre-selection
	bool passPreSelection = ApplyPreSelection(_evt);
	if(!passPreSelection) return false;	  

    // good shower selection
    bool passGoodShowerIdentification = ApplyGoodShowerSelection(_evt);
    if(!passGoodShowerIdentification) return false;

    // good track selection
    bool passGoodTrackSelection = ApplyGoodTrackSelection(_evt);
    if(!passGoodTrackSelection) return false;

    // reconstruction failure checks
    bool passReconstructionFailureChecks = ApplyReconstructionFailureChecks(_evt);
    if(!passReconstructionFailureChecks) return false;

    // cosmic rejection
    bool passCosmicRejection = ApplyCosmicRejection(_evt, runPeriod);
    if(!passCosmicRejection) return false;

    // neutral pion rejection
    bool passNeutralPionRejection = ApplyNeutralPionRejection(_evt);
    if(!passNeutralPionRejection) return false;

    // proton rejection
    bool passProtonRejection = ApplyProtonRejection(_evt);
    if(!passProtonRejection) return false;

    // determine event classification
    _evt.EventClassifier(type);

    // determine event weight
    _evt.calculateCVEventWeight(type, runPeriod); 

    // event passes
    return true;
}

// ------------------------------------------------------------------------------

bool Selection::ApplyBDTBasedSelection(EventContainer &_evt, const BDTTool &_bdt, Utility::FileTypeEnums type, Utility::RunPeriodEnums runPeriod) {

    // populate derived variables
    _evt.populateDerivedVariables(type, runPeriod);

    // apply reconstruction recovery algorithms
    _evt.applyEventRecoveryAlgorithms();

    // determine event classification
    _evt.EventClassifier(type);

    // determine interaction mode (MC)
    _evt.InteractionClassifier(type);
	
    // determine event weight
    _evt.calculateCVEventWeight(type, runPeriod);
    
    // trigger [impacts MC only]
	bool passTrigger = ApplyMCTrigger(_evt, type, runPeriod);
	if (!passTrigger) return false;
	
	// pre-selection
	bool passPreSelection = ApplyPreSelection(_evt);
	if (!passPreSelection) return false;

    // good shower selection
    bool passGoodShowerIdentification = ApplyGoodShowerSelection(_evt);
    if (!passGoodShowerIdentification) return false;

    // good track selection
    bool passGoodTrackSelection = ApplyGoodTrackSelection(_evt);
    if (!passGoodTrackSelection) return false;

    // reconstruction failure checks
    bool passReconstructionFailureChecks = ApplyReconstructionFailureChecks(_evt);
    if (!passReconstructionFailureChecks) return false;

    // cosmic rejection
    bool passCosmicRejection = ApplyCosmicRejection(_evt, runPeriod);
    if (!passCosmicRejection) return false;

    // loose neutral pion rejection
    bool passLooseNeutralPionRejection = ApplyLooseNeutralPionRejection(_evt);
    if (!passLooseNeutralPionRejection) return false;
    
    // loose proton rejection
    bool passLooseProtonPionRejection = ApplyLooseProtonRejection(_evt);
    if (!passLooseProtonPionRejection) return false;

    // event passes loose background rejection
    _evt.sel_passLooseRejection_ = true;

    // Evaluate BDTs
    bool passBDTNeutralPionRejection = ApplyNeutralPionRejectionBDT(_evt, _bdt, runPeriod);
    bool passBDTProtonRejection = ApplyProtonRejectionBDT(_evt, _bdt, runPeriod);   

    // set selected pion information
    setSelectedPionInformation(_evt);

    // BDT neutral pion rejection
    if (!passBDTNeutralPionRejection) return false;

    // event BDT pi0 rejection
    _evt.sel_passBDTPi0Rejection_ = true;   
    
    // BDT proton rejection 
    if (!passBDTProtonRejection) return false;

    // event passes
    _evt.sel_NueCC1piXp_ = true;

    // count number of proton-like tracks
    _evt.numberProtons = CountProtons(_evt, _bdt, runPeriod);

    // set angular variables
    _evt.setNuMIAngularVariables();

    return true;

}

// ------------------------------------------------------------------------------

bool Selection::ApplyElectronPhotonBDTTrainingSelection(EventContainer &_evt, Utility::FileTypeEnums type, Utility::RunPeriodEnums runPeriod) {

	// populate derived variables
    _evt.populateDerivedVariables(type, runPeriod);

    // apply reconstruction recovery algorithms
    _evt.applyEventRecoveryAlgorithms();

	// trigger [impacts MC only]
	bool passTrigger = ApplyMCTrigger(_evt, type, runPeriod);
	if (!passTrigger) return false;

	// pre-selection
	bool passPreSelection = ApplyPreSelection(_evt);
	if (!passPreSelection) return false;	  

    // good shower selection
    bool passGoodShowerIdentification = ApplyGoodShowerSelection(_evt);
    if (!passGoodShowerIdentification) return false;

    // reconstruction failure checks
    bool passReconstructionFailureChecks = ApplyReconstructionFailureChecks(_evt);
    if (!passReconstructionFailureChecks) return false;

    // cosmic rejection
    bool passCosmicRejection = ApplyCosmicRejection(_evt, runPeriod);
    if (!passCosmicRejection) return false;

    // loose neutral pion rejection
	bool passLooseNeutralPionRejection = ApplyLooseNeutralPionRejection(_evt);
    if (!passLooseNeutralPionRejection) return false;

    // determine event classification
    _evt.EventClassifier(type);

    // determine event weight
    _evt.calculateCVEventWeight(type, runPeriod);

    // event passes
    return true;
}

// ------------------------------------------------------------------------------

bool Selection::ApplyPionProtonBDTTrainingSelection(EventContainer &_evt, Utility::FileTypeEnums type, Utility::RunPeriodEnums runPeriod) {

	// populate derived variables
    _evt.populateDerivedVariables(type, runPeriod);

    // apply reconstruction recovery algorithms
    _evt.applyEventRecoveryAlgorithms();

	// trigger [impacts MC only]
	bool passTrigger = ApplyMCTrigger(_evt, type, runPeriod);
	if (!passTrigger) return false;

	// pre-selection
	bool passPreSelection = ApplyPreSelection(_evt);
	if (!passPreSelection) return false;

	// good track selection
    bool passGoodTrackSelection = ApplyGoodTrackSelection(_evt);
    if (!passGoodTrackSelection) return false;

    // cosmic rejection
    bool passCosmicRejection = ApplyCosmicRejection(_evt, runPeriod);
    if (!passCosmicRejection) return false;

    // loose proton rejection
	bool passLooseProtonPionRejection = ApplyLooseProtonRejection(_evt);
    if (!passLooseProtonPionRejection) return false;

	// determine event classification
    _evt.EventClassifier(type);

    // determine event weight
    _evt.calculateCVEventWeight(type, runPeriod);

    // event passes
    return true;
}

// ------------------------------------------------------------------------------

bool Selection::ApplyMCTrigger(const EventContainer &_evt, Utility::FileTypeEnums type, Utility::RunPeriodEnums runPeriod) {
	// MC only cuts
	if (type == Utility::kMC || type == Utility::kDetVar || type == Utility::kDirt || type == Utility::kIntrinsic || type == Utility::kCCNCPiZero || type == Utility::kFakeData) {
		
		// software trigger [MC only], changed during Run 3
		if (runPeriod == Utility::kRun1a || runPeriod == Utility::kRun1b || runPeriod == Utility::kRun2a || runPeriod == Utility::kRun2b) {
			if(!ApplySWTriggerCut(_evt.swtrig_pre)) return false;
		}
		else if (runPeriod == Utility::kRun3b) {
			if (_evt.run < 16880) { if(!ApplySWTriggerCut(_evt.swtrig_pre)) return false; }
			else { if(!ApplySWTriggerCut(_evt.swtrig_post)) return false; }
		}
		else  {
			if(!ApplySWTriggerCut(_evt.swtrig_post)) return false; 
		}
	}

	return true;
}

// ------------------------------------------------------------------------------

bool Selection::ApplyPreSelection(const EventContainer &_evt) {
	
	if(!ApplySliceIDCut(_evt.nslice)) return false;									// slice ID
	
	if(!ApplyVertexFVCut(_evt.reco_nu_vtx_sce_x, _evt.reco_nu_vtx_sce_y, _evt.reco_nu_vtx_sce_z)) return false;	// neutrino vertex in fiducial volume

	if(!ApplySignalCanidateCut(_evt.n_showers_contained, _evt.n_tracks_contained)) return false;	// electron + pion candidate

	if(!ApplyContainedFractionCut(_evt.contained_fraction)) return false; 			// contained fraction

	if(!ApplyAssociatedHitsFractionCut(_evt.associated_hits_fraction)) return false;	// fraction of hits associated with tracks/showers
	
	return true;
}

// ------------------------------------------------------------------------------

bool Selection::ApplyGoodShowerSelection(const EventContainer &_evt) {

	if(_evt.shr_pfpgeneration != 2) return false; 	// require pfp generation 2

	if(!ApplyHitsOnAllPlanesCut(_evt.shr_planehits_U, _evt.shr_planehits_V, _evt.shr_planehits_Y)) return false; 	// require hits on all planes
	
	if(!ApplyShowerEnergyCut(_evt.shr_energy_cali)) return false;					// shower energy

	if(!ApplyShowerScoreCut(_evt.shr_score)) return false;							// shower score

	if(!ApplyShowerSubclustersCut(_evt.shrsubclusters)) return false;				// number of shower subclusters

	if(!ApplyShowerHitRatioCut(_evt.hits_ratio)) return false;						// shower hits ratio

	return true;
}

// ------------------------------------------------------------------------------

bool Selection::ApplyGoodTrackSelection(EventContainer &_evt) {

	bool primaryTrackPasses = false;
	bool secondaryTrackPasses = false;
	bool tertiaryTrackPasses = false;

	// primary track
	if (!_evt.hasSpuriousLeadingTrack &&
		_evt.trk_pfpgeneration == 2 &&
		ApplyHitsOnAllPlanesCut(_evt.trk_planehits_U, _evt.trk_planehits_V, _evt.trk_planehits_Y) &&
		ApplyTrackLengthCut(_evt.trk_len) && 
		ApplyTrackScoreCut(_evt.trk_score) &&
		ApplyTrackContainmentCut(_evt.trk_sce_end_x, _evt.trk_sce_end_y, _evt.trk_sce_end_z) &&
		ApplyTrackVertexDistanceCut(_evt.trk_distance)
		) primaryTrackPasses = true;  	// track length, score, distance, containment

	// secondary track	
	if (_evt.trk2_pfpgeneration == 2 &&
	    ApplyHitsOnAllPlanesCut(_evt.trk2_planehits_U, _evt.trk2_planehits_V, _evt.trk2_planehits_Y) &&
		ApplyTrackLengthCut(_evt.trk2_len) && 
		ApplyTrackScoreCut(_evt.trk2_score) &&
		ApplyTrackContainmentCut(_evt.trk2_sce_end_x, _evt.trk2_sce_end_y, _evt.trk2_sce_end_z) &&
		ApplyTrackVertexDistanceCut(_evt.trk2_distance)
		) secondaryTrackPasses = true;		// track length, score, distance, containment

	// tertiary track
	if (_evt.trk3_pfpgeneration == 2 &&
	    ApplyHitsOnAllPlanesCut(_evt.trk3_planehits_U, _evt.trk3_planehits_V, _evt.trk3_planehits_Y) &&
		ApplyTrackLengthCut(_evt.trk3_len) && 
		ApplyTrackScoreCut(_evt.trk3_score) &&
		ApplyTrackContainmentCut(_evt.trk3_sce_end_x, _evt.trk3_sce_end_y, _evt.trk3_sce_end_z) &&
		ApplyTrackVertexDistanceCut(_evt.trk3_distance)
		) tertiaryTrackPasses = true;		// track length, score, distance, containment
	
	// update selection status variables in event for use later
	_evt.primaryTrackValid = primaryTrackPasses;
	_evt.secondaryTrackValid = secondaryTrackPasses;
	_evt.tertiaryTrackValid = tertiaryTrackPasses;

	if (primaryTrackPasses || secondaryTrackPasses || tertiaryTrackPasses) return true;
	else return false;
}

// ------------------------------------------------------------------------------
bool Selection::ApplyReconstructionFailureChecks(const EventContainer &_evt) { 

	if (!ApplyTrackShowerOpeningAngleCut(_evt.tksh_angle)) return false;	// primary track-shower opening angle

	if (!ApplyShrTrackFitCut(_evt.trkfit)) return false;				    // shower track fit hits fraction
    
    if (!ApplyShrTrackLengthCut(_evt.shr_trk_len)) return false;			// shower track fit length

    if (!ApplyShowerCylFractionCut(_evt.CylFrac2h_1cm)) return false;		// leading shower 1cm cylinder energy fraction	

	return true;
} 

// ------------------------------------------------------------------------------

bool Selection::ApplyCosmicRejection(const EventContainer &_evt, Utility::RunPeriodEnums runPeriod) {

	if(!ApplyTopologicalScoreCut(_evt.topological_score)) return false;				// topological score

	if(!ApplyCosmicImpactParameterCut(_evt.CosmicIPAll3D)) return false;			// cosmic impact parameter

	//if (runPeriod == Utility::kRun3b || runPeriod == Utility::kRun4ab || runPeriod == Utility::kRun4cd || runPeriod == Utility::kRun5) {
	//	if(!ApplyCRTVetoCut(_evt.crtveto)) return false;							// crt veto
	//}

	return true;
}

// ------------------------------------------------------------------------------

bool Selection::ApplyNeutralPionRejection(const EventContainer &_evt){

	if(!ApplyNumberShowersCut(_evt.n_showers_contained)) return false; 	// number of showers

	if(!ApplyNeutralPionRejectionCut(_evt.shr_trkfit_gap10_dedx_max, _evt.shr_distance)) return false;		// neutral pion rejection: shower dE/dx and vertex separation
	
	if(!ApplyMoliereAverageCut(_evt.shrmoliereavg)) return false;					// shower moliere average
	
	if(!ApplyLeadingShowerEnergyFractionCut(_evt.shr_energyFraction)) return false;	// leading shower energy fraction

	if(!ApplySecondShowerClusterCut(_evt.secondshower_Y_nhit, _evt.secondshower_Y_vtxdist, _evt.secondshower_Y_anglediff)) return false; // second shower cluster tagger

	return true;
}

bool Selection::ApplyLooseNeutralPionRejection(const EventContainer &_evt){

	if(!ApplyLooseLeadingShowerEnergyFractionCut(_evt.shr_energyFraction)) return false;	// leading shower energy fraction (loose)

	if(!ApplyLooseShowerDistanceCut(_evt.shr_distance)) return false; 			// shower distance from vertex (loose)

	if(!ApplyLooseMoliereAverageCut(_evt.shrmoliereavg)) return false;			// shower moliere average (loose)
	
	return true;
}

bool Selection::ApplyNeutralPionRejectionBDT(EventContainer &_evt, const BDTTool &_bdt, Utility::RunPeriodEnums runPeriod){

	// FHC
	if ((runPeriod == Utility::kRun1a || runPeriod == Utility::kRun2a || runPeriod == Utility::kRun4cd || runPeriod == Utility::kRun5)) {
		_evt.BDTScoreElectronPhoton = _bdt.evaluateElectronPhotonBDTScoreFHC(_evt);
		if(!ApplyElectronPhotonBDTCutFHC(_evt.BDTScoreElectronPhoton)) return false;
	}

	// RHC
	if ((runPeriod == Utility::kRun1b || runPeriod == Utility::kRun2b || runPeriod == Utility::kRun3b || runPeriod == Utility::kRun4ab)) {
		_evt.BDTScoreElectronPhoton = _bdt.evaluateElectronPhotonBDTScoreRHC(_evt);
		if(!ApplyElectronPhotonBDTCutRHC(_evt.BDTScoreElectronPhoton)) return false;
	}

	return true;
}

// ------------------------------------------------------------------------------

bool Selection::ApplyLooseProtonRejection(EventContainer &_evt) {

	
	bool primaryTrackPasses = false;
	bool secondaryTrackPasses = false;
	bool tertiaryTrackPasses = false;

	// primary track
	if (_evt.primaryTrackValid) {
		if (ApplyLLRPIDScoreCut(_evt.trk_llr_pid_score)) primaryTrackPasses = true;   
	}

	// secondary track
	if (_evt.secondaryTrackValid) {
		if (ApplyLLRPIDScoreCut(_evt.trk2_llr_pid_score)) secondaryTrackPasses = true; 	
	}

	// tertiary track
	if (_evt.tertiaryTrackValid) {
		if (ApplyLLRPIDScoreCut(_evt.trk3_llr_pid_score)) tertiaryTrackPasses = true;
	}

	// update selection status variables in event for use later
	_evt.primaryTrackPionlikeLoose = primaryTrackPasses;
	_evt.secondaryTrackPionlikeLoose = secondaryTrackPasses;
	_evt.tertiaryTrackPionlikeLoose = tertiaryTrackPasses;

	// require at least one track passes loose cuts
	if (primaryTrackPasses || secondaryTrackPasses || tertiaryTrackPasses) return true;
	else return false;
	
}

bool Selection::ApplyProtonRejection(EventContainer &_evt) {

	
	bool primaryTrackPasses = false;
	bool secondaryTrackPasses = false;
	bool tertiaryTrackPasses = false;

	// primary track
	if (_evt.primaryTrackValid) {
		if (ApplyLLRPIDScoreCut(_evt.trk_llr_pid_score) &&
			ApplyTrackTrunkdEdxCut(_evt.trk_dEdx_trunk_max) &&
			ApplyTrackBraggPeakScoreCut(_evt.trk_bragg_mip_max, _evt.trk_bragg_pion_max)
			) primaryTrackPasses = true;   
	}

	// secondary track
	if (_evt.secondaryTrackValid) {
		if (ApplyLLRPIDScoreCut(_evt.trk2_llr_pid_score) &&
			ApplyTrackTrunkdEdxCut(_evt.trk2_dEdx_trunk_max) &&
			ApplyTrackBraggPeakScoreCut(_evt.trk2_bragg_mip_max, _evt.trk2_bragg_pion_max)
			) secondaryTrackPasses = true; 	
	}

	// tertiary track
	if (_evt.tertiaryTrackValid) {
		if (ApplyLLRPIDScoreCut(_evt.trk3_llr_pid_score) &&
			ApplyTrackTrunkdEdxCut(_evt.trk3_dEdx_trunk_max) &&
			ApplyTrackBraggPeakScoreCut(_evt.trk3_bragg_mip_max, _evt.trk3_bragg_pion_max)
			) tertiaryTrackPasses = true;
	}

	// update selection status variables in event for use later
	_evt.primaryTrackPionlike = primaryTrackPasses;
	_evt.secondaryTrackPionlike = secondaryTrackPasses;
	_evt.tertiaryTrackPionlike = tertiaryTrackPasses;

	// count number of tracks that pass
	int nPass = 0;
	if (primaryTrackPasses) nPass++;
	if (secondaryTrackPasses) nPass++;
	if (tertiaryTrackPasses) nPass++;	

	// require 1 and only 1 charged pion candidate
	//if (primaryTrackPasses || secondaryTrackPasses || tertiaryTrackPasses) return true;
	if (nPass == 1) return true;
	else return false;
	
}


bool Selection::ApplyProtonRejectionBDT(EventContainer &_evt, const BDTTool &_bdt, Utility::RunPeriodEnums runPeriod){

	bool primaryTrackPasses = false;
	bool secondaryTrackPasses = false;
	bool tertiaryTrackPasses = false;

	// primary track
	if (_evt.primaryTrackPionlikeLoose) {
		// FHC
		if ((runPeriod == Utility::kRun1a || runPeriod == Utility::kRun2a || runPeriod == Utility::kRun4cd || runPeriod == Utility::kRun5)) {
			_evt.primaryTrackBDTScorePionProton = _bdt.evaluatePionProtonBDTScoreFHC(_evt, 1);
			if(ApplyProtonRejectionBDTCutFHC(_evt.primaryTrackBDTScorePionProton)) primaryTrackPasses = true;
		}
		// RHC
		if ((runPeriod == Utility::kRun1b || runPeriod == Utility::kRun2b || runPeriod == Utility::kRun3b || runPeriod == Utility::kRun4ab)) {
			_evt.primaryTrackBDTScorePionProton = _bdt.evaluatePionProtonBDTScoreRHC(_evt, 1);
			if(ApplyProtonRejectionBDTCutRHC(_evt.primaryTrackBDTScorePionProton)) primaryTrackPasses = true;
		}
	}

	// secondary track
	if (_evt.secondaryTrackPionlikeLoose) {
		// FHC
		if ((runPeriod == Utility::kRun1a || runPeriod == Utility::kRun2a || runPeriod == Utility::kRun4cd || runPeriod == Utility::kRun5)) {
			_evt.secondaryTrackBDTScorePionProton = _bdt.evaluatePionProtonBDTScoreFHC(_evt, 2);
			if(ApplyProtonRejectionBDTCutFHC(_evt.secondaryTrackBDTScorePionProton)) secondaryTrackPasses = true;
		}
		// RHC
		if ((runPeriod == Utility::kRun1b || runPeriod == Utility::kRun2b || runPeriod == Utility::kRun3b || runPeriod == Utility::kRun4ab)) {
			_evt.secondaryTrackBDTScorePionProton = _bdt.evaluatePionProtonBDTScoreRHC(_evt, 2);
			if(ApplyProtonRejectionBDTCutRHC(_evt.secondaryTrackBDTScorePionProton)) secondaryTrackPasses = true;
		}
	}

	// tertiary track
	if (_evt.tertiaryTrackPionlikeLoose) {
		// FHC
		if ((runPeriod == Utility::kRun1a || runPeriod == Utility::kRun2a || runPeriod == Utility::kRun4cd || runPeriod == Utility::kRun5)) {
			_evt.tertiaryTrackBDTScorePionProton = _bdt.evaluatePionProtonBDTScoreFHC(_evt, 3);
			if(ApplyProtonRejectionBDTCutFHC(_evt.tertiaryTrackBDTScorePionProton)) tertiaryTrackPasses = true;
		}
		// RHC
		if ((runPeriod == Utility::kRun1b || runPeriod == Utility::kRun2b || runPeriod == Utility::kRun3b || runPeriod == Utility::kRun4ab)) {
			_evt.tertiaryTrackBDTScorePionProton = _bdt.evaluatePionProtonBDTScoreRHC(_evt, 3);
			if(ApplyProtonRejectionBDTCutRHC(_evt.tertiaryTrackBDTScorePionProton)) tertiaryTrackPasses = true;
		}
	}

	// update selection status variables in event for use later
	_evt.primaryTrackPionlike = primaryTrackPasses;
	_evt.secondaryTrackPionlike = secondaryTrackPasses;
	_evt.tertiaryTrackPionlike = tertiaryTrackPasses;

	// count number of tracks that pass
	int nPass = 0;
	if (primaryTrackPasses) nPass++;
	if (secondaryTrackPasses) nPass++;
	if (tertiaryTrackPasses) nPass++;

	// require 1 and only 1 charged pion candidate
	if (nPass == 1) return true;
	else return false;
}

// ------------------------------------------------------------------------------
// Selection cuts
// Software Trigger [MC only]
bool Selection::ApplySWTriggerCut(int swtrig){
	return swtrig;
}

// Common Optical Filter PE [MC only, not used]
bool Selection::ApplyCommonOpticalFilterPECut(float opfilter_pe_beam){
	if (opfilter_pe_beam > 0) return true;
    else return false;
}

// Common Optical Filter Michel Veto [MC only, not used]
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
bool Selection::ApplySignalCanidateCut(int n_showers, int n_tracks){
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
	if(contained_fraction >= 0.7) return true;
	else return false;
}

// Fraction of hits associated with tracks and showers
bool Selection::ApplyAssociatedHitsFractionCut(float associated_hits_fraction) {
	if(associated_hits_fraction >= 0.5) return true;
	else return false;
}

// PFP hits on all planes
bool Selection::ApplyHitsOnAllPlanesCut(int pfp_planehits_U, int pfp_planehits_V, int pfp_planehits_Y) {
	if (pfp_planehits_U > 0 && pfp_planehits_V > 0 && pfp_planehits_Y > 0) return true;
	else return false;
}

// Shower energy
bool Selection::ApplyShowerEnergyCut(float shr_energy) {
	if (shr_energy >= 0.07) return true;
	else return false;
}	

// Shower score
bool Selection::ApplyShowerScoreCut(float shr_score){
	if (shr_score <= 0.2 && shr_score >= -0.1) return true; // >= -0.1  to check is defined, rather than default value
	else return false;
}

// Shower hit ratio
bool Selection::ApplyShowerHitRatioCut(float hits_ratio){
	if (hits_ratio >= 0.4) return true; // 0.45
	else return false;
}

// Pandora topological score
bool Selection::ApplyTopologicalScoreCut(float topological_score){
	if(topological_score > 0.25) return true; // 0.4
	else return false;
}

// Cosmic impact parameter
bool Selection::ApplyCosmicImpactParameterCut(float CosmicIPAll3D) {
	if (CosmicIPAll3D > 10) return true;
	else return false;
}

// CRT Veto
bool Selection::ApplyCRTVetoCut(float crtveto) {
	if (!crtveto) return true;
	else return false;
}

// Number of showers
bool Selection::ApplyNumberShowersCut(int n_showers_contained) {
	if(n_showers_contained <= 2) return true;
	else return false;
}

// Leading shower Moliere average
bool Selection::ApplyMoliereAverageCut(float shrmoliereavg){
	if(shrmoliereavg < 8) return true;
	else return false;
}

// Leading shower Moliere average (loose)
bool Selection::ApplyLooseMoliereAverageCut(float shrmoliereavg){
	if(shrmoliereavg < 15) return true;
	else return false;
}

// Leading shower subclusters 
bool Selection::ApplyShowerSubclustersCut(unsigned int shrsubclusters) {
	if(shrsubclusters >= 5) return true;
	else return false;
}

// Leading shower energy fraction
bool Selection::ApplyLeadingShowerEnergyFractionCut(float shr_energyFraction){
	if(shr_energyFraction >= 0.8) return true;
	else return false;
}

// Loose leading shower energy fraction
bool Selection::ApplyLooseLeadingShowerEnergyFractionCut(float shr_energyFraction){
	if(shr_energyFraction >= 0.7) return true;
	else return false;
}

// Leading shower fraction of energy in 1cm cylinder from shower center [see PeLEE]
bool Selection::ApplyShowerCylFractionCut(float CylFrac2h_1cm) {
	if(CylFrac2h_1cm < 0.95)  return true;	// default value -1
	else return false;	
}

// Neutral pion rejection: shower dE/dx and vertex distance
// apply 2D cut
bool Selection::ApplyNeutralPionRejectionCut(float dEdxMax, float shr_distance) {
	
    if (dEdxMax <= 0) {
    	return false;
    }
    else if (dEdxMax > 0 && dEdxMax < 1.5){
        if (shr_distance > 3.0 ) return false;
        else return true;
    }
    else if (dEdxMax >= 1.5 && dEdxMax < 2.5){ 
        if (shr_distance > 5.0 ) return false;
        else return true;
    }
    else if (dEdxMax >= 2.5 && dEdxMax < 3.5){
        if (shr_distance > 3.0 ) return false;
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

// Loose shower distance from vertex cut
bool Selection::ApplyLooseShowerDistanceCut(float shr_distance) {
	if (shr_distance < 10) return true;
	else return false;
}

// Neutral pion rejection: second shower tagger
// Only using Y plane - increased noise etc, causing issues with other planes
bool Selection::ApplySecondShowerClusterCut(int secondshower_Y_nhit, float secondshower_Y_vtxdist, float secondshower_Y_anglediff) {
	if (secondshower_Y_nhit > 25 && secondshower_Y_vtxdist < 100 && secondshower_Y_anglediff > 10 && secondshower_Y_anglediff != 9999) return false;
	return true;
}

// Neutral pion rejection BDT
bool Selection::ApplyElectronPhotonBDTCutFHC(float bdtscore_electronPhoton) {
	if (bdtscore_electronPhoton > 0.800) return true;
	else return false;
}
bool Selection::ApplyElectronPhotonBDTCutRHC(float bdtscore_electronPhoton) {
	if (bdtscore_electronPhoton > 0.825) return true;
	else return false;
}

// Track Length
bool Selection::ApplyTrackLengthCut(float trk_len) {
	if (trk_len >= 5 && trk_len <= 200) return true; // 5
	else return false;
}

// Track Energy
bool Selection::ApplyTrackEnergyCut(float trk_energy){
	if (trk_energy >= 0.04) return true; // 40 MeV
	else return false;
}

// Track Vertex Distance
bool Selection::ApplyTrackVertexDistanceCut(float trk_distance) {
	if (trk_distance <= 4) return true;
	else return false;
}

// Track Score
bool Selection::ApplyTrackScoreCut(float trk_score) {
	if(trk_score >= 0.5 && trk_score <= 1.1) return true;
	else return false;
}

// Track Containment
bool Selection::ApplyTrackContainmentCut(float trk_sce_end_x, float trk_sce_end_y, float trk_sce_end_z) {
	bool isExiting = _utility.isExiting(trk_sce_end_x, trk_sce_end_y, trk_sce_end_z);
	return isExiting;
}

// Track Shower Opening Angle (remove back-to-back tracks)
bool Selection::ApplyTrackShowerOpeningAngleCut(float tksh_angle) {
	if(tksh_angle > 10 && tksh_angle < 165) return true;
	else return false;
}

// LLR PID Score
bool Selection::ApplyLLRPIDScoreCut(float trk_llr_pid_score) {	
	if(trk_llr_pid_score > 0 && trk_llr_pid_score < 1.1) return true;
	else return false;
}

// Proton rejection: BDT
bool Selection::ApplyProtonRejectionBDTCutFHC(float bdtscore_pionProton) {
	if (bdtscore_pionProton > 0.350) return true;
	else return false;
}
bool Selection::ApplyProtonRejectionBDTCutRHC(float bdtscore_pionProton) {
	if (bdtscore_pionProton > 0.325) return true;
	else return false;
}

// Track Trunk dE/dx
bool Selection::ApplyTrackTrunkdEdxCut(float trk_dEdx_trunk) {
	if(trk_dEdx_trunk <= 3.8) return true;
	else return false;
}

// Track Bragg Peak Score
bool Selection::ApplyTrackBraggPeakScoreCut(float trk_bragg_mip, float trk_bragg_pion) {
	if (trk_bragg_mip < 0.1 && trk_bragg_pion < 0.5) return false;
	else return true;
}

// Shower Track Fit Score
bool Selection::ApplyShrTrackFitCut(float trkfit) {
	if (trkfit < 0.5) return true;	// default value = 1 when unfilled (float)
	else return false;
}

// Shower Track Fit Length
bool Selection::ApplyShrTrackLengthCut(float shr_trk_len) {
	if (shr_trk_len <= 250) return true;
	else return false;
}

int Selection::CountProtons(EventContainer &_evt, const BDTTool &_bdt, Utility::RunPeriodEnums runPeriod) {

	int numberProtons = 0;

	// consider all tracks in the event
	for (int i = 0; i < _evt.trk_llr_pid_score_v->size(); i++) {

		// check entry does not correspond to the pion
		if ( i == _evt.trk_id-1 && _evt.primaryTrackPionlike ) continue;
		if ( i == _evt.trk2_id-1 && _evt.secondaryTrackPionlike ) continue;
		if ( i == _evt.trk3_id-1 && _evt.tertiaryTrackPionlike ) continue;

		// look at tracks only
		if ( _evt.trk_score_v->at(i) <= 0.5 ) continue;

		// skip tracks where llrpid not available
		if ( _evt.trk_llr_pid_score_v->at(i) < -10 ) continue;

		// count proton candiates
		if ( _evt.pfp_generation_v->at(i) == 2 && 
			 _evt.trk_distance_v->at(i) < 10 && 
			 _evt.trk_llr_pid_score_v->at(i) <= 0 //&&
			 //ApplyTrackContainmentCut(_evt.trk_sce_end_x_v->at(i), _evt.trk_sce_end_y_v->at(i), _evt.trk_sce_end_z_v->at(i))
			 ) {
			numberProtons++;
		}
		// check for cases where passes LLR-PID test, but rejection by pion BDT
		else if ( i == _evt.trk_id-1 && _evt.primaryTrackPionlikeLoose && !_evt.primaryTrackPionlike ) numberProtons++;
		else if ( i == _evt.trk2_id-1 && _evt.secondaryTrackPionlikeLoose && !_evt.secondaryTrackPionlike ) numberProtons++;
		else if ( i == _evt.trk2_id-1 && _evt.tertiaryTrackPionlikeLoose && !_evt.tertiaryTrackPionlike ) numberProtons++;
		/*
		// check for cases where passes LLR-PID test, but rejection by loose pion BDT
		// primary track
		else if ( i == _evt.trk_id-1 && 
				  _evt.pfp_generation_v->at(i) == 2 && 
			 	  _evt.trk_distance_v->at(i) <= 4 && 
			      _evt.trk_llr_pid_score_v->at(i) > 0 &&  	
			      ApplyTrackContainmentCut(_evt.trk_sce_end_x_v->at(i), _evt.trk_sce_end_y_v->at(i), _evt.trk_sce_end_z_v->at(i)) &&
			      !_evt.primaryTrackPionlike ) {

			// FHC
			if (runPeriod == Utility::kRun1a || runPeriod == Utility::kRun2a || runPeriod == Utility::kRun4cd || runPeriod == Utility::kRun5) {
				double TrackBDTScorePionProton = _bdt.evaluatePionProtonBDTScoreFHC(_evt, 1);
				if(!ApplyProtonRejectionBDTCutFHC(TrackBDTScorePionProton)) numberProtons++;
			}
			// RHC
			if (runPeriod == Utility::kRun1b || runPeriod == Utility::kRun2b || runPeriod == Utility::kRun3b || runPeriod == Utility::kRun4ab) {
				double TrackBDTScorePionProton = _bdt.evaluatePionProtonBDTScoreRHC(_evt, 1);
				if(ApplyProtonRejectionBDTCutRHC(TrackBDTScorePionProton)) numberProtons++;
			}
		}
		// secondary track
		else if ( i == _evt.trk2_id-1 && 
				  _evt.pfp_generation_v->at(i) == 2 && 
			 	  _evt.trk_distance_v->at(i) <= 4 && 
			      _evt.trk_llr_pid_score_v->at(i) > 0 &&  	
			      ApplyTrackContainmentCut(_evt.trk_sce_end_x_v->at(i), _evt.trk_sce_end_y_v->at(i), _evt.trk_sce_end_z_v->at(i)) &&
			      !_evt.secondaryTrackPionlike ) {

			// FHC
			if (runPeriod == Utility::kRun1a || runPeriod == Utility::kRun2a || runPeriod == Utility::kRun4cd || runPeriod == Utility::kRun5) {
				double TrackBDTScorePionProton = _bdt.evaluatePionProtonBDTScoreFHC(_evt, 2);
				if(!ApplyProtonRejectionBDTCutFHC(TrackBDTScorePionProton)) numberProtons++;
			}
			// RHC
			if (runPeriod == Utility::kRun1b || runPeriod == Utility::kRun2b || runPeriod == Utility::kRun3b || runPeriod == Utility::kRun4ab) {
				double TrackBDTScorePionProton = _bdt.evaluatePionProtonBDTScoreRHC(_evt, 2);
				if(ApplyProtonRejectionBDTCutRHC(TrackBDTScorePionProton)) numberProtons++;
			}
		}
		// tertiary track
		else if ( i == _evt.trk3_id-1 && 
				  _evt.pfp_generation_v->at(i) == 2 && 
			 	  _evt.trk_distance_v->at(i) <= 4 && 
			      _evt.trk_llr_pid_score_v->at(i) > 0 &&  	
			      ApplyTrackContainmentCut(_evt.trk_sce_end_x_v->at(i), _evt.trk_sce_end_y_v->at(i), _evt.trk_sce_end_z_v->at(i)) &&
			      !_evt.tertiaryTrackPionlike ) {

			// FHC
			if (runPeriod == Utility::kRun1a || runPeriod == Utility::kRun2a || runPeriod == Utility::kRun4cd || runPeriod == Utility::kRun5) {
				double TrackBDTScorePionProton = _bdt.evaluatePionProtonBDTScoreFHC(_evt, 3);
				if(!ApplyProtonRejectionBDTCutFHC(TrackBDTScorePionProton)) numberProtons++;
			}
			// RHC
			if (runPeriod == Utility::kRun1b || runPeriod == Utility::kRun2b || runPeriod == Utility::kRun3b || runPeriod == Utility::kRun4ab) {
				double TrackBDTScorePionProton = _bdt.evaluatePionProtonBDTScoreRHC(_evt, 3);
				if(ApplyProtonRejectionBDTCutRHC(TrackBDTScorePionProton)) numberProtons++;
			}
		}
		*/

	}
	
	// fudge for plotting purposes, to put all N proton events in single bin
	if (numberProtons > 1) numberProtons = 1;

	return numberProtons;
}

void Selection::setSelectedPionInformation(EventContainer &_evt) {

    // loose
    if (_evt.primaryTrackPionlikeLoose) {
    	_evt.trk_bragg_mip_pion_loose = _evt.trk_bragg_mip_max;
     	_evt.trk_daughters_pion_loose = _evt.trk_daughters;
    	_evt.trk_dEdx_trunk_pion_loose = _evt.trk_dEdx_trunk_max;
    	_evt.trk_bragg_pion_pion_loose = _evt.trk_bragg_pion_max;
    	_evt.trk_llr_pid_score_pion_loose = _evt.trk_llr_pid_score;
    	_evt.trk_score_pion_loose = _evt.trk_score;
    	_evt.trk_end_spacepoints_pion_loose = _evt.trk_end_spacepoints;
    }
    else if (_evt.secondaryTrackPionlikeLoose) {
    	_evt.trk_bragg_mip_pion_loose = _evt.trk2_bragg_mip_max;
     	_evt.trk_daughters_pion_loose = _evt.trk2_daughters;
    	_evt.trk_dEdx_trunk_pion_loose = _evt.trk2_dEdx_trunk_max;
    	_evt.trk_bragg_pion_pion_loose = _evt.trk2_bragg_pion_max;
    	_evt.trk_llr_pid_score_pion_loose = _evt.trk2_llr_pid_score;
    	_evt.trk_score_pion_loose = _evt.trk2_score;
    	_evt.trk_end_spacepoints_pion_loose = _evt.trk2_end_spacepoints;
    }
    else {
    	_evt.trk_bragg_mip_pion_loose = _evt.trk3_bragg_mip_max;
     	_evt.trk_daughters_pion_loose = _evt.trk3_daughters;
    	_evt.trk_dEdx_trunk_pion_loose = _evt.trk3_dEdx_trunk_max;
    	_evt.trk_bragg_pion_pion_loose = _evt.trk3_bragg_pion_max;
    	_evt.trk_llr_pid_score_pion_loose = _evt.trk3_llr_pid_score;
    	_evt.trk_score_pion_loose = _evt.trk3_score;
    	_evt.trk_end_spacepoints_pion_loose = _evt.trk3_end_spacepoints;
    }

    // full
    if (_evt.primaryTrackPionlike) {
    	_evt.trk_bragg_mip_pion = _evt.trk_bragg_mip_max;
     	_evt.trk_daughters_pion = _evt.trk_daughters;
    	_evt.trk_dEdx_trunk_pion = _evt.trk_dEdx_trunk_max;
    	_evt.trk_bragg_pion_pion = _evt.trk_bragg_pion_max;
    	_evt.trk_llr_pid_score_pion = _evt.trk_llr_pid_score;
    	_evt.trk_score_pion = _evt.trk_score;
    	_evt.trk_end_spacepoints_pion = _evt.trk_end_spacepoints;
    	_evt.reco_energy_pion = _evt.trk_energy_pion + (139.57039/1000);
    }
    else if (_evt.secondaryTrackPionlike) {
    	_evt.trk_bragg_mip_pion = _evt.trk2_bragg_mip_max;
     	_evt.trk_daughters_pion = _evt.trk2_daughters;
    	_evt.trk_dEdx_trunk_pion = _evt.trk2_dEdx_trunk_max;
    	_evt.trk_bragg_pion_pion = _evt.trk2_bragg_pion_max;
    	_evt.trk_llr_pid_score_pion = _evt.trk2_llr_pid_score;
    	_evt.trk_score_pion = _evt.trk2_score;
    	_evt.trk_end_spacepoints_pion = _evt.trk2_end_spacepoints;
    	_evt.reco_energy_pion = _evt.trk2_energy_pion;
	}
	else {
		_evt.trk_bragg_mip_pion = _evt.trk3_bragg_mip_max;
     	_evt.trk_daughters_pion = _evt.trk3_daughters;
    	_evt.trk_dEdx_trunk_pion = _evt.trk3_dEdx_trunk_max;
    	_evt.trk_bragg_pion_pion = _evt.trk3_bragg_pion_max;
    	_evt.trk_llr_pid_score_pion = _evt.trk3_llr_pid_score;
    	_evt.trk_score_pion = _evt.trk3_score;
    	_evt.trk_end_spacepoints_pion = _evt.trk3_end_spacepoints;
    	_evt.reco_energy_pion = _evt.trk3_energy_pion;
	}
}

