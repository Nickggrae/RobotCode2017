#include "Shared.h"
#include "Auton.h"
#include <ctime>
#include "AHRS.h"

// used to record time at auton init
std::time_t startTime;

void Auton::init() {
	SmartDashboard::PutNumber("State",0.0);
//	time(&startTime); // store time at time of initialization
//	DriveBase::drive(0.5, 0.5);
}

enum Auton::AutonRoutines
{
	RedLeft = 0,
	RedMiddle = 1,
	RedRight = 2,
	BlueLeft = 3,
	BlueMiddle = 4,
	BlueRight = 5
};
	int start = 1;
void Auton::periodic(int routine) {
	switch(routine)
	{
	case 0://Auton for RedLeft
		switch(start)
		{
		case 1:
			std::time(&startTime); // store time at time of initialization
			DriveBase::drive(0.5, 0.5);
			start = 2;
		break;

		case 2:
			std::time_t currentTime;
			std::time(&currentTime);
			//double difference = difftime(currentTime, startTime); // get difference in seconds
			if (std::difftime(currentTime, startTime) >= 5) { // stop after 5 seconds
				start = 3;
			}
		break;

		case 3:
			DriveBase::drive(0.5,-0.5);
			if(DriveBase::getYaw() == 45){
				start = 4;
			}
			else
				DriveBase::drive(0.5, -0.5);
			break;

		case 4:
			std::time(&startTime); // store time at time of initialization
					DriveBase::drive(0.5, 0.5);
					start = 5;
			break;

		case 5:
			std::time_t currentTime;
					std::time(&currentTime);
					//double difference = difftime(currentTime, startTime); // get difference in seconds
					if (std::difftime(currentTime, startTime) >= 2) { // stop after 2 seconds
						start = 5.1;
					}
			break;

		case 5.1:
				std::time(&startTime); // store time at time of initialization
						DriveBase::drive(0.0, 0.0);
						start = 5.2;
				break;

			case 5.2:
				std::time_t currentTime;
						std::time(&currentTime);
						//double difference = difftime(currentTime, startTime); // get difference in seconds
						if (std::difftime(currentTime, startTime) >= 1.5) { // stop after 2 seconds
							start = 6;
						}
			break;

		case 6:
			std::time(&startTime); // store time at time of initialization
							DriveBase::drive(-0.5, -0.5);
							start = 7;
			break;

		case 7:
			std::time_t currentTime;
							std::time(&currentTime);
							//double difference = difftime(currentTime, startTime); // get difference in seconds
							if (std::difftime(currentTime, startTime) >= 2) { // stop after 2 seconds
								start = 8;
			break;

		case 8:
			DriveBase::drive(0.5, -0.5);
			if(DriveBase::getYaw() == -45)
				start = 9;
			else
				DriveBase::drive(0.5, -0.5);
			break;

		case 9:
			std::time(&startTime); // store time at time of initialization
									DriveBase::drive(-0.5, -0.5);
									start = 10;
			break;

		case 10:
			std::time_t currentTime;
				std::time(&currentTime);
				//double difference = difftime(currentTime, startTime); // get difference in seconds
			if (std::difftime(currentTime, startTime) >= 2) { // stop after 2 seconds
				start = 11;
			}
			break;

		case 11:
			DriveBase::drive(0.5, -0.5);
			if(DriveBase::getYaw() == 0){
				start = 12;
			}
			else
				DriveBase::drive(0.5, -0.5);
		break;

			case 12:
				std::time(&startTime); // store time at time of initialization
				DriveBase::drive(0.5, 0.5);
					start = 13;
			break;

			case 13:
				std::time_t currentTime;
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
				else
					DriveBase::drive(-0.5, 0.5);
			break;

			case 15:
				std::time(&startTime); // store time at time of initialization
					DriveBase::drive(0.5, 0.5);
						start = 16;
			break;

			case 16:
				std::time_t currentTime;
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
				std::time_t currentTime;
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
				std::time_t currentTime;
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
		break;


		case 1://Auton for RedMiddle
			//Add switch case here
		break;

		case 2://Auton for RedRight
			//Add switch case here
		break;

		case 3://Auton for BlueLeft
			//switch case here
		break;

		case 4://Auton for BlueMiddle
			//switch case here
		break;

		case 5://Auton for BlueRight
			//switch case here
		break;

	SmartDashboard::PutNumber("State", static_cast<double>(start));
}
