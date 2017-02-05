#include "Shared.h"
#include "Auton.h"

// used to record time at auton init
time_t startTime;


void Auton::init() {
	DriveBase::init();
//	time(&startTime); // store time at time of initialization
//	DriveBase::drive(0.5, 0.5);
}

void Auton::periodic() {
	switch(start){
	case 1:
		time(&startTime); // store time at time of initialization
		DriveBase::drive(0.5, 0.5);
		start = 2;
	break;
	case 2:
		time_t currentTime;
		time(&currentTime);
		//double difference = difftime(currentTime, startTime); // get difference in seconds
		if (difftime(currentTime, startTime) >= 10) { // stop after 10 seconds
			start = 3;
		}
	break;
	case 3:
		DriveBase::drive(0, 0);
	break;
	default:
		DriveBase::drive(0, 0);
		break;
	}
}
