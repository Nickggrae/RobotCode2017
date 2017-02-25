#include "Climber.h"

Climber& Climber::getInstance(){
	static Climber instance;
	return instance;
}

void Climber::init(){
	climb = new CANTalon(MAP_CLIMBER);
	climb->ClearStickyFaults();
	climb->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);
}

void Climber::ClimbUp(){
	climb->Set(-1.0);
}

void Climber::turnOff(){
	climb->Set(0);
}
