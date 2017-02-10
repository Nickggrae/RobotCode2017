#pragma once
#include "Shared.h"
 //#include <CANTalon.h>

class Shooter {
public:
	static CANTalon* shooter;
 	static CANTalon* angle;
 	static CANTalon* shooterIntake;
 	static CANTalon* conveyor;

 	static void init();

 	static void set(double rpm);

 	static double get();

 	static void setangle(double ihatedavid);

 	static double getangle();

 	static void agitatorOn();

 	static void agitatorOff();
};


