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
		kCCNue1pi = 0,
		kCCNueNpi = 1,
		kCCNuepizero = 2,
		kCCNueOther = 3,
		kCCNumupizero = 4,
		kCCNumuOther = 5,
		kNCpizero = 6,
		kNCOther = 7,
		kOutFV = 8,
		kCosmic = 9,
		kUnknown = 10
	};

	// PlotVariable enums
	enum PlotVariableEnums {
		kSliceID,
		kNuE,
		kNShower,
		kNTrack,
		kContainedFraction,
		kTopologicalScore,
		kCosmicImpactParameter
	};

}; 

#endif