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




