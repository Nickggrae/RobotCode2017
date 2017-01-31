#include "Shared.h"
//#include <CANTalon.h>

class Intake{

public:
	static CANTalon* Intakeu;
	static double motorSpeed;

	static void init();

	static void turnOn();
//	static double turnon;
	static void turnOff();
	static bool isOn();

};
