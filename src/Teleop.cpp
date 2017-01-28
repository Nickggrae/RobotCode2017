/*
 * Teleop.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: Academy HS Robotics
 */
#include "Teleop.h"
#include "DriveBase.h"
#include "Shooter.h"

int Prev_Button_1 = 0;

Joystick* Teleop::joy;
void Teleop::init() {
	Teleop::joy = new Joystick(0);
	DriveBase::init();

}
void Teleop::run() {
	double leftDrive = Teleop::joy->GetRawAxis(1);
	double rightDrive = Teleop::joy->GetRawAxis(5);
	DriveBase::drive(leftDrive, rightDrive);

	bool Switch = Teleop::joy->GetRawButton(1);
	if(Switch == true){
		if(DriveBase::getGearState()){
			DriveBase::switchGear(false);

		}
		else{
			DriveBase::switchGear(true);
		}
		SmartDashboard::PutBoolean("Gear State", DriveBase::getGearState());
	}
	SmartDashboard::PutBoolean("Button", Switch);
//	bool Shooter = joy->GetRawButton(1);
//	if(Shooter > Prev_Button_1){
//		if(DriveBase::shooterOn() == true){
//			DriveBase::setShooter(false);
//		}
//		else{
//			DriveBase::setShooter(true);
//		}
//	}

}


