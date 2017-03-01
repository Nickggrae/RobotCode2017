/*
 * Teleop.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: Academy HS Robotics
 */
#include "Teleop.h"
#include "DriveBase.h"
#include "Shooter.h"
#include "Intake.h"
#include "Copernicus.h"
#include <iostream>

int autoFire = 0;
Teleop& Teleop::getInstance(){
  static Teleop instance;
  return instance;
}

void Teleop::init() {
	xBox = new Joystick(0);
	extremePro = new Joystick(1);
	SmartDashboard::PutNumber("Angle",0.0);
	SmartDashboard::PutNumber("Shooter",0.0);
	SmartDashboard::PutNumber("ShooterRPM",0.0);
	SmartDashboard::PutNumber("ShooterTarget",0.0);

	driveBase.disableBrake();
}

void Teleop::run() {
	double leftDrive = xBox->GetRawAxis(1);
	double rightDrive = xBox->GetRawAxis(5);
	SmartDashboard::PutNumber("ShooterRPM",shooter.get());
	//Dead zone
	if(leftDrive < 0.1 && leftDrive > -0.1)
		leftDrive = 0.0;
	if(rightDrive < 0.1 && rightDrive > -0.1)
		rightDrive = 0.0;

	driveBase.drive(leftDrive, rightDrive);

	//toggle for the floor intake
	if(prevButton1 < xBox->GetRawButton(1)){
		intake.toggleIntake();
	}
	prevButton1 = xBox->GetRawButton(1);

	if(saladSpinnerButton < xBox->GetRawButton(4)){
		intake.toggleSalad();
	}
	saladSpinnerButton = xBox->GetRawButton(4);

	//toggle for the agitator
	if(prevButton4 < extremePro->GetRawButton(5)){
		shooter.agitatorToggle();
	}
	prevButton4 = extremePro ->GetRawButton(5);


	bool climberUpButton = extremePro->GetRawButton(8);
	bool climberOffButton = extremePro->GetRawButton(9);

	if (climberUpButton && !climberOffButton) {
		climber.ClimbUp();
	}

	if(!climberUpButton && climberOffButton){
		climber.turnOff();
	}

	bool rightButton = xBox->GetRawButton(6);
	bool leftButton = xBox->GetRawButton(5);
	if(rightButton && !leftButton){
		if(!driveBase.getGearState()){
			driveBase.switchGear(true);
		}
	}
	else if(!rightButton && leftButton){
		if(driveBase.getGearState()){
			driveBase.switchGear(false);
		}
	}

	bool rightSlider = xBox->GetRawButton(2);
	bool leftSlider = xBox->GetRawButton(3);
	if(rightSlider && !leftSlider){
		if(!driveBase.getSliderState()){
			driveBase.switchSlider(true);
		}
	}
	else if(!rightSlider && leftSlider){
		if(driveBase.getSliderState()){
			driveBase.switchSlider(false);
		}
	}

	if(xBox->GetRawButton(5))
	{
		driveBase.ahrs->ResetDisplacement();
	}
	Copernicus::setFlywheelRPM(shooter.get());

	double zAxis = extremePro->GetRawAxis(2);
	if(zAxis > 0.3 || zAxis < -0.3){
		shooter.setangle(30.0 * -(zAxis));
	}else{
		shooter.setangle(0);
	}


	double yAxis = extremePro->GetRawAxis(3);
	double RPMraw = ((((yAxis+1)/2)*6000) + 500) - (2000*yAxis);
	shooter.set(RPMraw);//(SmartDashboard::GetNumber("ShooterTarget",0.0));


//	if (yAxis < -0.2){
//		Shooter::getInstance().set(yAxis*-4500);
//	}else{
//		Shooter::getInstance().set(0);
//	}


/*
	if (!Teleop::extremePro->GetRawButton(1))
		autoFire = 0;
	else if (autoFire == 0)
		autoFire = 10;

	switch (autoFire) { //will fix error later
		case 10: {
			double raw_fire_power = Teleop::extremePro->GetRawAxis(1);

			double rpm_flywheel = (((raw_fire_power + 1) / 2) * 8000)
					- (1500 * raw_fire_power);
			SmartDashboard::PutNumber("Wanted Flywheel Speed", rpm_flywheel);

			Shooter::getInstance().set(rpm_flywheel);

			int flywheel_error =
					Shooter::getInstance().getShooterCANTalon()->GetClosedLoopError();

			SmartDashboard::PutNumber("Flywheel closed loop error", flywheel_error);

			if (flywheel_error < 500) {
				Shooter::getInstance().agitatorOn();
			}

			if (flywheel_error < 10) {
				autoFire = 20;
			}



		}
		break;

		case 20: {
			Intake::getInstance().saladSpinnerOn();
		}
		break;

		default: {
		}
		break;
	}*/
}
