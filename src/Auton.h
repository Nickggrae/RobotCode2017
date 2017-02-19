#pragma once
#include "Shared.h"
#include "DriveBase.h"
#include <ctime>

class Auton {
	std::time_t startTime; //Used to calculate delay through time
	int state; //Number the state machine is at
	//singleton- hide constructor and copy constructor
	Auton(): startTime(0), state(10) { init(); }
	Auton(Auton const&);
	void operator=(Auton const&);

	void init();
	//POWER ALWAYS HAS TO BE POSITIVE
	void TurnRight(double power = 0.5);
	void TurnLeft(double power = 0.5);
	void DriveForward(double power = 0.5);
	void DriveBackwards(double power = 0.5);
	void StayStill();

	bool waited(double seconds); //Used to wait x seconds returns true if time period has expired

public:
	static Auton& getInstance();

	// Initialize the drivebase, set's starttime to current time, set's motor speed to half

	//it has auton so it isnt the same as the enums it looks bad sorry
	void TestYaw();
	void NothingAuton();
	void RedLeftAuton();
	void RedMiddleAuton();
	void RedRightShootAuton();
	void RedRightGearAuton();

	void BlueLeftShootAuton();
	void BlueLeftGearAuton();
	void BlueMiddleAuton();
	void BlueRightAuton();


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
