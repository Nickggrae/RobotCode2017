/*
 * teleopInit.h
 *
 *  Created on: Jan 24, 2017
 *      Author: Academy HS Robotics
 */
#pragma once
#ifndef SRC_TELEOP_H_
#define SRC_TELEOP_H_
#include "DriveBase.h"
#include "Shared.h"
#include "Climber.h"
#include "Intake.h"
#include "Shooter.h"

class Teleop{
	static Joystick* stick;
	static Joystick* joy;
	static Joystick* extremePro;
//	Intake &intake = Intake::getInstance();
public:
	static void init();
	static void run(double angle);
};

#endif /* SRC_TELEOP_H_ */
