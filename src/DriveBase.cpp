#include "DriveBase.h"


CANTalon* DriveBase::fl;
CANTalon* DriveBase::rl;
CANTalon* DriveBase::fr;
CANTalon* DriveBase::rr;

int DriveBase::gearState;

frc::DoubleSolenoid* DriveBase::solenoid;
frc::RobotDrive* DriveBase::robotDrive;
Compressor *c;
AHRS* ahrs;

void DriveBase::init() {


	DriveBase::fl = new CANTalon(2);
	DriveBase::fl->SetInverted(true);
	DriveBase::fr = new CANTalon(3);
	DriveBase::rl = new CANTalon(4);
	DriveBase::rl->SetInverted(true);
	DriveBase::rr = new CANTalon(9);
	DriveBase::robotDrive = new frc::RobotDrive(DriveBase::fl,DriveBase::rl,DriveBase::fr,DriveBase::rr);

	c = new Compressor(1);
	c->SetClosedLoopControl(true);
	c->Start();

	DriveBase::solenoid = new frc::DoubleSolenoid(1, 0, 1);
	DriveBase::solenoid->Set(frc::DoubleSolenoid::kOff);

	ahrs = new AHRS(frc::SPI::Port);
}

void DriveBase::drive(double left, double right){
	DriveBase::robotDrive ->TankDrive(left,right,false);
}

void DriveBase::switchGear(bool gear){
	SmartDashboard::PutBoolean("JordanIsGay", gear);
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
	return DriveBase::gearState;
}
