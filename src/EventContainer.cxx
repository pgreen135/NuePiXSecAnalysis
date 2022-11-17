#include "EventContainer.h"

#include <iostream>


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
	tree->SetBranchAddress("nu_purity_from_pfp", &nu_purity_from_pfp);

	tree->SetBranchAddress("reco_nu_vtx_sce_x", &reco_nu_vtx_sce_x);
    tree->SetBranchAddress("reco_nu_vtx_sce_y", &reco_nu_vtx_sce_y);
    tree->SetBranchAddress("reco_nu_vtx_sce_z", &reco_nu_vtx_sce_z);

    tree->SetBranchAddress("contained_fraction", &contained_fraction);

    tree->SetBranchAddress("topological_score", &topological_score);
    tree->SetBranchAddress("CosmicIPAll3D", &CosmicIPAll3D);

    tree->SetBranchAddress("shr_id", &shr_id);
    tree->SetBranchAddress("shr_distance", &shr_distance);
    tree->SetBranchAddress("shr_score", &shr_score);
    tree->SetBranchAddress("shr_energy_cali", &shr_energy_cali);
    tree->SetBranchAddress("shr_energy_tot_cali", &shr_energy_tot_cali);    
    tree->SetBranchAddress("hits_ratio", &hits_ratio);
    tree->SetBranchAddress("shrmoliereavg", &shrmoliereavg);

    tree->SetBranchAddress("shr_tkfit_dedx_Y", &shr_tkfit_dedx_Y);
    tree->SetBranchAddress("shr_tkfit_dedx_V", &shr_tkfit_dedx_V);
    tree->SetBranchAddress("shr_tkfit_dedx_U", &shr_tkfit_dedx_U);

    tree->SetBranchAddress("shr_tkfit_nhits_Y", &shr_tkfit_nhits_Y);
    tree->SetBranchAddress("shr_tkfit_nhits_V", &shr_tkfit_nhits_V);
    tree->SetBranchAddress("shr_tkfit_nhits_U", &shr_tkfit_nhits_U);

    tree->SetBranchAddress("shr_tkfit_gap10_dedx_Y", &shr_tkfit_gap10_dedx_Y);
    tree->SetBranchAddress("shr_tkfit_gap10_dedx_V", &shr_tkfit_gap10_dedx_V);
    tree->SetBranchAddress("shr_tkfit_gap10_dedx_U", &shr_tkfit_gap10_dedx_U);

    tree->SetBranchAddress("shr_tkfit_gap10_nhits_Y", &shr_tkfit_gap10_nhits_Y);
    tree->SetBranchAddress("shr_tkfit_gap10_nhits_V", &shr_tkfit_gap10_nhits_V);
    tree->SetBranchAddress("shr_tkfit_gap10_nhits_U", &shr_tkfit_gap10_nhits_U);


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
    tree->SetBranchAddress("trk_llr_pid_score_v", &trk_llr_pid_score_v);

    tree->SetBranchAddress("trk_llr_pid_score_5cm_v", &trk_llr_pid_score_5cm_v);

    tree->SetBranchAddress("all_shr_energies",          &all_shr_energies);
    tree->SetBranchAddress("shr_energy_u_v",          &shr_energy_u_v);
    tree->SetBranchAddress("shr_energy_v_v",          &shr_energy_v_v);
    tree->SetBranchAddress("shr_energy_y_v",          &shr_energy_y_v);
    tree->SetBranchAddress("shr_px_v",          &shr_px_v);
    tree->SetBranchAddress("shr_py_v",          &shr_py_v);
    tree->SetBranchAddress("shr_pz_v",          &shr_pz_v);

    tree->SetBranchAddress("pi0_mass_U",         &pi0_mass_U); 

    // dE/dx of leading track
    /*
    tree->SetBranchAddress("trk_nhits_u",	&trk_nhits_u);
    tree->SetBranchAddress("trk_nhits_v",	&trk_nhits_v);
    tree->SetBranchAddress("trk_nhits_y",	&trk_nhits_y);
    tree->SetBranchAddress("trk_dedx_u_v",	&trk_dedx_u_v);
    tree->SetBranchAddress("trk_dedx_v_v",	&trk_dedx_v_v);
    tree->SetBranchAddress("trk_dedx_y_v",	&trk_dedx_y_v);
    tree->SetBranchAddress("trk_rr_u_v",	&trk_rr_u_v);
    tree->SetBranchAddress("trk_rr_v_v",	&trk_rr_v_v);
    tree->SetBranchAddress("trk_rr_y_v",	&trk_rr_y_v);
    */

}

// Function to classify the event
void EventContainer::EventClassifier(Utility::FileTypeEnums type){

	// --- MC classification --
	if (type == Utility::kMC) {
		// identify cosmic / cosmic contaminated events
		// check fraction of hits that are not matched to neutrino
		if (nu_purity_from_pfp <= 0.5) {
			// low purity, classify as cosmic
			classification = Utility::kCosmic; // std::make_pair("Cosmic", _utility.kCosmic);
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
						classification = Utility::kCCNumupizero; //std::make_pair("CCNumupizero", _utility.kCCNumupizero);
						return;
					}
					else {
						// classify as CC numu other
						classification = Utility::kCCNumuOther; // std::make_pair("CCNumuOther", _utility.kCCNumuOther);
						return;
					}
				}
				// nue
				if (nu_pdg == 12 || nu_pdg == -12) {
					// check for pi-zero
					if (npi0 > 0) {
						// classify as CC nue pizero
						classification = Utility::kCCNuepizero; // std::make_pair("CCNuepizero", _utility.kCCNuepizero);
						return;
					}
					// single pion (signal)
					else if (npion == 1) {
						// check number of protons
						if (nproton >= 1) {
							// classify as CC nue 1pi Np
							classification = Utility::kCCNue1piNp; // std::make_pair("CCNue1pi", _utility.kCCNue1pi);
							return;	
						}
						else {
							// classify as CC nue 1pi 0p
							classification = Utility::kCCNue1pi0p; // std::make_pair("CCNue1pi", _utility.kCCNue1pi);
							return;	
						}
						
					}
					// multi pion
					else if (npion > 1) {
						// classify as CC nue Npi
						classification = Utility::kCCNueNpi; // std::make_pair("CCNueNpi", _utility.kCCNueNpi);
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
						classification = Utility::kCCNueOther; // std::make_pair("CCNueOther", _utility.kCCNueOther);
						return;
					}
				}
			}
			// Neutral Current
			else {
				// check for pi-zero (background)
				if (npi0 > 0) {
					// classify as NC pizero
					classification = Utility::kNCpizero; // std::make_pair("NCpizero", _utility.kNCpizero);
					return;
				}
				else {
					classification = Utility::kNCOther; // std::make_pair("NCOther", _utility.kNCOther);
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
	classification = Utility::kUnknown; // std::make_pair("Unknown", _utility.kUnknown);
	std::cout << "Warning: Unknown Event" << std::endl;
	return;
}

// Function to get event classification
Utility::ClassificationEnums EventContainer::getEventClassification(Utility::FileTypeEnums type) {
	EventClassifier(type);
	return classification;
}


// Function to evaluate derived variables
void EventContainer::populateDerivedVariables(){

	// Shower dE/dx
	GetdEdxMax(false);	// standard
	GetdEdxMax(true); 	// with 10mm gap from start

	// Track LLR PID Score
	// this is correct method, from Katrina's script
    if (trk_id < trk_llr_pid_score_v->size() && trk_id != 0) trk_llr_pid_score = trk_llr_pid_score_v->at(trk_id-1); 	// LLR PID Score
    else trk_llr_pid_score = 9999; 
    // 5cm
	//if (trk_id < trk_llr_pid_score_5cm_v->size() && trk_id != 0) trk_llr_pid_score_5cm = trk_llr_pid_score_5cm_v->at(trk_id-1); 	// LLR PID Score
    //else trk_llr_pid_score_5cm = 9999; 

    
    // Second Track LLR PID Score
    if (trk2_id < trk_llr_pid_score_v->size() && trk2_id != 0) trk2_llr_pid_score = trk_llr_pid_score_v->at(trk2_id-1); 	// LLR PID Score
    else trk2_llr_pid_score = 9999; 
    // 5cm
	//if (trk2_id < trk_llr_pid_score_5cm_v->size() && trk2_id != 0) trk2_llr_pid_score_5cm = trk_llr_pid_score_5cm_v->at(trk2_id-1); 	// LLR PID Score
    //else trk2_llr_pid_score_5cm = 9999;

    // Second Track length
    if (trk2_id < trk_len_v->size() && trk2_id != 0) trk2_len = trk_len_v->at(trk2_id-1); 	// Track length
    else trk2_len = 0; 
	

    // primary shower energy fraction [to be debugged...]
    shr_energyFraction = shr_energy_cali / shr_energy_tot_cali; 

    // Track dE/dx
    //GetTrackdEdx();

    // neutral pion invariant mass difference
   	if (n_showers > 1) neutralPionInvariantMassDifference = std::abs(pi0_mass_U - 134.9768);
   	else neutralPionInvariantMassDifference = 999; 
   
   	/*
   	if (n_showers > 1) {
	    // loop over each shower
	    for (int s1 = 0; s1 < n_showers; s1++) {

	    	double s1_energy = shr_energy_y_v->at(s1);	    

	    	// loop over each other shower
	    	for (int s2 = 0; s2 < n_showers; s2++) {

	    		if (s1 == s2) continue;

	    		double s2_energy = shr_energy_y_v->at(s2);

	    		// calculate invariant mass
	    		double inv_mass = std::sqrt( std::pow(s1_energy + s2_energy, 2) 
									- std::pow(shr_px_v->at(s1) + shr_px_v->at(s2), 2) 
									- std::pow(shr_py_v->at(s1) + shr_py_v->at(s2), 2) 
									- std::pow(shr_pz_v->at(s1) + shr_pz_v->at(s2), 2) );

	    		double inv_mass_difference = std::abs(inv_mass - 134.9768);		    


	    		// check whether smaller than current smallest difference
	    		if (inv_mass_difference < neutralPionInvariantMassDifference) neutralPionInvariantMassDifference = inv_mass_difference;
				
	    	}

	    }
	}
	*/
	
    

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

// get track dE/dx -- to-do: plane with most hits
void EventContainer::GetTrackdEdx(){

	// initial offset
	double startGap = 2; // 2 cm
	double endGap = 5; // 5 cm

	// loop through hits
	double dEdx_sum = 0;
	int dEdx_nhits = 0;

	//std::cout << "Total hits: " << trk_nhits_u << std::endl;
	for (int i = trk_nhits_u - 1; i >= 0; i--) {

		//std::cout << trk_rr_u_v->at(i) << std::endl;

		// skip first part of track
		if (trk_rr_u_v->at(trk_nhits_u - 1) - trk_rr_u_v->at(i) < startGap) continue;

		// average dE/dx over 5cm 
		if (trk_rr_u_v->at(trk_nhits_u - 1) - trk_rr_u_v->at(i) < startGap + endGap) {
			dEdx_sum += trk_dedx_u_v->at(i);
			dEdx_nhits++;
		}

		break;
	}

	// set average dE/dx
	trk_dEdx_5cm_max = dEdx_sum / dEdx_nhits;

}




