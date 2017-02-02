/*
 * teleopInit.h
 *
 *  Created on: Jan 24, 2017
 *      Author: Academy HS Robotics
 */

#ifndef SRC_COPERNCIUS_H_
#define SRC_COPERNICUS_H_
#include "Shared.h"
#include <string>

class Copernicus{
public:
	static void setNumber(const char* key, const double val);
	static void setBool(const char* key, const bool val);
	static void setString(const char* key, const char* val);
private:
	static void createTable();

	static NetworkTable* table;
};

#endif /* SRC_TELEOP_H_ */
