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
	int hello = 1;
	switch(hello){
	case 1:
		time(&startTime); // store time at time of initialization
		DriveBase::drive(0.5, 0.5);
		hello = 2;
	break;
	case 2:
		time_t currentTime;
		time(&currentTime);
		double difference = difftime(currentTime, startTime); // get difference in seconds
		if (difference >= 10) { // stop after 10 seconds
			hello = 3;
		}
		hello = 1;
	break;
	case 3:
		DriveBase::drive(0, 0);
	}
}
