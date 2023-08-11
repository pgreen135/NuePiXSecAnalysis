#include "../include/Utility.h"

#include <iostream>
#include <numeric>

// Constructor
Utility::Utility() {
	
	std::cout << "Initialising Utilities Class" << std::endl;

}

// ------------------------------------------------------------------------------

// Function to check if point is within FV
bool Utility::inFV(const double x, const double y, const double z) const {
	// check the point is in the boundary 										
	// NTuples definition
	if ( x   >= 10 && x <= 246
		 && y   >= -101 && y <= 101
	  	 && z   >= 10 && z <= 986  ) {
	  	return true;
	}
	else return false;
}

// ------------------------------------------------------------------------------

// Function to check whether a track is exiting
// Currently same definition as FV, but could be altered
bool Utility::isExiting(const double x, const double y, const double z) const {
	// NTuples definition
	//if ( x   >= 10 && x <= 246
	//	 && y   >= -101 && y <= 101
	//  	 && z   >= 10 && z <= 986  ) {
	//  	return true;
	//}
	// containment definition (10 cm from borders)
	if ( x   >= 10 && x <= 246
		 && y   >= -106 && y <= 106
	  	 && z   >= 10 && z <= 1026  ) {
	  	return true;
	}
	else return false;
}

// ------------------------------------------------------------------------------

// Function to check whether number is valid
bool Utility::isNumber(float input) {

	// infinite 
	if (std::isinf(input)) {
		return false;
	}

	// nan 
	if (std::isnan(input)) {
		return false;
	}

	return true;
}