#include "Shared.h"

class Climber{
	static CANTalon* climb;
public:
	static void init();
	static void turnOn();
	static void back();
};
