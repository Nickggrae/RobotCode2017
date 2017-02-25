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

	 frc::Compressor* compressor;


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
