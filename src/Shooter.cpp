#include "Shooter.h"

CANTalon* Shooter::shooter;
CANTalon* Shooter::angle;

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
	Shooter::shooter->SetControlMode(CANSpeedController::kSpeed);s

	Shooter::angle = new CANTalon(8);
	Shooter::angle->Set (0.0);
	Shooter::angle ->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	Shooter::angle->ConfigNominalOutputVoltage(+0., -0.);
	Shooter::angle->ConfigPeakOutputVoltage(+12., -12.);
	Shooter::angle->SetAllowableClosedLoopErr(0);
	Shooter::angle->SelectProfileSlot(0);
	Shooter::angle ->SetPID(0.2,0.00015,0.0011);
	Shooter::angle ->SetPID(0.2,0.0001,0.001);
	Shooter::angle->SetControlMode(CANSpeedController::kPosition);
}
void Shooter::set(double rpm){
	Shooter::shooter->Set(rpm);
}
double Shooter::get(){
	return Shooter::shooter->Get();
}

void Shooter::setangle(double position){
	Shooter::angle->Set(position);
}
double Shooter::getangle(){
	return Shooter::angle->Get();
}

