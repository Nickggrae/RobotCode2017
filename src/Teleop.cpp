/*
 * Teleop.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: Academy HS Robotics
 */
#include "Teleop.h"
#include "Shooter.h"
#include "Intake.h"
//#include "DriveBase.h"



int prevButton1 = 0;
int prevButton2 =0;

Joystick* Teleop::joy;
Joystick* Teleop::stick;
Joystick* Teleop::extremepro;

void Teleop::init() {
	Teleop::joy = new Joystick(0);
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
	DriveBase::drive(leftDrive, rightDrive);

	if(prevButton1 < Teleop::joy->GetRawButton(1)){
		Intake::toggleIntake();
	}
	prevButton1 = Teleop::joy->GetRawButton(1);

	if(prevButton1 <Teleop::stick->GetRawButton(7)){
		Climber::turnOn();
	}

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
	frc::Wait(0.005);

//	double shooter = SmartDashboard::GetNumber("Shooter", 0.0);
	Shooter::set(extremepro->GetRawAxis(1));
	SmartDashboard::PutNumber("Shooter speed", Shooter::get());


	SmartDashboard::PutNumber("Pitch", DriveBase::getPitch());

	SmartDashboard::PutNumber("Roll", DriveBase::getRoll());

	SmartDashboard::PutNumber("Yaw", DriveBase::getYaw());

	SmartDashboard::PutNumber("DisplacementX", (DriveBase::DisplacementX()*100));

	SmartDashboard::PutNumber("DisplacementY", (DriveBase::DisplacementY()*100));

	SmartDashboard::PutNumber("DisplacementZ", (DriveBase::DisplacementZ()*100));

	SmartDashboard::PutNumber("AccelX", DriveBase::getAccelX());

	SmartDashboard::PutNumber("AccelY", DriveBase::getAccelY());

	SmartDashboard::PutNumber("AccelZ", DriveBase::getAccelZ());

	SmartDashboard::PutNumber("isTalonEnabled", DriveBase::isTalonEnabled());

//Usaid if you are reading this it was a test just get rid of it
	SmartDashboard::PutNumber("VelocityX", DriveBase::velocityX());

	SmartDashboard::PutNumber("VelocityY", DriveBase::velocityY());

	SmartDashboard::PutNumber("VelocityZ", DriveBase::velocityZ());
}


