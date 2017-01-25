/*
 * Teleop.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: Academy HS Robotics
 */
#include "Teleop.h"
#include "DriveBase.h"

void Teleop::init() {
	joy = new Joystick(1);
	DriveBase::init();

}
void Teleop::run() {
	double leftDrive = joy->GetRawAxis(1);
	double rightDrive = joy->GetRawAxis(5);
	DriveBase::drive(leftDrive, rightDrive);

}


