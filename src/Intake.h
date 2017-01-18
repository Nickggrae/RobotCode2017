#include "Shared.h"
#include <CANTalon.h>
#include "Intake.cpp"

class intake{

	static CANTalon* Intakeu;

public:

	static void init();

	static void turnOn();

};
