/*
 * Teleop.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: Academy HS Robotics
 */
#include "Teleop.h"
#include "DriveBase.h"
#include "Shooter.h"
#include "Intake.h"
#include "udpServer.hpp"
#include "Copernicus.h"
#include <iostream>

Teleop& Teleop::getInstance(){
  static Teleop instance;
  return instance;
}

void Teleop::init() {
	joy = new Joystick(0);
	extremePro = new Joystick(1);
	SmartDashboard::PutNumber("Angle",0.0);
	SmartDashboard::PutNumber("Shooter",0.0);
	driveBase.disableBrake();
}

void Teleop::run() {
	double leftDrive = joy->GetRawAxis(1);
	double rightDrive = joy->GetRawAxis(5);

	//Dead zone
	if(leftDrive < 0.1 && leftDrive > -0.1)
		leftDrive = 0.0;
	if(rightDrive < 0.1 && rightDrive > -0.1)
		rightDrive = 0.0;

	driveBase.drive(leftDrive, rightDrive);
	SmartDashboard::PutNumber("left drive", leftDrive);
	SmartDashboard::PutNumber("right drive", rightDrive);

	//toggle for the floor intake
	if(prevButton1 < joy->GetRawButton(1)){
		intake.toggleIntake();
	}
	prevButton1 = joy->GetRawButton(1);

	//toggle for the salad spinner
	if(prevButton3 <joy->GetRawButton(4)){
		intake.toggleSaladSpinner();
	}
	prevButton3 = joy->GetRawButton(4);

	//toggle for the agitator
	if(prevButton4 <joy->GetRawButton(5)){
		shooter.agitatorToggle();
	}

	bool climberUpButton = extremePro->GetRawButton(8);
	bool climberOffButton = extremePro->GetRawButton(9);

	if (climberUpButton && !climberOffButton) {
		climber.ClimbUp();
	}

	if(!climberUpButton && climberOffButton){
		climber.turnOff();
	}

	bool rightButton = joy->GetRawButton(6);
	bool leftButton = joy->GetRawButton(5);
	if(rightButton && !leftButton){
		driveBase.getGearState();
	}
		if(!driveBase.getGearState()){
			driveBase.switchGear(true);
		}
	else if(!rightButton && leftButton){
		if(driveBase.getGearState()){
			driveBase.switchGear(false);
		}
	}
	bool rightSlider = joy->GetRawButton(2);
	bool leftSlider = joy->GetRawButton(3);
	if(rightSlider && !leftSlider){
		if(!driveBase.getSliderState()){
			driveBase.switchSlider(true);
		}
	}
	else if(!rightSlider && leftSlider){
		if(driveBase.getSliderState()){
			driveBase.switchSlider(false);
		}
	}
	SmartDashboard::PutBoolean("Slider State", driveBase.getSliderState());

	if(joy->GetRawButton(5))
	{
		driveBase.ahrs->ResetDisplacement();
	}

	SmartDashboard::PutNumber("Vision Angle", angle);
	SmartDashboard::PutNumber("Attempted Angle", angle + shooter.getangle());
	SmartDashboard::PutNumber("Shooter Angle", shooter.getangle());

	Copernicus::setFlywheelRPM(shooter.get());

	double currentRPM = shooter.get();

	SmartDashboard::PutNumber("Shooter speed", currentRPM);
	SmartDashboard::PutNumber("YawTeleop", driveBase.getYaw());
	SmartDashboard::PutNumber("FeedRPM", shooter.agitatorRPM());
}
