#include "Shooter.h"

CANTalon* Shooter::shooter;
CANTalon* Shooter::angle;
CANTalon* Shooter::shooterIntake;
CANTalon* Shooter::conveyor;

void Shooter::init() {
	Shooter::shooter = new CANTalon(5);
	Shooter::shooter->Set (0.0);
	Shooter::shooter->SetFeedbackDevice(CANTalon::EncRising);
	Shooter::shooter->SetStatusFrameRateMs(CANTalon::StatusFrameRate::StatusFrameRateFeedback, 1);
	Shooter::shooter->ConfigEncoderCodesPerRev(1024);
	Shooter::shooter->ConfigNominalOutputVoltage(+0., -0.);
	Shooter::shooter->ConfigPeakOutputVoltage(+12., -12.);
	Shooter::shooter->SetAllowableClosedLoopErr(0);
	Shooter::shooter->SelectProfileSlot(0);
	Shooter::shooter->SetPID(6.25,0.0025,0.0);
	Shooter::shooter->SetControlMode(CANSpeedController::kSpeed);


	Shooter::angle = new CANTalon(2);
	Shooter::angle->Set (0.0);
	Shooter::angle ->SetFeedbackDevice(CANTalon::QuadEncoder);
	Shooter::angle->ConfigEncoderCodesPerRev(1024);
	Shooter::angle->ConfigNominalOutputVoltage(+0., -0.);
	Shooter::angle->ConfigPeakOutputVoltage(+12., -12.);
	Shooter::angle->SetAllowableClosedLoopErr(0.5);
	Shooter::angle->SelectProfileSlot(0);
	Shooter::angle ->SetPID(.005,0.0,0.0);
//	Shooter::angle->SetPID(0.005, 0.0, 0.0);
	Shooter::angle->SetControlMode(CANSpeedController::kPosition);
	Shooter::angle->SetSensorDirection(true);

	Shooter::shooterIntake = new CANTalon(3);
	Shooter::shooterIntake->Set(0.0);
	Shooter::shooterIntake->SetInverted(false);

	Shooter::conveyor = new CANTalon(2);
	Shooter::conveyor->Set(0.0);
	Shooter::conveyor->SetInverted(false);
}

void Shooter::set(double rpm){
	Shooter::shooter->Set(rpm);
}

double Shooter::get(){
	return Shooter::shooter->GetSpeed();
}

//Set CANTalon rotations based on angle [aka ihatedavid]
void Shooter::setangle(double ihatedavid){
	Shooter::angle->Set(ihatedavid);// * (0.007638888888889));
}
double Shooter::getangle(){
	return (Shooter::angle->GetNumberOfQuadIdxRises());// / .00076388888888889);
}

void Shooter::agitatorOn(){
	Shooter::shooterIntake->Set(0.5);
	Shooter::conveyor->Set(0.45);
}

void Shooter::agitatorOff(){
	Shooter::shooterIntake->Set(0.0);
	Shooter::conveyor->Set(0.0);
}

void Shooter::resetAngle(){
	Shooter::angle->Reset();
}
