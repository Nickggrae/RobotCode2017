#include "Shared.h"
#include "Auton.h"
#include <ctime>
#include "AHRS.h"

Auton& Auton::getInstance(){
	static Auton instance;
	return instance;
}

void Auton::init() {
	SmartDashboard::PutNumber("State", 0.0);
	DriveBase::enableBrake();
	DriveBase::resetAHRS(); //Resetting NavX before getting angle
	state = 10;
	startTime = 0;
	DriveBase::switchGear(true);
}

void Auton::TestYaw(){
	StayStill();
	SmartDashboard::PutNumber("yaw for michael", DriveBase::getYaw());
	SmartDashboard::PutNumber("roll for michael", DriveBase::getRoll());
	SmartDashboard::PutNumber("Pitch for michael", DriveBase::getPitch());
}

void Auton::TurnLeft(double power){
	DriveBase::drive(power, -power);
}

void Auton::TurnRight(double power){
	DriveBase::drive(-power, power);
}

void Auton::DriveForward(double power){ //define power as positive always
	DriveBase::drive(-power, -power);
}

void Auton::DriveBackwards(double power){
	DriveBase::drive(power, power);
}

void Auton::StayStill(){
	DriveBase::drive(0.0, 0.0);
}

bool Auton::waited(double seconds){
	if(startTime == 0){
		std::time(&startTime);
	}
	std::time_t currentTime;
	std::time(&currentTime);
	if (std::difftime(currentTime, startTime) >= seconds) {
		startTime = 0;
		return true;
	}
	return false;
}

void Auton::NothingAuton(){
	//Auton for nothing
	StayStill();
}

void Auton::RedLeftAuton(){
	//done for now -katka
	//Auton for REDLEFT
	//robot will go deliver the gear on the right
	//drive forward until the line
	switch (state) {
		case 10: //drive forward at half speed until ready to turn to get gear
			DriveForward();
			if(waited(2)){
				state = 30;
			}
			break;

		case 30: //turn right 45 degrees
			TurnRight();
			if (DriveBase::getYaw() >= 45) {
				state = 40;
			}
			break;

		case 40: // drive forward till at gear
			DriveForward();
			if(waited(0.8)){
				state = 50;
			}
			break;

		case 50: // stay stopped for 1.5 seconds; wait for gear to leave
			StayStill();
			if(waited(1.5)){
				state = 60;
			}
			break;

		case 60: // drive backward for some other time seconds away from gear
			DriveBackwards();
			if(waited(1)){
				state = 70;
			}
			break;

		case 70: // turn left for 45 degrees to head to launchpad line
			TurnLeft();
			if (DriveBase::getYaw() <= 0){ //turn until facing forward to launchpad line
				state = 80;
			}
			break;

		case 80: // drive forward for 2 seconds until at launchpad line
			DriveForward();
			if(waited(1.5)){
				state = 90;
			}
			break;

		case 90:
			StayStill();
			break;
		}

		SmartDashboard::PutNumber("State", state);
		SmartDashboard::PutNumber("NavXYaw", DriveBase::getYaw());
		SmartDashboard::PutNumber("NavXRoll", DriveBase::getRoll());
		SmartDashboard::PutNumber("NavXPitch", DriveBase::getPitch());
}

void Auton::BlueRightAuton(){
		//Auton for BLUERIGHT //HAS MANY PROBLEMS WITH TURNING AND EVERYTHING AND...EVEN MOVING STRAIGHT...HIGH FIVE BUILD TEAM!!
		//robot will go deliver gear to the left most one
		//robot will back out and turn left and go forward until at launch pad line
	switch (state) {
	case 10: //drive forward at half speed until ready to turn to get gear
			DriveForward();
			if(waited(2)){ //maybe 2
				state = 20;
			}
		break;

		case 20: // turn left 45 degrees to head to gear
			TurnLeft();
			if (DriveBase::getYaw() <= -45) {
				state = 30;
			}
		break;

		case 30: // drive forward till at gear
			DriveForward();
			if(waited(2)){
				state = 40;
			}
		break;

		case 40: // reset time to zero and stop driving; wait for person to pick up gear
			StayStill();
			state = 50;
		break;

		case 50: // stay stopped for 1.5 seconds; wait for gear to leave
			if(waited(1.5)){
				state = 60;
			}
		break;

		case 60: // drive backward away from gear
			DriveBackwards();
			if(waited(1.5)){
				state = 65;
			}
			break;

		case 65:
			StayStill();
			if(waited(0.2)){
				state = 70;
			}
			break;

		case 70:
			TurnRight();
			if (DriveBase::getYaw() >= 0){ //turn left until facing forward to launchpad line
				state = 80;
			}
			break;

		case 80: // drive forward for 2 seconds until at launchpad line
			DriveForward();
			if(waited(1.5)){
				state = 90;
			}
			break;

		case 90:
			StayStill();
			break;
		}
		SmartDashboard::PutNumber("State", state);
		SmartDashboard::PutNumber("NavXYaw", DriveBase::getYaw());
		SmartDashboard::PutNumber("NavXRoll", DriveBase::getRoll());
		SmartDashboard::PutNumber("NavXPitch", DriveBase::getPitch());
}

void Auton::RedMiddleAuton(){
	//Auton for RedMiddle
	//robot will move forward to the middle gear and deliver it
	//will shoot the 10 balls while(or after??) delivering gear
	//robot will turn left and go forward until at the launchpad
	switch (state) {
		case 10: //drive forward at half speed until at gear
			DriveForward();
			if(waited(2)){
				state = 30;
			}
			break;

		case 30: // stay stopped for 1.5 seconds; wait for gear to leave
			//NEED TO ADD SHOOTING WHILE PLACING GEAR
			StayStill();
			if(waited(3.5)){
				state = 40;
			}
			break;

		case 40: //move backwards away from gear
			DriveBackwards();
			if(waited(.4)){
				state = 50;
			}
			break;

		case 50: //turn left 90 degrees
			TurnLeft();
			if (DriveBase::getYaw() <= -90) //turn until facing left
				state = 60;
			break;

		case 60: // go forward to be ready to turn right
			DriveForward();
			if(waited(1.5)){
				state = 70;
			}
			break;

		case 70:
			TurnRight();
			if (DriveBase::getYaw() >= -10)
				state = 80;
		break;

		case 80:
			DriveForward();
			if(waited(1.5)){
				state = 90;
			}
		break;

		case 90:
			StayStill();
		break;
	}
}

void Auton::BlueLeftShootAuton(){
	//Auton for BlueLeft
	//Robot will get balls from hopper and shoot them
	switch (state){
	case 10:
		DriveForward();
		if(waited(2)){
			state = 15;
		}
	break;

	case 15:
		StayStill();
		if(waited(0.2)){
			state = 20;
		}
		break;

	case 20: //turn left to face hopper
		TurnLeft();
		if (DriveBase::getYaw() <= -90) {//turn until facing the hopper
			state = 30;
		}
	break;

	case 30:
		DriveForward(); //to hopper
		if(waited(1.5)){
			state = 40;
		}
	break;

	case 40:
		//SHOOT
		StayStill(); //stays at the hopper
	break;

//when it's done shooting, back out to prepare for teleop
	}
}

void Auton::BlueLeftGearAuton(){
	switch (state) {
		case 10: //drive forward at half speed until ready to turn to get gear
			DriveForward();
			if(waited(2)){
				state = 20;
			}
			break;

		case 20: //turn right 45 degrees
			TurnRight();
			if (DriveBase::getYaw() >= 45) {
				state = 30;
			}
			break;

		case 30: // drive forward till at gear
			DriveForward();
			if(waited(0.8)){
				state = 40;
			}
			break;

		case 40: // stay stopped for 1.5 seconds; wait for gear to leave
			StayStill();
			//SHOOT
			break;
	}
}

void Auton::BlueMiddleAuton(){
	//Auton for BlueMiddle
	//robot will move forward to the middle gear and deliver it
	//will shoot the 10 balls while(or after??) delivering gear
	//robot will turn right and go forward until at the launchpad line
	switch (state) {
		case 10: //drive forward at half speed until at gear
			DriveForward();
			if(waited(2)){
				state = 30;
			}
			break;

		case 30: // stay stopped for 1.5 seconds; wait for gear to leave
			//NEED TO ADD SHOOTING WHILE PLACING GEAR
			StayStill();
			if(waited(3.5)){
				state = 40;
			}
			break;

		case 40: //move backwards away from gear
			DriveBackwards();
			if(waited(.4)){
				state = 50;
			}
			break;

		case 50: //turn left 90 degrees
			TurnRight();
			if (DriveBase::getYaw() >= 90) //turn until facing Right
				state = 60;
			break;

		case 60: // go forward to be ready to turn right
			DriveForward();
			if(waited(1.5)){
				state = 70;
			}
			break;

		case 70:
			TurnLeft();
			if (DriveBase::getYaw() <= 0)
				state = 80;
		break;

		case 80:
			DriveForward();
			if(waited(1.5)){
				state = 90;
			}
		break;

		case 90:
			StayStill();
		break;
	}
}


void Auton::RedRightShootAuton(){
	//Auton for RedRight
	//Robot will go to the hopper to get the balls and shoot them
	switch (state){
	case 10:
		DriveForward();
		if(waited(2)){
			state = 30;
		}
	break;

	case 30: //turn right to face hopper
		TurnRight();
		if (DriveBase::getYaw() >= 90) {//turn until facing the hopper
			state = 40;
		}
	break;

	case 40:
		DriveForward(); //to hopper
		if(waited(1)){
			state = 50;
		}
	break;

	case 50:
		//SHOOT
		StayStill(); //stays at the hopper
	break;

//when it's done shooting, back out to prepare for teleop
	}
}

void Auton::RedRightGearAuton(){
	switch (state) {
		case 10: //drive forward at half speed until ready to turn to get gear
			DriveForward();
			if(waited(2)){
				state = 20;
			}
			break;

		case 20: //turn left 45 degrees
			TurnLeft();
			if (DriveBase::getYaw() <= -45) {
				state = 30;
			}
			break;

		case 30: // drive forward till at gear
			DriveForward();
			if(waited(1.1)){
				state = 40;
			}
			break;

		case 40: // stay stopped for 1.5 seconds; wait for gear to leave
			StayStill();
			//SHOOT
			break;
	}
}
