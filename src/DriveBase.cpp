#include "DriveBase.h"

CANTalon* DriveBase::fl;
CANTalon* DriveBase::ml;
CANTalon* DriveBase::rl;
CANTalon* DriveBase::fr;
CANTalon* DriveBase::mr;
CANTalon* DriveBase::rr;

frc::DoubleSolenoid* DriveBase::solenoid;
frc::RobotDrive* DriveBase::robotDrive;
Compressor *c;


void DriveBase::init() {
	c = new Compressor();

	c->SetClosedLoopControl(true);
	DriveBase::fl = new CANTalon(7);
	DriveBase::fr = new CANTalon(5);
	DriveBase::robotDrive = new frc::RobotDrive(DriveBase::fl,DriveBase::fr);
	DriveBase::ml = new CANTalon(6);
	DriveBase::rl = new CANTalon(0);
	DriveBase::mr = new CANTalon(2);
	DriveBase::rr = new CANTalon(3);
	DriveBase::ml->SetControlMode(frc::CANSpeedController::kFollower);
	DriveBase::rl->SetControlMode(frc::CANSpeedController::kFollower);
	DriveBase::mr->SetControlMode(frc::CANSpeedController::kFollower);
	DriveBase::rr->SetControlMode(frc::CANSpeedController::kFollower);
	DriveBase::ml->Set(DriveBase::fl->GetDeviceID());
	DriveBase::rl->Set(DriveBase::fl->GetDeviceID());
	DriveBase::mr->Set(DriveBase::fr->GetDeviceID());
	DriveBase::rr->Set(DriveBase::fr->GetDeviceID());
	DriveBase::solenoid = new frc::DoubleSolenoid(0,1);
	DriveBase::solenoid->Set(frc::DoubleSolenoid::kOff);
}

void DriveBase::drive(double left, double right){
	DriveBase::robotDrive ->TankDrive(left,right,false);
}

void DriveBase::switchGear(bool gear){
	if (gear){
		DriveBase::solenoid->Set(frc::DoubleSolenoid::kForward);
		DriveBase::gearState = 1;
	}
	else{
		DriveBase::solenoid->Set(frc::DoubleSolenoid::kReverse);
		DriveBase::gearState = 0;
	}
}

int DriveBase::getGearState(){
	return gearState;
}
