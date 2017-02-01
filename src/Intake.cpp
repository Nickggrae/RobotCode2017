#include "Intake.h"

CANTalon* Intake::Intakeu;
double Intake::motorSpeed;

void Intake::init() {
	Intake::Intakeu = new CANTalon(0);
}

void Intake::turnOn() {
	Intake::Intakeu->Set(.50);
}

void Intake::turnOff() {
	Intake::Intakeu->Set(0.0);
}

bool Intake::isOn() {
	return (Intake::Intakeu->Get() > 0.1); // Returns true if intake is on
}

void Intake::toggleIntake() { // Used for toggle in Teleop
	if (Intake::isOn()) {
		Intake::turnOff();
	} else {
		Intake::turnOn();
	}
}
