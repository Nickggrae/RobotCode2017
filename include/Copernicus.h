/*
 * teleopInit.h
 *
 *  Created on: Jan 24, 2017
 *      Author: Academy HS Robotics
 */

#ifndef SRC_COPERNCIUS_H_
#define SRC_COPERNICUS_H_

#include <Shared.hpp>
#include <memory>

#include <SmartDashboard/SmartDashboard.h>

/**
 * Sends data to the dashboard. To control how it does that, define either COPERNICUS_USE_UDP for John's UDP server code or COPERNICUS_USE_TABLES for Liav's NetworkTables before including Copernicus.h. If you don't define a macro, it will default to COPERNICUS_USE_TABLES. You can also defined COPERNICUS_USE_NONE to make it not send anything.
 * */
class Copernicus{
	//the way this works is that we have the front end functions which are the same and then we have the implemenation ones. The architecture is based on a singleton/PIMPL approach which changes the pointer type based on the macro.
public:
	/**
	For Copernicus::setMode(const Mode)
	*/
	enum Mode{
		DISABLED = 0,
		TELEOP = 1,
		AUTON = 2
	};

	/**
	Set whether the floor intake is running
	*/
	static void setFloorIntake(const bool intaking);

	/**
	Set whether the top (turret) intake is running. Whether this includes the agitator should be discussed with the drivers
	*/
	static void setTopIntake(const bool intaking);

	/**
	Set the PSI of the system.
	*/
	static void setPressure(const double psi);

	/**
	Set whether the drive base is in high gear, where true is high gear and false is low gear
	*/
	static void setHighGear(const bool gear);

	/**
	What camera stream to use. True is to ues the front gear camera, and false is the turret camera.
	*/
	static void setStream(const bool stream);

	/**
	Set the offset of the crosshair, where 1 is the farthest right and -1 is the farthest left. 0 is the center of the screen. This should come from vision.
	*/
	static void setCrosshairOffset(const double offset);

	/**
	Set the angle of the turret in RADIANS.
	*/
	static void setTurretAngle(const double radians);//dont blame me if you accidently give it degrees - liav (2/5/17)

	/**
	Set the actual RPM of the flywheel based on the encoder
	*/
	static void setFlywheelRPM(const int rpm);

	/**
	Set what vision thinks the flywheel RPM should be.
	*/
	static void setTargetRPM(const int rpm);

	/**
	Set the actual RPM of the left wheels on the drivebase based on the encoder.
	*/
	static void setLeftRPM(const int rpm);

	/**
	Set the actual RPM of the right wheels on the drivebase based on the encoder
	*/
	static void setRightRPM(const int rpm);

	/**
	Set whether the robot is currently holding a gear, where true means the robot has a gear and false is the robot has no gear. This should not be confused with whether the drive base in high gear
	*/
	static void setHasGear(const bool hasGear);

	/**
	Set which mode the robot is currently in. (DISABLED, TELEOP, AUTON)
	*/
	static void setMode(const Mode mode);

	/**
	This should be called every iteration, no matter if the robot is enabled.
	*/
	static void update();
private:
	static void setNumber(const char* key, const double val);
	static void setBool(const char* key, const bool val);
	static void setString(const char* key, const char* val);

	static void createTable();

	static std::shared_ptr<NetworkTable> table;
};

#endif /* SRC_TELEOP_H_ */
