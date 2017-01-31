/*
 * Teleop.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: Academy HS Robotics
 */
#include "Teleop.h"
#include "Intake.h"

int prevButton1 = 0;

Joystick* Teleop::joy;
void Teleop::init() {
	Teleop::joy = new Joystick(0);
	DriveBase::init();
	Intake::init();
}
void Teleop::run() {
	double leftDrive = Teleop::joy->GetRawAxis(1);
	double rightDrive = Teleop::joy->GetRawAxis(5);
	DriveBase::drive(leftDrive, rightDrive);

	if(prevButton1 < Teleop::joy->GetRawButton(1)){
		if (Intake::isOn()){
			Intake::turnOff();
		}
		else{
			Intake::turnOn();
		}
	}
	prevButton1 = Teleop::joy->GetRawButton(1);

	bool rightButton = Teleop::joy->GetRawButton(6);
	bool leftButton = Teleop::joy->GetRawButton(5);
	if(rightButton && !leftButton){
		if(!DriveBase::getGearState()){
			DriveBase::switchGear(true);
//			frc::Wait(.1);
		}
	}
	else if(!rightButton && leftButton){
		if(DriveBase::getGearState()){
					DriveBase::switchGear(false);
//					frc::Wait(.1);
		}
	}

//	SmartDashboard::PutBoolean("Usaid Wanted It", intakebutton);
//	bool Shooter = joy->GetRawButton(1);
//	if(Shooter > Prev_Button_1){
//		if(DriveBase::shooterOn() == true){
//			DriveBase::setShooter(false);
//		}
//		else{
//			DriveBase::setShooter(true);
//		}
//	}

	frc::Wait(0.005);


}


