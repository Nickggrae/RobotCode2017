#include "Shared.h"
#include "Auton.h"
#include <ctime>

// used to record time at auton init
std::time_t startTime;


void Auton::init() {
	DriveBase::init();
//	time(&startTime); // store time at time of initialization
//	DriveBase::drive(0.5, 0.5);
}
	int start = 1;
void Auton::periodic() {
	switch(start){
	case 1:
		std::time(&startTime); // store time at time of initialization
		DriveBase::drive(0.5, 0.5);
		start = 2;
	break;
	case 2:
		std::time_t currentTime;
		std::time(&currentTime);
		//double difference = difftime(currentTime, startTime); // get difference in seconds
		if (std::difftime(currentTime, startTime) >= 10) { // stop after 10 seconds
			start = 3;
		}
	break;
	default:
	case 3:
		DriveBase::drive(0, 0);
	break;
	}
}
