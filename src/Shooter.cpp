#include "Shooter.h"

Shooter& Shooter::getInstance(){
	static Shooter instance;
	return instance;
}

void Shooter::init() {
	shooterMaster = new CANTalon(MAP_SHOOTERMASTER);
	shooterMaster->Set (0.0);
	shooterMaster->SetFeedbackDevice(CANTalon::EncRising);
	shooterMaster->SetStatusFrameRateMs(CANTalon::StatusFrameRate::StatusFrameRateFeedback, 1);
	shooterMaster->ConfigEncoderCodesPerRev(1024);
	shooterMaster->ConfigNominalOutputVoltage(+0., -0.);
	shooterMaster->ConfigPeakOutputVoltage(+12., -12.);
	shooterMaster->SetAllowableClosedLoopErr(0);
	shooterMaster->SelectProfileSlot(0);
	shooterMaster->SetPID(6.25,0.0025,0.0);
	shooterMaster->SetControlMode(CANSpeedController::kSpeed);

	shooterSlave = new CANTalon(MAP_SHOOTERSLAVE);
	shooterSlave->SetControlMode(CANTalon::ControlMode::kFollower);
	shooterSlave->Set(shooterMaster->GetDeviceID());


	angle = new CANTalon(MAP_ANGLE);
	angle->Set (0.0);
	angle ->SetFeedbackDevice(CANTalon::QuadEncoder);
	angle->ConfigEncoderCodesPerRev(1024);
	angle->ConfigNominalOutputVoltage(+0., -0.);
	angle->ConfigPeakOutputVoltage(+12., -12.);
	angle->SetAllowableClosedLoopErr(0.5);
	angle->SelectProfileSlot(0);
	angle->SetPID(.005,0.0,0.0);
	angle->SetControlMode(CANSpeedController::kPosition);
	angle->SetSensorDirection(true);

	shooterIntake = new CANTalon(MAP_SHOOTERINTAKE);
	shooterIntake->Set(0.0);
	shooterIntake->SetInverted(false);

}

void Shooter::set(double rpm){
	shooterMaster->Set(rpm);
}

double Shooter::get(){
	return shooterMaster->GetSpeed();
}

//Set CANTalon rotations based on angle
void Shooter::setangle(double angleToSet){
	angle->Set(angleToSet);// * (0.007638888888889));f
}
double Shooter::getangle(){
	return (angle->GetNumberOfQuadIdxRises());// / .00076388888888889);
}

void Shooter::agitatorOn(){
	shooterIntake->Set(0.5);
}

void Shooter::agitatorOff(){
	shooterIntake->Set(0.0);
}

void Shooter::resetAngle(){
	angle->Reset();
}
