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
	tree->SetBranchAddress("npion", &npion);
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

    tree->SetBranchAddress("shr_distance", &shr_distance);
    tree->SetBranchAddress("shr_score", &shr_score);
    tree->SetBranchAddress("shr_energy", &shr_energy);    
    tree->SetBranchAddress("hits_ratio", &hits_ratio);
    tree->SetBranchAddress("shrmoliereavg", &shrmoliereavg);

    tree->SetBranchAddress("shr_tkfit_dedx_Y", &shr_tkfit_dedx_Y);
    tree->SetBranchAddress("shr_tkfit_dedx_V", &shr_tkfit_dedx_V);
    tree->SetBranchAddress("shr_tkfit_dedx_U", &shr_tkfit_dedx_U);

    tree->SetBranchAddress("shr_tkfit_nhits_Y", &shr_tkfit_nhits_Y);
    tree->SetBranchAddress("shr_tkfit_nhits_V", &shr_tkfit_nhits_V);
    tree->SetBranchAddress("shr_tkfit_nhits_U", &shr_tkfit_nhits_U);

    tree->SetBranchAddress("trk_len", &trk_len);
    tree->SetBranchAddress("trk_distance", &trk_distance);

    tree->SetBranchAddress("trk_bragg_p", &trk_bragg_p);
    tree->SetBranchAddress("trk_bragg_mu", &trk_bragg_mu);
    tree->SetBranchAddress("trk_bragg_pion", &trk_bragg_pion);

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

}

// Function to classify the event
void EventContainer::EventClassifier(){

	// --- MC classification --
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
					// classify as CC nue 1pi
					classification = Utility::kCCNue1pi; // std::make_pair("CCNue1pi", _utility.kCCNue1pi);
					return;
				}
				// multi pion
				else if (npion > 1) {
					// classify as CC nue Npi
					classification = Utility::kCCNueNpi; // std::make_pair("CCNueNpi", _utility.kCCNueNpi);
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

	// Catch any events without classification
	// Shouldn't be any of these! Will cause issues.
	classification = Utility::kUnknown; // std::make_pair("Unknown", _utility.kUnknown);
	std::cout << "Warning: Unknown Event" << std::endl;
	return;
}

// Function to get event classification
Utility::ClassificationEnums EventContainer::getEventClassification() {
	EventClassifier();
	return classification;
}


// Function to evaluate derived variables
void EventContainer::populateDerivedVariables(){

	// populate derived variables
    auto it = std::max_element(trk_len_v->begin(), trk_len_v->end());
    longestTrackIndex = std::distance(trk_len_v->begin(), it);

    trk_llr_pid_score = trk_llr_pid_score_v->at(longestTrackIndex); 	// LLR PID Score
    trk_score = trk_score_v->at(longestTrackIndex); 					// Pandora track score
    trk_distance_alt = trk_distance_v->at(longestTrackIndex); 			// Distance from vertex
    trk_bragg_mu_alt = trk_bragg_mu_v->at(longestTrackIndex); 				

    


}




