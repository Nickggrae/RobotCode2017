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
//#include <asio.hpp>
//#include <bind.hpp>
//#include <shared_ptr.hpp>
//#include <rapidjson/document.h>
//#include <rapidjson/writer.h>
//#include <rapidjson/stringbuffer.h>
//#include <thread>
//#include <chrono>
//#include <iostream>
//#include <udpServer.h>

class Teleop{
	static Joystick* joy;
public:
	static void init();
	static void run();
};



#endif /* SRC_TELEOP_H_ */