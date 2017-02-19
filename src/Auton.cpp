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
		case 10: //set start time to zero at start
			StayStill();
			start = 20;
			break;

		case 20: //drive forward at half speed until ready to turn to get gear
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
		case 1: //set start time to zero at start
			start = 2;
			break;

		case 2: //drive forward at half speed until ready to turn to get gear
			DriveForward();
			if(waited(2)){ //maybe 2
				start = 3;
			}
		break;

		case 3: // turn left 45 degrees to head to gear
			TurnLeft();
			if (DriveBase::getYaw() >= 6) {
				start = 4;
			}
		break;

		case 4: // drive forward till at gear
			DriveForward();
			if(waited(2)){
				start = 5;
			}
		break;

		case 5: // reset time to zero and stop driving; wait for person to pick up gear
			StayStill();
			start = 6;
		break;

		case 6: // stay stopped for 1.5 seconds; wait for gear to leave
			if(waited(1.5)){
				start = 8;
			}
		break;

		case 8: // drive backward away from gear
			DriveBackwards();
			if(waited(1.5)){
				start = 9;
			}
			break;

		case 9: // turn right for 135 degrees to head to launchpad line
			TurnRight();
			if (DriveBase::getYaw() <= -45){ //turn left until facing forward to launchpad line
				start = 11;
			}
			break;

		case 11: // drive forward for 2 seconds until at launchpad line
			DriveForward();
			if(waited(1.5)){
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
			start = 20;
			break;

		case 20: //drive forward at half speed until at gear
			DriveForward();
			if(waited(1)){
				start = 30;
			}
			break;

		case 30: // stay stopped for 1.5 seconds; wait for gear to leave
			//NEED TO ADD SHOOTING WHILE PLACING GEAR
			StayStill();
			if(waited(1)){
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
			if(waited(.5)){
				start = 70;
			}
			break;

		case 70:
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
	switch (start){
	case 10:
		start = 20;

	break;

	case 20:
		DriveForward(); //moves forward going towards the hopper
		if(waited(2)){
			start = 30;
		}

	break;

	case 30:
		TurnLeft();
		if (DriveBase::getYaw() >= 90) {//turn until facing left initialization
			start = 40;
		}
	break;

	case 40:
		DriveForward(); //
		if(waited(0.8)){
			start = 50;
		}
	break;

	case 50:
		StayStill();
		if(waited(3)){
			start = 60;
		}
	break;

	case 60:
		DriveBackwards();
		if(waited(.8)){
			start = 70;
		}
	break;
	}
}
// this is not done yet

void Auton::BlueMiddleAuton(){
	//Goes forward and delivers gears
	//Shoots while waiting for the gear
	//Turns right and goes to the line
	switch (start) {
		case 10: //set start time to zero at start
			start = 20;
			break;

		case 20: //drive forward at half speed until at gear
			DriveForward();
			if(waited(1)){
				start = 30;
			}
			break;

		case 30: // stay stopped for 1.5 seconds; wait for gear to leave
			//NEED TO ADD SHOOTING WHILE PLACING GEAR
			StayStill();
			if(waited(1)){
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
			if(waited(.5)){
				start = 70;
			}
			break;

		case 70:
			StayStill();
		break;

	}
}

void Auton::RedRightAuton(){
	//Auton for RedRight
	//Robot will go to the hopper to get the balls
	//Drive to the gear and deliver it
	//while at the gear, shoot the balls that were picked up from the hopper
	//stay at the gear and don't move until teleop...
	switch (start){
	case 10:
		start = 20;
	break;

	case 20:
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
		if(waited(.6)){
			start = 50;
		}
	break;

	case 50:
		DriveBackwards(); //moves backwards away from the hopper
		if(waited(.8)){
			start = 60;
		}
	break;

	case 60:	//angle is estimated by Oliver, if it is wrong it is Oliver's fault...
		TurnLeft();
		if(DriveBase::getYaw() <= -90) {
			start = 70;
		}
	break;

	case 70:
		DriveBackwards();//moves the robot to the gear
		if(waited(1.5)){
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
