
#ifndef INCLUDE_DRIVE_BASE_HPP_
#define INCLUDE_DRIVE_BASE_HPP_

#include <Shared.hpp>
#include <Compressor.h>
#include <DoubleSolenoid.h>
#include <AHRS.h>


namespace DriveBase {
	void init();

	void drive(double left, double right); //tank drive robot drive with left and right side

	void switchGear(bool gear); //set piston forward if true and reverse if false

	int getGearState(); //check whether gear has been released or not

	double getEncoderflInches(); //gets the encoder position of encoder front left

	void resetEncoderfl(); //resets the front left encoder

	double getEncoderfrInches(); // get the encoder position of encoder front right

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

	AHRS *getAHRS();

	int getSliderState();

	//Enable Brake Mode
	void enableBrake();

	//Disable Brake Mode
	void disableBrake();

	bool isCompressorOn();
};

#endif /* INCLUDE_DRIVE_BASE_HPP_ */
