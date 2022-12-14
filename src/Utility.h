#ifndef UTILITY_H
#define UTILITY_H

// class containing utility functions and enum definitions
// allows suite of utilities to be included where required

class Utility {

public:	
	
	// ----------------------------------
	// Constructor
	Utility();

	// Destructor
	~Utility(){};

	// Function to check if point is within FV
	bool inFV(const double x, const double y, const double z) const;

	// Function to check if track is exiting
	bool isExiting(const double x, const double y, const double z) const;
	
	// ----------------------------------

	// File types
	enum FileTypeEnums{
		kMC,
		kEXT,
		kDirt
	};

	// Event classification enums
	enum ClassificationEnums {
		//kCCNue1pi,
		kCCNue1pi0p,
		kCCNue1piNp,
		kCCNueNpi,
		kCCNuepizero,
		kCCNue1p,
		kCCNueNp,
		kCCNueOther,
		kCCNumupizero,
		kCCNumuOther,
		kNCpizero,
		kNCOther,
		kOutFV,
		kCosmic,
		kBeamOff,
		kOutOfCryo,
		kUnknown
	};

	// PlotVariable enums
	enum PlotVariableEnums {
		kSliceID,
		kNuE,
		kNShower,
		kNTrack,
		kVertexInFV,
		kContainedFraction,
		kAssociatedHitsFraction,
		kTopologicalScore,
		kCosmicImpactParameter,
		kShowerScore,
		kShowerEnergy,
		kHitRatio,
		kMoliereAverage,
		kShowerEnergyRatio,
		kSecondShowerEnergy,
		kShowerdEdxMax,
		kNeutralPionInvariantMass,
		kTrackLength,
		kTrackScore,
		kTrackDistance,
		kTrackTheta,
		kTrackPhi,
		kTrackBraggPion,
		kTrackBraggP,
		kTrackBraggMu,
		kLLRPID,
		kTrackdEdx,
		kTrackWiggliness,
		kPi0InvMassDifference,
		kTrackShowerAngle,
		kNTrackDaughters,
		kSecondShowerNHit,
		kShowerLLRPID		
	};

}; 

#endif