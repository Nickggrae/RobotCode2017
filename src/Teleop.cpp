/*
 * Teleop.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: Academy HS Robotics
 */
#include "Teleop.h"
#include "Shooter.h"
#include "Intake.h"
#include <iostream>
//#include "DriveBase.h"

int prevButton1 = 0;
int prevButton2 = 0;

double target = 3200;
double max = 0;
double min = 1000000;
bool passedTarget = false;

Joystick* Teleop::joy;
Joystick* Teleop::stick;
Joystick* Teleop::extremepro;

void Teleop::init() {
	Teleop::joy = new Joystick(0);
	Teleop::extremepro = new Joystick(1);
	DriveBase::init();
	Shooter::init();
	Intake::init();
	Climber::init();
	SmartDashboard::PutNumber("Angle",0.0);
	SmartDashboard::PutNumber("Shooter",0.0);
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

void Teleop::run() {
	double leftDrive = Teleop::joy->GetRawAxis(1);
	double rightDrive = Teleop::joy->GetRawAxis(5);
	DriveBase::drive(leftDrive, rightDrive){
		DriveBase::robotDrive->TankDrive(leftDrive, rightDrive, false);
	}

	if(prevButton1 < Teleop::joy->GetRawButton(1)){
		Intake::toggleIntake();
	}
	prevButton1 = Teleop::joy->GetRawButton(1);

	bool climberUpButton = Teleop::extremepro->GetRawButton(8);
	bool climberDownButton = Teleop::extremepro->GetRawButton(7);

	if(climberUpButton && !climberDownButton) {
		Climber::turnOn();
	}
	else if (!climberUpButton && climberDownButton) {
		Climber::back();
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


	if((Shooter::get() > target) && !passedTarget)
	{
		passedTarget = true;
	}

//	SmartDashboard::PutNumber("XDisplacement", DriveBase::ahrs.GetDisplacementX());
//	SmartDashboard::PutNumber("YDisplacement", DriveBase::ahrs.GetDisplacementY());
//	SmartDashboard::PutNumber("ZDisplacement", DriveBase::ahrs.GetDisplacementZ());
//
	if(joy->GetRawButton(5))
	{
		DriveBase::ahrs->ResetDisplacement();
	}
//	SmartDashboard::PutBoolean("Usaid Wanted It", intakebutton);
//	bool Shooter = joy->GetRawButton(1);
//	if(Shooter > Prev_Button_1){
//		if(DriveBase::shooterOn() == true){
//			DriveBase::setShooter(false);
//		}
//		else{
//			DriveBase::setShooter(true);
//		}
//	}s

	double angle = SmartDashboard::GetNumber("Angle", 0.0);
	Shooter::setangle(angle);
	SmartDashboard::PutNumber("Shooter Angle", Shooter::getangle());
//	frc::Wait(0.005);

	double shooter = SmartDashboard::GetNumber("Shooter", 0.0);
	if(shooter > 0.1)
	{
		target = shooter;
	}

	if(Teleop::extremepro->GetRawButton(12))
	{
		min = 100000;
		max = 0;
	}

	//Liav here - nice camel case. by that i mean that there isnt any.
	double extreme_y = extremepro->GetRawAxis(1);
	double scaled_y = (extreme_y*0.5)+0.5;
	// -1 to 1
	if(Teleop::extremepro->GetRawButton(2))
	{
		Shooter::agitatorOn();
	}
	else
	{
		Shooter::agitatorOff();
	}
	//Accepts rpm setting
	double setRPM = scaled_y * 6000.0;
	Shooter::set(shooter);
	double currentRPM = Shooter::get();
	if(passedTarget)
	{

		if(max < currentRPM)
			max = currentRPM;
		if(min > currentRPM)
			min = currentRPM;
		//std::cout << currentRPM << "," << max << "," << min << "," << max - min << "\n";
	}
	SmartDashboard::PutNumber("Shooter speed", currentRPM);


	SmartDashboard::PutNumber("MaxRPM", max);
	SmartDashboard::PutNumber("MinRPM", min);
}


