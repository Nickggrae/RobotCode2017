#include <Copernicus.h>
#include <Intake.hpp>

#include <MotorMap.hpp>

namespace Intake {

	// CANTalon used to control the intake
	CANTalon* intakeTalon;
	CANTalon* saladSpinner;
	double motorSpeed;
	bool initialized = false;

	void init() {
		if(initialized) return;

		intakeTalon = new CANTalon(MOTOR_MAP_FLOOR_INTAKE);
		intakeTalon->SetSafetyEnabled(false);
		intakeTalon->SetInverted(true);

		saladSpinner = new CANTalon(MOTOR_MAP_SALAD_SPINNER);
		saladSpinner->SetSafetyEnabled(false);

		initialized = true;
	}

	void turnOn() {
		intakeTalon->Set(1.0);
	}

	void turnOff() {
		intakeTalon->Set(0.0);
	}

	bool isOn() {
		return (abs(intakeTalon->Get()) > 0.1); // Returns true if intake is on
	}

	void toggleIntake() { // Used for toggle in Teleop
		if (Intake::isOn()) {
			Intake::turnOff();
			Copernicus::setFloorIntake(false);
		} else {
			Intake::turnOn();
			Copernicus::setFloorIntake(true);
		}
	}

	void saladOff(){
		saladSpinner->Set(0.0);
	}

	void saladOn(){
		saladSpinner->Set(0.5);
	}

	bool isSalading(){
		return (saladSpinner->Get() != 0.0);
	}

	void toggleSalad(){
		if (Intake::isSalading()) {
			Intake::saladOff();
		} else {
			Intake::saladOn();
		}
	}
}
