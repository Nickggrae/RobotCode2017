#include "Intake.h"
#include "Copernicus.h"

Intake& Intake::getInstance(){
  static Intake instance;
  return instance;
}

void Intake::init() {
	intakeTalon = new CANTalon(MAP_INTAKETALON);
	intakeTalon->SetSafetyEnabled(false);
	intakeTalon->SetInverted(true);

	saladSpinner = new CANTalon(MAP_SALADSPINNER);
	saladSpinner->SetSafetyEnabled(false);
}

void Intake::turnOn() {
	intakeTalon->Set(1.0);
}

void Intake::turnOff() {
	intakeTalon->Set(0.0);
}

bool Intake::isOn() {
	return (abs(intakeTalon->Get()) > 0.1); // Returns true if intake is on
}

void Intake::toggleIntake() { // Used for toggle in Teleop
	if (Intake::isOn()) {
		Intake::turnOff();
		Copernicus::setFloorIntake(false);
	} else {
		Intake::turnOn();
		Copernicus::setFloorIntake(true);
	}
}

void Intake::saladOff(){
	saladSpinner->Set(0.0);
}

void Intake::saladOn(){
	saladSpinner->Set(0.5);
}

bool Intake::isSalading(){
	return (saladSpinner->Get() != 0.0);
}

void Intake::toggleSalad(){
	if (Intake::isSalading()) {
		Intake::saladOff();
	} else {
		Intake::saladOn();
	}
}

