/*
 * teleopInit.h
 *
 *  Created on: Jan 24, 2017
 *      Author: Academy HS Robotics
 */

#ifndef SRC_TELEOP_H_
#define SRC_TELEOP_H_

#include "Shared.h"

class Teleop{
	static Joystick* joy;
public:
	static void init();
	static void run();
};



#endif /* SRC_TELEOP_H_ */
