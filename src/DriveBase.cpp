#include "DriveBase.h"
#include "Copernicus.h"

DriveBase& DriveBase::getInstance(){
  static DriveBase instance;
  return instance;
}

//Limit Switch for Gear is DIO 9
void DriveBase::init() {
	ahrs = new AHRS(SPI::Port::kMXP);

	// CanTalon pair(2,3) pair(4,5)
	fl = new CANTalon(MAP_FRONTLEFT);
	//fl->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	fl->SetInverted(true);
//	fl->SetSafetyEnabled(false);

	fr = new CANTalon(MAP_FRONTRIGHT);
	fr->SetInverted(true);
//	fr->SetSafetyEnabled(false);

	rl = new CANTalon(MAP_REARLEFT);
	rl->SetInverted(true);
//	rl->SetSafetyEnabled(false);

	rr = new CANTalon(MAP_REARRIGHT);
	rr->SetInverted(true);
//	rr->SetSafetyEnabled(false);
	robotDrive = new frc::RobotDrive(fl,rl,fr,rr);

	compressor = new frc::Compressor(0);
	compressor->SetClosedLoopControl(true);
	compressor->Start();

	solenoid = new frc::DoubleSolenoid(0, 1);
	solenoid->Set(frc::DoubleSolenoid::kReverse);

	solenoid2 = new frc::DoubleSolenoid(2, 3);
	solenoid2->Set(frc::DoubleSolenoid::kReverse);

}

void DriveBase::drive(double left, double right){
	robotDrive->TankDrive(left,right,false);
}

void DriveBase::switchGear(bool gear){
	//HEY - BAD NAMING
	SmartDashboard::PutBoolean("Gear Status", gear);
	if (gear){
		solenoid->Set(frc::DoubleSolenoid::kForward); //sets into high gear
		gearState = 1; //1 is high gear
		Copernicus::setHighGear(true);
	}
	else{
		solenoid->Set(frc::DoubleSolenoid::kReverse); //sets into low gear
		gearState = 0; //0 is low gear
		Copernicus::setHighGear(false);
	}
}

void DriveBase::switchSlider(bool slider){
	if (slider){
		solenoid2->Set(frc::DoubleSolenoid::kForward);
		sliderState = 1;
	}
	else{
		solenoid2->Set(frc::DoubleSolenoid::kReverse);
		sliderState = 0;
	}
}

int DriveBase::getSliderState(){
	return sliderState;
}
int DriveBase::getGearState(){
	return gearState;
}

double DriveBase::getEncoderfl(){
	return fl->GetEncPosition();
}

void DriveBase::resetEncoderfl(){
	fl->Reset();
}
double DriveBase::getEncoderfr(){
	return fr->GetEncPosition();
}

void DriveBase::resetEncoderfr(){
	fr->Reset();
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

void DriveBase::resetAHRS(){
	ahrs->Reset();
	ahrs->ZeroYaw();
}

void DriveBase::talonEnable(){
	fl->Enable();
	rl->Enable();
	rr->Enable();
	fr->Enable();
}

void DriveBase::talonDisable(){
	fl->Disable();
	rl->Disable();
	rr->Disable();
	fr->Disable();
}

double DriveBase::isTalonEnabled(){
	return fl->IsEnabled();
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

void DriveBase::enableBrake(){
	fl->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	fr->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	rl->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	rr->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
}

void DriveBase::disableBrake(){
	fl->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	fr->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	rl->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	rr->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
}

bool DriveBase::isCompressorOn(){
	return compressor->GetPressureSwitchValue();
}
