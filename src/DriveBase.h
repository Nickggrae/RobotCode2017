#pragma once

#include "Shared.h"
#include <Compressor.h>
//#include <Solenoid.h>
#include <DoubleSolenoid.h>
#include <AHRS.h>
//#include "DriveBase.cpp"

class DriveBase {
public:
	//initializes front left
	static CANTalon* fl;

	//initializes rear left
	static CANTalon* rl;

	//initializes front right
	static CANTalon* fr;

	//initializes rear right
	static CANTalon* rr;

	//initializes robot drive
	static frc::RobotDrive* robotDrive;

	//initializes solenoid for pneumatics
	static frc::DoubleSolenoid* solenoid;

	static frc::DoubleSolenoid* solenoid2;

	//initializes the gear state
	static int gearState;

	static int sliderState;

public:

	//starts navX
	static AHRS *ahrs;

	//initializes base robot code
	static void init();

	static void drive(double left, double right); //tank drive robot drive with left and right side

	static void switchGear(bool gear); //set piston forward if true and reverse if false

	static int getGearState(); //check whether gear has been released or not

	static double getEncoderfl(); //gets the encoder position of encoder front left

	static void resetEncoderfl(); //resets the front left encoder

	static double getEncoderfr(); // get the encoder position of encoder front right

	static void resetEncoderfr(); //resets the front right encoder

	static void enable(); // enables the DriveBase. TURNED ON BY DEFAULT

	static void disable(); // disables the DriveBase CANTalons

	static double getPitch(); // gets Pitch

	static double getYaw(); // gets Yaw

	static double getRoll(); // gets Roll

	static void resetAHRS(); // resets NavX

	static double DisplacementX();

	static double DisplacementY();

	static double DisplacementZ();

	static double getAccelX();

	static double getAccelY();

	static double getAccelZ();

	static void talonEnable();

	static void talonDisable();

	static double isTalonEnabled();

//Usaid if you are reading this it was a test just get rid of it
	static double velocityX();

	static double velocityY();

	static double velocityZ();

	static void switchSlider(bool slider);

	static int getSliderState();

	//Enable Brake Mode
	static void enableBrake();

	//Disable Brake Mode
	static void disableBrake();
};

/**TODO:
 * Create DriveBase class that:
 * has a constructor that:
 *  - initializes all CANTalons used on DriveBase
 *  - initializes all sensors used on DriveBase (Encoders, Accel, Gyro)
 *  - resets sensors
 *  - configures CANTalons (Followers)
 * has a drive(double left, double right)
 *  - Drives the robot in TankDrive using the left/right provided
 * has a resetGyro()
 *  - resets the gyro
 * has a resetAccel()
 *  - resets the accel
 * has a getGyro()
 *  - returns a DOUBLE with the current Gyro value
 * has a getAccel()
 *  - returns a DOUBLE with the current Accel value
 * has a enable()
 *  - enables the DriveBase. TURNED ON BY DEFAULT
 * has a disable()
 *  - disables the DriveBase CANTalons
 *\]
 * QUESTIONS:
 *  - Have a PID mode to set position encoders/gyro/accel should be at?
 *    = would need a set(double position) function as well as a PIDMode() function and a VbusMode() function to swith between the two
 */
