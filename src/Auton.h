#include "Shared.h"
#include "DriveBase.h"
#include <ctime>

class Auton {
	// Initialize the drivebase, set's starttime to current time, set's motor speed to half
	static void init();

	// Loops through for the whole time of autonomous
	static void periodic();
};
