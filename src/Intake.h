#include "Shared.h"
//#include <CANTalon.h>

class Intake{

public:
	// CANTalon used to control the intake
	static CANTalon* Intakeu;
	static double motorSpeed;
	//initialize the CANTalon for intake
	static void init();
	//turns on intake
	static void turnOn();
	//turns off intake
	static void turnOff();
	// checks if the intake is on (for toggle)
	static bool isOn();
	// Switches intake from on to off if intake button is pressed
	static void toggleIntake();

};
