#include "../include/EventContainer.h"

#include <iostream>
#include <algorithm>
#include <numeric>

#include "TVector3.h"
#include "TRotation.h"

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
	tree->SetBranchAddress("elec_px", &elec_px);
    tree->SetBranchAddress("elec_py", &elec_py);
    tree->SetBranchAddress("elec_pz", &elec_pz);
	tree->SetBranchAddress("npion", &npion);
	tree->SetBranchAddress("pion_e", &pion_e);
	tree->SetBranchAddress("npi0", &npi0);
	tree->SetBranchAddress("pi0_e", &pi0_e);
	tree->SetBranchAddress("nproton", &nproton);
	tree->SetBranchAddress("proton_e", &proton_e);
	tree->SetBranchAddress("neta", &neta);
    tree->SetBranchAddress("eta_e", &eta_e);

	tree->SetBranchAddress("true_nu_vtx_x", &true_nu_vtx_x);
	tree->SetBranchAddress("true_nu_vtx_y", &true_nu_vtx_y);
	tree->SetBranchAddress("true_nu_vtx_z", &true_nu_vtx_z);
	tree->SetBranchAddress("true_nu_vtx_sce_x", &true_nu_vtx_sce_x);
	tree->SetBranchAddress("true_nu_vtx_sce_y", &true_nu_vtx_sce_y);
	tree->SetBranchAddress("true_nu_vtx_sce_z", &true_nu_vtx_sce_z);
	tree->SetBranchAddress("true_nu_px", &true_nu_px);
    tree->SetBranchAddress("true_nu_py", &true_nu_py);
    tree->SetBranchAddress("true_nu_pz", &true_nu_pz);

	tree->SetBranchAddress("swtrig", &swtrig);
    tree->SetBranchAddress("swtrig_pre", &swtrig_pre);
    tree->SetBranchAddress("swtrig_post", &swtrig_post);

    tree->SetBranchAddress("_opfilter_pe_beam", &opfilter_pe_beam);
    tree->SetBranchAddress("_opfilter_pe_veto", &opfilter_pe_veto);

    tree->SetBranchAddress("weightSplineTimesTune", &weightSplineTimesTune);
    tree->SetBranchAddress("weightSpline", &weightSpline);
    tree->SetBranchAddress("weightTune", &weightTune);
    tree->SetBranchAddress("ppfx_cv", &ppfx_cv);
    tree->SetBranchAddress("weights", &mc_weights_map_);

	tree->SetBranchAddress("nslice", &nslice);
	tree->SetBranchAddress("n_tracks", &n_tracks);
    tree->SetBranchAddress("n_showers", &n_showers);
    tree->SetBranchAddress("n_showers_contained", &n_showers_contained);
    tree->SetBranchAddress("n_tracks_contained", &n_tracks_contained);
    tree->SetBranchAddress("slpdg", &slpdg);
	tree->SetBranchAddress("nu_purity_from_pfp", &nu_purity_from_pfp);

	tree->SetBranchAddress("shr_hits_tot", &shr_hits_tot);
	tree->SetBranchAddress("trk_hits_tot", &trk_hits_tot);
	tree->SetBranchAddress("trk_hits_max", &trk_hits_max);
	tree->SetBranchAddress("trk_hits_2nd", &trk_hits_2nd);

	tree->SetBranchAddress("total_hits_y", &total_hits_y);
	tree->SetBranchAddress("shr_hits_y_tot", &shr_hits_y_tot);
	tree->SetBranchAddress("trk_hits_y_tot", &trk_hits_y_tot);
	tree->SetBranchAddress("extra_energy_y", &extra_energy_y);

	tree->SetBranchAddress("crtveto", &crtveto);

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
    tree->SetBranchAddress("shr3_id", &shr3_id);
    tree->SetBranchAddress("shr_distance", &shr_distance);
    tree->SetBranchAddress("shr_score", &shr_score);
    tree->SetBranchAddress("shr_energy_cali", &shr_energy_cali);
    tree->SetBranchAddress("shr_energy_second_cali", &shr_energy_second_cali);
    tree->SetBranchAddress("shr_energy_third_cali", &shr_energy_third_cali);
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

    tree->SetBranchAddress("shr_tkfit_2cm_dedx_Y", &shr_tkfit_2cm_dedx_Y);
    tree->SetBranchAddress("shr_tkfit_2cm_dedx_V", &shr_tkfit_2cm_dedx_V);
    tree->SetBranchAddress("shr_tkfit_2cm_dedx_U", &shr_tkfit_2cm_dedx_U);

    tree->SetBranchAddress("shr_tkfit_2cm_nhits_Y", &shr_tkfit_2cm_nhits_Y);
    tree->SetBranchAddress("shr_tkfit_2cm_nhits_V", &shr_tkfit_2cm_nhits_V);
    tree->SetBranchAddress("shr_tkfit_2cm_nhits_U", &shr_tkfit_2cm_nhits_U);

    tree->SetBranchAddress("shrclusdir0", &shrclusdir0);
    tree->SetBranchAddress("shrclusdir1", &shrclusdir1);
    tree->SetBranchAddress("shrclusdir2", &shrclusdir2);

    tree->SetBranchAddress("shrsubclusters0", &shrsubclusters0);
    tree->SetBranchAddress("shrsubclusters1", &shrsubclusters1);
    tree->SetBranchAddress("shrsubclusters2", &shrsubclusters2);

    tree->SetBranchAddress("shrPCA1CMed_5cm", &shrPCA1CMed_5cm);
    tree->SetBranchAddress("CylFrac1h_1cm", &CylFrac1h_1cm);
    tree->SetBranchAddress("CylFrac2h_1cm", &CylFrac2h_1cm);
    tree->SetBranchAddress("DeltaRMS2h", &DeltaRMS2h);
    tree->SetBranchAddress("shrMCSMom", &shrMCSMom);

    tree->SetBranchAddress("shr_bkt_E", &shr_bkt_E);

    tree->SetBranchAddress("secondshower_U_nhit", &secondshower_U_nhit);
    tree->SetBranchAddress("secondshower_V_nhit", &secondshower_V_nhit);
    tree->SetBranchAddress("secondshower_Y_nhit", &secondshower_Y_nhit);
    tree->SetBranchAddress("secondshower_U_vtxdist", &secondshower_U_vtxdist);
    tree->SetBranchAddress("secondshower_V_vtxdist", &secondshower_V_vtxdist);
    tree->SetBranchAddress("secondshower_Y_vtxdist", &secondshower_Y_vtxdist);
    tree->SetBranchAddress("secondshower_U_dot", &secondshower_U_dot);
    tree->SetBranchAddress("secondshower_V_dot", &secondshower_V_dot);
    tree->SetBranchAddress("secondshower_Y_dot", &secondshower_Y_dot);	
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

    tree->SetBranchAddress("pfnplanehits_U",          &pfnplanehits_U);
    tree->SetBranchAddress("pfnplanehits_V",          &pfnplanehits_V);
    tree->SetBranchAddress("pfnplanehits_Y",          &pfnplanehits_Y);

    tree->SetBranchAddress("trk_score_v",          &trk_score_v);
    tree->SetBranchAddress("trk_start_x_v",        &trk_start_x_v);
    tree->SetBranchAddress("trk_start_y_v",        &trk_start_y_v);
    tree->SetBranchAddress("trk_start_z_v",        &trk_start_z_v);
    tree->SetBranchAddress("trk_end_x_v",          &trk_end_x_v);
    tree->SetBranchAddress("trk_end_y_v",          &trk_end_y_v);
    tree->SetBranchAddress("trk_end_z_v",          &trk_end_z_v);
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
	tree->SetBranchAddress("trk_calo_energy_y_v",      &trk_calo_energy_y_v);
	tree->SetBranchAddress("trk_energy_proton_v",      &trk_energy_proton_v);
	tree->SetBranchAddress("trk_energy_muon_v",      &trk_energy_muon_v);
	
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

 	tree->SetBranchAddress("trk_end_spacepoints_v", &trk_end_spacepoints_v);
 	 
 	tree->SetBranchAddress("pfpplanesubclusters_U", &pfpplanesubclusters_U_v);
 	tree->SetBranchAddress("pfpplanesubclusters_V", &pfpplanesubclusters_V_v);
 	tree->SetBranchAddress("pfpplanesubclusters_Y", &pfpplanesubclusters_Y_v);
    
    tree->SetBranchAddress("pfp_generation_v", &pfp_generation_v);
 	  
 	tree->SetBranchAddress("backtracked_pdg", &backtracked_pdg_v); 	
    
    tree->SetBranchAddress("pi0_mass_U",         &pi0_mass_U);

    tree->SetBranchAddress("mc_pdg",       &mc_pdg_v);
    tree->SetBranchAddress("mc_E",         &mc_E_v);
    tree->SetBranchAddress("mc_px",           &mc_px_v);
    tree->SetBranchAddress("mc_py",           &mc_py_v);
    tree->SetBranchAddress("mc_pz",           &mc_pz_v); 

    // track trunk dE/dx
    tree->SetBranchAddress("trk_nhits_u_v",		&trk_nhits_u_v);
    tree->SetBranchAddress("trk_nhits_v_v",		&trk_nhits_v_v);
    tree->SetBranchAddress("trk_nhits_y_v",		&trk_nhits_y_v);
    tree->SetBranchAddress("trk_trunk_dEdx_u_v",	&trk_trunk_dEdx_u_v);
    tree->SetBranchAddress("trk_trunk_dEdx_v_v",	&trk_trunk_dEdx_v_v);
    tree->SetBranchAddress("trk_trunk_dEdx_y_v",	&trk_trunk_dEdx_y_v);

}

// Destructor
EventContainer::~EventContainer(){
	
}

// Function to classify the event
void EventContainer::EventClassifier(Utility::FileTypeEnums type){

	// --- MC classification --
	if (type == Utility::kMC || type == Utility::kDetVar || type == Utility::kIntrinsic || type == Utility::kCCNCPiZero || type == Utility::kFakeData) {

		// check whether vertex is within fiducial volume
		//bool isInFV = _utility.inFV(true_nu_vtx_sce_x, true_nu_vtx_sce_y, true_nu_vtx_sce_z);
		bool isInFV = _utility.inFV(true_nu_vtx_x, true_nu_vtx_y, true_nu_vtx_z);	// swapping to non-space-charged corrected variables in truth

		// Outside of FV
		if (!isInFV) {
			// classify as outFV
			classification = Utility::kOutFV;
			category_ = static_cast<int>(classification);
			return;
		}
		// Inside of FV
		else {
			// Charged Current
			if (ccnc == 0) {
				// numu
				if (nu_pdg == 14 || nu_pdg == -14) {
					// check for pi-zero (background)
					if (npi0 > 0 || neta > 0) {
                    //if ( (npi0 > 0 && pi0_e > 0.04 + 134.9768/1000) || (neta > 0 && eta_e > 0.04 + 547.862/1000) ) {
						// classify as CC numu pizero
						classification = Utility::kCCNumupizero;
						category_ = static_cast<int>(classification);
						return;
					}
					else {
						// classify as CC numu other
						classification = Utility::kCCNumuOther;
						category_ = static_cast<int>(classification);
						return;
					}
				}
				// nue
				if (nu_pdg == 12 || nu_pdg == -12) {

					// tag as inclusive signal, 30 MeV threshold
					if (nelec > 0) mc_is_inclusive_signal_ = true;

					// check for pi-zero (or eta)
                    if (npi0 > 0 || neta > 0) {
					//if ( (npi0 > 0 && pi0_e > 0.04 + 134.9768/1000) || (neta > 0 && eta_e > 0.04 + 547.862/1000) ) {
						// classify as CC nue pizero
						classification = Utility::kCCNuepizero;
						category_ = static_cast<int>(classification);
						return;
					}
					// single pion (signal)
					else if (npion == 1) {
						
						// check neutrino energy and electron energy, to match signal definition
						// nelec only counts electrons above threshold, set to 30 KeV in ntuple maker

						// check pion/electron opening angle
						TVector3 elec_dir(elec_px, elec_py, elec_pz);
						TVector3 pion_dir(pion_px, pion_py, pion_pz);
						elec_dir.Unit();
						pion_dir.Unit();
						double opening_angle = elec_dir.Angle(pion_dir) * 180 / 3.14159;

						// count other mesons present
						int nkaon = 0;
						int nrho = 0;
						int nomega = 0;
						int nphi = 0;
						
						for (int i = 0; i < mc_pdg_v->size(); i++) {
							//if ((mc_pdg_v->at(i) == 321 || mc_pdg_v->at(i) == -321 || mc_pdg_v->at(i) == 311) && mc_E_v->at(i) > 0.04 + 493.677/1000) nkaon++;
							//if ((mc_pdg_v->at(i) == 213 || mc_pdg_v->at(i) == -213 || mc_pdg_v->at(i) == 113) && mc_E_v->at(i) > 0.04 + 775.11/1000) nrho++;
							//if ((mc_pdg_v->at(i) == 223) && mc_E_v->at(i) > 0.04 + 782.66/1000) nomega++;
							//if ((mc_pdg_v->at(i) == 333) && mc_E_v->at(i) > 0.04 + 1019.461/1000) nphi++;
                            if ((mc_pdg_v->at(i) == 321 || mc_pdg_v->at(i) == -321 || mc_pdg_v->at(i) == 311)) nkaon++;
                            if ((mc_pdg_v->at(i) == 213 || mc_pdg_v->at(i) == -213 || mc_pdg_v->at(i) == 113)) nrho++;
                            if ((mc_pdg_v->at(i) == 223)) nomega++;
                            if ((mc_pdg_v->at(i) == 333)) nphi++;   	
						}
						
						if (nelec > 0 && nkaon == 0 && nrho == 0 && nomega == 0 && nphi == 0 && opening_angle <= 170) { // && opening_angle >= 10) {

							// classify as CC nue 1pi Xp
							classification = Utility::kCCNue1piXp;
							category_ = static_cast<int>(classification);
							mc_is_signal_ = true;
							return;
							
							/*
							// check number of protons
							if (nproton == 0) {
								// classify as CC nue 1pi 0p
								classification = Utility::kCCNue1pi0p;
								category_ = static_cast<int>(classification);
								mc_is_signal_ = true;
								return;	
							}
							else if (nproton == 1) {
								// classify as CC nue 1pi 1p
								classification = Utility::kCCNue1pi1p;
								category_ = static_cast<int>(classification);
								mc_is_signal_ = true;
								return;	
							}
							else {
								// classify as CC nue 1pi Np
								classification = Utility::kCCNue1piNp;
								category_ = static_cast<int>(classification);
								mc_is_signal_ = true;
								return;
							}
							*/							
							
						}
						else {
							// otherwise re-define as CC nue other -- is there a better way to do this?
							classification = Utility::kCCNueOther;
							category_ = static_cast<int>(classification);
							return;
						}
					}
					// multi pion
					else if (npion > 1) {
						// classify as CC nue Npi
						classification = Utility::kCCNueNpi;
						category_ = static_cast<int>(classification);
						return;
					}
					// proton, and no pions
					else if (nproton >= 1) {
						// classify as CC nue Np
						classification = Utility::kCCNueNp;
						category_ = static_cast<int>(classification);
						return;
					}
					else {
						// classify as CC nue other
						classification = Utility::kCCNueOther;
						category_ = static_cast<int>(classification);
						return;
					}
				}
			}
			// Neutral Current
			else {
				// check for pi-zero (or eta)
				if (npi0 > 0 || neta > 0) {
                //if ( (npi0 > 0 && pi0_e > 0.04 + 134.9768/1000) || (neta > 0 && eta_e > 0.04 + 547.862/1000) ) {
					// classify as NC pizero
					classification = Utility::kNCpizero;
					category_ = static_cast<int>(classification); 
					return;
				}
				else {
					classification = Utility::kNCOther;
					category_ = static_cast<int>(classification);
					return;
				}
			}
		}
	}
	// Beam Off Classification
	else if (type == Utility::kEXT) {
		classification = Utility::kBeamOff;
		category_ = static_cast<int>(classification);
		return;
	}
	// Dirt
	else if (type == Utility::kDirt) {
		classification = Utility::kOutOfCryo;
		category_ = static_cast<int>(classification);
		return;
	}
	// Data
	else if (type == Utility::kData) {
		classification = Utility::kBeamOn;
		category_ = static_cast<int>(classification);
		return;
	}

	// Catch any events without classification
	// Shouldn't be any of these! Will cause issues.
	std::cout << "Warning: Unknown Event" << std::endl;
	std::cout << "Type: " << type << std::endl;
	exit(10);
	return;
}

// Function to get event classification
Utility::ClassificationEnums EventContainer::getEventClassification(Utility::FileTypeEnums type) {
	EventClassifier(type);
	return classification;
}

// Function to set interaction type enum
void EventContainer::InteractionClassifier(Utility::FileTypeEnums type){
	// --- MC classification --
	if (type == Utility::kMC || type == Utility::kDetVar || type == Utility::kIntrinsic || type == Utility::kCCNCPiZero || type == Utility::kFakeData) {
		
		if (interaction == 0) {
			interactionMode = Utility::kQE;
		}
		else if (interaction == 1) {
			interactionMode = Utility::kRES;
		}
		else if (interaction == 2) {
			interactionMode = Utility::kDIS;
		}
		else if (interaction == 3) {
			interactionMode = Utility::kCOH;
		}
		else if (interaction == 10) {
			interactionMode = Utility::kMEC;
		}
		else {
			interactionMode = Utility::kOther;
		}
	}
	else {
		// undefined for data
		interactionMode = Utility::kOther;
	}
}

// Function to calculate CV event weight
void EventContainer::calculateCVEventWeight(Utility::FileTypeEnums type, Utility::RunPeriodEnums runPeriod) {

	float weight = 1.0;

	// check weights are sensible
	ppfx_cv = checkWeight(ppfx_cv);
	weightSpline = checkWeight(weightSpline);
	weightTune = checkWeight(weightTune);

	// overlay MC events
	if (type == Utility::kMC || type == Utility::kDetVar || type == Utility::kIntrinsic || type == Utility::kCCNCPiZero || type == Utility::kFakeData) {
			
		// TESTING
		//ppfx_cv = 1;

		// CV weight
		weight = ppfx_cv * weightSpline * weightTune;

		// set normalisation weight
		normalisation_weight = 1;

		// normalisation scaling of pi0 events performed in LEE analyses, but not included in Krishan's measurement
		// unclear whether this should be included or not
		// further re-scale events containing pi-zeros
		/*
		if (npi0 > 0) {
			
			// energy dependent scaling, from PeLEE analysis
        	double pi0_e_threshold = 0.6; // GeV
            if (pi0_e > 0.1 && pi0_e < pi0_e_threshold){
            	normalisation_weight = 1. - 0.4 * pi0_e;
            }
            else if (pi0_e > 0.1 && pi0_e >= pi0_e_threshold){
                normalisation_weight = 1. - 0.4 * pi0_e_threshold;
            }
           
			//weight = weight * 0.759;	// flat normalisation scaling, from Krishan's analysis  
		}
		*/

		/*
		if (type == Utility::kIntrinsic) {
			if (runPeriod == Utility::kRun1a) fake_data_weight = 0.177705;
			else if (runPeriod == Utility::kRun1b) fake_data_weight = 0.048335;
			else if (runPeriod == Utility::kRun2a) fake_data_weight = 0.050983;
			else if (runPeriod == Utility::kRun2b) fake_data_weight = 0.034205;	
			else if (runPeriod == Utility::kRun3b) fake_data_weight = 0.133753;
			else if (runPeriod == Utility::kRun4ab) fake_data_weight = 0.158684;
			else if (runPeriod == Utility::kRun4cd) fake_data_weight = 0.163655;
			else if (runPeriod == Utility::kRun5) fake_data_weight = 0.160654;
			else std::cout << "Warning: run period: " << runPeriod << " not found, fake data weight not set." << std::endl;
		}
		
		
		if (type == Utility::kMC) fake_data_weight = 1;

        if (type == Utility::kFakeData) {
            if (runPeriod == Utility::kRun1a) fake_data_weight = 0.0389127;      // 6.65042e+20 / 1.70906e+22
            else if (runPeriod == Utility::kRun3b) fake_data_weight = 0.0873354; // 7.4309e+20 / 8.50846e+21
            else std::cout << "Warning: run period: " << runPeriod << " not found, fake data weight not set." << std::endl;
        }
        */

	}
	
	// dirt events
	// using scaling factors from Katrina's analysis, DocDb: 39436
	if (type == Utility::kDirt) {

		weight = ppfx_cv * weightSpline * weightTune;
		
		// FHC
		if (runPeriod == Utility::kRun1a || runPeriod == Utility::kRun2a || runPeriod == Utility::kRun4cd || runPeriod == Utility::kRun5) {
			weight = weight*0.65;
			
			// set normalisation weight
			normalisation_weight = 0.65;
		}

		// RHC
		if (runPeriod == Utility::kRun1b || runPeriod == Utility::kRun2b || runPeriod == Utility::kRun3b || runPeriod == Utility::kRun4ab) {
			weight = weight*0.45;

			// set normalisation weight
			normalisation_weight = 0.45;
		}	
	}

	// beam off events
	if (type == Utility::kEXT) {
		weight = 0.98;

		// set normalisation weight
	    normalisation_weight = 0.98;
	}

	// beam on
	if (type == Utility::kData) {
		weight = 1;

		// set normalisation weight
	    normalisation_weight = 1;
	}	

	// check weight is sensible
	weight = checkWeight(weight);

	// set weight in event
	weight_cv = weight;

}

// Function to calculate beamline variation weights
void EventContainer::calculateBeamlineVariationWeights(Utility::RunPeriodEnums runPeriod) {

	// true nu angle from numi beamline 
    nu_angle = GetNuMIAngle(true_nu_px, true_nu_py, true_nu_pz, "beam");

    // get weights vector
    std::vector<double> weights;
    if (nu_pdg == 12) weights = _utility.getWeightsNue(nu_e, nu_angle, runPeriod);
    else if (nu_pdg == -12) weights = _utility.getWeightsNuebar(nu_e, nu_angle, runPeriod);
    else if (nu_pdg == 14) weights = _utility.getWeightsNumu(nu_e, nu_angle, runPeriod);
    else if (nu_pdg == -14) weights = _utility.getWeightsNumubar(nu_e, nu_angle, runPeriod);
    else {
    	std::cout << "Error: cannot get beamline variation weights" << std::endl;
    	exit(1);
    }

    // sanity check
    if (weights.size() != 20) {
    	std::cout << "Error: missing expected beamline variation weights" << std::endl;
    	exit(1);
    }

    // populate weights appropriately
	Horn_2kA.push_back(checkWeight(weights[0]));
	Horn_2kA.push_back(checkWeight(weights[1]));
	Horn1_x_3mm.push_back(checkWeight(weights[2]));
	Horn1_x_3mm.push_back(checkWeight(weights[3]));
	Horn1_y_3mm.push_back(checkWeight(weights[4]));
	Horn1_y_3mm.push_back(checkWeight(weights[5]));
	Beam_spot_1_1mm.push_back(checkWeight(weights[6]));
	Beam_spot_1_5mm.push_back(checkWeight(weights[7]));
	Horn2_x_3mm.push_back(checkWeight(weights[8]));
	Horn2_x_3mm.push_back(checkWeight(weights[9]));
	Horn2_y_3mm.push_back(checkWeight(weights[10]));
	Horn2_y_3mm.push_back(checkWeight(weights[11]));
	Horns_0mm_water.push_back(checkWeight(weights[12]));
	Horns_2mm_water.push_back(checkWeight(weights[13]));
	Beam_shift_x_1mm.push_back(checkWeight(weights[14]));
	Beam_shift_x_1mm.push_back(checkWeight(weights[15]));
	Beam_shift_y_1mm.push_back(checkWeight(weights[16]));
	Beam_shift_y_1mm.push_back(checkWeight(weights[17]));
	Target_z_7mm.push_back(checkWeight(weights[18]));
	Target_z_7mm.push_back(checkWeight(weights[19]));

	beamlineVarWeightsPresent = true;
}

// Function to update CV weights for NuWro fake data 
void EventContainer::updateNuWroCVWeights(Utility::RunPeriodEnums runPeriod) {

	// set Genie CV weights to be 1
	weightSpline = 1;
	weightTune = 1;
	normalisation_weight = 1;
	
    // true nu angle from numi beamline 
    nu_angle = GetNuMIAngle(true_nu_px, true_nu_py, true_nu_pz, "beam");

    // get PPFX CV from flux file
    if (nu_pdg == 12) ppfx_cv = _utility.getCVWeightNue(nu_e, nu_angle, runPeriod);
    else if (nu_pdg == -12) ppfx_cv = _utility.getCVWeightNuebar(nu_e, nu_angle, runPeriod);
    else if (nu_pdg == 14) ppfx_cv = _utility.getCVWeightNumu(nu_e, nu_angle, runPeriod);
    else if (nu_pdg == -14) ppfx_cv = _utility.getCVWeightNumubar(nu_e, nu_angle, runPeriod);
    else {
    	std::cout << "Error: cannot get PPFX CV weights" << std::endl;
    	exit(1);
    }

    // check new weight is sensible
	ppfx_cv = checkWeight(ppfx_cv);
}

// Function to calculate Flugg weight, set as normalisation weight to be applied in XSecAnalyser
void EventContainer::calculateFluggWeights(Utility::RunPeriodEnums runPeriod) {

	float flugg_weight = 1;

	// true nu angle from numi beamline 
    nu_angle = GetNuMIAngle(true_nu_px, true_nu_py, true_nu_pz, "beam");

    // get PPFX CV from flux file
    if (nu_pdg == 12) flugg_weight = _utility.getFluggWeightNue(nu_e, nu_angle, runPeriod);
    else if (nu_pdg == -12) flugg_weight = _utility.getFluggWeightNuebar(nu_e, nu_angle, runPeriod);
    else if (nu_pdg == 14) flugg_weight = _utility.getFluggWeightNumu(nu_e, nu_angle, runPeriod);
    else if (nu_pdg == -14) flugg_weight = _utility.getFluggWeightNumubar(nu_e, nu_angle, runPeriod);
    else {
    	std::cout << "Error: cannot get Flugg weights" << std::endl;
    	exit(1);
    }

    // check new weight is sensible
	flugg_weight = checkWeight(flugg_weight);

	// set as normalisation weight
	//normalisation_weight *= flugg_weight;

	// set Flugg weight
	fluggWeightsPresent = true;	
	FluggCV.push_back(flugg_weight);
}

// Function to calculate CV Reweight Ratio [testing]
void EventContainer::calculateReweightRatio(Utility::RunPeriodEnums runPeriod) {

	float reweight_ratio = 1;

	// true nu angle from numi beamline 
    nu_angle = GetNuMIAngle(true_nu_px, true_nu_py, true_nu_pz, "beam");

    // get PPFX CV from flux file
    if (nu_pdg == 12) reweight_ratio = _utility.getReweightRatioNue(nu_e, nu_angle, runPeriod);
    else if (nu_pdg == -12) reweight_ratio = _utility.getReweightRatioNuebar(nu_e, nu_angle, runPeriod);
    else if (nu_pdg == 14) reweight_ratio = _utility.getReweightRatioNumu(nu_e, nu_angle, runPeriod);
    else if (nu_pdg == -14) reweight_ratio = _utility.getReweightRatioNumubar(nu_e, nu_angle, runPeriod);
    else {
    	std::cout << "Error: cannot get weights" << std::endl;
    	exit(1);
    }

    // check new weight is sensible
	reweight_ratio = checkWeight(reweight_ratio);

	// set weight
	reweightRatioPresent = true;	
	reweightRatio = reweight_ratio;
}

// Function to check event weight is sensible
float EventContainer::checkWeight(float weight) {


	// infinite or nan weight
	if (!_utility.isNumber(weight)) {
		//std::cout << "Warning: infinite/nan event weight" << std::endl;
		weight = 1.0;
	}

	// overly large weight
	else if (weight > 30.0) {
		//std::cout << "Warning: overly large event weight, " << weight << std::endl;
		weight = 1.0;
	}

	// negative weight
	else if (weight < 0.0) {
		//std::cout << "Warning: negative event weight" << std::endl;
		weight = 1.0;
	}

	// approximately zero weight
	else if (weight > -1.0e-4 && weight < 1e-4) {
		weight = 0.0;
	}

	return weight;
}

// apply reconstruction failure recovery algorithms
void EventContainer::applyEventRecoveryAlgorithms() {

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

	bool shr2Split = false;
	bool shr3Split = false;

	// identify events with failure: secondary shower
	if (n_tracks_contained > 0 && n_showers_contained > 1 && shr_score <= 0.1 && shrsubclusters >= 4 && shr12_p1_dstart < 20 && tk1sh2_distance > 60 && tk1sh2_distance != 9999) {
		
		hasSplitPrimaryShower = true;
		
		// update event ntuple variables
		n_showers_contained--;
		shrsubclusters += shr2subclusters;
		if (shr1shr2moliereavg > 0) shrmoliereavg = shr1shr2moliereavg;
		//if (shr_energy_second_cali > 0) shr_energy_cali += shr_energy_second_cali;
		if (shr2_energy != 9999) shr_energy_cali += shr2_energy;

		shr2Split = true;
	}

	// identify events with failure: tertiary shower
	if (n_tracks_contained > 0 && n_showers_contained > 1 && shr_score <= 0.1 && shrsubclusters >= 4 && shr13_p1_dstart < 20 && tk1sh3_distance > 60 && tk1sh3_distance != 9999) {
		
		hasSplitPrimaryShower = true;

		// update event ntuple variables
		n_showers_contained--;
		shrsubclusters += shr3subclusters;
		//if (shr_energy_third_cali > 0) shr_energy_cali += shr_energy_third_cali;
		if (shr3_energy != 9999) shr_energy_cali += shr3_energy;

		shr3Split = true;
	}

	// update secondary and tertiary shower energies as appropriate, default/missing values in cases where information not present (e.g. requiring 4th/5th shower information) 
	if (shr2Split && shr3Split) {
		shr_energy_second_cali = 0;
		shr_energy_third_cali = 0;

		shr2_distance = 9999;
		shr12_p1_dstart = 9999;

		shr3_distance = 9999;
		shr13_p1_dstart = 9999;
	}
	else if (shr2Split) {
		shr_energy_second_cali = shr_energy_third_cali;
		shr2_distance = shr3_distance;
		shr12_p1_dstart = shr13_p1_dstart;
	}
	else if (shr3Split) {
		shr_energy_third_cali = 0;
		shr3_distance = 9999;
		shr13_p1_dstart = 9999;
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
void EventContainer::populateDerivedVariables(Utility::FileTypeEnums type, Utility::RunPeriodEnums runPeriod){

	// fraction of hits associated with tracks or showers
	associated_hits_fraction = ((float)trk_hits_y_tot + (float)shr_hits_y_tot) / (float)total_hits_y;
	
	// number of showers above threshold
	n_showers_alt = all_shr_energies->size();
	n_showers_above_threshold = 0;
	for (unsigned int i = 0; i < all_shr_energies->size(); i++) {
		if (all_shr_energies->at(i) > 0.07) n_showers_above_threshold++; // 70 MeV, michels
	}

	// Shower dE/dx
	GetdEdxMax(false);	// first 2cm only 
	GetdEdxMax(true); 	// with 10mm gap from start
 
	// Primary track information
	// if information primary track present -- vectors are all the same size by construction
	if (trk_id < trk_sce_start_x_v->size() && trk_id != 0) {

		trk_llr_pid_score = trk_llr_pid_score_v->at(trk_id-1); 	// LLR PID Score
		trk_daughters = pfp_trk_daughters_v->at(trk_id-1); 		// Track daughters
		trk_start_x = trk_start_x_v->at(trk_id-1);				// Track start, without SCE to allow comparison with shower start
		trk_start_y = trk_start_y_v->at(trk_id-1);				// Track start, without SCE to allow comparison with shower start
		trk_start_z = trk_start_z_v->at(trk_id-1);				// Track start, without SCE to allow comparison with shower start
		trk_end_x = trk_end_x_v->at(trk_id-1); 					// Track end, without SCE to allow comparison with shower start
        trk_end_y = trk_end_y_v->at(trk_id-1); 					// Track end, without SCE to allow comparison with shower start
        trk_end_z = trk_end_z_v->at(trk_id-1); 					// Track end, without SCE to allow comparison with shower start
		trk_sce_end_x = trk_sce_end_x_v->at(trk_id-1); 			// Track end
        trk_sce_end_y = trk_sce_end_y_v->at(trk_id-1); 			// Track end
        trk_sce_end_z = trk_sce_end_z_v->at(trk_id-1); 			// Track end
        trk_dir_x = trk_dir_x_v->at(trk_id-1);
        trk_dir_y = trk_dir_y_v->at(trk_id-1);  	
        trk_dir_z = trk_dir_z_v->at(trk_id-1);
        trk_calo_energy = trk_calo_energy_y_v->at(trk_id-1);
        trk_energy_proton = trk_energy_proton_v->at(trk_id-1);
        trk_energy_muon = trk_energy_muon_v->at(trk_id-1);
        trk_end_spacepoints = trk_end_spacepoints_v->at(trk_id-1);
        trk_planehits_U = pfnplanehits_U->at(trk_id-1);
        trk_planehits_V = pfnplanehits_U->at(trk_id-1);
        trk_planehits_Y = pfnplanehits_U->at(trk_id-1);
        trk_pfpgeneration = pfp_generation_v->at(trk_id-1);
	}
	else {
		trk_llr_pid_score = 9999;
		trk_daughters = 9999;
		trk_start_x = 9999;
		trk_start_y = 9999;
		trk_start_z = 9999;
		trk_end_x = 9999;
		trk_end_y = 9999;
		trk_end_z = 9999;
		trk_sce_end_x = 9999;
		trk_sce_end_y = 9999;
		trk_sce_end_z = 9999;
		trk_dir_x = 9999;
		trk_dir_y = 9999;
		trk_dir_z = 9999;
		trk_calo_energy = 9999;
		trk_energy_proton = 0;
        trk_energy_muon = 0;
        trk_end_spacepoints = 9999;
        trk_planehits_U = 0;
        trk_planehits_V = 0;
        trk_planehits_Y = 0;
        trk_pfpgeneration = 0;
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
		trk2_end_x = trk_end_x_v->at(trk2_id-1); 					// Track end, without SCE to allow comparison with shower start
        trk2_end_y = trk_end_y_v->at(trk2_id-1); 					// Track end, without SCE to allow comparison with shower start
        trk2_end_z = trk_end_z_v->at(trk2_id-1); 					// Track end, without SCE to allow comparison with shower start
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
		trk2_bragg_pion = trk_bragg_pion_v->at(trk2_id-1); 			// Bragg Pion
		trk2_calo_energy = trk_calo_energy_y_v->at(trk2_id-1);
		trk2_energy_proton = trk_energy_proton_v->at(trk2_id-1);
        trk2_energy_muon = trk_energy_muon_v->at(trk2_id-1);
        trk2_end_spacepoints = trk_end_spacepoints_v->at(trk2_id-1);
		if (type != Utility::kEXT && type != Utility::kData) trk2_bkt_pdg = backtracked_pdg_v->at(trk2_id-1);			// Backtracked PDG
		else trk2_bkt_pdg = 9999;
		trk2_planehits_U = pfnplanehits_U->at(trk2_id-1);
        trk2_planehits_V = pfnplanehits_U->at(trk2_id-1);
        trk2_planehits_Y = pfnplanehits_U->at(trk2_id-1);
        trk2_pfpgeneration = pfp_generation_v->at(trk2_id-1);
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
		trk2_bkt_pdg = 9999;
		trk2_start_x = 9999;
		trk2_start_y = 9999;
		trk2_start_z = 9999;
		trk2_end_x = 9999;
		trk2_end_y = 9999;
		trk2_end_z = 9999;
		trk2_sce_end_x = 9999;
		trk2_sce_end_y = 9999;
		trk2_sce_end_z = 9999;
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
		trk2_calo_energy = 9999;
		trk2_energy_proton = 0;
        trk2_energy_muon = 0;
        trk2_end_spacepoints = 9999;
        trk2_planehits_U = 0;
        trk2_planehits_V = 0;
        trk2_planehits_Y = 0;
        trk2_pfpgeneration = 0;
	}

	// tertiary track information
	if (trk3_id < trk_sce_start_x_v->size() && trk3_id != 0) {

		trk3_bragg_p = trk_bragg_p_v->at(trk3_id-1); 				// Bragg Proton
		trk3_bragg_mu = trk_bragg_mu_v->at(trk3_id-1); 				// Bragg Muon
		trk3_bragg_mip = trk_bragg_mip_v->at(trk3_id-1); 			// Bragg MIP
		trk3_llr_pid_score = trk_llr_pid_score_v->at(trk3_id-1); 	// LLR PID Score
		trk3_len = trk_len_v->at(trk3_id-1); 						// Track length
		trk3_score = trk_score_v->at(trk3_id-1); 					// Track score
		trk3_distance = trk_distance_v->at(trk3_id-1);				// Track distance
		trk3_daughters = pfp_trk_daughters_v->at(trk3_id-1); 		// Track daughters
		trk3_end_x = trk_end_x_v->at(trk3_id-1); 					// Track end, without SCE to allow comparison with shower start
        trk3_end_y = trk_end_y_v->at(trk3_id-1); 					// Track end, without SCE to allow comparison with shower start
        trk3_end_z = trk_end_z_v->at(trk3_id-1); 					// Track end, without SCE to allow comparison with shower start
		trk3_sce_end_x = trk_sce_end_x_v->at(trk3_id-1); 			// Track end
        trk3_sce_end_y = trk_sce_end_y_v->at(trk3_id-1); 			// Track end
        trk3_sce_end_z = trk_sce_end_z_v->at(trk3_id-1); 			// Track end
        trk3_dir_x = trk_dir_x_v->at(trk3_id-1);
        trk3_dir_y = trk_dir_y_v->at(trk3_id-1);  	
        trk3_dir_z = trk_dir_z_v->at(trk3_id-1);
		trk3_bragg_pion = trk_bragg_pion_v->at(trk3_id-1);
		trk3_calo_energy = trk_calo_energy_y_v->at(trk3_id-1);
		trk3_energy_proton = trk_energy_proton_v->at(trk3_id-1);
        trk3_energy_muon = trk_energy_muon_v->at(trk3_id-1); 									
        trk3_end_spacepoints = trk_end_spacepoints_v->at(trk3_id-1);
		if (type != Utility::kEXT && type != Utility::kData) trk3_bkt_pdg = backtracked_pdg_v->at(trk3_id-1);			// Backtracked PDG
		else trk3_bkt_pdg = 9999;
		trk3_planehits_U = pfnplanehits_U->at(trk3_id-1);
        trk3_planehits_V = pfnplanehits_U->at(trk3_id-1);
        trk3_planehits_Y = pfnplanehits_U->at(trk3_id-1);
        trk3_pfpgeneration = pfp_generation_v->at(trk3_id-1);
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
		trk3_bkt_pdg = 9999;
		trk3_end_x = 9999;
		trk3_end_y = 9999;
		trk3_end_z = 9999;
		trk3_sce_end_x = 9999;
		trk3_sce_end_y = 9999;
		trk3_sce_end_z = 9999;
		trk3_calo_energy = 0;
		trk3_energy_proton = 0;
        trk3_energy_muon = 0;
        trk3_end_spacepoints = 9999;
        trk3_planehits_U = 0;
        trk3_planehits_V = 0;
        trk3_planehits_Y = 0;
        trk3_pfpgeneration = 0;
        trk3_dir_x = 9999;
		trk3_dir_y = 9999;
		trk3_dir_z = 9999;
	}


	// track PID variables, best plane 
	// primary track
	if (trk_id < trk_sce_start_x_v->size() && trk_id != 0) {
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
	if (trk2_id < trk_sce_start_x_v->size() && trk2_id != 0) {
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
	if (trk3_id < trk_sce_start_x_v->size() && trk3_id != 0) {
		trk3_dEdx_trunk_max = GetTrackTrunkdEdxBestPlane(trk3_id);
		trk3_bragg_pion_max = GetTrackBraggPionBestPlane(trk3_id);
		trk3_bragg_mip_max = GetTrackBraggMIPBestPlane(trk3_id);
	}
	else {
		trk3_dEdx_trunk_max = 9999;
		trk3_bragg_pion_max = 9999;
		trk3_bragg_mip_max = 9999;
	}

	// Shower energy correction
	shr_energy_cali = shr_energy_cali / 0.83;
	shr_energy_tot_cali = shr_energy_tot_cali / 0.83;

	// Primary shower energy fraction
    shr_energyFraction = shr_energy_cali / shr_energy_tot_cali;

    // primary shower subclusters
    shrsubclusters = shrsubclusters0 + shrsubclusters1 + shrsubclusters2;

    // primary shower back-tracked truth, set to zero when not filled
    if (shr_bkt_E < -1 || shr_bkt_E > 100) shr_bkt_E=0; 

    // Primary shower information
    if (shr_id < shr_energy_y_v->size() && shr_id != 0) {
    	shr_start_x = shr_start_x_v->at(shr_id-1);
    	shr_start_y = shr_start_y_v->at(shr_id-1);
    	shr_start_z = shr_start_z_v->at(shr_id-1);
    	shr_dir_x = shr_px_v->at(shr_id-1);
    	shr_dir_y = shr_py_v->at(shr_id-1);
    	shr_dir_z = shr_pz_v->at(shr_id-1);
    	shr_planehits_U = pfnplanehits_U->at(shr_id-1);
        shr_planehits_V = pfnplanehits_U->at(shr_id-1);
        shr_planehits_Y = pfnplanehits_U->at(shr_id-1);
        shr_pfpgeneration = pfp_generation_v->at(shr_id-1);	
    } 
    else {
    	shr_start_x = 9999;
    	shr_start_y = 9999;
    	shr_start_z = 9999;
    	shr_dir_x = 9999;
    	shr_dir_y = 9999;
    	shr_dir_z = 9999;
    	shr_planehits_U = 0;
    	shr_planehits_V = 0;
    	shr_planehits_Y = 0;
    	shr_pfpgeneration = 0;
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
    	shr2_pfpgeneration = pfp_generation_v->at(shr2_id-1);	
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
    	shr2_pfpgeneration = 0;
    }

    // Tertiary shower information
    if (shr3_id < shr_start_x_v->size() && shr3_id != 0) {
    	shr3_energy = shr_energy_y_v->at(shr3_id-1)/1000;	// shower energy, in GeV
    	shr3_start_x = shr_start_x_v->at(shr3_id-1);
    	shr3_start_y = shr_start_y_v->at(shr3_id-1);
    	shr3_start_z = shr_start_z_v->at(shr3_id-1);
    	shr3subclusters = pfpplanesubclusters_U_v->at(shr3_id-1) + pfpplanesubclusters_V_v->at(shr3_id-1) + pfpplanesubclusters_Y_v->at(shr3_id-1);
    	shr3_distance = shr_dist_v->at(shr3_id-1);	
    }
    else {
    	shr3_energy = 9999;
    	shr3_start_x = 9999;
    	shr3_start_y = 9999;
    	shr3_start_z = 9999;
    	shr3subclusters = 9999;
    	shr3_distance = 9999;
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

	// Tertiary shower opening angle
	if (n_showers > 1 && shr_dir_x != 9999 && shr3_start_x != 9999) {

    	TVector3 showerDir(shr_dir_x, shr_dir_y, shr_dir_z);
    	TVector3 shower13StartDist(shr3_start_x - shr_start_x, shr3_start_y - shr_start_y, shr3_start_z - shr_start_z);
    	shr13_p1_dstart = showerDir.Angle(shower13StartDist) * 180 / 3.14159;
	}
	else shr13_p1_dstart = 9999;	

	// second shower distance from primary track
	if (n_showers_contained > 1 && n_tracks_contained > 0 && trk_start_x != 9999 & shr2_start_x != 9999) {
		tk1sh2_distance = std::sqrt( std::pow(shr2_start_x - trk_start_x, 2) + std::pow(shr2_start_y - trk_start_y, 2) + std::pow(shr2_start_z - trk_start_z, 2) );
	}
	else {
		tk1sh2_distance = 9999;
	}

	// tertiary shower distance from primary track
	if (n_showers_contained > 1 && n_tracks_contained > 0 && trk_start_x != 9999 & shr3_start_x != 9999) {
		tk1sh3_distance = std::sqrt( std::pow(shr3_start_x - trk_start_x, 2) + std::pow(shr3_start_y - trk_start_y, 2) + std::pow(shr3_start_z - trk_start_z, 2) );
	}
	else {
		tk1sh3_distance = 9999;
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

    // Pion-hypothesis track energies (A. Smith)
    if (trk_len > 0) trk_momentum_pion = CalculatePionMomentumRange(trk_len);
    else trk_momentum_pion = 0;
    if (trk2_len > 0) trk2_momentum_pion = CalculatePionMomentumRange(trk2_len);
    else trk2_momentum_pion = 0;
    if (trk3_len > 0) trk3_momentum_pion = CalculatePionMomentumRange(trk3_len);
    else trk3_momentum_pion = 0;

    // second shower track proximity
    shr2_trackEndProximity = GetShowerTrackEndProximity(shr2_id);
    shr3_trackEndProximity = GetShowerTrackEndProximity(shr3_id);

    // truth pion momentum
    pion_px = 9999;
    pion_py = 9999;
    pion_pz = 9999;
    // loop through truth particles and find pion
    for (int i = 0; i < mc_pdg_v->size(); i++) {
    	if (mc_pdg_v->at(i) == 211 || mc_pdg_v->at(i) == -211) {
    		// check energy threshold, need to get correct pion if ones below threshold
    		if (mc_E_v->at(i) > 0.04 + (139.57039/1000)) {
    			pion_px = mc_px_v->at(i);
    			pion_py = mc_py_v->at(i); 
    			pion_pz = mc_pz_v->at(i); 

                pion_p = std::sqrt ( std::pow(pion_px, 2) + std::pow(pion_py, 2) + std::pow(pion_pz, 2));

    			break; 
    		}
    	}
    }

    // track - shower opening angles
    trk_shr_opening_angle = 9999;
    trk2_shr_opening_angle = 9999;
    trk3_shr_opening_angle = 9999;

    if (n_showers_contained >= 1) {
	    TVector3 shr_dir(shr_dir_x, shr_dir_y, shr_dir_z); // Shower direction
	    shr_dir.Unit();

	    if (trk_id != 0) {
		    TVector3 trk_dir(trk_dir_x, trk_dir_y, trk_dir_z);	
		    trk_dir.Unit();
		    trk_shr_opening_angle = trk_dir.Angle(shr_dir) * 180 / 3.14159;
		}
		if (trk2_id != 0) {
			TVector3 trk2_dir(trk2_dir_x, trk2_dir_y, trk2_dir_z);	
		    trk2_dir.Unit();
		    trk2_shr_opening_angle = trk2_dir.Angle(shr_dir) * 180 / 3.14159;
		}
		if (trk3_id != 0) {
			TVector3 trk3_dir(trk3_dir_x, trk3_dir_y, trk3_dir_z);	
		    trk3_dir.Unit();
		    trk3_shr_opening_angle = trk3_dir.Angle(shr_dir) * 180 / 3.14159;
		}
	}

    // re-define truth nproton with alternate threshold
    // loop through truth particles and find protons
    nprotonalternate = 0; 
    for (int i = 0; i < mc_pdg_v->size(); i++) {
    	if (mc_pdg_v->at(i) == 2212) {
    		// check energy threshold
    		if (mc_E_v->at(i) > 0.04 + (938.27208816/1000)) { // 50 MeV
    			nprotonalternate++;
    		}
    	}
    }

    // initialise reconstruction failure condition variables
    hasSplitPrimaryShower = false;
    hasSpuriousLeadingTrack = false;
    hasSplitTrackShower = false;
    hasSecondShowerProton = false;

	// Initialise selection condition variables
	primaryTrackValid = false;
	secondaryTrackValid = false;
	tertiaryTrackValid = false;

	primaryTrackPionlike = false;
	secondaryTrackPionlike = false;

	tertiaryTrackPionlike = false;

	primaryTrackPionlikeLoose = false;
	secondaryTrackPionlikeLoose = false;
	tertiaryTrackPionlikeLoose = false;

	// number protons
	numberProtons = 0;
	if (nproton > 2) nproton = 2; // fudge to make N proton bin
	if (nprotonalternate > 2) nprotonalternate = 2; // fudge to make N proton bin

	// subtract electron mass from electron energy
	elec_e = elec_e - (0.51099895/1000);

	// initialise BDT score variables
	BDTScoreElectronPhoton = -1;
    primaryTrackBDTScorePionProton = -1;
    secondaryTrackBDTScorePionProton = -1;
    tertiaryTrackBDTScorePionProton = -1;
    BDTScorePionProtonAlternate = -1;

    // initialise STV tree variables
    if (type == Utility::kMC || type == Utility::kDetVar || type == Utility::kIntrinsic || type == Utility::kDirt || type == Utility::kFakeData) is_mc_ = true;
    else is_mc_ = false;
    mc_is_signal_ = false;
    mc_is_inclusive_signal_ = false;
    category_ = 9999;
    sel_passLooseRejection_ = false;
    sel_passBDTPi0Rejection_ = false;
    sel_passPi0Sideband_ = false;
    sel_passProtonSidebandLoose_ = false;
    sel_passProtonSidebandStrict_ = false;
    sel_NueCC1piXp_ = false;
    sel_passInclusiveSelection_ = false;

    // set horn current
    // FHC
	if (runPeriod == Utility::kRun1a || runPeriod == Utility::kRun2a || runPeriod == Utility::kRun4cd || runPeriod == Utility::kRun5) hornCurrent_ = 0;
	// RHC
	else if (runPeriod == Utility::kRun1b || runPeriod == Utility::kRun2b || runPeriod == Utility::kRun3b || runPeriod == Utility::kRun4ab) hornCurrent_ = 1;
	// Unknown
	else {
		std::cout << "[EventContainer::populateDerivedVariables] Error: unknown run period." << std::endl;
		exit(1);
	}

    // clear weights
    beamlineVarWeightsPresent = false;
    Horn_2kA.clear();
    Horn1_x_3mm.clear();
    Horn1_y_3mm.clear();
    Beam_spot_1_1mm.clear();
    Beam_spot_1_5mm.clear();
    Horn2_x_3mm.clear();
    Horn2_y_3mm.clear();
    Horns_0mm_water.clear();
    Horns_2mm_water.clear();
    Beam_shift_x_1mm.clear();
    Beam_shift_y_1mm.clear();
    Target_z_7mm.clear();

    fluggWeightsPresent = false;
    FluggCV.clear();

    reweightRatioPresent = false;	
	reweightRatio = 1;
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
		temp_shr_hits_u_tot = shr_tkfit_2cm_nhits_U;
    	temp_shr_hits_v_tot = shr_tkfit_2cm_nhits_V;
    	temp_shr_hits_y_tot = shr_tkfit_2cm_nhits_Y;
		temp_shr_tkfit_dedx_U = shr_tkfit_2cm_dedx_U;
		temp_shr_tkfit_dedx_V = shr_tkfit_2cm_dedx_V;
		temp_shr_tkfit_dedx_Y = shr_tkfit_2cm_dedx_Y;   
	}
	// If the dedx is undefined, set the hits to zero
    if (temp_shr_tkfit_dedx_U <= 0 || !_utility.isNumber(temp_shr_tkfit_dedx_U)) temp_shr_hits_u_tot = 0;
    if (temp_shr_tkfit_dedx_V <= 0 || !_utility.isNumber(temp_shr_tkfit_dedx_V)) temp_shr_hits_v_tot = 0;
    if (temp_shr_tkfit_dedx_Y <= 0 || !_utility.isNumber(temp_shr_tkfit_dedx_Y)) temp_shr_hits_y_tot = 0;

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
    else shr_trkfit_2cm_dedx_max = temp_shr_trkfit_dedx_max;

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
	float tolerance = 25; 	// degrees

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
	if (trk_trunk_dEdx_y_v->at(trackID-1) != 9999 && _utility.isNumber(trk_trunk_dEdx_y_v->at(trackID-1)) && trk_trunk_dEdx_y_v->at(trackID-1) > 0.0001 && !isAlongWire_y && Nhits_Y > 0 && trk_trunk_dEdx_y_v->at(trackID-1) < 100) {
		return trk_trunk_dEdx_y_v->at(trackID-1);
	}
	else if (trk_trunk_dEdx_u_v->at(trackID-1) != 9999 && _utility.isNumber(trk_trunk_dEdx_u_v->at(trackID-1)) && trk_trunk_dEdx_u_v->at(trackID-1) > 0.0001 && !isAlongWire_u && trk_trunk_dEdx_v_v->at(trackID-1) != 9999 && _utility.isNumber(trk_trunk_dEdx_v_v->at(trackID-1)) && trk_trunk_dEdx_v_v->at(trackID-1) > 0.0001 && !isAlongWire_v && Nhits_U > 0 && Nhits_V > 0 && trk_trunk_dEdx_u_v->at(trackID-1) < 100 && trk_trunk_dEdx_v_v->at(trackID-1) < 100) {
		return (Nhits_U * trk_trunk_dEdx_u_v->at(trackID-1) + Nhits_V * trk_trunk_dEdx_v_v->at(trackID-1)) / (Nhits_U + Nhits_V);
	}
	else if (trk_trunk_dEdx_v_v->at(trackID-1) != 9999 && _utility.isNumber(trk_trunk_dEdx_v_v->at(trackID-1)) && trk_trunk_dEdx_v_v->at(trackID-1) > 0.0001 && !isAlongWire_v && Nhits_V > 0 && trk_trunk_dEdx_v_v->at(trackID-1) < 100) {
		return trk_trunk_dEdx_v_v->at(trackID-1);
	} 
	else if (trk_trunk_dEdx_u_v->at(trackID-1) != 9999 && _utility.isNumber(trk_trunk_dEdx_u_v->at(trackID-1)) && trk_trunk_dEdx_u_v->at(trackID-1) > 0.0001 && !isAlongWire_u && Nhits_U > 0 && trk_trunk_dEdx_u_v->at(trackID-1) < 100) {
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
	if (trk_bragg_pion_v->at(trackID-1) != 9999 && !isAlongWire_y && Nhits_Y > 0 && trk_bragg_pion_v->at(trackID-1) >= 0.0001) {
		return trk_bragg_pion_v->at(trackID-1);
	}
	else if (trk_bragg_pion_u_v->at(trackID-1) != 9999 && !isAlongWire_u && trk_bragg_pion_v_v->at(trackID-1) != 9999 && !isAlongWire_v && Nhits_U > 0 && Nhits_V > 0 && trk_bragg_pion_u_v->at(trackID-1) >= 0.0001 && trk_bragg_pion_v_v->at(trackID-1) >= 0.0001) {
		return (Nhits_U * trk_bragg_pion_u_v->at(trackID-1) + Nhits_V * trk_bragg_pion_v_v->at(trackID-1)) / (Nhits_U + Nhits_V);
	}
	else if (trk_bragg_pion_v_v->at(trackID-1) != 9999 && !isAlongWire_v && Nhits_V > 0 && trk_bragg_pion_v_v->at(trackID-1) >= 0.0001) {
		return trk_bragg_pion_v_v->at(trackID-1);
	} 
	else if (trk_bragg_pion_u_v->at(trackID-1) != 9999 && !isAlongWire_u && Nhits_U > 0 && trk_bragg_pion_u_v->at(trackID-1) >= 0.0001) {
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
	if (trk_bragg_mip_v->at(trackID-1) != 9999 && !isAlongWire_y && Nhits_Y > 0 && trk_bragg_mip_v->at(trackID-1) >= 0.0001) {
		return trk_bragg_mip_v->at(trackID-1);
	}
	else if (trk_bragg_mip_u_v->at(trackID-1) != 9999 && !isAlongWire_u && trk_bragg_mip_v_v->at(trackID-1) != 9999 && !isAlongWire_v && Nhits_U > 0 && Nhits_V > 0 && trk_bragg_mip_u_v->at(trackID-1) >= 0.0001 && trk_bragg_mip_v_v->at(trackID-1) >= 0.0001) {
		return (Nhits_U * trk_bragg_mip_u_v->at(trackID-1) + Nhits_V * trk_bragg_mip_v_v->at(trackID-1)) / (Nhits_U + Nhits_V);
	}
	else if (trk_bragg_mip_v_v->at(trackID-1) != 9999 && !isAlongWire_v && Nhits_V > 0 && trk_bragg_mip_v_v->at(trackID-1) >= 0.0001) {
		return trk_bragg_mip_v_v->at(trackID-1);
	} 
	else if (trk_bragg_mip_u_v->at(trackID-1) != 9999 && !isAlongWire_u && Nhits_U > 0 && trk_bragg_mip_u_v->at(trackID-1) >= 0.0001) {
		return trk_bragg_mip_u_v->at(trackID-1);
	}
	else return 9999;
}

// pion energy range-based
// from A. Smith analysis -- docid=33809
float EventContainer::CalculatePionMomentumRange(float R) {

	float p_range = 0.25798 + (0.0024088 * R) - (0.18828 * std::pow(R, - 0.11687));	// GeV
	float e_range = std::sqrt(std::pow(p_range, 2) + std::pow(0.13957, 2)) - 0.13957; // GeV

	if (p_range > 0) return p_range;
	else return 0;
}

// shower track end proximity
float EventContainer::GetShowerTrackEndProximity(unsigned int shrID) {

	float shr_trackEndProximity = 9999;

	if (shrID < shr_start_x_v->size() && shrID != 0) {

		// check against each track end to find nearest
		// primary
		if (trk_id < trk_end_x_v->size() && trk_id != 0) { 
			float distance = std::sqrt(	std::pow(shr_start_x_v->at(shrID-1) - trk_end_x, 2) + std::pow(shr_start_y_v->at(shrID-1) - trk_end_y, 2) + std::pow(shr_start_z_v->at(shrID-1) - trk_end_z, 2));
			if (distance < shr_trackEndProximity) shr_trackEndProximity = distance; 
		}
		// secondary
		if (trk2_id < trk_end_x_v->size() && trk2_id != 0) { 
			float distance = std::sqrt(	std::pow(shr_start_x_v->at(shrID-1) - trk2_end_x, 2) + std::pow(shr_start_y_v->at(shrID-1) - trk2_end_y, 2) + std::pow(shr_start_z_v->at(shrID-1) - trk2_end_z, 2));
			if (distance < shr_trackEndProximity) shr_trackEndProximity = distance; 
		}
		// tertiary
		if (trk3_id < trk_end_x_v->size() && trk3_id != 0) { 
			float distance = std::sqrt(	std::pow(shr_start_x_v->at(shrID-1) - trk3_end_x, 2) + std::pow(shr_start_y_v->at(shrID-1) - trk3_end_y, 2) + std::pow(shr_start_z_v->at(shrID-1) - trk3_end_z, 2));
			if (distance < shr_trackEndProximity) shr_trackEndProximity = distance; 
		}
	}

	return shr_trackEndProximity;
}

// -----------------------------------------------------------------------------
// NuMI angle calculate, from Krishan
double EventContainer::GetNuMIAngle(double px, double py, double pz, std::string direction){

    // Variables
    TRotation RotDet2Beam;             // Rotations
    TVector3  detxyz, BeamCoords;      // Translations
    std::vector<double> rotmatrix;     // Inputs

    // input detector coordinates to translate
    detxyz = {px, py, pz};     

    // From beam to detector rotation matrix
    rotmatrix = {
        0.92103853804025681562, 0.022713504803924120662, 0.38880857519374290021,
        4.6254001262154668408e-05, 0.99829162468141474651, -0.058427989452906302359,
        -0.38947144863934973769, 0.053832413938664107345, 0.91946400794392302291 };

    // Return the TRotation
    TVector3 newX, newY, newZ;
    newX = TVector3(rotmatrix[0], rotmatrix[1], rotmatrix[2]);
    newY = TVector3(rotmatrix[3], rotmatrix[4], rotmatrix[5]);
    newZ = TVector3(rotmatrix[6], rotmatrix[7], rotmatrix[8]);

    RotDet2Beam.RotateAxes(newX, newY, newZ); // Return the TRotation now det to beam
    // RotDet2Beam.Invert(); // Invert back to the beam to det

    // Rotate to beam coords
    BeamCoords = RotDet2Beam * detxyz;

    TVector3 beamdir = {0 , 0 , 1};;
    
    // Get the angle wrt to the beam
    if (direction == "beam") beamdir = {0 , 0 , 1};
    
    // Get the angle wrt to the target to detector direction
    else if (direction == "target") {
        beamdir = {5502, 7259, 67270};
        beamdir = beamdir.Unit(); // Get the direction
    }
    else {
        std::cout << "Warning unknown angle type specified, you should check this" << std::endl;
    }
    
    double angle = BeamCoords.Angle(beamdir) * 180 / 3.1415926;

    // Create vectors to get the angle in the yz and xz planes
    TVector3 BeamCoords_yz = { 0, BeamCoords.Y(), BeamCoords.Z() }; // Angle upwards
    TVector3 BeamCoords_xz = { BeamCoords.X(), 0, BeamCoords.Z() }; // Angle across

    return angle;
}

// -----------------------------------------------------------------------------
// NuMI angular variables, from Krishan
void EventContainer::setRecoNuMIAngularVariables(bool isSideband = false){
	
	// Effective angle - beta (see K. Mistry Thesis)
    // Electron
	// Calculate the angle between the shower direction and the vector from the target to the nu vtx
    TVector3 shr_dir(shr_dir_x, shr_dir_y, shr_dir_z); // Shower direction
    shr_dir.Unit();
    
    TVector3 v_targ_uboone(-31387.58422, -3316.402543, -60100.2414);
    TVector3 v_nu_vtx(reco_nu_vtx_sce_x, reco_nu_vtx_sce_y, reco_nu_vtx_sce_z);
    TVector3 v_targ_to_vtx = (-1*v_targ_uboone + v_nu_vtx).Unit(); // -1 because the vector points from uboone to tgt, we need the other way around

    // Set the values
    reco_electron_effective_angle = shr_dir.Angle(v_targ_to_vtx) * 180 / 3.14159;
    reco_cos_electron_effective_angle = std::cos(shr_dir.Angle(v_targ_to_vtx));

    // Pion
    if (isSideband) {
    	// for sidebands use primary track
    	TVector3 piontrk_dir;	
	    piontrk_dir.SetXYZ(trk_dir_x, trk_dir_y, trk_dir_z);
	    piontrk_dir.Unit();

	    // Set the values
	    reco_pion_effective_angle = piontrk_dir.Angle(v_targ_to_vtx) * 180 / 3.14159;
	    reco_cos_pion_effective_angle = std::cos(piontrk_dir.Angle(v_targ_to_vtx));	

	    // opening angle
	    reco_electron_pion_opening_angle = piontrk_dir.Angle(shr_dir) * 180 / 3.14159;
	    reco_cos_electron_pion_opening_angle = std::cos(piontrk_dir.Angle(shr_dir));

        // for the sidebands also need to set momentum of pion to primary track, otherwise undefined
        reco_momentum_pion = trk_momentum_pion;	
    }
    else {
        if (primaryTrackPionlike || secondaryTrackPionlike || tertiaryTrackPionlike) {
	    	TVector3 piontrk_dir;
	    	if (primaryTrackPionlike) {
	    		piontrk_dir.SetXYZ(trk_dir_x, trk_dir_y, trk_dir_z);
	    		
	    	}
	    	else if (secondaryTrackPionlike) {
	    		piontrk_dir.SetXYZ(trk2_dir_x, trk2_dir_y, trk2_dir_z);
	    	}
	    	else {
	    		piontrk_dir.SetXYZ(trk3_dir_x, trk3_dir_y, trk3_dir_z);
	    	}
	    	piontrk_dir.Unit();

	    	// Set the values
		    reco_pion_effective_angle = piontrk_dir.Angle(v_targ_to_vtx) * 180 / 3.14159;
		    reco_cos_pion_effective_angle = std::cos(piontrk_dir.Angle(v_targ_to_vtx));

		    // opening angle
	    	reco_electron_pion_opening_angle = piontrk_dir.Angle(shr_dir) * 180 / 3.14159;
	    	reco_cos_electron_pion_opening_angle = std::cos(piontrk_dir.Angle(shr_dir));
	    }
	}
}

void EventContainer::setTrueNuMIAngularVariables(){
	
	// neutrino
    TVector3 nu_dir(true_nu_px, true_nu_py, true_nu_pz); 
    nu_dir.Unit();

    // electron
    TVector3 elec_dir(elec_px, elec_py, elec_pz); 
    elec_dir.Unit();
    true_electron_effective_angle = elec_dir.Angle(nu_dir) * 180 / 3.14159; 
    true_cos_electron_effective_angle = std::cos(elec_dir.Angle(nu_dir));

    // pion
   	TVector3 pion_dir(pion_px, pion_py, pion_pz); 
    pion_dir.Unit();

	true_pion_effective_angle = pion_dir.Angle(nu_dir) * 180 / 3.14159;
	true_cos_pion_effective_angle = std::cos(pion_dir.Angle(nu_dir));

    // opening angle
    true_electron_pion_opening_angle = pion_dir.Angle(elec_dir) * 180 / 3.14159; 
    true_cos_electron_pion_opening_angle = std::cos(pion_dir.Angle(elec_dir));
}

