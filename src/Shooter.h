#include "Shared.h"

	class Shooter {
	static CANTalon* shooter;

	void Shooter::init();

	void Shooter::set(double rpm);

	double Shooter::get();
};
