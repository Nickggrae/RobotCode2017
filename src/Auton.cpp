#include "Shared.h"
#include "Auton.h"

// used to record time at auton init
time_t startTime;


void Auton::init() {
	DriveBase::init();
	time(&startTime); // store time at time of initialization
	DriveBase::drive(0.5, 0.5);
}

void Auton::periodic() {
	time_t currentTime;
	time(&currentTime);
	double difference = difftime(currentTime, startTime); // get difference in seconds
	if (difference >= 10) { // stop after 10 seconds
		DriveBase::drive(0, 0);
	}
}
