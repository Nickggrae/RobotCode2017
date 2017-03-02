
#ifndef INCLUDE_INTAKE_HPP_
#define INCLUDE_INTAKE_HPP_

#include <Shared.hpp>

namespace Intake {

	//initialize the CANTalon for intake
	void init();

	//turns on intake
	void turnOn();
	//turns off intake
	void turnOff();
	// checks if the intake is on (for toggle)
	bool isOn();
	// Switches intake from on to off if intake button is pressed
	void toggleIntake();

	void saladOn();

	void saladOff();

	bool isSalading();

	void toggleSalad();
};

#endif /* INCLUDE_INTAKE_HPP_ */
