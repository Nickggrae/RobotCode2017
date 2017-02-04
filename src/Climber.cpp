#include "Climber.h"

CANTalon* Climber::climb;

void Climber::init(){
	climb = new CANTalon(0);
	climb->Set(0.0);

}
