#include "Shared.h"
//#include <CANTalon.h>

	class Shooter {
	static CANTalon* shooter;
	static CANTalon* angle;

	void Shooter::init();

	void Shooter::set(double rpm);

	double Shooter::get();

	void Shooter::setangle(double position);

	double Shooter::getangle();
};
