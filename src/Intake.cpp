//made by the one and only Nicholas Wharton
#include "Shared.h"
#include "Intake.h"

class Intake{

	CANTalon* Intake::Intakeu;
	int motorSpeed;


	void Intake::init(){
		Intake::Intakeu = new CANTalon(2);


	}

	void Intake::turnOn(){
		Intake::Intakeu->Set (Intake::motorSpeed);

	}
};
