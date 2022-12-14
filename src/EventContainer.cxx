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
	tree->SetBranchAddress("nu_purity_from_pfp", &nu_purity_from_pfp);

	tree->SetBranchAddress("total_hits_y", &total_hits_y);
	tree->SetBranchAddress("shr_hits_y_tot", &shr_hits_y_tot);
	tree->SetBranchAddress("trk_hits_y_tot", &trk_hits_y_tot);
	tree->SetBranchAddress("extra_energy_y", &extra_energy_y);

	tree->SetBranchAddress("reco_nu_vtx_sce_x", &reco_nu_vtx_sce_x);
    tree->SetBranchAddress("reco_nu_vtx_sce_y", &reco_nu_vtx_sce_y);
    tree->SetBranchAddress("reco_nu_vtx_sce_z", &reco_nu_vtx_sce_z);

    tree->SetBranchAddress("contained_fraction", &contained_fraction);

    tree->SetBranchAddress("topological_score", &topological_score);
    tree->SetBranchAddress("CosmicIPAll3D", &CosmicIPAll3D);

    tree->SetBranchAddress("shr_id", &shr_id);
    tree->SetBranchAddress("shr2_id", &shr2_id);
    tree->SetBranchAddress("shr_distance", &shr_distance);
    tree->SetBranchAddress("shr_score", &shr_score);
    tree->SetBranchAddress("shr_energy_cali", &shr_energy_cali);
    tree->SetBranchAddress("shr_energy_tot_cali", &shr_energy_tot_cali);    
    tree->SetBranchAddress("hits_ratio", &hits_ratio);
    tree->SetBranchAddress("shrmoliereavg", &shrmoliereavg);

    tree->SetBranchAddress("shr_llrpid_dedx", &shr_llrpid_dedx);
    
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

    tree->SetBranchAddress("trk_score_v",             &trk_score_v);
    tree->SetBranchAddress("trk_sce_start_x_v",        &trk_sce_start_x_v);
    tree->SetBranchAddress("trk_sce_start_y_v",        &trk_sce_start_y_v);
    tree->SetBranchAddress("trk_sce_start_z_v",        &trk_sce_start_z_v);
    tree->SetBranchAddress("trk_sce_end_x_v",          &trk_sce_end_x_v);
    tree->SetBranchAddress("trk_sce_end_y_v",          &trk_sce_end_y_v);
    tree->SetBranchAddress("trk_sce_end_z_v",          &trk_sce_end_z_v);
    tree->SetBranchAddress("trk_len_v",                &trk_len_v);
    tree->SetBranchAddress("trk_distance_v",           &trk_distance_v);

    tree->SetBranchAddress("trk_bragg_p_v", &trk_bragg_p_v);
    tree->SetBranchAddress("trk_bragg_mu_v", &trk_bragg_mu_v);
    tree->SetBranchAddress("trk_bragg_pion_v", &trk_bragg_pion_v);
    tree->SetBranchAddress("trk_bragg_mip_v", &trk_bragg_mip_v);
    tree->SetBranchAddress("trk_llr_pid_score_v", &trk_llr_pid_score_v);

    tree->SetBranchAddress("all_shr_energies",          &all_shr_energies);
    tree->SetBranchAddress("shr_energy_u_v",          &shr_energy_u_v);
    tree->SetBranchAddress("shr_energy_v_v",          &shr_energy_v_v);
    tree->SetBranchAddress("shr_energy_y_v",          &shr_energy_y_v);
    tree->SetBranchAddress("shr_px_v",          &shr_px_v);
    tree->SetBranchAddress("shr_py_v",          &shr_py_v);
    tree->SetBranchAddress("shr_pz_v",          &shr_pz_v);

    tree->SetBranchAddress("shr_start_x_v",     &shr_start_x_v);
    tree->SetBranchAddress("shr_start_y_v",     &shr_start_y_v);
    tree->SetBranchAddress("shr_start_z_v",     &shr_start_z_v);

    tree->SetBranchAddress("pfp_trk_daughters_v", &pfp_trk_daughters_v);
 	tree->SetBranchAddress("pfp_shr_daughters_v", &pfp_shr_daughters_v);    

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


// Function to populate derived variables
void EventContainer::populateDerivedVariables(Utility::FileTypeEnums type){

	// fraction of hits associated with tracks or showers
	associated_hits_fraction = ((float)trk_hits_y_tot + (float)shr_hits_y_tot) / (float)total_hits_y;
	
	// number of showers above threshold
	n_showers_alt = all_shr_energies->size();
	n_showers_above_threshold = 0;
	for (unsigned int i = 0; i < all_shr_energies->size(); i++) {
		if (all_shr_energies->at(i) > 0.05) n_showers_above_threshold++; // 50 MeV, michels
	}

	// Shower dE/dx
	GetdEdxMax(false);	// standard
	GetdEdxMax(true); 	// with 10mm gap from start

	// Primary track information
	// if information primary track present -- vectors are all the same size by construction
	if (trk_id < trk_sce_start_x_v->size() && trk_id != 0) {

		trk_llr_pid_score = trk_llr_pid_score_v->at(trk_id-1); 	// LLR PID Score
		trk_daughters = pfp_trk_daughters_v->at(trk_id-1); 		// Track daughters
		trk_sce_end_x = trk_sce_end_x_v->at(trk_id-1); 			// Track end
        trk_sce_end_y = trk_sce_end_y_v->at(trk_id-1); 			// Track end
        trk_sce_end_z = trk_sce_end_z_v->at(trk_id-1); 			// Track end

		if (type == Utility::kMC) {
			trk_avg_deflection_mean = trk_avg_deflection_mean_v->at(trk_id-1)*180/3.1415;			// wiggliness, mean
			trk_avg_deflection_stdev = trk_avg_deflection_stdev_v->at(trk_id-1)*180/3.1415;			// wiggliness, stdev
			trk_avg_deflection_separation_mean = trk_avg_deflection_separation_mean_v->at(trk_id-1); // wiggliness, spacepoint separations
			trk_end_spacepoints = trk_end_spacepoints_v->at(trk_id-1); // daughter spacepoints
		}
		else {
			trk_avg_deflection_mean = 9999;
			trk_avg_deflection_stdev = 9999;
			trk_end_spacepoints = 9999;
		}
	}
	else {
		trk_llr_pid_score = 9999;
		trk_daughters = 9999;
		trk_avg_deflection_mean = 9999;
		trk_avg_deflection_stdev = 9999;
		trk_sce_end_x = 9999;
		trk_sce_end_y = 9999;
		trk_sce_end_z = 9999;
		trk_end_spacepoints = 9999;
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
		trk2_sce_end_x = trk_sce_end_x_v->at(trk2_id-1); 			// Track end
        trk2_sce_end_y = trk_sce_end_y_v->at(trk2_id-1); 			// Track end
        trk2_sce_end_z = trk_sce_end_z_v->at(trk2_id-1); 			// Track end

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
		trk2_sce_end_x = 9999;
		trk2_sce_end_y = 9999;
		trk2_sce_end_z = 9999;
		trk2_end_spacepoints = 9999;
	}

	// track trunk dE/dx
	// primary track
	if (type == Utility::kMC && trk_id < trk_trunk_dEdx_y_v->size() && trk_id != 0) trk_dEdx_trunk_max = GetTrackTrunkdEdxMax(trk_id);
	else trk_dEdx_trunk_max = 9999;
	// secondary track
	if (type == Utility::kMC && trk2_id < trk_trunk_dEdx_y_v->size() && trk2_id != 0) trk2_dEdx_trunk_max = GetTrackTrunkdEdxMax(trk2_id);
	else trk2_dEdx_trunk_max = 9999;

	// Primary shower energy fraction
    shr_energyFraction = shr_energy_cali / shr_energy_tot_cali;

    // Secondary shower energy
    if (shr2_id < shr_energy_y_v->size() && shr2_id != 0) shr2_energy = shr_energy_y_v->at(shr2_id-1)/1000;	// shower energy, in GeV
    else shr2_energy = 9999;

    // Second shower cluster opening angle
    GetSecondShowerClusterAngleDiff();	
    
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

// get track trunk dE/dx on plane with the most hits; currently just using collection plane, other planes seem not useful -- maybe just for specific track directions??
float EventContainer::GetTrackTrunkdEdxMax(unsigned int trackID) {

	// get number of hits on each plane
	int Nhits_Y = trk_nhits_y_v->at(trackID-1);
	int Nhits_U = trk_nhits_u_v->at(trackID-1);
	int Nhits_V = trk_nhits_v_v->at(trackID-1);

	//if (trk_trunk_dEdx_y_v->at(trackID-1) == 9999) std::cout << Nhits_U << ", " <<  Nhits_V << ", " <<  Nhits_Y << std::endl;

	// prefer collection plane, where available
	//if (trk_trunk_dEdx_y_v->at(trackID-1) != 9999) {
		return trk_trunk_dEdx_y_v->at(trackID-1);
	//}
	// otherwise take largest of U and V planes, prefering V if equal
	//else if (Nhits_V >= Nhits_U && trk_trunk_dEdx_v_v->at(trackID-1) != 9999) return trk_trunk_dEdx_v_v->at(trackID-1); 
	//else if (Nhits_U > Nhits_V && trk_trunk_dEdx_u_v->at(trackID-1) != 9999) return trk_trunk_dEdx_u_v->at(trackID-1); 
	// if no planes available, return invalid
	//else return 9999;  
}