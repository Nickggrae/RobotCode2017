#include "Shared.h"
#include "Auton.h"
#include <ctime>
#include "AHRS.h"

// used to record time at auton init
std::time_t startTime;
int start = 1;//Declared as a double so that we can create decimal states when we want to insert a state (for example 5.1)

void Auton::init() {
	SmartDashboard::PutNumber("State",0.0);
	DriveBase::enableBrake();
	DriveBase::resetAHRS();//Resetting NavX before getting angle
	start = 1;
//	time(&startTime); // store time at time of initialization
//	DriveBase::drive(0.5, 0.5);
}

void Auton::periodic(int routine) {
	switch(routine)
	{
	case 0://Auton for nothing
		DriveBase::drive(0.0,0.0);
	break;

	case 1://Auton for RedRight
		switch(start)
		{
		case 1: //set start time to zero at start
			std::time(&startTime); // store time at time of initialization
			start = 2;
		break;

		case 2: //drive forward at half speed until ready to turn to get gear
			DriveBase::drive(-0.45, -0.45);
			std::time_t currentTime;
			std::time(&currentTime);
			//double difference = difftime(currentTime, startTime); // get difference in seconds
			if (std::difftime(currentTime, startTime) >= 1.03) { // stop after x seconds
				DriveBase::resetAHRS();//Resetting NavX before getting angle
				start = 3;
			}
		break;

		case 3: // turn left 45 degrees to head to gear
			DriveBase::drive(-0.28,0.28);
			if(DriveBase::getYaw() <= -45){
				start = 4;
			}
		break;

		case 4: // reset time to zero
			std::time(&startTime); // store time at time of initialization
			start = 5;
		break;

		case 5: // drive forward till at gear
			DriveBase::drive(-0.4, -0.4);
//			std::time_t currentTime;
			std::time(&currentTime);
			//double difference = difftime(currentTime, startTime); // get difference in seconds
			if (std::difftime(currentTime, startTime) >= 2.9) { // stop after 2 seconds
				start = -1;
			}
		break;

		case -1: // reset time to zero and stop driving; wait for person to pick up gear
			std::time(&startTime); // store time at time of initialization
			DriveBase::drive(0.0, 0.0);
			start = -2;
		break;

		case -2: // stay stopped for 1.5 seconds; wait for gear to leave
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 1.5) { // stop after 2 seconds
				start = 6;
			}
		break;

		case 6: // reset time to zero and drive backward at half speed away from airship
			std::time(&startTime); // store time at time of initialization
			DriveBase::drive(0.5, 0.5);
			start = 7;
		break;

		case 7: // drive backward for 2.5 seconds away from gear
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 2.5) { // stop after 2 seconds
				DriveBase::resetAHRS();
				start = 8;//Change later - just to get gear on for now
			}
		break;

		case 8: // turn right for 45 degrees to head to hopper
			DriveBase::drive(0.5, -0.5);
			if(DriveBase::getYaw() >= 135)
				start = 9;
			break;

		case 9: // reset time and drive forward towards hopper
			std::time(&startTime); // store time at time of initialization
			DriveBase::drive(-0.5, -0.5);
			start = 10;
		break;

		case 10: // drive forward for 2 seconds to hopper
			std::time(&currentTime);
			if (std::difftime(currentTime, startTime) >= 2) {
				DriveBase::resetAHRS();
				start = 11;
			}
		break;

		case 11: //
			DriveBase::drive(0.5, -0.5);
			if(DriveBase::getYaw() >= 90){
				start = 12;
			}
		break;

		case 12:
			std::time(&startTime); // store time at time of initialization
			DriveBase::drive(0.5, 0.5);
			start = 13;
		break;

		case 13:
//			std::time_t currentTime;
			std::time(&currentTime);
			//double difference = difftime(currentTime, startTime); // get difference in seconds
			if (std::difftime(currentTime, startTime) >= 3) { // stop after 3 seconds
				start = 14;
			}
		break;

		case 14:
			DriveBase::drive(-0.5, 0.5);
			if(DriveBase::getYaw() == -90){
				start = 15;
			}
		break;

		case 15:
			std::time(&startTime); // store time at time of initialization
			DriveBase::drive(0.5, 0.5);
			start = 16;
		break;

		case 16:
//				std::time_t currentTime;
			std::time(&currentTime);
			//double difference = difftime(currentTime, startTime); // get difference in seconds
			if (std::difftime(currentTime, startTime) >= 2) { // stop after 2 seconds
				start = 17;
			}
		break;

		case 17:
			frc::Wait(2);
			start = 18;
		break;

		case 18:
			std::time(&startTime); // store time at time of initialization
			DriveBase::drive(-0.5, -0.5);
			start = 19;
		break;

		case 19:
//			std::time_t currentTime;
			std::time(&currentTime);
			//double difference = difftime(currentTime, startTime); // get difference in seconds
			if (std::difftime(currentTime, startTime) >= 2) { // stop after 2 seconds
				start = 20;
			}
		break;

		case 20:
			DriveBase::drive(0.5, -0.5);
			if(DriveBase::getYaw() == 0){
				start = 21;
			}
			else
				DriveBase::drive(0.5, -0.5);
		break;

		case 21:
			std::time(&startTime); // store time at time of initialization
			DriveBase::drive(-0.5, -0.5);
			start = 22;
		break;

		case 22:
//			std::time_t currentTime;
			std::time(&currentTime);
			//double difference = difftime(currentTime, startTime); // get difference in seconds
			if (std::difftime(currentTime, startTime) >= 4) { // stop after 2 seconds
				start = 23;
			}
		break;

		case 23:
			DriveBase::drive(0, 0);
		break;

		default:
			std::cout << "Passed limit on RedLeft!" << std::endl;
		break;
		}
		SmartDashboard::PutNumber("State", start);
		SmartDashboard::PutNumber("NavXYaw", DriveBase::getYaw());
		SmartDashboard::PutNumber("NavXRoll", DriveBase::getRoll());
		SmartDashboard::PutNumber("NavXPitch", DriveBase::getPitch());
	break;



	case 2://Auton for RedRight
		//Add switch case here
	break;

	case 3://Auton for BlueLeft
		//switch case here
	break;

	case 4://Auton for BlueMiddle
		switch(start){
		case 1:
//		std::time(&currentTime);
//		DriveBase::drive(.45, .45);
//		if(std::difftime(currentTime, startTime) >= 3){
//			start = 2;
//		}
		break;

		case 2:
			DriveBase::drive(0,0);
		break;

		}
	break;

	case 5://Auton for BlueRight
		//switch case here
	break;
	}
}
