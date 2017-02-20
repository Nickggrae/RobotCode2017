/*
 * Teleop.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: Academy HS Robotics
 */
#include "Teleop.h"
#include "Shooter.h"
#include "Intake.h"
#include "udpServer.hpp"
#include "Copernicus.h"
#include <iostream>

//#include "DriveBase.h"

int prevButton1 = 0;
int prevButton2 = 0;
int prevButton3 = 0;

double target = 3200;
//double max_d = 0;
//double min_d = 1000000;
bool passedTarget = false;

bool isDriving = false;
double angle = 0.0;
bool isAgitatorOn = false;

Joystick* Teleop::joy;
Joystick* Teleop::stick;
Joystick* Teleop::extremePro;

void Teleop::init() {
	Teleop::joy = new Joystick(0);
	Teleop::extremePro = new Joystick(1);
	SmartDashboard::PutNumber("Angle",0.0);
	SmartDashboard::PutNumber("Shooter",0.0);
	DriveBase::disableBrake();
}
/*lt intake off
//rt intake on
 * button for reversing the intake
 * get amperage for the backup climber stop
 * limit switch to work for stopping the climber
 * brain storm stopping the rope
 * 2nd joy stick for manual override y axis = rpm
 * manuel shooting on top and trigger to automatically shooting
 *
*/

void Teleop::run(double turnAngle) {
	double leftDrive = Teleop::joy->GetRawAxis(5);
	double rightDrive = Teleop::joy->GetRawAxis(1);

	//Dead zone
	if(leftDrive < 0.1 && leftDrive > -0.1)
		leftDrive = 0.0;
	if(rightDrive < 0.1 && rightDrive > -0.1)
		rightDrive = 0.0;

	DriveBase::drive(leftDrive, rightDrive);
	SmartDashboard::PutNumber("left drive", leftDrive);
	SmartDashboard::PutNumber("right drive", rightDrive);

	//toggle for the floor intake
	if(prevButton1 < Teleop::joy->GetRawButton(1)){
		Intake::getInstance().toggleIntake();
	}
	prevButton1 = Teleop::joy->GetRawButton(1);

	//toggle for the salad spinner
	if(prevButton3 <Teleop::joy->GetRawButton(4)){
		Intake::getInstance().toggleSaladSpinner();
	}
	prevButton3 = Teleop::joy->GetRawButton(4);


	bool climberUpButton = Teleop::extremePro->GetRawButton(8);
	bool climberDownButton = Teleop::extremePro->GetRawButton(7);
	bool climberUpSlowButton = Teleop::extremePro->GetRawButton(10);
	bool climberOffButton = Teleop::extremePro->GetRawButton(9);
//#gotta fix the code cause the code is bad to the bone!!!!!!!!!!!!
	if(climberUpButton && !climberDownButton && !climberUpSlowButton && !climberOffButton) {
		Climber::getInstance().turnOn();
	}
	else if (!climberUpButton && climberDownButton && !climberUpSlowButton && !climberOffButton) {
		Climber::getInstance().back();
	}
	if(!climberUpButton && !climberDownButton && climberUpSlowButton && !climberOffButton)
	{
		Climber::getInstance().turnOnSlow();
	}
	if(!climberUpButton && !climberDownButton && climberUpSlowButton && !climberOffButton){
		Climber::getInstance().turnOff();
	}

//	if(prevButton2 < Teleop::stick->GetRawButton(7)){
//		Climber::turnOn();
//	}

	bool rightButton = Teleop::joy->GetRawButton(6);
	bool leftButton = Teleop::joy->GetRawButton(5);
	if(rightButton && !leftButton){
		if(!DriveBase::getGearState()){
			DriveBase::switchGear(true);
//			frc::Wait(.1);
		}
	}
	else if(!rightButton && leftButton){
		if(DriveBase::getGearState()){
			DriveBase::switchGear(false);
//			frc::Wait(.1);
		}
	}
	bool rightSlider = Teleop::joy->GetRawButton(2);
	bool leftSlider = Teleop::joy->GetRawButton(3);
	if(rightSlider && !leftSlider){
		if(!DriveBase::getSliderState()){
			DriveBase::switchSlider(true);
		}
	}
	else if(!rightSlider && leftSlider){
		if(DriveBase::getSliderState()){
			DriveBase::switchSlider(false);
		}
	}
	SmartDashboard::PutBoolean("Slider State", DriveBase::getSliderState());

//	if((Shooter::get() > target) && !passedTarget)
//	{
//		passedTarget = true;
//	}

	if(joy->GetRawButton(5))
	{
		DriveBase::ahrs->ResetDisplacement();
	}

	if(turnAngle != angle)
	{
		angle = turnAngle;
		if(angle < 180 && angle > -180)
		{
			if(turnAngle != 666)
				Shooter::getInstance().setangle(angle);
			else
				std::cout << "TA DA~" << std::endl;
		}
	}

	SmartDashboard::PutNumber("Vision Angle", angle);
	SmartDashboard::PutNumber("Turn Angle", turnAngle);
	SmartDashboard::PutNumber("Attempted Angle", angle + Shooter::getInstance().getangle());
	SmartDashboard::PutNumber("Shooter Angle", Shooter::getInstance().getangle());

	Copernicus::setFlywheelRPM(Shooter::getInstance().get());


	double shooter = Teleop::extremePro->GetRawAxis(1);
//	double shooter = SmartDashboard::GetNumber("Shooter", 0.0);
	if(shooter > 0.1)
	{
		target = shooter;
	}

	/*if(Teleop::extremePro->GetRawButton(12))
	{
		min = 100000;
		max = 0;
	}*/

//	double extreme_y = extremePro->GetRawAxis(1);
//	double scaled_y = (extreme_y*0.5)+0.5;
	// -1 to 1
	if(Teleop::extremePro->GetRawButton(2))
	{
		Shooter::getInstance().agitatorOn();
	}
	else
		Shooter::getInstance().agitatorOff();
	//Accepts rpm setting
//	double setRPM = scaled_y * 6000.0;
	Shooter::getInstance().set(shooter);
	double currentRPM = Shooter::getInstance().get();
	/*if(passedTarget)
	{

		if(max_d < currentRPM)
			max_d = currentRPM;
		if(min_d > currentRPM)
			min_d = currentRPM;
		//std::cout << currentRPM << "," << max << "," << min << "," << max - min << "\n";
	}*/
	SmartDashboard::PutNumber("Shooter speed", currentRPM);
	SmartDashboard::PutNumber("YawTeleop", DriveBase::getYaw());

	//SmartDashboard::PutNumber("MaxRPM", max);
	//SmartDashboard::PutNumber("MinRPM", min);
}
