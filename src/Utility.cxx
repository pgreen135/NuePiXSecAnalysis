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
	if ( x   >= 8.45 && x <= 244.8
	  && y   >= -106.5 && y <= 106.5
	  && z   >= 5 && z <= 1031.8  ) {
	  return true;
	}  
	else return false;
}