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

	// Function to check whether number is valid
	bool isNumber(float input);
	
	// ----------------------------------

	// File types
	enum FileTypeEnums{
		kIntrinsic,
		kCCNCPiZero,
		kMC,
		kEXT,
		kDirt
	};

	// Run periods
	enum RunPeriodEnums {
		kRun1a,
		kRun1b,
		kRun2a,
		kRun2b,
		kRun3b,
		kRun4c,
		kRun4d,
		kRun5
	};

	// BDT types
	enum BDTEnums {
		kElectronPhoton,
		kPionProton,
		kPionProtonAlternate
	};

	// Event classification enums
	enum ClassificationEnums {
		kCCNue1pi0p,
		kCCNue1piNp,
		kCCNueNpi,
		kCCNuepizero,
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
		kSecondShowerPFPGeneration,
		kShowerDistance,
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
		kTrackEnergy,
		kSecondShowerNHit,
		kShowerLLRPID,
		kPionETrue,
		kNeutrinoETrue,
		kElectronETrue,
		kElectronNeutralPionBDT,
		kPionProtonBDT		
	};

}; 

#endif