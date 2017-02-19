#include "Shared.h"
#include "Auton.h"
#include <ctime>
#include "AHRS.h"

// used to record time at auton init
std::time_t Auton::startTime;

int start; //Declared as a double so that we can create decimal states when we want to insert a state (for example 5.1)
int loopCount = 0;

void Auton::init() {
	SmartDashboard::PutNumber("State", 0.0);
	DriveBase::enableBrake();
	DriveBase::resetAHRS(); //Resetting NavX before getting angle
	start = 10;
	Auton::startTime = 0;
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
	if(Auton::startTime == 0){
		std::time(&Auton::startTime);
	}
	std::time_t currentTime;
	std::time(&currentTime);
	if (std::difftime(currentTime, Auton::startTime) >= seconds) {
		Auton::startTime = 0;
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
	loopCount += 1;
	SmartDashboard::PutNumber("LoopCount", loopCount);
	switch (start) {
		case 10: //drive forward at half speed until ready to turn to get gear
			DriveForward();
			if(waited(2)){
				start = 30;
			}
			break;

		case 30: //turn right 45 degrees
			TurnRight();
			if (DriveBase::getYaw() >= 45) {
				start = 40;
			}
			break;

		case 40: // drive forward till at gear
			DriveForward();
			if(waited(0.8)){
				start = 50;
			}
			break;

		case 50: // stay stopped for 1.5 seconds; wait for gear to leave
			StayStill();
			if(waited(1.5)){
				start = 60;
			}
			break;

		case 60: // drive backward for some other time seconds away from gear
			DriveBackwards();
			if(waited(1)){
				start = 70;
			}
			break;

		case 70: // turn left for 45 degrees to head to launchpad line
			TurnLeft();
			if (DriveBase::getYaw() <= 0){ //turn until facing forward to launchpad line
				start = 80;
			}
			break;

		case 80: // drive forward for 2 seconds until at launchpad line
			DriveForward();
			if(waited(1.5)){
				start = 90;
			}
			break;

		case 90:
			StayStill();
			break;
		}

		SmartDashboard::PutNumber("State", start);
		SmartDashboard::PutNumber("NavXYaw", DriveBase::getYaw());
		SmartDashboard::PutNumber("NavXRoll", DriveBase::getRoll());
		SmartDashboard::PutNumber("NavXPitch", DriveBase::getPitch());
}

void Auton::BlueRightAuton(){
		//Auton for BLUERIGHT //HAS MANY PROBLEMS WITH TURNING AND EVERYTHING AND...EVEN MOVING STRAIGHT...HIGH FIVE BUILD TEAM!!
		//robot will go deliver gear to the left most one
		//robot will back out and turn left and go forward until at launch pad line
	switch (start) {
	case 10: //drive forward at half speed until ready to turn to get gear
			DriveForward();
			if(waited(2)){ //maybe 2
				start = 20;
			}
		break;

		case 20: // turn left 45 degrees to head to gear
			TurnLeft();
			if (DriveBase::getYaw() <= -45) {
				start = 30;
			}
		break;

		case 30: // drive forward till at gear
			DriveForward();
			if(waited(2)){
				start = 40;
			}
		break;

		case 40: // reset time to zero and stop driving; wait for person to pick up gear
			StayStill();
			start = 50;
		break;

		case 50: // stay stopped for 1.5 seconds; wait for gear to leave
			if(waited(1.5)){
				start = 60;
			}
		break;

		case 60: // drive backward away from gear
			DriveBackwards();
			if(waited(1.5)){
				start = 65;
			}
			break;

		case 65:
			StayStill();
			if(waited(0.2)){
				start = 70;
			}
			break;

		case 70:
			TurnRight();
			if (DriveBase::getYaw() >= 0){ //turn left until facing forward to launchpad line
				start = 80;
			}
			break;

		case 80: // drive forward for 2 seconds until at launchpad line
			DriveForward();
			if(waited(1.5)){
				start = 90;
			}
			break;

		case 90:
			StayStill();
			break;
		}
		SmartDashboard::PutNumber("State", start);
		SmartDashboard::PutNumber("NavXYaw", DriveBase::getYaw());
		SmartDashboard::PutNumber("NavXRoll", DriveBase::getRoll());
		SmartDashboard::PutNumber("NavXPitch", DriveBase::getPitch());
}

void Auton::RedMiddleAuton(){
	//Auton for RedMiddle
	//robot will move forward to the middle gear and deliver it
	//will shoot the 10 balls while(or after??) delivering gear
	//robot will turn left and go forward until at the launchpad
	switch (start) {
		case 10: //drive forward at half speed until at gear
			DriveForward();
			if(waited(2)){
				start = 30;
			}
			break;

		case 30: // stay stopped for 1.5 seconds; wait for gear to leave
			//NEED TO ADD SHOOTING WHILE PLACING GEAR
			StayStill();
			if(waited(3.5)){
				start = 40;
			}
			break;

		case 40: //move backwards away from gear
			DriveBackwards();
			if(waited(.4)){
				start = 50;
			}
			break;

		case 50: //turn left 90 degrees
			TurnLeft();
			if (DriveBase::getYaw() <= -90) //turn until facing left
				start = 60;
			break;

		case 60: // go forward to be ready to turn right
			DriveForward();
			if(waited(1.5)){
				start = 70;
			}
			break;

		case 70:
			TurnRight();
			if (DriveBase::getYaw() >= -10)
				start = 80;
		break;

		case 80:
			DriveForward();
			if(waited(1.5)){
				start = 90;
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
	switch (start){
	case 10:
		DriveForward();
		if(waited(2)){
			start = 15;
		}
	break;

	case 15:
		StayStill();
		if(waited(0.2)){
			start = 20;
		}
		break;

	case 20: //turn left to face hopper
		TurnLeft();
		if (DriveBase::getYaw() <= -90) {//turn until facing the hopper
			start = 30;
		}
	break;

	case 30:
		DriveForward(); //to hopper
		if(waited(1.5)){
			start = 40;
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
	switch (start) {
		case 10: //drive forward at half speed until ready to turn to get gear
			DriveForward();
			if(waited(2)){
				start = 20;
			}
			break;

		case 20: //turn right 45 degrees
			TurnRight();
			if (DriveBase::getYaw() >= 45) {
				start = 30;
			}
			break;

		case 30: // drive forward till at gear
			DriveForward();
			if(waited(0.8)){
				start = 40;
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
	switch (start) {
		case 10: //drive forward at half speed until at gear
			DriveForward();
			if(waited(2)){
				start = 30;
			}
			break;

		case 30: // stay stopped for 1.5 seconds; wait for gear to leave
			//NEED TO ADD SHOOTING WHILE PLACING GEAR
			StayStill();
			if(waited(3.5)){
				start = 40;
			}
			break;

		case 40: //move backwards away from gear
			DriveBackwards();
			if(waited(.4)){
				start = 50;
			}
			break;

		case 50: //turn left 90 degrees
			TurnRight();
			if (DriveBase::getYaw() >= 90) //turn until facing Right
				start = 60;
			break;

		case 60: // go forward to be ready to turn right
			DriveForward();
			if(waited(1.5)){
				start = 70;
			}
			break;

		case 70:
			TurnLeft();
			if (DriveBase::getYaw() <= 0)
				start = 80;
		break;

		case 80:
			DriveForward();
			if(waited(1.5)){
				start = 90;
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
	switch (start){
	case 10:
		DriveForward();
		if(waited(2)){
			start = 30;
		}
	break;

	case 30: //turn right to face hopper
		TurnRight();
		if (DriveBase::getYaw() >= 90) {//turn until facing the hopper
			start = 40;
		}
	break;

	case 40:
		DriveForward(); //to hopper
		if(waited(1)){
			start = 50;
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
	switch (start) {
		case 10: //drive forward at half speed until ready to turn to get gear
			DriveForward();
			if(waited(2)){
				start = 20;
			}
			break;

		case 20: //turn left 45 degrees
			TurnLeft();
			if (DriveBase::getYaw() <= -45) {
				start = 30;
			}
			break;

		case 30: // drive forward till at gear
			DriveForward();
			if(waited(1.1)){
				start = 40;
			}
			break;

		case 40: // stay stopped for 1.5 seconds; wait for gear to leave
			StayStill();
			//SHOOT
			break;
	}
}

