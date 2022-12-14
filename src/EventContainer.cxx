#include "EventContainer.h"

#include <iostream>
#include <algorithm>
#include <numeric>


// Constructor
EventContainer::EventContainer(TTree *tree, const Utility &utility): _utility{ utility } {
	
	std::cout << "Initialising Event Container Class" << std::endl;

	// set tree addresses
	tree->SetBranchAddress("run", &run);
	tree->SetBranchAddress("sub", &sub);
	tree->SetBranchAddress("evt", &evt);

	tree->SetBranchAddress("nu_pdg", &nu_pdg);
	tree->SetBranchAddress("ccnc", &ccnc);
	tree->SetBranchAddress("interaction", &interaction);
	tree->SetBranchAddress("nu_e", &nu_e);
	
	tree->SetBranchAddress("nmuon", &nmuon);
	tree->SetBranchAddress("nelec", &nelec);
	tree->SetBranchAddress("elec_e", &elec_e);
	tree->SetBranchAddress("npion", &npion);
	tree->SetBranchAddress("pion_e", &pion_e);
	tree->SetBranchAddress("npi0", &npi0);
	tree->SetBranchAddress("nproton", &nproton);
	tree->SetBranchAddress("proton_e", &proton_e);

	tree->SetBranchAddress("true_nu_vtx_sce_x", &true_nu_vtx_sce_x);
	tree->SetBranchAddress("true_nu_vtx_sce_y", &true_nu_vtx_sce_y);
	tree->SetBranchAddress("true_nu_vtx_sce_z", &true_nu_vtx_sce_z);

	tree->SetBranchAddress("swtrig", &swtrig);
    tree->SetBranchAddress("swtrig_pre", &swtrig_pre);
    tree->SetBranchAddress("swtrig_post", &swtrig_post);

    tree->SetBranchAddress("_opfilter_pe_beam", &opfilter_pe_beam);
    tree->SetBranchAddress("_opfilter_pe_veto", &opfilter_pe_veto);

	tree->SetBranchAddress("nslice", &nslice);
	tree->SetBranchAddress("n_tracks", &n_tracks);
    tree->SetBranchAddress("n_showers", &n_showers);
    tree->SetBranchAddress("n_showers_contained", &n_showers_contained);
    tree->SetBranchAddress("n_tracks_contained", &n_tracks_contained);
	tree->SetBranchAddress("nu_purity_from_pfp", &nu_purity_from_pfp);

	tree->SetBranchAddress("shr_hits_tot", &shr_hits_tot);
	tree->SetBranchAddress("trk_hits_tot", &trk_hits_tot);
	tree->SetBranchAddress("trk_hits_max", &trk_hits_max);
	tree->SetBranchAddress("trk_hits_2nd", &trk_hits_2nd);

	tree->SetBranchAddress("total_hits_y", &total_hits_y);
	tree->SetBranchAddress("shr_hits_y_tot", &shr_hits_y_tot);
	tree->SetBranchAddress("trk_hits_y_tot", &trk_hits_y_tot);
	tree->SetBranchAddress("extra_energy_y", &extra_energy_y);

	tree->SetBranchAddress("shr_hits_u_tot", &shr_hits_u_tot);
	tree->SetBranchAddress("trk_hits_u_tot", &trk_hits_u_tot);

	tree->SetBranchAddress("shr_hits_v_tot", &shr_hits_v_tot);
	tree->SetBranchAddress("trk_hits_v_tot", &trk_hits_v_tot);

	tree->SetBranchAddress("reco_nu_vtx_sce_x", &reco_nu_vtx_sce_x);
    tree->SetBranchAddress("reco_nu_vtx_sce_y", &reco_nu_vtx_sce_y);
    tree->SetBranchAddress("reco_nu_vtx_sce_z", &reco_nu_vtx_sce_z);

    tree->SetBranchAddress("contained_fraction", &contained_fraction);

    tree->SetBranchAddress("topological_score", &topological_score);
    tree->SetBranchAddress("CosmicIPAll3D", &CosmicIPAll3D);
    tree->SetBranchAddress("CosmicDirAll3D", &CosmicDirAll3D);

    tree->SetBranchAddress("shr_id", &shr_id);
    tree->SetBranchAddress("shr2_id", &shr2_id);
    tree->SetBranchAddress("shr_distance", &shr_distance);
    tree->SetBranchAddress("shr_score", &shr_score);
    tree->SetBranchAddress("shr_energy_cali", &shr_energy_cali);
    tree->SetBranchAddress("shr_energy_tot_cali", &shr_energy_tot_cali);    
    tree->SetBranchAddress("hits_ratio", &hits_ratio);
    tree->SetBranchAddress("shrmoliereavg", &shrmoliereavg);
    tree->SetBranchAddress("shr1shr2moliereavg", &shr1shr2moliereavg);
    tree->SetBranchAddress("shr1trk2moliereavg", &shr1trk2moliereavg);

    tree->SetBranchAddress("shr_llrpid_dedx", &shr_llrpid_dedx);

    tree->SetBranchAddress("trkfit", &trkfit);
 
    tree->SetBranchAddress("shr_tkfit_dedx_Y", &shr_tkfit_dedx_Y);
    tree->SetBranchAddress("shr_tkfit_dedx_V", &shr_tkfit_dedx_V);
    tree->SetBranchAddress("shr_tkfit_dedx_U", &shr_tkfit_dedx_U);

    tree->SetBranchAddress("shr_tkfit_nhits_Y", &shr_tkfit_nhits_Y);
    tree->SetBranchAddress("shr_tkfit_nhits_V", &shr_tkfit_nhits_V);
    tree->SetBranchAddress("shr_tkfit_nhits_U", &shr_tkfit_nhits_U);

    tree->SetBranchAddress("shr_tkfit_gap05_dedx_Y", &shr_tkfit_gap05_dedx_Y);
    tree->SetBranchAddress("shr_tkfit_gap05_dedx_V", &shr_tkfit_gap05_dedx_V);
    tree->SetBranchAddress("shr_tkfit_gap05_dedx_U", &shr_tkfit_gap05_dedx_U);

    tree->SetBranchAddress("shr_tkfit_gap05_nhits_Y", &shr_tkfit_gap05_nhits_Y);
    tree->SetBranchAddress("shr_tkfit_gap05_nhits_V", &shr_tkfit_gap05_nhits_V);
    tree->SetBranchAddress("shr_tkfit_gap05_nhits_U", &shr_tkfit_gap05_nhits_U);

    tree->SetBranchAddress("shr_tkfit_gap10_dedx_Y", &shr_tkfit_gap10_dedx_Y);
    tree->SetBranchAddress("shr_tkfit_gap10_dedx_V", &shr_tkfit_gap10_dedx_V);
    tree->SetBranchAddress("shr_tkfit_gap10_dedx_U", &shr_tkfit_gap10_dedx_U);

    tree->SetBranchAddress("shr_tkfit_gap10_nhits_Y", &shr_tkfit_gap10_nhits_Y);
    tree->SetBranchAddress("shr_tkfit_gap10_nhits_V", &shr_tkfit_gap10_nhits_V);
    tree->SetBranchAddress("shr_tkfit_gap10_nhits_U", &shr_tkfit_gap10_nhits_U);

    tree->SetBranchAddress("shrclusdir0", &shrclusdir0);
    tree->SetBranchAddress("shrclusdir1", &shrclusdir1);
    tree->SetBranchAddress("shrclusdir2", &shrclusdir2);

    tree->SetBranchAddress("shrsubclusters0", &shrsubclusters0);
    tree->SetBranchAddress("shrsubclusters1", &shrsubclusters1);
    tree->SetBranchAddress("shrsubclusters2", &shrsubclusters2);

    tree->SetBranchAddress("shrPCA1CMed_5cm", &shrPCA1CMed_5cm);
    tree->SetBranchAddress("CylFrac2h_1cm", &CylFrac2h_1cm);

    tree->SetBranchAddress("secondshower_U_nhit", &secondshower_U_nhit);
    tree->SetBranchAddress("secondshower_V_nhit", &secondshower_V_nhit);
    tree->SetBranchAddress("secondshower_Y_nhit", &secondshower_Y_nhit);
    tree->SetBranchAddress("secondshower_U_vtxdist", &secondshower_U_vtxdist);
    tree->SetBranchAddress("secondshower_V_vtxdist", &secondshower_V_vtxdist);
    tree->SetBranchAddress("secondshower_Y_vtxdist", &secondshower_Y_vtxdist);
    tree->SetBranchAddress("secondshower_U_dir", &secondshower_U_dir);
    tree->SetBranchAddress("secondshower_V_dir", &secondshower_V_dir);
    tree->SetBranchAddress("secondshower_Y_dir", &secondshower_Y_dir);
    
    tree->SetBranchAddress("trk_id", &trk_id);
    tree->SetBranchAddress("trk2_id", &trk2_id);
    tree->SetBranchAddress("trk3_id", &trk3_id);
    tree->SetBranchAddress("trk_len", &trk_len);
    tree->SetBranchAddress("trk_distance", &trk_distance);
    tree->SetBranchAddress("trk_score", &trk_score);
    tree->SetBranchAddress("trk_theta", &trk_theta);
    tree->SetBranchAddress("trk_phi", &trk_phi);
    tree->SetBranchAddress("trk_bkt_pdg", &trk_bkt_pdg);

    tree->SetBranchAddress("trk_bragg_p", &trk_bragg_p);
    tree->SetBranchAddress("trk_bragg_mu", &trk_bragg_mu);
    tree->SetBranchAddress("trk_bragg_pion", &trk_bragg_pion);
    tree->SetBranchAddress("trk_bragg_mip", &trk_bragg_mip);

    tree->SetBranchAddress("tksh_distance", &tksh_distance);
    tree->SetBranchAddress("tksh_angle", &tksh_angle);

    tree->SetBranchAddress("trk_score_v",          &trk_score_v);
    tree->SetBranchAddress("trk_start_x_v",        &trk_start_x_v);
    tree->SetBranchAddress("trk_start_y_v",        &trk_start_y_v);
    tree->SetBranchAddress("trk_start_z_v",        &trk_start_z_v);
    tree->SetBranchAddress("trk_sce_start_x_v",        &trk_sce_start_x_v);
    tree->SetBranchAddress("trk_sce_start_y_v",        &trk_sce_start_y_v);
    tree->SetBranchAddress("trk_sce_start_z_v",        &trk_sce_start_z_v);
    tree->SetBranchAddress("trk_sce_end_x_v",          &trk_sce_end_x_v);
    tree->SetBranchAddress("trk_sce_end_y_v",          &trk_sce_end_y_v);
    tree->SetBranchAddress("trk_sce_end_z_v",          &trk_sce_end_z_v);
    tree->SetBranchAddress("trk_dir_x_v",          &trk_dir_x_v);
    tree->SetBranchAddress("trk_dir_y_v",          &trk_dir_y_v);
    tree->SetBranchAddress("trk_dir_z_v",          &trk_dir_z_v);

    tree->SetBranchAddress("trk_len_v",                &trk_len_v);
    tree->SetBranchAddress("trk_distance_v",           &trk_distance_v);

    tree->SetBranchAddress("trk_bragg_p_v", &trk_bragg_p_v);
    tree->SetBranchAddress("trk_bragg_mu_v", &trk_bragg_mu_v);
    tree->SetBranchAddress("trk_bragg_pion_v", &trk_bragg_pion_v);
    tree->SetBranchAddress("trk_bragg_pion_u_v", &trk_bragg_pion_u_v);
    tree->SetBranchAddress("trk_bragg_pion_v_v", &trk_bragg_pion_v_v);
    tree->SetBranchAddress("trk_bragg_mip_v", &trk_bragg_mip_v);
    tree->SetBranchAddress("trk_bragg_mip_u_v", &trk_bragg_mip_u_v);
    tree->SetBranchAddress("trk_bragg_mip_v_v", &trk_bragg_mip_v_v);
    tree->SetBranchAddress("trk_llr_pid_score_v", &trk_llr_pid_score_v);

    tree->SetBranchAddress("all_trk_hits", &all_trk_hits);
    
    tree->SetBranchAddress("all_shr_energies",          &all_shr_energies);
    tree->SetBranchAddress("shr_energy_u_v",          &shr_energy_u_v);
    tree->SetBranchAddress("shr_energy_v_v",          &shr_energy_v_v);
    tree->SetBranchAddress("shr_energy_y_v",          &shr_energy_y_v);
    tree->SetBranchAddress("shr_px_v",          &shr_px_v);
    tree->SetBranchAddress("shr_py_v",          &shr_py_v);
    tree->SetBranchAddress("shr_pz_v",          &shr_pz_v);
    tree->SetBranchAddress("shr_dist_v",        &shr_dist_v);
    tree->SetBranchAddress("shr_moliere_avg_v", &shr_moliere_avg_v);
    
    tree->SetBranchAddress("shr_start_x_v",     &shr_start_x_v);
    tree->SetBranchAddress("shr_start_y_v",     &shr_start_y_v);
    tree->SetBranchAddress("shr_start_z_v",     &shr_start_z_v);

    tree->SetBranchAddress("shr_tkfit_dedx_u_v",     &shr_tkfit_dedx_u_v);
    tree->SetBranchAddress("shr_tkfit_dedx_v_v",     &shr_tkfit_dedx_v_v);
    tree->SetBranchAddress("shr_tkfit_dedx_y_v",     &shr_tkfit_dedx_y_v);
    tree->SetBranchAddress("shr_tkfit_dedx_nhits_u_v",    &shr_tkfit_dedx_nhits_u_v);
    tree->SetBranchAddress("shr_tkfit_dedx_nhits_v_v",    &shr_tkfit_dedx_nhits_v_v);
    tree->SetBranchAddress("shr_tkfit_dedx_nhits_y_v",    &shr_tkfit_dedx_nhits_y_v);

    tree->SetBranchAddress("pfp_trk_daughters_v", &pfp_trk_daughters_v);
 	tree->SetBranchAddress("pfp_shr_daughters_v", &pfp_shr_daughters_v);  

 	tree->SetBranchAddress("pfpplanesubclusters_U", &pfpplanesubclusters_U_v);
 	tree->SetBranchAddress("pfpplanesubclusters_V", &pfpplanesubclusters_V_v);
 	tree->SetBranchAddress("pfpplanesubclusters_Y", &pfpplanesubclusters_Y_v);  

 	tree->SetBranchAddress("backtracked_pdg", &backtracked_pdg_v); 	
    
    tree->SetBranchAddress("pi0_mass_U",         &pi0_mass_U);

    tree->SetBranchAddress("mc_pdg",       &mc_pdg_v);
    tree->SetBranchAddress("mc_E",         &mc_E_v); 

    // track trunk dE/dx
    tree->SetBranchAddress("trk_nhits_u_v",		&trk_nhits_u_v);
    tree->SetBranchAddress("trk_nhits_v_v",		&trk_nhits_v_v);
    tree->SetBranchAddress("trk_nhits_y_v",		&trk_nhits_y_v);
    tree->SetBranchAddress("trk_trunk_dEdx_u_v",	&trk_trunk_dEdx_u_v);
    tree->SetBranchAddress("trk_trunk_dEdx_v_v",	&trk_trunk_dEdx_v_v);
    tree->SetBranchAddress("trk_trunk_dEdx_y_v",	&trk_trunk_dEdx_y_v);

    // track deflections
    tree->SetBranchAddress("trk_avg_deflection_mean_v",		&trk_avg_deflection_mean_v);
    tree->SetBranchAddress("trk_avg_deflection_stdev_v",	&trk_avg_deflection_stdev_v);
    tree->SetBranchAddress("trk_avg_deflection_separation_mean_v",	&trk_avg_deflection_separation_mean_v);  

    // track end spacepoints
    tree->SetBranchAddress("trk_end_spacepoints_v",		&trk_end_spacepoints_v);
            
}

// Function to classify the event
void EventContainer::EventClassifier(Utility::FileTypeEnums type){

	// --- MC classification --
	if (type == Utility::kMC) {
		// identify cosmic / cosmic contaminated events
		// check fraction of hits that are not matched to neutrino
		if (nu_purity_from_pfp <= 0.5) {
			// low purity, classify as cosmic
			classification = Utility::kCosmic;
			return;
		}

		// check whether vertex is within fiducial volume
		bool isInFV = _utility.inFV(true_nu_vtx_sce_x, true_nu_vtx_sce_y, true_nu_vtx_sce_z);

		// Outside of FV
		if (!isInFV) {
			// classify as outFV
			classification = Utility::kOutFV;
			return;
		}
		// Inside of FV
		else {
			// Charged Current
			if (ccnc == 0) {
				// numu
				if (nu_pdg == 14 || nu_pdg == -14) {
					// check for pi-zero (background)
					if (npi0 > 0) {
						// classify as CC numu pizero
						classification = Utility::kCCNumupizero;
						return;
					}
					else {
						// classify as CC numu other
						classification = Utility::kCCNumuOther;
						return;
					}
				}
				// nue
				if (nu_pdg == 12 || nu_pdg == -12) {
					// check for pi-zero
					if (npi0 > 0) {
						// classify as CC nue pizero
						classification = Utility::kCCNuepizero;
						return;
					}
					// single pion (signal)
					else if (npion == 1) {
						// check number of protons
						if (nproton >= 1) {
							// classify as CC nue 1pi Np
							classification = Utility::kCCNue1piNp;
							return;	
						}
						else {
							// classify as CC nue 1pi 0p
							classification = Utility::kCCNue1pi0p;
							return;	
						}
						
					}
					// multi pion
					else if (npion > 1) {
						// classify as CC nue Npi
						classification = Utility::kCCNueNpi;
						return;
					}
					// single proton, and no pions
					else if (nproton == 1) {
						// classify as CC nue 1p
						classification = Utility::kCCNue1p;
						return;
					}
					// single proton, and no pions
					else if (nproton > 1) {
						// classify as CC nue Np
						classification = Utility::kCCNueNp;
						return;
					}
					else {
						// classify as CC nue other
						classification = Utility::kCCNueOther;
						return;
					}
				}
			}
			// Neutral Current
			else {
				// check for pi-zero (background)
				if (npi0 > 0) {
					// classify as NC pizero
					classification = Utility::kNCpizero; 
					return;
				}
				else {
					classification = Utility::kNCOther;
					return;
				}
			}
		}
	}
	// Beam Off Classification
	else if (type == Utility::kEXT) {
		classification = Utility::kBeamOff;
		return;
	}
	// Dirt
	else if (type == Utility::kDirt) {
		classification = Utility::kOutOfCryo;
		return;
	}

	// Catch any events without classification
	// Shouldn't be any of these! Will cause issues.
	classification = Utility::kUnknown;
	std::cout << "Warning: Unknown Event" << std::endl;
	return;
}

// Function to get event classification
Utility::ClassificationEnums EventContainer::getEventClassification(Utility::FileTypeEnums type) {
	EventClassifier(type);
	return classification;
}

// apply reconstruction failure recovery algorithms
void EventContainer::applyEventRecoveryAlgorithms(Utility::FileTypeEnums type) {

	// mode #1: shower split into two or more showers
	failureRecoverySplitShowers(); 

	// mode #2: spurious leading track
	failureRecoverySpuriousTrack();

	// mode #3: shower split into subleading track + shower [not useful currently]
	//failureRecoverySplitTrackShower();

	// mode #4: second shower is proton [not useful currently]
	//failureRecoverySecondShowerProton();


}

// Failure mode #1: split showers
void EventContainer::failureRecoverySplitShowers() {
	
	// identify events with failure
	if (n_tracks_contained > 0 && n_showers_contained > 1 && shr_score <= 0.1 && shrsubclusters >= 4 && shr12_p1_dstart < 20 && tk1sh2_distance > 60 && tk1sh2_distance != 9999) {
		
		hasSplitPrimaryShower = true;

		// update event ntuple variables
		n_showers_contained--;
		shrsubclusters += shr2subclusters;
		if (shr1shr2moliereavg > 0) shrmoliereavg = shr1shr2moliereavg;

	}
}

// Failure mode #2: spurious leading track
void EventContainer::failureRecoverySpuriousTrack() { 

	// identify events with failure
	if (n_tracks_contained > 1 && trk_distance > 30) {

		hasSpuriousLeadingTrack = true;

		// update event ntuple variables
		n_tracks_contained--;
		hits_ratio = (float)shr_hits_tot / ((float)shr_hits_tot + (float)trk_hits_tot - (float)trk_hits_max);
		tksh_angle = tk2sh1_angle;
	}

}

// Failure mode #3: shower split into subleading track + shower
void EventContainer::failureRecoverySplitTrackShower() {

	// identify events with failure
	if (n_tracks_contained > 1 && tk2sh1_angle < 10  && tk1tk2_distance < tksh_distance && shr_score <= 0.1) {

		hasSplitTrackShower = true;

		// update event ntuple variables
		n_tracks_contained--;
		tksh_distance = tk1tk2_distance;
		tksh_angle = tk1tk2_angle;
		hits_ratio = ((float)shr_hits_tot + (float)trk_hits_2nd) / ((float)shr_hits_tot + (float)trk_hits_tot);
		shrsubclusters0 += trk2subclusters0;
		shrsubclusters1 += trk2subclusters1;
		shrsubclusters2 += trk2subclusters2;
		if (shr1trk2moliereavg > 0) shrmoliereavg = shr1trk2moliereavg;

		// dE/dx
		shr_tkfit_nhits_U = trk2_tkfit_nhits_u;
		shr_tkfit_nhits_V = trk2_tkfit_nhits_v;
		shr_tkfit_nhits_Y = trk2_tkfit_nhits_y;
		shr_tkfit_gap10_nhits_U = trk2_tkfit_nhits_u;
		shr_tkfit_gap10_nhits_V = trk2_tkfit_nhits_v;
		shr_tkfit_gap10_nhits_Y = trk2_tkfit_nhits_y;		// how do I include gap?! make the same for testing
		shr_tkfit_dedx_U = trk2_tkfit_dedx_u;
		shr_tkfit_dedx_V = trk2_tkfit_dedx_v;
		shr_tkfit_dedx_Y = trk2_tkfit_dedx_y;
		shr_tkfit_gap10_dedx_U = trk2_tkfit_dedx_u;
		shr_tkfit_gap10_dedx_V = trk2_tkfit_dedx_v;
		shr_tkfit_gap10_dedx_Y = trk2_tkfit_dedx_y;

	}


}

// Failure mode #4: second shower is proton
void EventContainer::failureRecoverySecondShowerProton() { 

	// indentify events with failure
	if (n_showers_contained > 1 && tk1sh2_distance < 6.0 && shr2subclusters <= 4 && shr2pid < 0) {
		
		hasSecondShowerProton = true;

		// update varaibles
		n_tracks_contained++;
		n_showers_contained--;
	}
}


// Function to populate derived variables
void EventContainer::populateDerivedVariables(Utility::FileTypeEnums type){

	// fraction of hits associated with tracks or showers
	associated_hits_fraction = ((float)trk_hits_y_tot + (float)shr_hits_y_tot) / (float)total_hits_y;
	
	// number of showers above threshold
	n_showers_alt = all_shr_energies->size();
	n_showers_above_threshold = 0;
	for (unsigned int i = 0; i < all_shr_energies->size(); i++) {
		if (all_shr_energies->at(i) > 0.07) n_showers_above_threshold++; // 70 MeV, michels
	}

	// Shower dE/dx
	GetdEdxMax(false);	// standard
	GetdEdxMax(true); 	// with 10mm gap from start
 
	// Primary track information
	// if information primary track present -- vectors are all the same size by construction
	if (trk_id < trk_sce_start_x_v->size() && trk_id != 0) {

		trk_llr_pid_score = trk_llr_pid_score_v->at(trk_id-1); 	// LLR PID Score
		trk_daughters = pfp_trk_daughters_v->at(trk_id-1); 		// Track daughters
		trk_start_x = trk_start_x_v->at(trk_id-1);				// Track start, without SCE to allow comparison with shower start
		trk_start_y = trk_start_y_v->at(trk_id-1);				// Track start, without SCE to allow comparison with shower start
		trk_start_z = trk_start_z_v->at(trk_id-1);				// Track start, without SCE to allow comparison with shower start
		trk_sce_end_x = trk_sce_end_x_v->at(trk_id-1); 			// Track end
        trk_sce_end_y = trk_sce_end_y_v->at(trk_id-1); 			// Track end
        trk_sce_end_z = trk_sce_end_z_v->at(trk_id-1); 			// Track end
        trk_dir_x = trk_dir_x_v->at(trk_id-1);
        trk_dir_y = trk_dir_y_v->at(trk_id-1);  	
        trk_dir_z = trk_dir_z_v->at(trk_id-1);

		if (type == Utility::kMC) {
			trk_avg_deflection_mean = trk_avg_deflection_mean_v->at(trk_id-1)*180/3.1415;			// wiggliness, mean
			trk_avg_deflection_stdev = trk_avg_deflection_stdev_v->at(trk_id-1)*180/3.1415;			// wiggliness, stdev
			trk_avg_deflection_separation_mean = trk_avg_deflection_separation_mean_v->at(trk_id-1); // wiggliness, spacepoint separations
			trk_end_spacepoints = trk_end_spacepoints_v->at(trk_id-1); // daughter spacepoints
		}
		else {
			trk_avg_deflection_mean = 9999;
			trk_avg_deflection_stdev = 9999;
			trk_avg_deflection_separation_mean = 9999;
			trk_end_spacepoints = 9999;
		}
	}
	else {
		trk_llr_pid_score = 9999;
		trk_daughters = 9999;
		trk_avg_deflection_mean = 9999;
		trk_avg_deflection_stdev = 9999;
		trk_avg_deflection_separation_mean = 9999;
		trk_start_x = 9999;
		trk_start_y = 9999;
		trk_start_z = 9999;
		trk_sce_end_x = 9999;
		trk_sce_end_y = 9999;
		trk_sce_end_z = 9999;
		trk_end_spacepoints = 9999;
		trk_dir_x = 9999;
		trk_dir_y = 9999;
		trk_dir_z = 9999;
	}

	// Secondary track information
	if (trk2_id < trk_sce_start_x_v->size() && trk2_id != 0) {

		trk2_bragg_p = trk_bragg_p_v->at(trk2_id-1); 				// Bragg Proton
		trk2_bragg_mu = trk_bragg_mu_v->at(trk2_id-1); 				// Bragg Muon
		trk2_bragg_mip = trk_bragg_mip_v->at(trk2_id-1); 			// Bragg MIP
		trk2_llr_pid_score = trk_llr_pid_score_v->at(trk2_id-1); 	// LLR PID Score
		trk2_len = trk_len_v->at(trk2_id-1); 						// Track length
		trk2_score = trk_score_v->at(trk2_id-1); 					// Track score
		trk2_distance = trk_distance_v->at(trk2_id-1);				// Track distance
		trk2_daughters = pfp_trk_daughters_v->at(trk2_id-1); 		// Track daughters
		trk2_start_x = trk_start_x_v->at(trk2_id-1);				// Track start, without SCE to allow comparison with shower start
		trk2_start_y = trk_start_y_v->at(trk2_id-1);				// Track start, without SCE to allow comparison with shower start
		trk2_start_z = trk_start_z_v->at(trk2_id-1);				// Track start, without SCE to allow comparison with shower start
		trk2_sce_end_x = trk_sce_end_x_v->at(trk2_id-1); 			// Track end
        trk2_sce_end_y = trk_sce_end_y_v->at(trk2_id-1); 			// Track end
        trk2_sce_end_z = trk_sce_end_z_v->at(trk2_id-1); 			// Track end
        trk2_dir_x = trk_dir_x_v->at(trk2_id-1);
        trk2_dir_y = trk_dir_y_v->at(trk2_id-1);  	
        trk2_dir_z = trk_dir_z_v->at(trk2_id-1);
        trk2_tkfit_dedx_u = shr_tkfit_dedx_u_v->at(trk2_id-1);
        trk2_tkfit_dedx_v = shr_tkfit_dedx_v_v->at(trk2_id-1); 
        trk2_tkfit_dedx_y = shr_tkfit_dedx_y_v->at(trk2_id-1);
        trk2_tkfit_nhits_u = shr_tkfit_dedx_nhits_u_v->at(trk2_id-1);
        trk2_tkfit_nhits_v = shr_tkfit_dedx_nhits_v_v->at(trk2_id-1);
        trk2_tkfit_nhits_y = shr_tkfit_dedx_nhits_y_v->at(trk2_id-1);
        trk2subclusters0 = pfpplanesubclusters_U_v->at(trk2_id-1);
        trk2subclusters1 = pfpplanesubclusters_V_v->at(trk2_id-1);
        trk2subclusters2 = pfpplanesubclusters_Y_v->at(trk2_id-1);

		if (type == Utility::kMC) {
			trk2_bragg_pion = trk_bragg_pion_v->at(trk2_id-1); 									// Bragg Pion
			trk2_avg_deflection_mean = trk_avg_deflection_mean_v->at(trk2_id-1)*180/3.1415;		// wiggliness, mean
			trk2_avg_deflection_stdev = trk_avg_deflection_stdev_v->at(trk2_id-1)*180/3.1415;	// wiggliness, stdev
			trk2_end_spacepoints = trk_end_spacepoints_v->at(trk2_id-1); // daughter spacepoints
			trk2_bkt_pdg = backtracked_pdg_v->at(trk2_id-1);			// Backtracked PDG
		}
		else {
			trk2_bragg_pion = 9999;
			trk2_avg_deflection_mean = 9999;
			trk2_avg_deflection_stdev = 9999;
			trk2_bkt_pdg = 9999;
			trk2_end_spacepoints = 9999;
		}
	}
	else {
		trk2_len = 0;
		trk2_score = 9999;
		trk2_distance =9999;
		trk2_bragg_p = 9999;
		trk2_bragg_mu = 9999;
		trk2_bragg_pion = 9999;
		trk2_bragg_mip = 9999;
		trk2_llr_pid_score = 9999;
		trk2_daughters = 9999;
		trk2_avg_deflection_mean = 9999;
		trk2_avg_deflection_stdev = 9999; 
		trk2_bkt_pdg = 9999;
		trk2_start_x = 9999;
		trk2_start_y = 9999;
		trk2_start_z = 9999;
		trk2_sce_end_x = 9999;
		trk2_sce_end_y = 9999;
		trk2_sce_end_z = 9999;
		trk2_end_spacepoints = 9999;
		trk2_dir_x = 9999;
		trk2_dir_y = 9999;
		trk2_dir_z = 9999;
		trk2_tkfit_dedx_u = 9999;
		trk2_tkfit_dedx_v = 9999;
		trk2_tkfit_dedx_y = 9999;
		trk2_tkfit_nhits_u = 0;
		trk2_tkfit_nhits_v = 0;
		trk2_tkfit_nhits_y = 0;
		trk2subclusters0 = 9999;
		trk2subclusters1 = 9999;
		trk2subclusters2 = 9999;
	}

	// tertiary track information
	if (type == Utility::kMC && trk3_id < trk_sce_start_x_v->size() && trk3_id != 0) {

		trk3_bragg_p = trk_bragg_p_v->at(trk3_id-1); 				// Bragg Proton
		trk3_bragg_mu = trk_bragg_mu_v->at(trk3_id-1); 				// Bragg Muon
		trk3_bragg_mip = trk_bragg_mip_v->at(trk3_id-1); 			// Bragg MIP
		trk3_llr_pid_score = trk_llr_pid_score_v->at(trk3_id-1); 	// LLR PID Score
		trk3_len = trk_len_v->at(trk3_id-1); 						// Track length
		trk3_score = trk_score_v->at(trk3_id-1); 					// Track score
		trk3_distance = trk_distance_v->at(trk3_id-1);				// Track distance
		trk3_daughters = pfp_trk_daughters_v->at(trk3_id-1); 		// Track daughters
		trk3_sce_end_x = trk_sce_end_x_v->at(trk3_id-1); 			// Track end
        trk3_sce_end_y = trk_sce_end_y_v->at(trk3_id-1); 			// Track end
        trk3_sce_end_z = trk_sce_end_z_v->at(trk3_id-1); 			// Track end

		trk3_bragg_pion = trk_bragg_pion_v->at(trk3_id-1); 									// Bragg Pion
		trk3_avg_deflection_mean = trk_avg_deflection_mean_v->at(trk3_id-1)*180/3.1415;		// wiggliness, mean
		trk3_avg_deflection_stdev = trk_avg_deflection_stdev_v->at(trk3_id-1)*180/3.1415;	// wiggliness, stdev
		trk3_end_spacepoints = trk_end_spacepoints_v->at(trk3_id-1); // daughter spacepoints
		trk3_bkt_pdg = backtracked_pdg_v->at(trk3_id-1);			// Backtracked PDG
	}
	else {
		trk3_len = 0;
		trk3_score = 9999;
		trk3_distance =9999;
		trk3_bragg_p = 9999;
		trk3_bragg_mu = 9999;
		trk3_bragg_pion = 9999;
		trk3_bragg_mip = 9999;
		trk3_llr_pid_score = 9999;
		trk3_daughters = 9999;
		trk3_avg_deflection_mean = 9999;
		trk3_avg_deflection_stdev = 9999; 
		trk3_bkt_pdg = 9999;
		trk3_sce_end_x = 9999;
		trk3_sce_end_y = 9999;
		trk3_sce_end_z = 9999;
		trk3_end_spacepoints = 9999;
	}


	// track PID variables, best plane 
	// primary track
	if (type == Utility::kMC && trk_id < trk_sce_start_x_v->size() && trk_id != 0) {
		trk_dEdx_trunk_max = GetTrackTrunkdEdxBestPlane(trk_id);
		trk_bragg_pion_max = GetTrackBraggPionBestPlane(trk_id);
		trk_bragg_mip_max = GetTrackBraggMIPBestPlane(trk_id);
	}
	else {
		trk_dEdx_trunk_max = 9999;
		trk_bragg_pion_max = 9999;
		trk_bragg_mip_max = 9999;
	}
	// secondary track
	if (type == Utility::kMC && trk2_id < trk_sce_start_x_v->size() && trk2_id != 0) {
		trk2_dEdx_trunk_max = GetTrackTrunkdEdxBestPlane(trk2_id);
		trk2_bragg_pion_max = GetTrackBraggPionBestPlane(trk2_id);
		trk2_bragg_mip_max = GetTrackBraggMIPBestPlane(trk2_id);
	}
	else {
		trk2_dEdx_trunk_max = 9999;
		trk2_bragg_pion_max = 9999;
		trk2_bragg_mip_max = 9999;
	}
	// tertiary track
	if (type == Utility::kMC && trk3_id < trk_sce_start_x_v->size() && trk3_id != 0) {
		trk3_dEdx_trunk_max = GetTrackTrunkdEdxBestPlane(trk3_id);
		trk3_bragg_pion_max = GetTrackBraggPionBestPlane(trk3_id);
		trk3_bragg_mip_max = GetTrackBraggMIPBestPlane(trk3_id);
	}
	else {
		trk3_dEdx_trunk_max = 9999;
		trk3_bragg_pion_max = 9999;
		trk3_bragg_mip_max = 9999;
	}

	// Primary shower energy fraction
    shr_energyFraction = shr_energy_cali / shr_energy_tot_cali;

    // primary shower subclusters
    shrsubclusters = shrsubclusters0 + shrsubclusters1 + shrsubclusters2;

    // Primary shower information
    if (shr_id < shr_energy_y_v->size() && shr_id != 0) {
    	shr_start_x = shr_start_x_v->at(shr_id-1);
    	shr_start_y = shr_start_y_v->at(shr_id-1);
    	shr_start_z = shr_start_z_v->at(shr_id-1);
    	shr_dir_x = shr_px_v->at(shr_id-1);
    	shr_dir_y = shr_py_v->at(shr_id-1);
    	shr_dir_z = shr_pz_v->at(shr_id-1);	
    } 
    else {
    	shr_start_x = 9999;
    	shr_start_y = 9999;
    	shr_start_z = 9999;
    	shr_dir_x = 9999;
    	shr_dir_y = 9999;
    	shr_dir_z = 9999;
    }

    // Secondary shower information
    if (shr2_id < shr_energy_y_v->size() && shr2_id != 0) {
    	shr2_energy = shr_energy_y_v->at(shr2_id-1)/1000;	// shower energy, in GeV
    	shr2_score = trk_score_v->at(shr2_id-1); 			// note track-shower score, full vector contains all PFPs not just "track-like" ones
    	shr2_start_x = shr_start_x_v->at(shr2_id-1);
    	shr2_start_y = shr_start_y_v->at(shr2_id-1);
    	shr2_start_z = shr_start_z_v->at(shr2_id-1);
    	shr2_dir_x = shr_px_v->at(shr2_id-1);
    	shr2_dir_y = shr_py_v->at(shr2_id-1);
    	shr2_dir_z = shr_pz_v->at(shr2_id-1);
    	shr2_distance = shr_dist_v->at(shr2_id-1);
    	shr2moliereavg = shr_moliere_avg_v->at(shr2_id-1); 	
    	shr2subclusters = pfpplanesubclusters_U_v->at(shr2_id-1) + pfpplanesubclusters_V_v->at(shr2_id-1) + pfpplanesubclusters_Y_v->at(shr2_id-1);
    	shr2pid = trk_llr_pid_score_v->at(shr2_id-1);
    } 
    else {
    	shr2_energy = 9999;
    	shr2_score = 9999;
    	shr2_dir_x = 9999;
    	shr2_dir_y = 9999;
    	shr2_dir_z = 9999;
    	shr2_start_x = 9999;
    	shr2_start_y = 9999;
    	shr2_start_z = 9999;
    	shr2_distance = 9999;
    	shr2moliereavg = 9999;
    	shr2subclusters = 9999;
    	shr2pid = 9999;
    }

    // convert tksh angle
    tksh_angle = std::acos(tksh_angle) * 180 / 3.14159;

    // Second shower opening angle
    if (n_showers > 1 && shr_dir_x != 9999 && shr2_start_x != 9999) {

    	TVector3 showerDir(shr_dir_x, shr_dir_y, shr_dir_z);
    	TVector3 shower12StartDist(shr2_start_x - shr_start_x, shr2_start_y - shr_start_y, shr2_start_z - shr_start_z);
    	shr12_p1_dstart = showerDir.Angle(shower12StartDist) * 180 / 3.14159;
	}
	else shr12_p1_dstart = 9999;

	// second shower distance from primary track
	if (n_showers_contained > 1 && n_tracks_contained > 0 && trk_start_x != 9999 & shr2_start_x != 9999) {
		tk1sh2_distance = std::sqrt( std::pow(shr2_start_x - trk_start_x, 2) + std::pow(shr2_start_y - trk_start_y, 2) + std::pow(shr2_start_z - trk_start_z, 2) );
	}
	else {
		tk1sh2_distance = 9999;
	}

	// distance between primary track and secondary track
	if (n_tracks_contained > 1 && trk_start_x != 9999 && trk2_start_x != 9999) {
		tk1tk2_distance = std::sqrt( std::pow(trk2_start_x - trk_start_x, 2) + std::pow(trk2_start_y - trk_start_y, 2) + std::pow(trk2_start_z - trk_start_z, 2) );
	}
	else {
		tk1tk2_distance = 9999;
	}

	// primary shower and second track opening angle
	if (n_tracks_contained > 1 && n_showers_contained > 0 && shr_dir_x != 9999 && trk2_dir_x != 9999) {

		TVector3 showerDir(shr_dir_x, shr_dir_y, shr_dir_z);
		TVector3 trk2Dir(trk2_dir_x, trk2_dir_y, trk2_dir_z);
		tk2sh1_angle = trk2Dir.Angle(showerDir) * 180 / 3.14159;
	}
	
	// primary track and second track opening angle
	if (n_tracks_contained > 1 && trk_dir_x != 9999 && trk2_dir_x != 9999) {

		TVector3 trkDir(trk_dir_x, trk_dir_x, trk_dir_x);
		TVector3 trk2Dir(trk2_dir_x, trk2_dir_y, trk2_dir_z);
		tk1tk2_angle = trkDir.Angle(trk2Dir) * 180 / 3.14159;
	}
	

    // Second shower cluster opening angle
    GetSecondShowerClusterAngleDiff();	

    // Shower track fit
    if (shr_id < trk_sce_start_x_v->size() && shr_id != 0) {
    	shr_trk_sce_start_x = trk_sce_start_x_v->at(shr_id-1);
    	shr_trk_sce_start_y = trk_sce_start_y_v->at(shr_id-1);
    	shr_trk_sce_start_z = trk_sce_start_z_v->at(shr_id-1);
    	shr_trk_sce_end_x = trk_sce_end_x_v->at(shr_id-1);
    	shr_trk_sce_end_y = trk_sce_end_y_v->at(shr_id-1);
    	shr_trk_sce_end_z = trk_sce_end_z_v->at(shr_id-1);

    	shr_trk_len = std::sqrt( std::pow(shr_trk_sce_end_x - shr_trk_sce_start_x, 2) + std::pow(shr_trk_sce_end_y - shr_trk_sce_start_y, 2) + std::pow(shr_trk_sce_end_z - shr_trk_sce_start_z, 2) );
    }
    else {
    	shr_trk_sce_start_x = 9999;
    	shr_trk_sce_start_y = 9999;
    	shr_trk_sce_start_z = 9999;
    	shr_trk_sce_end_x = 9999;
    	shr_trk_sce_end_y = 9999;
    	shr_trk_sce_end_z = 9999;
    	shr_trk_len = 9999;
    }

    // initialise reconstruction failure condition variables
    hasSplitPrimaryShower = false;
    hasSpuriousLeadingTrack = false;
    hasSplitTrackShower = false;
    hasSecondShowerProton = false;

	// Initialise selection condition variables
	primaryTrackValid = false;
	secondaryTrackValid = false;

	primaryTrackPionlike = false;
	secondaryTrackPionlike = false;

    // neutral pion invariant mass difference
   	//if (n_showers > 1) neutralPionInvariantMassDifference = std::abs(pi0_mass_U - 134.9768);
   	//else neutralPionInvariantMassDifference = 999; 
}

// get shower dE/dx on plane with the most hits
void EventContainer::GetdEdxMax(bool includeGap = false) {

	float temp_shr_trkfit_dedx_max = -1;

    // We want to also use the dedx when it is defined properly. Sometimes, the plane can have hits but an undefined dedx
    // use the dedx where we get the max number of hits and the dedx > 0
    int temp_shr_hits_u_tot, temp_shr_hits_v_tot, temp_shr_hits_y_tot;    
	float temp_shr_tkfit_dedx_U, temp_shr_tkfit_dedx_V, temp_shr_tkfit_dedx_Y;

	// Case where gap is included
	if (includeGap) {
		temp_shr_hits_u_tot = shr_tkfit_gap10_nhits_U;
    	temp_shr_hits_v_tot = shr_tkfit_gap10_nhits_V;
    	temp_shr_hits_y_tot = shr_tkfit_gap10_nhits_Y;
		temp_shr_tkfit_dedx_U = shr_tkfit_gap10_dedx_U;
		temp_shr_tkfit_dedx_V = shr_tkfit_gap10_dedx_V;
		temp_shr_tkfit_dedx_Y = shr_tkfit_gap10_dedx_Y;
	}
	else {
		temp_shr_hits_u_tot = shr_tkfit_nhits_U;
    	temp_shr_hits_v_tot = shr_tkfit_nhits_V;
    	temp_shr_hits_y_tot = shr_tkfit_nhits_Y;
		temp_shr_tkfit_dedx_U = shr_tkfit_dedx_U;
		temp_shr_tkfit_dedx_V = shr_tkfit_dedx_V;
		temp_shr_tkfit_dedx_Y = shr_tkfit_dedx_Y;   
	}
	// If the dedx is undefined, set the hits to zero
    if (temp_shr_tkfit_dedx_U <= 0) temp_shr_hits_u_tot = 0;
    if (temp_shr_tkfit_dedx_V <= 0) temp_shr_hits_v_tot = 0;
    if (temp_shr_tkfit_dedx_Y <= 0) temp_shr_hits_y_tot = 0;

    // Collection plane is the largest
    if (temp_shr_hits_y_tot > temp_shr_hits_u_tot && temp_shr_hits_y_tot > temp_shr_hits_v_tot ){
        temp_shr_trkfit_dedx_max = temp_shr_tkfit_dedx_Y;
    }
    // V Plane is the largest
    else if (temp_shr_hits_v_tot > temp_shr_hits_u_tot && temp_shr_hits_v_tot > temp_shr_hits_y_tot) {
        temp_shr_trkfit_dedx_max = temp_shr_tkfit_dedx_V;        
    }
    // U Plane is the largest
    else if (temp_shr_hits_u_tot > temp_shr_hits_v_tot && temp_shr_hits_u_tot > temp_shr_hits_y_tot){
        temp_shr_trkfit_dedx_max = temp_shr_tkfit_dedx_U;
    }
    // One plane was equal, so need to prioritise planes in preference of y, v, u
    else {

        // If y == any other plane, then y wins
        if (temp_shr_hits_y_tot == temp_shr_hits_u_tot || temp_shr_hits_y_tot == temp_shr_hits_v_tot ){
            temp_shr_trkfit_dedx_max = temp_shr_tkfit_dedx_Y;           
        }
        // U == V, ALL Y cases have been used up, so default to v
        else if (temp_shr_hits_u_tot == temp_shr_hits_v_tot ){
            temp_shr_trkfit_dedx_max = temp_shr_tkfit_dedx_V;            
        }
        else {
            temp_shr_trkfit_dedx_max = temp_shr_tkfit_dedx_U;
        }
    }

    if (temp_shr_trkfit_dedx_max == -1) {
        std::cout << shr_tkfit_dedx_U << " " << shr_tkfit_dedx_V << " " << shr_tkfit_dedx_Y<< std::endl;
        std::cout << "Error [Selection.h]: Edge case of dEdx comparisons." << std::endl;
    }

    // set variable
    if (includeGap) shr_trkfit_gap10_dedx_max = temp_shr_trkfit_dedx_max;
    else shr_trkfit_dedx_max = temp_shr_trkfit_dedx_max;

}

// get second shower opening angle, if present
void EventContainer::GetSecondShowerClusterAngleDiff() {
	
	// U plane, if defined
	if (secondshower_U_nhit > 0 && shrclusdir0 > 0) {

		// check each combination to determine correct direction - to account for cases where showers are on different sides of the wire direction
		float anglediff_case_1 = std::abs(secondshower_U_dir - shrclusdir0);
		float anglediff_case_2 = std::abs((360 - secondshower_U_dir) + shrclusdir0);
		float anglediff_case_3 = std::abs(secondshower_U_dir + (360 - shrclusdir0));

		// set as minimum of the three cases
		if (anglediff_case_1 <= anglediff_case_2 && anglediff_case_1 <= anglediff_case_3) secondshower_U_anglediff = anglediff_case_1;
		else if (anglediff_case_2 <= anglediff_case_1 && anglediff_case_2 <= anglediff_case_3) secondshower_U_anglediff = anglediff_case_2;
		else if (anglediff_case_3 <= anglediff_case_1 && anglediff_case_3 <= anglediff_case_2) secondshower_U_anglediff = anglediff_case_3; 
	}
	else secondshower_U_anglediff = 9999;

	// V plane, if defined
	if (secondshower_V_nhit > 0 && shrclusdir1 > 0) {

		// check each combination to determine correct direction - to account for cases where showers are on different sides of the wire direction
		float anglediff_case_1 = std::abs(secondshower_V_dir - shrclusdir1);
		float anglediff_case_2 = std::abs((360 - secondshower_V_dir) + shrclusdir1);
		float anglediff_case_3 = std::abs(secondshower_V_dir + (360 - shrclusdir1));

		// set as minimum of the three cases
		if (anglediff_case_1 <= anglediff_case_2 && anglediff_case_1 <= anglediff_case_3) secondshower_V_anglediff = anglediff_case_1;
		else if (anglediff_case_2 <= anglediff_case_1 && anglediff_case_2 <= anglediff_case_3) secondshower_V_anglediff = anglediff_case_2;
		else if (anglediff_case_3 <= anglediff_case_1 && anglediff_case_3 <= anglediff_case_2) secondshower_V_anglediff = anglediff_case_3; 
	}
	else secondshower_V_anglediff = 9999;

	// Y plane, if defined
	if (secondshower_Y_nhit > 0 && shrclusdir2 > 0) {

		// check each combination to determine correct direction - to account for cases where showers are on different sides of the wire direction
		float anglediff_case_1 = std::abs(secondshower_Y_dir - shrclusdir2);
		float anglediff_case_2 = std::abs((360 - secondshower_Y_dir) + shrclusdir2);
		float anglediff_case_3 = std::abs(secondshower_Y_dir + (360 - shrclusdir2));

		// set as minimum of the three cases
		//secondshower_Y_anglediff = anglediff_case_1;
		if (anglediff_case_1 <= anglediff_case_2 && anglediff_case_1 <= anglediff_case_3) secondshower_Y_anglediff = anglediff_case_1;
		else if (anglediff_case_2 <= anglediff_case_1 && anglediff_case_2 <= anglediff_case_3) secondshower_Y_anglediff = anglediff_case_2;
		else if (anglediff_case_3 <= anglediff_case_1 && anglediff_case_3 <= anglediff_case_2) secondshower_Y_anglediff = anglediff_case_3; 
	}
	else secondshower_Y_anglediff = 9999;
}

void EventContainer::isAlongWire(unsigned int trackID, bool &isAlongWire_u, bool &isAlongWire_v, bool &isAlongWire_y) {
	float tolerance = 20; 	// degrees

	// calculate theta_yz
	float delta_y = trk_sce_end_y_v->at(trackID-1) - trk_sce_start_y_v->at(trackID-1);
	float delta_z = trk_sce_end_z_v->at(trackID-1) - trk_sce_start_z_v->at(trackID-1);
	float theta_yz = std::atan2(delta_z, delta_y) * 180 / 3.1415;

	// check whether track along wire directions
	if ((theta_yz > 60 - tolerance && theta_yz < 60 + tolerance) || (theta_yz > -120 - tolerance && theta_yz < -120 + tolerance)) isAlongWire_u = true; // +60
	if ((theta_yz > 120 - tolerance && theta_yz < 120 + tolerance) || (theta_yz > -60 - tolerance && theta_yz < -60 + tolerance)) isAlongWire_v = true; // - 60	
	if (std::abs(theta_yz) < tolerance || std::abs(theta_yz) > 180 - tolerance) isAlongWire_y = true; // vertical
}

// get track trunk dE/dx - use collection plane when available, unless track along wire direction
float EventContainer::GetTrackTrunkdEdxBestPlane(unsigned int trackID) {

	// check whether track is along wire
	bool isAlongWire_u = false; bool isAlongWire_v = false; bool isAlongWire_y = false;
	isAlongWire(trackID, isAlongWire_u, isAlongWire_v, isAlongWire_y);

	// get number of hits on each plane
	int Nhits_Y = trk_nhits_y_v->at(trackID-1);
	int Nhits_U = trk_nhits_u_v->at(trackID-1);
	int Nhits_V = trk_nhits_v_v->at(trackID-1);
	 
	// prefer collection plane where available, otherwise take average of u,v planes if available
	// track trunk dE/dx
	if (trk_trunk_dEdx_y_v->at(trackID-1) != 9999 && !isAlongWire_y && Nhits_Y > 0) {
		return trk_trunk_dEdx_y_v->at(trackID-1);
	}
	else if (trk_trunk_dEdx_u_v->at(trackID-1) != 9999 && !isAlongWire_u && trk_trunk_dEdx_v_v->at(trackID-1) != 9999 && !isAlongWire_v && Nhits_U + Nhits_V > 0) {
		return (Nhits_U * trk_trunk_dEdx_u_v->at(trackID-1) + Nhits_V * trk_trunk_dEdx_v_v->at(trackID-1)) / (Nhits_U + Nhits_V);
	}
	else if (trk_trunk_dEdx_v_v->at(trackID-1) != 9999 && !isAlongWire_v && Nhits_V > 0) {
		return trk_trunk_dEdx_v_v->at(trackID-1);
	} 
	else if (trk_trunk_dEdx_u_v->at(trackID-1) != 9999 && !isAlongWire_u && Nhits_U > 0) {
		return trk_trunk_dEdx_u_v->at(trackID-1);
	}
	else return 9999;
}

// bragg peak pion
float EventContainer::GetTrackBraggPionBestPlane(unsigned int trackID) {

	// check whether track is along wire
	bool isAlongWire_u = false; bool isAlongWire_v = false; bool isAlongWire_y = false;
	isAlongWire(trackID, isAlongWire_u, isAlongWire_v, isAlongWire_y);

	// get number of hits on each plane
	int Nhits_Y = trk_nhits_y_v->at(trackID-1);
	int Nhits_U = trk_nhits_u_v->at(trackID-1);
	int Nhits_V = trk_nhits_v_v->at(trackID-1);

	// track bragg peak pion
	if (trk_bragg_pion_v->at(trackID-1) != 9999 && !isAlongWire_y && Nhits_Y > 0) {
		return trk_bragg_pion_v->at(trackID-1);
	}
	else if (trk_bragg_pion_u_v->at(trackID-1) != 9999 && !isAlongWire_u && trk_bragg_pion_v_v->at(trackID-1) != 9999 && !isAlongWire_v && Nhits_U + Nhits_V > 0) {
		return (Nhits_U * trk_bragg_pion_u_v->at(trackID-1) + Nhits_V * trk_bragg_pion_v_v->at(trackID-1)) / (Nhits_U + Nhits_V);
	}
	else if (trk_bragg_pion_v_v->at(trackID-1) != 9999 && !isAlongWire_v && Nhits_V > 0) {
		return trk_bragg_pion_v_v->at(trackID-1);
	} 
	else if (trk_bragg_pion_u_v->at(trackID-1) != 9999 && !isAlongWire_u && Nhits_U > 0) {
		return trk_bragg_pion_u_v->at(trackID-1);
	}
	else return 9999;
}

// bragg peak mip
float EventContainer::GetTrackBraggMIPBestPlane(unsigned int trackID) {

	// check whether track is along wire
	bool isAlongWire_u = false; bool isAlongWire_v = false; bool isAlongWire_y = false;
	isAlongWire(trackID, isAlongWire_u, isAlongWire_v, isAlongWire_y);

	// get number of hits on each plane
	int Nhits_Y = trk_nhits_y_v->at(trackID-1);
	int Nhits_U = trk_nhits_u_v->at(trackID-1);
	int Nhits_V = trk_nhits_v_v->at(trackID-1);

	// track bragg peak pion
	if (trk_bragg_mip_v->at(trackID-1) != 9999 && !isAlongWire_y && Nhits_Y > 0) {
		return trk_bragg_mip_v->at(trackID-1);
	}
	else if (trk_bragg_mip_u_v->at(trackID-1) != 9999 && !isAlongWire_u && trk_bragg_mip_v_v->at(trackID-1) != 9999 && !isAlongWire_v && Nhits_U + Nhits_V > 0) {
		return (Nhits_U * trk_bragg_mip_u_v->at(trackID-1) + Nhits_V * trk_bragg_mip_v_v->at(trackID-1)) / (Nhits_U + Nhits_V);
	}
	else if (trk_bragg_mip_v_v->at(trackID-1) != 9999 && !isAlongWire_v && Nhits_V > 0) {
		return trk_bragg_mip_v_v->at(trackID-1);
	} 
	else if (trk_bragg_mip_u_v->at(trackID-1) != 9999 && !isAlongWire_u && Nhits_U > 0) {
		return trk_bragg_mip_u_v->at(trackID-1);
	}
	else return 9999;
}
