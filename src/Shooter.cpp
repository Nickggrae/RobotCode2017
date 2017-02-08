#include "Shooter.h"

CANTalon* Shooter::shooter;
CANTalon* Shooter::angle;
CANTalon* Shooter::shooterIntake;
CANTalon* Shooter::conveyor;

void Shooter::init() {
	Shooter::shooter = new CANTalon(14);
	Shooter::shooter->Set (0.0);
	Shooter::shooter->SetFeedbackDevice(CANTalon::EncRising);
	Shooter::shooter->ConfigEncoderCodesPerRev(1024);
	Shooter::shooter->ConfigNominalOutputVoltage(+0., -0.);
	Shooter::shooter->ConfigPeakOutputVoltage(+12., -12.);
	Shooter::shooter->SetAllowableClosedLoopErr(0);
	Shooter::shooter->SelectProfileSlot(0);
	Shooter::shooter->SetPID(0.2,0.0015,0.0001);
	Shooter::shooter->SetControlMode(CANSpeedController::kSpeed);


	Shooter::angle = new CANTalon(2);
	Shooter::angle->Set (0.0);
	Shooter::angle ->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	Shooter::angle ->SetClosedLoopOutputDirection(true);
	Shooter::angle->ConfigNominalOutputVoltage(+0., -0.);
	Shooter::angle->ConfigPeakOutputVoltage(+12., -12.);
	Shooter::angle->SetAllowableClosedLoopErr(0.05);
	Shooter::angle->SelectProfileSlot(0);
	Shooter::angle ->SetPID(.415,0,0);
	Shooter::angle->SetControlMode(CANSpeedController::kPosition);
	Shooter::angle->SetSensorDirection(true);

	Shooter::shooterIntake = new CANTalon(9);
	Shooter::shooterIntake->Set(0.0);
	Shooter::shooterIntake->SetInverted(true);

	Shooter::conveyor = new CANTalon(13);
	Shooter::conveyor->Set(0.0);
	Shooter::conveyor->SetInverted(true);
}

void Shooter::set(double rpm){
	Shooter::shooter->Set(rpm);
}

double Shooter::get(){
	return Shooter::shooter->GetSpeed();
}

//Set CANTalon rotations based on angle [aka ihatedavid]
void Shooter::setangle(double ihatedavid){
	Shooter::angle->Set(ihatedavid * (0.007638888888889));
}
double Shooter::getangle(){
	return (Shooter::angle->Get() / .00076388888888889);
}

void Shooter::agitatorOn(){
	Shooter::shooterIntake->Set(0.5);
	Shooter::conveyor->Set(0.5);
}

void Shooter::agitatorOff(){
	Shooter::shooterIntake->Set(0.0);
	Shooter::conveyor->Set(0.0);
}
