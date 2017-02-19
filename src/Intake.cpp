#include "Intake.h"
#include "Copernicus.h"

Intake& Intake::getInstance(){
  static Intake instance;
  return instance;
}

void Intake::init() {
	intakeTalon = new CANTalon(12);
	intakeTalon->SetSafetyEnabled(false);
}

void Intake::turnOn() {
	intakeTalon->Set(.50);
}

void Intake::turnOff() {
	intakeTalon->Set(0.0);
}

bool Intake::isOn() {
	return (intakeTalon->Get() > 0.1); // Returns true if intake is on
}

void Intake::toggleIntake() { // Used for toggle in Teleop
	if (isOn()) {
		turnOff();
		Copernicus::setFloorIntake(false);
	} else {
		turnOn();
		Copernicus::setFloorIntake(true);
	}
}
