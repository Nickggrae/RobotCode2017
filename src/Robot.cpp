#include <WPILib.h>
#include "Teleop.h"
#include "Intake.h"
#include "Auton.h"
#include "Climber.h"
#include "Copernicus.h"
#include "Shooter.h"

// #include "DriveBase.h"


class Robot: public IterativeRobot, public ITableListener {
public:
	std::shared_ptr<NetworkTable> table;

	void RobotInit(){
		DriveBase::getInstance();	// the very first time we call it will init()
		Shooter::getInstance(); //calls init within function
		Intake::getInstance();
		Climber::getInstance();		// the very first time we call it will init() the climber
		CameraServer::GetInstance()->StartAutomaticCapture();
		Copernicus::setMode(Copernicus::Mode::DISABLED);
	}

	void TeleopInit(){
		Teleop::getInstance(); //will init
		Copernicus::setMode(Copernicus::Mode::TELEOP);
	}

	void TeleopPeriodic(){
		Teleop::getInstance().run();
		Copernicus::update();
	}

	void AutonomousInit(){
		Auton::getInstance(); //first call will create and instance and call init
		Copernicus::setMode(Copernicus::Mode::AUTON);
	}

	void AutonomousPeriodic(){
		Auton::getInstance().RedRightGearAuton();
		Copernicus::update();
	}

	void DisabledInit(){
		Copernicus::setMode(Copernicus::Mode::DISABLED);
	}

	void DisabledPeriodic(){
		DriveBase::getInstance().disableBrake();
		Copernicus::update();
	}

	void ValueChanged(ITable* source, llvm::StringRef key, std::shared_ptr<nt::Value> value, bool isNew) override{
		if(key == "horz_angle"){
			double newAngle = value->GetDouble();
			if(newAngle != -666 && newAngle != 666){
				Shooter::getInstance().setangle(newAngle);
			}
		}
	}
};


START_ROBOT_CLASS(Robot)
