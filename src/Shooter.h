#pragma once
#include "Shared.h"
 //#include <CANTalon.h>

class Shooter {
	//singleton- hide constructor and copy constructor
	Shooter() { init(); }
	Shooter(Shooter const&);
	void operator=(Shooter const&);

	CANTalon* shooterMaster;
	CANTalon* shooterSlave;
	CANTalon* angle;
	CANTalon* shooterIntake;

 	void resetAngle();
public:
	static Shooter& getInstance();

	void setangle(double angleToSet);
 	void init();
 	double getangle();
 	double get();
 	void set(double rpm);
 	void agitatorOn(double rpm);
 	void agitatorOff();
 	double agitatorRPM();
};


