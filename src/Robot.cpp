#pragma once
 #include <WPILib.h>
 #include "Teleop.h"
 #include "Intake.h"
// #include "DriveBase.h"


 /**
6  * This is a demo program showing the use of the RobotDrive class.
7  * The SampleRobot class is the base of a robot application that will automatically call your
8  * Autonomous and OperatorControl methods at the right time as controlled by the switches on
9  * the driver station or the field controls.
10  *
11  * WARNING: While it may look like a good choice to use for your code if you're inexperienced,
12  * don't. Unless you know what you are doing, complex code will be much more difficult under
13  * this system. Use IterativeRobot or Command-Based instead if you're new.
14  */
 class Robot: public IterativeRobot {

 public:


	 void RobotInit(){
//		 Intake::init();
		 Teleop::init();
//		 DriveBase::init();
		 DriveBase::switchGear(false);

	 }
	 void TeleopPeriodic(){
		 Teleop::run();
	 }

 };


 START_ROBOT_CLASS(Robot)
