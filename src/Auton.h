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
		Nothing = 0,
		RedLeft = 3,
		RedMiddle = 2,
		RedRight = 1,
		BlueLeft = 6,
		BlueMiddle = 5,
		BlueRight = 4
	};
};
