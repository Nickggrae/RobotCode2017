#include "Shooter.h"

CANTalon* Shooter::shooter;

	void Shooter::init() {

		Shooter::shooter = new CANTalon(5);
		Shooter::shooter->Set (0.0);
		Shooter::shooter ->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
		Shooter::shooter->ConfigNominalOutputVoltage(+0., -0.);
		Shooter::shooter->ConfigPeakOutputVoltage(+12., -12.);
		Shooter::shooter->SetAllowableClosedLoopErr(0);
		Shooter::shooter->SelectProfileSlot(0);
		Shooter::shooter ->SetPID(0.2,0.00015,0.0011);
		Shooter::shooter ->SetPID(0.2,0.0001,0.001);
		Shooter::shooter->SetControlMode(CANSpeedController::kSpeed);
	}
	void Shooter::set(double rpm){
		Shooter::shooter->Set(rpm);
	}
	double Shooter::get(){
		return Shooter::shooter->Get();
	}
