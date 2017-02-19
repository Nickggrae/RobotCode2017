#pragma once
#include "Shared.h"
//#include <CANTalon.h>

class Intake{
  //singleton- hide constructor and copy constructor
 Intake() { init(); }
 Intake(Intake const&);
 void operator=(Intake const&);

   // CANTalon used to control the intake
  CANTalon* intakeTalon;
  double motorSpeed;

  //initialize the CANTalon for intake
  void init();

public:
  static Intake& getInstance();

	//turns on intake
	void turnOn();
	//turns off intake
	void turnOff();
	// checks if the intake is on (for toggle)
	bool isOn();
	// Switches intake from on to off if intake button is pressed
	void toggleIntake();



};
