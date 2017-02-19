#pragma once
#include "Shared.h"
#include "DriveBase.h"
#include <ctime>

class Auton {
public:

	static std::time_t startTime;
	// Initialize the drivebase, set's starttime to current time, set's motor speed to half
	static void init();

	//POWER ALWAYS HAS TO BE POSITIVE
	static void TurnRight(double power = 0.5);
	static void TurnLeft(double power = 0.5);
	static void DriveForward(double power = 0.5);
	static void DriveBackwards(double power = 0.5);
	static void StayStill();

	//it has auton so it isnt the same as the enums it looks bad sorry
	static void TestYaw();
	static void NothingAuton();
	static void RedLeftAuton();
	static void RedMiddleAuton();
	static void RedRightShootAuton();
	static void RedRightGearAuton();

	static void BlueLeftShootAuton();
	static void BlueLeftGearAuton();
	static void BlueMiddleAuton();
	static void BlueRightAuton();

	static bool waited(double seconds);


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
