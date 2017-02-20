#include "Intake.h"
#include "Copernicus.h"

Intake& Intake::getInstance(){
  static Intake instance;
  return instance;
}

void Intake::init() {
	intakeTalon = new CANTalon(MAP_INTAKETALON);
	intakeTalon->SetSafetyEnabled(false);

	saladSpinner = new CANTalon(MAP_SALADSPINNER);
	saladSpinner->SetInverted(true);
	intakeTalon->SetInverted(true);
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

void Intake::saladSpinnerOn(){
	saladSpinner->Set(.50);
}

void Intake::saladSpinnerOff(){
	saladSpinner->Set(.50);
}

bool Intake::isOnSalad(){
	return (abs(saladSpinner->Get()) > 0.1);
}

void Intake::toggleSaladSpinner(){
	if (Intake::isOnSalad()) {
		Intake::saladSpinnerOff();
	} else {
		Intake::saladSpinnerOn();
	}

}
