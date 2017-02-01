#include "Shared.h"
#include "Auton.h"
#include <ctime>

time_t startTime;

void Auton::init() {
	DriveBase::init();
	time(&startTime);
	DriveBase::drive(0.5, 0.5);
}

void Auton::periodic() {
	time_t currentTime;
	time(&currentTime);
	double difference = difftime(currentTime, startTime);
	if (difference >= 10) {
		DriveBase::drive(0, 0);
	}
}
