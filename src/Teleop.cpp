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


void Teleop::init() {
	joy = new Joystick(1);
	DriveBase::init();

}
void Teleop::run() {
	double leftDrive = joy->GetRawAxis(1);
	double rightDrive = joy->GetRawAxis(5);
	DriveBase::drive(leftDrive, rightDrive);

	bool Switch = joy->GetRawButton(0);
	if(Switch == true){
		if(DriveBase::getGearState()){
			DriveBase::switchGear(false);

		}
		else{
			DriveBase::switchGear(true);
		}

	}
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


