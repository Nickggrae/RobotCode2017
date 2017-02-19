#include "Climber.h"

Climber& Climber::getInstance(){
	static Climber instance;
	return instance;
}

void Climber::init(){
	climb = new CANTalon(4);
	climb->ClearStickyFaults();
	climb->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);
}

void Climber::turnOn(){
	Climber::climb->Set(0.9);
}
void Climber::back(){
	Climber::climb->Set(-0.3);
}
void Climber::turnOnSlow(){
	Climber::climb->Set(0.3);
}
void Climber::turnOff(){
	Climber::climb->Set(0);
}
