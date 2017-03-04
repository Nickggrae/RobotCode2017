#pragma once
#include <DriveBase.hpp>
#include <Shared.hpp>
#include <ctime>

#define LEFT_POWER_OFFSET	0.0
#define RIGHT_POWER_OFFSET	0.02
namespace Auton {
	void init();
	//POWER ALWAYS HAS TO BE POSITIVE
	void TurnRight(double power = 0.5);
	void TurnLeft(double power = 0.5);
	void DriveForward(double power = 0.5);
	void DriveBackwards(double power = 0.5);
	void StayStill();

	bool waited(double seconds); //Used to wait x seconds returns true if time period has expired
	bool travelled(double inches);
	// Initialize the drivebase, set's starttime to current time, set's motor speed to half

	//it has auton so it isnt the same as the enums it looks bad sorry
	void Test();
	void NothingAuton();
	void RedLeftAuton();
	void RedMiddleAuton();
	void RedRightShootAuton();
	void RedRightGearAuton();

	void BlueLeftShootAuton();
	void BlueLeftGearAuton();
	void BlueMiddleAuton();
	void BlueRightAuton();
};
