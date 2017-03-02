#include <Copernicus.h>
#include <DriveBase.hpp>

#include <MotorMap.hpp>

namespace DriveBase {
	CANTalon *fl, *rl, *fr, *rr;
	//initializes robot drive
	frc::RobotDrive* robotDrive;
	//initializes solenoid for pneumatics
	frc::DoubleSolenoid *solenoid, *solenoid2;
	frc::Compressor* compressor;

	//initializes the gear state
	int gearState;
	int sliderState;
	double inchesPerClick;
	AHRS *ahrs;

	bool initialized = false;

	//Limit Switch for Gear is DIO 9
	void init() {
		if(initialized) return;

		ahrs = new AHRS(SPI::Port::kMXP);

		// CanTalon pair(2,3) pair(4,5)
		fl = new CANTalon(MOTOR_MAP_LEFT_ONE);
		fl->SetFeedbackDevice(CANTalon::EncRising);
		fl->ConfigEncoderCodesPerRev(2048);//2x encoder revs
		fl->SetInverted(true);

		fr = new CANTalon(MOTOR_MAP_RIGHT_ONE);
		fr->SetFeedbackDevice(CANTalon::EncRising);
		fr->ConfigEncoderCodesPerRev(2048);//2x encoder revs
		fr->SetInverted(true);

		rl = new CANTalon(MOTOR_MAP_LEFT_TWO);
		rl->SetInverted(true);

		rr = new CANTalon(MOTOR_MAP_RIGHT_TWO);
		rr->SetInverted(true);
		robotDrive = new frc::RobotDrive(fl,rl,fr,rr);

		compressor = new frc::Compressor(0);
		compressor->SetClosedLoopControl(true);
		compressor->Start();

		solenoid = new frc::DoubleSolenoid(0, 7);
		solenoid->Set(frc::DoubleSolenoid::kReverse);

		solenoid2 = new frc::DoubleSolenoid(6, 1);
		solenoid2->Set(frc::DoubleSolenoid::kReverse);

		inchesPerClick = 0.00589294059473;

		initialized = true;
	}

	void drive(double left, double right){
		robotDrive->TankDrive(left,right,false);
	}

	void switchGear(bool gear){
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

	void switchSlider(bool slider){
		if (slider){
			solenoid2->Set(frc::DoubleSolenoid::kForward);
			sliderState = 1;
		}
		else{
			solenoid2->Set(frc::DoubleSolenoid::kReverse);
			sliderState = 0;
		}
	}

	AHRS *getAHRS() {
		return ahrs;
	}

	int getSliderState(){
		return sliderState;
	}
	int getGearState(){
		return gearState;
	}

	double getEncoderflInches(){
		return fl->GetEncPosition() * inchesPerClick;
	}

	void resetEncoderfl(){
		fl->Reset();
	}
	double getEncoderfrInches(){
		return fr->GetEncPosition() * inchesPerClick;
	}

	void resetEncoderfr(){
		fr->Reset();
	}

	double getYaw(){
		return ahrs->GetYaw();
	}

	double getPitch(){
		return ahrs->GetPitch();
	}

	double getRoll(){
		return ahrs->GetRoll();
	}

	double DisplacementX(){
		return ahrs->GetDisplacementX();
	}

	double DisplacementY(){
		return ahrs->GetDisplacementY();
	}

	double DisplacementZ(){
		return ahrs->GetDisplacementZ();
	}

	double getAccelX(){
		return ahrs->GetWorldLinearAccelX();
	}

	double getAccelY(){
		return ahrs->GetWorldLinearAccelY();
	}

	double getAccelZ(){
		return ahrs->GetWorldLinearAccelZ();
	}

	void resetAHRS(){
		ahrs->Reset();
		ahrs->ZeroYaw();
	}

	void talonEnable(){
		fl->Enable();
		rl->Enable();
		rr->Enable();
		fr->Enable();
	}

	void talonDisable(){
		fl->Disable();
		rl->Disable();
		rr->Disable();
		fr->Disable();
	}

	double isTalonEnabled(){
		return fl->IsEnabled();
	}


	//Usaid if you are reading this it was a test just get rid of it
	//Liav is reading this do it yourself
	double velocityX(){
		return ahrs->GetVelocityX();
	}

	double velocityY(){
		return ahrs->GetVelocityY();
	}

	double velocityZ(){
		return ahrs->GetVelocityZ();
	}

	void enableBrake(){
		fl->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
		fr->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
		rl->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
		rr->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	}

	void disableBrake(){
		fl->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		fr->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		rl->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		rr->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	}

	bool isCompressorOn(){
		return compressor->GetPressureSwitchValue();
	}
}
