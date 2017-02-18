#include "Shared.h"
#include "Auton.h"
#include <ctime>
#include "AHRS.h"

// used to record time at auton init
std::time_t startTime;
int start = 1; //Declared as a double so that we can create decimal states when we want to insert a state (for example 5.1)

void Auton::init() {
	SmartDashboard::PutNumber("State", 0.0);
	DriveBase::enableBrake();
	DriveBase::resetAHRS(); //Resetting NavX before getting angle
	start = 1;
}

void Auton::NothingAuton(){
	//Auton for nothing
	DriveBase::drive(0.0, 0.0);
}

void Auton::RedLeftAuton(){
	//done for now -katka
	//Auton for REDLEFT
	//robot will go deliver the gear on the right
	//drive forward until the line
	switch (start) {
		case 1: //set start time to zero at start
			std::time(&startTime); // store time at time of initialization
			start = 2;
			break;

		case 2: //drive forward at half speed until ready to turn to get gear
			DriveBase::drive(-0.45, -0.45);
			std::time_t currentTime;
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 2) { // stop after x seconds
				DriveBase::resetAHRS(); //Resetting NavX before getting angle
				start = 3;
			}
			break;

		case 3: // turn left 45 degrees to head to gear
			DriveBase::drive(-0.40, 0.40);
			if (DriveBase::getYaw() >= 45) {
				std::time(&startTime); // store time at time of initialization
				start = 4;
			}
			break;

		case 4: // drive forward till at gear
			DriveBase::drive(-0.4, -0.4);
			std::time(&currentTime);
			//double difference = difftime(currentTime, startTime); // get difference in seconds
			if (std::difftime(currentTime, startTime) >= 1) { // stop after x seconds
				start = 5;
			}
			break;

		case 5: // reset time to zero and stop driving; wait for person to pick up gear
			std::time(&startTime); // store time at time of initialization
			DriveBase::drive(0.0, 0.0);
			start = 6;
			break;

		case 6: // stay stopped for 1.5 seconds; wait for gear to leave
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 1.5) { // stop after 2 seconds
				start = 7;
			}
			break;

		case 7: // reset time to zero and drive backward at half speed away from airship
			std::time(&startTime); // store time at time of initialization
			DriveBase::drive(0.5, 0.5);
			start = 8;
			break;

		case 8: // drive backward for 2.5 seconds away from gear
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 2) { // stop after 2 seconds
				DriveBase::resetAHRS();
				start = 9; //Change later - just to get gear on for now
			}
			break;

		case 9: // turn right for 135 degrees to head to launchpad line
			DriveBase::drive(0.5, -0.5);
			if (DriveBase::getYaw() >= 45) //turn until facing forward to launchpad line
				start = 9;
			break;

		case 10: // reset time and drive forward towards launchpad line
			std::time(&startTime); // store time at time of initialization
			DriveBase::drive(-0.5, -0.5);
			start = 11;
			break;

		case 11: // drive forward for 2 seconds until at launchpad line
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 2) {
				DriveBase::resetAHRS();
				start = 12;
			}
			break;

		case 12:
			DriveBase::drive(0, 0);
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
			DriveBase::drive(-0.5, -0.5);
			std::time_t currentTime;
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 5) { // stop after x seconds
				DriveBase::resetAHRS(); //Resetting NavX before getting angle
				start = 3;
			}
		break;

		case 3: // turn right 45 degrees to head to gear
			DriveBase::drive(0.28, -0.28);
			if (DriveBase::getYaw() >= 6) {
				std::time(&startTime); // store time at time of initialization
				start = 4;
			}
		break;

		case 4: // drive forward till at gear
			DriveBase::drive(-0.5, -0.5);
			std::time(&currentTime);
			//double difference = difftime(currentTime, startTime); // get difference in seconds
			if (std::difftime(currentTime, startTime) >= 2) { // stop after x seconds
				start = 5;
			}
		break;

		case 5: // reset time to zero and stop driving; wait for person to pick up gear
			std::time(&startTime); // store time at time of initialization
			DriveBase::drive(0.0, 0.0);
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
			DriveBase::drive(0.5, 0.5);
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 0.5) { // stop after 2 seconds
				DriveBase::resetAHRS();
				start = 9; //Change later - just to get gear on for now
			}
			break;

		case 9: // turn right for 135 degrees to head to launchpad line
			DriveBase::drive(-0.5, 0.5);
			if (DriveBase::getYaw() <= -6) //turn left until facing forward to launchpad line
				start = 9;
			break;

		case 10: // reset time and drive forward towards launchpad line
			std::time(&startTime); // store time at time of initialization
			DriveBase::drive(-0.5, -0.5);
			start = 11;
			break;

		case 11: // drive forward for 2 seconds until at launchpad line
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 2) {
				DriveBase::resetAHRS();
				start = 12;
			}
			break;

		case 12:
			DriveBase::drive(0, 0);
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
		case 1: //set start time to zero at start
			std::time(&startTime); // store time at time of initialization
			start = 2;
			break;

		case 2: //drive forward at half speed until at gear
			DriveBase::drive(-0.5, -0.5);
			std::time_t currentTime;
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 1.7) { // stop after x seconds
				std::time(&startTime); // store time at time of initialization
				start = 3;
			}
			break;

		case 3: // stay stopped for 1.5 seconds; wait for gear to leave
			//NEED TO ADD SHOOTING WHILE PLACING GEAR
			DriveBase::drive(0.0, 0.0);
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 1) { // stop after 2 seconds
				std::time(&startTime); // store time at time of initialization
				start = 4;
			}
			break;

		case 4: //move backwards away from gear
			DriveBase::drive(0.5, 0.5);
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 0.4) { // stop after 2 seconds
				DriveBase::resetAHRS();
				start = 5;
			}
			break;

		case 5: //turn left 90 degrees
			DriveBase::drive(0.4, 0.4);
			if (DriveBase::getYaw() <= -30) //turn until facing left
				std::time(&startTime); // store time at time of initialization
				start = 6;
			break;

		case 6: // go forward to be ready to turn right
			DriveBase::drive(-0.5, -0.5);
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 0.5) { // stop after 2 seconds
				DriveBase::resetAHRS();
				start = 5;
			}
			break;

		case 7:
			DriveBase::drive(0.0, 0.0);
		}
}

void Auton::BlueLeftAuton(){
	//Auton for BlueLeft
	//Robot will get balls from hopper
	//Go to the Left Gear and deliver it -- while shooting balls at the same time
	//after delivering the gear, stop and don't move till teleop
	//switch case here
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
}
void Auton::periodic(int routine) {

}
