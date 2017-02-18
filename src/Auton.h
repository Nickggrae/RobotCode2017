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

	//it has auton so it isnt the same as the enums it looks bad sorry
	static void TurnRight(double power);
	static void TurnLeft(double power);
	static void DriveForward(double power);
	static void DriveBackwards(double power);
	static void StayStill();

	static void TestYaw();
	static void NothingAuton();
	static void RedLeftAuton();
	static void RedMiddleAuton();
	static void RedRightAuton();
	static void BlueLeftAuton();
	static void BlueMiddleAuton();
	static void BlueRightAuton();

	enum AutonRoutines
	{
		Nothing = 0,
		RedLeft = 4,
		RedMiddle = 2,
		RedRight = 1,
		BlueLeft = 6,
		BlueMiddle = 5,
		BlueRight = 3
	};
};
