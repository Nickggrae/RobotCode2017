#include "DriveBase.h"

CANTalon* DriveBase::fl;
CANTalon* DriveBase::ml;
CANTalon* DriveBase::rl;
CANTalon* DriveBase::fr;
CANTalon* DriveBase::mr;
CANTalon* DriveBase::rr;
RobotDrive* DriveBase::robotDrive;
AHRS* DriveBase::Navxahrs;
void DriveBase::init() {
	DriveBase::fl = new CANTalon(7);
	DriveBase::fr = new CANTalon(1);
	DriveBase::robotDrive = new RobotDrive(DriveBase::fl,DriveBase::fr);
	DriveBase::ml = new CANTalon(6);
	DriveBase::rl = new CANTalon(0);
	DriveBase::mr = new CANTalon(2);
	DriveBase::rr = new CANTalon(3);
	DriveBase::ml ->SetControlMode(CANSpeedController::kFollower);
	DriveBase::rl->SetControlMode(CANSpeedController::kFollower);
	DriveBase::mr->SetControlMode(CANSpeedController::kFollower);
	DriveBase::rr->SetControlMode(CANSpeedController::kFollower);
	DriveBase::ml->Set(DriveBase::fl->GetDeviceID());
	DriveBase::rl->Set(DriveBase::fl->GetDeviceID());
	DriveBase::mr->Set(DriveBase::fr->GetDeviceID());
	DriveBase::rr->Set(DriveBase::fr->GetDeviceID());

	DriveBase::Navxahrs = new AHRS(SPI::Port::kMXP);

	DriveBase::Navxahrs ->Reset();


}
void DriveBase::resetAccelGyro(){
	DriveBase::Navxahrs ->Reset();
}
void DriveBase::drive(double x, double y){
	DriveBase::robotDrive ->TankDrive(x,y,false);
}
double DriveBase::roll(){
	return DriveBase::Navxahrs ->GetRoll();
}
double DriveBase::yaw(){
	return DriveBase::Navxahrs ->GetYaw();
}
double DriveBase::pitch(){
	return DriveBase::Navxahrs ->GetPitch();
}
