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
	//singleton- hide constructor and copy constructor
	Teleop() { init(); }
	Teleop(Teleop const&);
	void operator=(Teleop const&);

	Joystick* joy;
	Joystick* extremePro;
	int prevButton1 = 0;
	int prevButton2 = 0;
	int prevButton3 = 0;
	int prevButton4 = 0;
	double angle = 0.0;
	DriveBase & driveBase = DriveBase::getInstance();
	Intake & intake = Intake::getInstance();
	Shooter & shooter = Shooter::getInstance();
	Climber & climber = Climber::getInstance();

	void init();
public:
	static Teleop& getInstance();

	void run(double angle);
};

#endif /* SRC_TELEOP_H_ */
