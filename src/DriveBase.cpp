#include "DriveBase.h"

CANTalon* DriveBase::fl;
CANTalon* DriveBase::rl;
CANTalon* DriveBase::fr;
CANTalon* DriveBase::rr;

int DriveBase::gearState;
int DriveBase::sliderState;

frc::DoubleSolenoid* DriveBase::solenoid;
frc::DoubleSolenoid* DriveBase::solenoid2;
frc::RobotDrive* DriveBase::robotDrive;
frc::Compressor *c;
AHRS *DriveBase::ahrs(NULL);

void DriveBase::init() {
	DriveBase::ahrs = new AHRS(SPI::Port::kMXP);
	DriveBase::fl = new CANTalon(3);
	DriveBase::fl->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	DriveBase::fl->SetInverted(true);
	DriveBase::fr = new CANTalon(8);
	DriveBase::rl = new CANTalon(11);
	DriveBase::rl->SetInverted(true);
	DriveBase::rr = new CANTalon(10);
	DriveBase::robotDrive = new frc::RobotDrive(DriveBase::fl,DriveBase::rl,DriveBase::fr,DriveBase::rr);

	c = new frc::Compressor(0);
	c->SetClosedLoopControl(true);
	c->Start();

	DriveBase::solenoid = new frc::DoubleSolenoid(0, 0, 1);
	DriveBase::solenoid->Set(frc::DoubleSolenoid::kReverse);

	DriveBase::solenoid2 = new frc::DoubleSolenoid(0, 2, 3);
	DriveBase::solenoid2->Set(frc::DoubleSolenoid::kReverse);

}

void DriveBase::drive(double left, double right){
	DriveBase::robotDrive ->TankDrive(left,right,false);
}

void DriveBase::switchGear(bool gear){
	//HEY - BAD NAMING
	SmartDashboard::PutBoolean("Jordan", gear);
	if (gear){
		DriveBase::solenoid->Set(frc::DoubleSolenoid::kForward); //sets into high gear
		DriveBase::gearState = 1; //1 is high gear
	}
	else{
		DriveBase::solenoid->Set(frc::DoubleSolenoid::kReverse); //sets into low gear
		DriveBase::gearState = 0; //0 is low gear
	}
}

void DriveBase::switchSlider(bool slider){
	if (slider){
		DriveBase::solenoid2->Set(frc::DoubleSolenoid::kForward);
		DriveBase::sliderState = 1;
	}
	else{
		DriveBase::solenoid2->Set(frc::DoubleSolenoid::kReverse);
		DriveBase::sliderState = 0;
	}
}

int DriveBase::getSliderState(){
	return DriveBase::sliderState;
}
int DriveBase::getGearState(){
	return DriveBase::gearState;
}

double DriveBase::getEncoderfl(){
	return DriveBase::fl->GetEncPosition();
}

void DriveBase::resetEncoderfl(){
	DriveBase::fl->Reset();
}
double DriveBase::getEncoderfr(){
	return DriveBase::fr->GetEncPosition();
}

void DriveBase::resetEncoderfr(){
	DriveBase::fr->Reset();
}

double DriveBase::getYaw(){
	return ahrs->GetYaw();
}

double DriveBase::getPitch(){
	return ahrs->GetPitch();
}

double DriveBase::getRoll(){
	return ahrs->GetRoll();
}

double DriveBase::DisplacementX(){
	return ahrs->GetDisplacementX();
}

double DriveBase::DisplacementY(){
	return ahrs->GetDisplacementY();
}

double DriveBase::DisplacementZ(){
	return ahrs->GetDisplacementZ();
}

double DriveBase::getAccelX(){
	return ahrs->GetWorldLinearAccelX();

}

double DriveBase::getAccelY(){
	return ahrs->GetWorldLinearAccelY();

}

double DriveBase::getAccelZ(){
	return ahrs->GetWorldLinearAccelZ();

}

void DriveBase::talonEnable(){
	DriveBase::fl->Enable();
	DriveBase::rl->Enable();
	DriveBase::rr->Enable();
	DriveBase::fr->Enable();
}

void DriveBase::talonDisable(){
	DriveBase::fl->Disable();
	DriveBase::rl->Disable();
	DriveBase::rr->Disable();
	DriveBase::fr->Disable();
}

double DriveBase::isTalonEnabled(){
	return DriveBase::fl->IsEnabled();
}


//Usaid if you are reading this it was a test just get rid of it
//Liav is reading this do it yourself
double DriveBase::velocityX(){
	return ahrs->GetVelocityX();
}

double DriveBase::velocityY(){
	return ahrs->GetVelocityY();
}

double DriveBase::velocityZ(){
	return ahrs->GetVelocityZ();
}
