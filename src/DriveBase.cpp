#include "DriveBase.h"


CANTalon* DriveBase::fl;
CANTalon* DriveBase::rl;
CANTalon* DriveBase::fr;
CANTalon* DriveBase::rr;

int DriveBase::gearState;

frc::DoubleSolenoid* DriveBase::solenoid;
frc::RobotDrive* DriveBase::robotDrive;
Compressor *c;
//AHRS ahrs = AHRS(frc::SPI::Port);

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
	DriveBase::solenoid->Set(frc::DoubleSolenoid::kReverse);

}

void DriveBase::drive(double left, double right){
	DriveBase::robotDrive ->TankDrive(left,right,false);
}

void DriveBase::switchGear(bool gear){
	SmartDashboard::PutBoolean("JordanIsGay", gear);
	if (gear){
		DriveBase::solenoid->Set(frc::DoubleSolenoid::kForward); //sets into high gear
		DriveBase::gearState = 1; //1 is high gear
	}
	else{
		DriveBase::solenoid->Set(frc::DoubleSolenoid::kReverse); //sets into low gear
		DriveBase::gearState = 0; //0 is low gear
	}
}

int DriveBase::getGearState(){
	return DriveBase::gearState;
}
