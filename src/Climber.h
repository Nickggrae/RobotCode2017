#pragma once
#include "Shared.h"

class Climber{
	static CANTalon* climb;
public:
	static void init();
	static void turnOn();
	static void back();
	static void turnOnSlow();
	static void turnOff();
};
