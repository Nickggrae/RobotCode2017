//made by the one and only Nicholas Wharton
//#include "Shared.h"
#include "Intake.h"

CANTalon* Intake::Intakeu;
double Intake::motorSpeed;

void Intake::init(){
	Intake::Intakeu = new CANTalon(7);
}

void Intake::turnOn(){
	Intake::Intakeu->Set(1.0);
}

void Intake::turnOff(){
	Intake::Intakeu->Set(0.0);
}
