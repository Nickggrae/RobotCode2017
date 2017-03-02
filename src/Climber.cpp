#include <Climber.hpp>

#include <MotorMap.hpp>

namespace Climber {

	CANTalon* climb;
	bool initialized = false;

	void init() {
		if(initialized) return;

		climb = new CANTalon(MOTOR_MAP_CLIMBER);
		climb->ClearStickyFaults();
		climb->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);

		initialized = true;
	}

	void ClimbUp(){
		climb->Set(-1.0);
	}

	void turnOff(){
		climb->Set(0);
	}

}
