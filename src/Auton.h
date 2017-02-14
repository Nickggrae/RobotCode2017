#pragma once
#include "Shared.h"
#include "DriveBase.h"
#include <ctime>

class Auton {
public:
	// Initialize the drivebase, set's starttime to current time, set's motor speed to half
	static void init();

	// Loops through for the whole time of autonomous
	static void periodic(int routine);

	enum AutonRoutines
	{
		RedLeft = 3,
		RedMiddle = 1,
		RedRight = 2,
		BlueLeft = 0,
		BlueMiddle = 4,
		BlueRight = 5
	};
};
