#pragma once
#include "Shared.h"

class Climber{
	CANTalon* climb;
	Climber() { init(); }
	// singleton methods - no definition
	Climber(Climber const&);
	void operator=(Climber const&);
	void init();

public:
	static Climber& getInstance();
	void turnOn();
	void back();
	void turnOnSlow();
	void turnOff();
};
