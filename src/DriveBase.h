#pragma once

#include "Shared.h"
#include <Compressor.h>
//#include <Solenoid.h>
#include <DoubleSolenoid.h>
#include <AHRS.h>
//#include "DriveBase.cpp"


class DriveBase {
	void init();
	//singleton- hide constructor and copy constructor
	 DriveBase() { init(); }
	 DriveBase(DriveBase const&);
	 void operator=(DriveBase const&);

	//initializes front left
	 CANTalon* fl;

	//initializes rear left
	 CANTalon* rl;

	//initializes front right
	 CANTalon* fr;

	//initializes rear right
	 CANTalon* rr;

	//initializes robot drive
	 frc::RobotDrive* robotDrive;

	//initializes solenoid for pneumatics
	 frc::DoubleSolenoid* solenoid;

	 frc::DoubleSolenoid* solenoid2;

	//initializes the gear state
	 int gearState;

	 int sliderState;

public:
	 AHRS *ahrs;
	 static DriveBase& getInstance();

	 void drive(double left, double right); //tank drive robot drive with left and right side

	 void switchGear(bool gear); //set piston forward if true and reverse if false

	 int getGearState(); //check whether gear has been released or not

	 double getEncoderfl(); //gets the encoder position of encoder front left

	 void resetEncoderfl(); //resets the front left encoder

	 double getEncoderfr(); // get the encoder position of encoder front right

	 void resetEncoderfr(); //resets the front right encoder

	 void enable(); // enables the DriveBase. TURNED ON BY DEFAULT

	 void disable(); // disables the DriveBase CANTalons

	 double getPitch(); // gets Pitch

	 double getYaw(); // gets Yaw

	 double getRoll(); // gets Roll

	 void resetAHRS(); // resets NavX

	 double DisplacementX();

	 double DisplacementY();

	 double DisplacementZ();

	 double getAccelX();

	 double getAccelY();

	 double getAccelZ();

	 void talonEnable();

	 void talonDisable();

	 double isTalonEnabled();

//Usaid if you are reading this it was a test just get rid of it
	 double velocityX();

	 double velocityY();

	 double velocityZ();

	 void switchSlider(bool slider);

	 int getSliderState();

	//Enable Brake Mode
	 void enableBrake();

	//Disable Brake Mode
	 void disableBrake();

	 bool isCompressorOn();
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
