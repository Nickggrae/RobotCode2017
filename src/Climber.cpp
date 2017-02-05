#include "Climber.h"

CANTalon* Climber::climb;
Joystick* Climber::joy;


void Climber::init(){
	climb = new CANTalon(0);
}

void Climber::turnOn(){
	Climber::climb->Set(0.9);
}
