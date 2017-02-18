#include "Shared.h"
#include "Auton.h"
#include <ctime>
#include "AHRS.h"

// used to record time at auton init
std::time_t startTime;
int start; //Declared as a double so that we can create decimal states when we want to insert a state (for example 5.1)
int loopCount = 0;

void Auton::init() {
	SmartDashboard::PutNumber("State", 0.0);
	DriveBase::enableBrake();
	DriveBase::resetAHRS(); //Resetting NavX before getting angle
	start = 10;
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
	std::time_t currentTime;
	switch (start) {
		case 10: //set start time to zero at start
			std::time(&startTime); // store time at time of initialization
			StayStill();
			start = 20;
			break;

		case 20: //drive forward at half speed until ready to turn to get gear
			DriveForward(0.5);
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 2) { // stop after x seconds
//				DriveBase::resetAHRS(); //Resetting NavX before getting angle
				start = 30;
			}
			break;

		case 30: //turn right 45 degrees
			TurnRight(0.5);
			if (DriveBase::getYaw() >= 45) {
				std::time(&startTime); // store time at time
				start = 40;
			}
			break;

		case 40: // drive forward till at gear
			DriveForward(0.5);
			std::time(&currentTime);
			//double difference = difftime(currentTime, startTime); // get difference in seconds
			if (std::difftime(currentTime, startTime) >= 0.8) { // stop after x seconds
				std::time(&startTime); // store time at time of initialization
				start = 50;
			}
			break;

		case 50: // stay stopped for 1.5 seconds; wait for gear to leave
			StayStill();
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 1.5) { // stop after 2 seconds
				std::time(&startTime); // store time at time of initialization
				start = 60;
			}
			break;

		case 60: // drive backward for 2.5 seconds away from gear
			DriveBackwards(0.5);
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 0.6) { // stop after 2 seconds
				start = 70; //Change later - just to get gear on for now
			}
			break;

		case 70: // turn left for 45 degrees to head to launchpad line
			TurnLeft(0.5);
			if (DriveBase::getYaw() <= 0){ //turn until facing forward to launchpad line
				std::time(&startTime); // store time at time of initialization
				start = 80;
			}
			break;

		case 80: // drive forward for 2 seconds until at launchpad line
			DriveForward(0.5);
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 2) {
//				DriveBase::resetAHRS();
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
		case 1: //set start time to zero at start
			std::time(&startTime); // store time at time of initialization
			start = 2;
			break;

		case 2: //drive forward at half speed until ready to turn to get gear
			DriveForward(0.5);
			std::time_t currentTime;
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 5) { // stop after x seconds
//				DriveBase::resetAHRS(); //Resetting NavX before getting angle
				start = 3;
			}
		break;

		case 3: // turn left 45 degrees to head to gear
			TurnLeft(0.5);
			if (DriveBase::getYaw() >= 6) {
				std::time(&startTime); // store time at time of initialization
				start = 4;
			}
		break;

		case 4: // drive forward till at gear
			DriveForward(0.5);
			std::time(&currentTime);
			//double difference = difftime(currentTime, startTime); // get difference in seconds
			if (std::difftime(currentTime, startTime) >= 2) { // stop after x seconds
				start = 5;
			}
		break;

		case 5: // reset time to zero and stop driving; wait for person to pick up gear
			std::time(&startTime); // store time at time of initialization
			StayStill();
			start = 6;
		break;

		case 6: // stay stopped for 1.5 seconds; wait for gear to leave
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 1.5) { // stop after 2 seconds
				std::time(&startTime); // store time at time of initialization
				start = 8; //CHANGE THE NUMBERS OF CASES LATER
			}
		break;

		case 8: // drive backward for 2.5 seconds away from gear
			DriveBackwards(0.5);
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 0.5) { // stop after 2 seconds
//				DriveBase::resetAHRS();
				start = 9; //Change later - just to get gear on for now
			}
			break;

		case 9: // turn right for 135 degrees to head to launchpad line
			TurnRight(0.5);
			if (DriveBase::getYaw() <= -45){ //turn left until facing forward to launchpad line
				std::time(&startTime); // store time
				start = 11;
			}
			break;

		case 11: // drive forward for 2 seconds until at launchpad line
			DriveForward(0.5);
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 2) {
//				DriveBase::resetAHRS();
				start = 12;
			}
			break;

		case 12:
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
		case 10: //set start time to zero at start
			std::time(&startTime); // store time at time of initialization
			start = 20;
			break;

		case 20: //drive forward at half speed until at gear
			DriveForward(0.5);
			std::time_t currentTime;
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 1.7) { // stop after x seconds
				std::time(&startTime); // store time at time of initialization
				start = 30;
			}
			break;

		case 30: // stay stopped for 1.5 seconds; wait for gear to leave
			//NEED TO ADD SHOOTING WHILE PLACING GEAR
			StayStill();
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 1) { // stop after 2 seconds
				std::time(&startTime); // store time at time of initialization
				start = 40;
			}
			break;

		case 40: //move backwards away from gear
			DriveBackwards(0.5);
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 0.4) { // stop after 2 seconds
				start = 50;
			}
			break;

		case 50: //turn left 90 degrees
			DriveBackwards(0.5);
			if (DriveBase::getYaw() <= -30) //turn until facing left
				std::time(&startTime); // store time at time of initialization
				start = 60;
			break;

		case 60: // go forward to be ready to turn right
			DriveForward(0.5);
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 0.5) { // stop after 2 seconds
				start = 70;
			}
			break;

		case 70:
			StayStill();
		break;

		case 80:
			StayStill();
		break;
	}
}

void Auton::BlueLeftAuton(){
	//Auton for BlueLeft
	//Robot will get balls from hopper
	//Go to the Left Gear and deliver it -- while shooting balls at the same time
	//after delivering the gear, stop and don't move till teleop
	//switch case here
	std::time_t currentTime;
	switch (start){
	case 10:
		std::time(&startTime); // store time at time of initialization
		start = 20;

	break;

	case 20:
		DriveForward(0.5); //moves forward going towards the hopper
		std::time(&currentTime);
		if (std::difftime(currentTime, startTime) >= 2) { // time needs to for sure be changed in testing...
			std::time(&startTime); // store time at time of initialization
			start = 30;
		}

	break;

	case 30:
		TurnLeft(0.5);
			std::time(&startTime); // store time at time of
		if (DriveBase::getYaw() >= 90) {//turn until facing left initialization
			start = 40;
		}
	break;

	case 40:
		DriveForward(0.5); //
		std::time(&currentTime);
		if (std::difftime(currentTime, startTime) >= .8) { // time needs to for sure be changed in testing...
			std::time(&startTime); // store time at time of initialization
			start = 50;
		}
	break;

	case 50:
		StayStill();
		if (std::difftime(currentTime, startTime) >= 3) { // time needs to for sure be changed in testing...
			std::time(&startTime); // store time at time of initialization
		}
	break;

	case 60:
		DriveBackwards(0.5);
		std::time(&currentTime);
		if (std::difftime(currentTime, startTime) >= .8) { // time needs to for sure be changed in testing...
			std::time(&startTime); // store time at time of initialization
		}
	break;
	}
}

void Auton::BlueMiddleAuton(){
	//Auton for BlueMiddle
	//robot will deliver the gear to the middle option
	//robot will turn right and go forward until at lannch pad line
	//switch case here
}

void Auton::RedRightAuton(){
	//Auton for RedRight
	//Robot will go to the hopper to get the balls
	//Drive to the gear and deliver it
	//while at the gear, shoot the balls that were picked up from the hopper
	//stay at the gear and don't move until teleop...
	std::time_t currentTime;
	switch (start){
	case 10:
		std::time(&startTime); // store time at time of initialization
		start = 20;
	break;

	case 20:
		DriveForward(0.5);
		std::time(&currentTime);
		if (std::difftime(currentTime, startTime) >= 2) {
			std::time(&startTime);
			start = 30;
		}
	break;

	case 30: //turn right to face hopper
		TurnRight(0.5);
		std::time(&startTime);
		if (DriveBase::getYaw() >= 90) {//turn until facing the hopper
			start = 40;
		}
	break;

	case 40:
		DriveForward(0.5); //to hopper
		std::time(&currentTime);
		if (std::difftime(currentTime, startTime) >= .6) {
			std::time(&startTime);
			start = 50;
		}
	break;

	case 50:
		DriveBackwards(0.5); //moves backwards away from the hopper
		std::time(&currentTime);
		if (std::difftime(currentTime, startTime) >= .8) {
			std::time(&startTime);
			start = 60;
		}
	break;

	case 60:	//angle is estimated by Oliver, if it is wrong it is Oliver's fault...
		TurnLeft(0.5);
		std::time(&startTime);
		if(DriveBase::getYaw() <= -90) {
			start = 70;
		}
	break;

	case 70:
		DriveBackwards(0.5);//moves the robot to the gear
		std::time_t currentTime;
		std::time(&currentTime);
		if (std::difftime(currentTime, startTime) >= 1.5) {
		std::time(&startTime);
		start = 80;
		}

	break;

	case 80:
		StayStill();
	break;
	}
}
void Auton::periodic(int routine) {

}
