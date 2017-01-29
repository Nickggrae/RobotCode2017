#include "Intake.h"

CANTalon* Intake::Intakeu;
double Intake::motorSpeed;

void Intake::init(){
	Intake::Intakeu = new CANTalon(0);
}

void Intake::turnOn(){
	Intake::Intakeu->Set(.50);
}

void Intake::turnOff(){
	Intake::Intakeu->Set(0.0);
}
