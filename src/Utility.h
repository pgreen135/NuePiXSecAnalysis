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
	// ----------------------------------


	// Event classification enums
	enum ClassificationEnums {
		kCCNue1pi,
		kCCNueNpi,
		kCCNuepizero,
		kCCNueOther,
		kCCNumupizero,
		kCCNumuOther,
		kNCpizero,
		kNCOther,
		kOutFV,
		kCosmic,
		kBeamOff,
		kUnknown
	};

	// PlotVariable enums
	enum PlotVariableEnums {
		kSliceID,
		kNuE,
		kNShower,
		kNTrack,
		kContainedFraction,
		kTopologicalScore,
		kCosmicImpactParameter,
		kShowerScore,
		kShowerEnergy,
		kHitRatio,
		kMoliereAverage,
		kTrackLength,
		kTrackBraggPion,
		kTrackBraggP,
		kTrackBraggMu,
		kLLRPID,
		kTrackScore,
		kTrackDistance
	};

}; 

#endif