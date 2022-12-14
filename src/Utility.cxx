#include "Utility.h"

#include <iostream>

// Constructor
Utility::Utility() {
	
	std::cout << "Initialising Utilities Class" << std::endl;

}

// ------------------------------------------------------------------------------

// Function to check if point is within FV
bool Utility::inFV(const double x, const double y, const double z) const {
	// check the point is in the boundary 										[TODO: make configurable]
	// Krishan's defintion
	//if ( x   >= 8.45 && x <= 244.8
	//  && y   >= -106.5 && y <= 106.5
	//  && z   >= 5 && z <= 1031.8  ) {
	//  return true;
	//}
	// Katrina's definition
	//if ( x   >= 10 && x <= 246
	//	 && y   >= -106 && y <= 106
	//  	 && z   >= 10 && z <= 1026  ) {
	//  	return true;
	//}
	// NTuples definition
	if ( x   >= 10 && x <= 246
		 && y   >= -101 && y <= 101
	  	 && z   >= 10 && z <= 986  ) {
	  	return true;
	}

	// To do: optimise this? 
	else return false;
}

// Function to check whether a track is exiting
// Same definition as FV, except without buffer in Z
// i.e. requirement on track start is more strict
bool Utility::isExiting(const double x, const double y, const double z) const {
	// 10cm 
	if ( x   >= 10 && x <= 246
		 && y   >= -106 && y <= 106
	  	 && z   >= 10 && z <= 1026  ) {
	  	return true;
	}
	else return false;
}