/*
 * Teleop.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: Academy HS Robotics
 */
#include "Teleop.h"
#include "Shooter.h"
#include "Intake.h"

int prevButton1 = 0;

Joystick* Teleop::joy;
void Teleop::init() {
	Teleop::joy = new Joystick(0);
	DriveBase::init();
	Shooter::init();
	Intake::init();
	SmartDashboard::PutNumber("Angle",0.0);
	SmartDashboard::PutNumber("Shooter",0.0);
}
void Teleop::run() {
	double leftDrive = Teleop::joy->GetRawAxis(1);
	double rightDrive = Teleop::joy->GetRawAxis(5);
	DriveBase::drive(leftDrive, rightDrive);

	if(prevButton1 < Teleop::joy->GetRawButton(1)){
		Intake::toggleIntake();
	}
	prevButton1 = Teleop::joy->GetRawButton(1);

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
//					frc::Wait(.1);
		}
	}
//	SmartDashboard::PutNumber("XDisplacement", DriveBase::ahrs.GetDisplacementX());
//	SmartDashboard::PutNumber("YDisplacement", DriveBase::ahrs.GetDisplacementY());
//	SmartDashboard::PutNumber("ZDisplacement", DriveBase::ahrs.GetDisplacementZ());
//
//	if(joy->GetRawButton(5))
//	{
//		DriveBase::ahrs.ResetDisplacement();
//	}
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
	frc::Wait(0.005);

	double shooter = SmartDashboard::GetNumber("Shooter", 0.0);
	Shooter::set(0.5);
	SmartDashboard::PutNumber("Shooter speed", Shooter::get());

}


