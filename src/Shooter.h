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
 	void init();
public:
	static Shooter& getInstance();

	void setangle(double angleToSet);
 	double getangle();
 	double get();
 	void set(double rpm);
 	void agitatorOn();
 	void agitatorOff();
 	double agitatorRPM();
 	void agitatorToggle();
 	bool agitatorIsOn();
 	CANTalon *getShooterCANTalon();

};


