/*
 * Teleop.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: Academy HS Robotics
 */
#include <Shooter.hpp>
#include <Copernicus.h>
#include <DriveBase.hpp>
#include <Intake.hpp>
#include <Teleop.hpp>

int autoFire = 0;

namespace Teleop {

	Joystick* xBox;
	Joystick* extremePro;
	int prevButton1 = 0;
	int prevButton2 = 0;
	int saladSpinnerButton = 0;
	int prevButton4 = 0;
	double angle = 0.0;

	void init() {
		Shooter::init();
		DriveBase::init();
		Intake::init();




		xBox = new Joystick(0);
		extremePro = new Joystick(1);
		//SmartDashboard::PutNumber("Angle",0.0);
		SmartDashboard::PutNumber("Shooter",0.0);
		SmartDashboard::PutNumber("ShooterRPM",0.0);
		SmartDashboard::PutNumber("ShooterTarget",0.0);

		DriveBase::disableBrake();
	}

	void run() {
		double leftDrive = xBox->GetRawAxis(1);
		double rightDrive = xBox->GetRawAxis(5);
		SmartDashboard::PutNumber("ShooterRPM", Shooter::get());
		//Dead zone
		if(leftDrive < 0.1 && leftDrive > -0.1)
			leftDrive = 0.0;
		if(rightDrive < 0.1 && rightDrive > -0.1)
			rightDrive = 0.0;

		DriveBase::drive(leftDrive, rightDrive);

		//toggle for the floor intake
		if(prevButton1 < xBox->GetRawButton(1)){
			Intake::toggleIntake();
		}
		prevButton1 = xBox->GetRawButton(1);

		if(saladSpinnerButton < xBox->GetRawButton(4)){
			Intake::toggleSalad();
		}
		saladSpinnerButton = xBox->GetRawButton(4);

		//toggle for the agitator
		if(prevButton4 < extremePro->GetRawButton(5)){
			Shooter::agitatorToggle();
		}
		prevButton4 = extremePro ->GetRawButton(5);


		bool climberUpButton = extremePro->GetRawButton(8);
		bool climberOffButton = extremePro->GetRawButton(9);

		if (climberUpButton && !climberOffButton) {
			Climber::ClimbUp();
		}

		if(!climberUpButton && climberOffButton){
			Climber::turnOff();
		}

		bool rightButton = xBox->GetRawButton(6);
		bool leftButton = xBox->GetRawButton(5);
		if(rightButton && !leftButton){
			if(!DriveBase::getGearState()){
				DriveBase::switchGear(true);
			}
		}
		else if(!rightButton && leftButton){
			if(DriveBase::getGearState()){
				DriveBase::switchGear(false);
			}
		}

		bool rightSlider = xBox->GetRawButton(2);
		bool leftSlider = xBox->GetRawButton(3);
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

		if(xBox->GetRawButton(5))
		{
			DriveBase::getAHRS()->ResetDisplacement();
		}
		Copernicus::setFlywheelRPM(Shooter::get());

		/*double zAxis = extremePro->GetRawAxis(2);
		if(zAxis > 0.3 || zAxis < -0.3){
			Shooter::setangle(30.0 * -(zAxis));
		}else{
			Shooter::setangle(0);
		}*/




		double yAxis = extremePro->GetRawAxis(3);
		double RPMraw = ((((yAxis+1)/2)*6000) + 500) - (2000*yAxis);
		Shooter::set(RPMraw);//(SmartDashboard::GetNumber("ShooterTarget",0.0));


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
}
