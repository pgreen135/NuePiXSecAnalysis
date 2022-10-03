#ifndef EVENTCONTAINER_H
#define EVENTCONTAINER_H

// class to read and contain events from the pandora ntuples
// event information can then be passed as required to other parts of the analysis code
// variables public for ease of access

#include <string>

#include <TTree.h>

#include "Utility.h"

class EventContainer {

public:
	
	// ----------------------------------
	
	// Constructor
	EventContainer(TTree *tree, const Utility &utility);

	// Destructor
	~EventContainer(){};

	// Functions to classify the event
	void  EventClassifier();
	Utility::ClassificationEnums getEventClassification();
    
    
    // ----------------------------------

    // -- Utility --
    Utility _utility;


	// --- Event classification ---
	Utility::ClassificationEnums classification;


	// --- Event information
	int run, sub, evt;			// run, subrun, event numbers

	// --- MC Truth ---

	// truth interaction properties
	int nu_pdg;					// Truth: neutrino pdg
	int ccnc; 					// Truth: CC or NC interaction
	int interaction;			// Truth: interaction code from GENIE
	float nu_e;        			// Truth: Neutrino Energy [GeV]
  	
  	int nmuon; 					// Truth: number of muons
  	int nelec; 					// Truth: number of electrons
  	int npion; 					// Truth: number of charged pions
  	int npi0; 					// Truth: number of neutral pions
  	int nproton; 				// Truth: number of protons

  	// truth interaction vertex
  	float true_nu_vtx_sce_x;     // True Neutrino Vtx Space Charge x
  	float true_nu_vtx_sce_y;     // True Neutrino Vtx Space Charge y
  	float true_nu_vtx_sce_z;     // True Neutrino Vtx Space Charge z

  	// --- Software trigger [MC only] ---
  	int swtrig;     			// Software Trigger
    int swtrig_pre;     		// Software Trigger before change -- Run 1
    int swtrig_post;     		// Software Trigger after change

    // --- Common optical filter [MC only] ---
    float opfilter_pe_beam; // Common Optical Filter (beam window)
    float opfilter_pe_veto; // Common Optical Filter (michel veto)

  	// --- Slice information ---
  	// number
  	int nslice;		// Reco: number of neutrino slices identified by the SliceID. Values are 0 or 1.
    int n_tracks;   // Reco: number of tracks identified with a track score cut
    int n_showers;  // Reco: number of showers with a shower score cut

  	// slice quality
  	float nu_purity_from_pfp;   // Neutrino Purity from PFP (how many out of all the hits are the neutrino)

  	// --- Neutrino Reconstruction ---
  	// reconstructed neutrino vertex, space charge corrected
  	float reco_nu_vtx_sce_x;    // Reco: neutrino Vtx Space Charge x
    float reco_nu_vtx_sce_y;    // Reco: neutrino Vtx Space Charge y
    float reco_nu_vtx_sce_z;    // Reco: neutrino Vtx Space Charge z

    float contained_fraction;   // Reco: hits in PFParticles contained in the fiducial volume over the total number of clustered hits in the slice

    // --- Cosmic Reconstruction
    float topological_score;  	// Reco: topological Score
    float CosmicIPAll3D;        // Reco: 3D distance of shower start from closest spacepoint of any pfp not in the neutrino slice

};

#endif

