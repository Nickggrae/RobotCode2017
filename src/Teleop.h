/*
 * teleopInit.h
 *
 *  Created on: Jan 24, 2017
 *      Author: Academy HS Robotics
 */

#ifndef SRC_TELEOP_H_
#define SRC_TELEOP_H_
#include "DriveBase.h"
#include "Shared.h"
#include "Climber.h"

class Teleop{
	static Joystick* stick;
	static Joystick* joy;
public:
	static void init();
	static void run();
};



#endif /* SRC_TELEOP_H_ */
