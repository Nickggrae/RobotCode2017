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
	shooterMaster->SetVoltageRampRate(12);
	shooterMaster->SelectProfileSlot(0);
	shooterMaster->SetPID(0.6,0.0001,0.00005);
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
	angle->SetPID(.0034,0.0,0.00015);
	angle->SetControlMode(CANSpeedController::kPosition);
	angle->SetSensorDirection(true);

	shooterIntake = new CANTalon(MAP_SHOOTERINTAKE);
	shooterIntake->Set(0.0);
	shooterIntake->SetFeedbackDevice(CANTalon::EncRising);
	shooterIntake->SetStatusFrameRateMs(CANTalon::StatusFrameRate::StatusFrameRateFeedback, 1);
	shooterIntake->SetClosedLoopOutputDirection(true);
	shooterIntake->SetSensorDirection(false);
	shooterIntake->ConfigEncoderCodesPerRev(1024);
	shooterIntake->ConfigNominalOutputVoltage(+0., -0.);
	shooterIntake->ConfigPeakOutputVoltage(+12., -12.);
	shooterIntake->SetAllowableClosedLoopErr(0);
	shooterIntake->SelectProfileSlot(0);
	shooterIntake->SetPID(1,0.002,0.0);
	shooterIntake->SetControlMode(CANSpeedController::kSpeed);
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
	return (angle->GetPosition());// / .00076388888888889);
}

void Shooter::agitatorOn(){
	shooterIntake->Set(2400);
}

void Shooter::agitatorOff(){
	shooterIntake->Set(0.0);
}

double Shooter::agitatorRPM(){
	return shooterIntake->GetSpeed();
}
void Shooter::resetAngle(){
	angle->Reset();
}

bool Shooter::agitatorIsOn() {
	return (abs(shooterIntake->Get()) > 0.1); // Returns true if intake is on
}

CANTalon * Shooter::getShooterCANTalon() {
	return shooterMaster;
}

void Shooter::agitatorToggle() { // Used for toggle in Teleop
	if (Shooter::agitatorIsOn()) {
		Shooter::agitatorOff();
	} else {
		Shooter::agitatorOn();
	}
}
