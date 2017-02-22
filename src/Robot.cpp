#include <WPILib.h>
#include "Teleop.h"
#include "Intake.h"
#include "Auton.h"
#include "Climber.h"
#include "Copernicus.h"
#include "Shooter.h"

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/chrono.hpp>
// #include "DriveBase.h"


class Robot: public IterativeRobot, public ITableListener {
public:
	std::shared_ptr<NetworkTable> table;

	void RobotInit(){
//		NetworkTable::Initialize();
//		NetworkTable::SetServerMode();
//		NetworkTable::SetTeam(5431);
		DriveBase::init();
		Shooter::getInstance().init();
		Intake::getInstance();

		NetworkTable::Initialize();
		NetworkTable::SetServerMode();
		NetworkTable::SetTeam(5431);
		table = NetworkTable::GetTable("vision");
		//table->AddTableListener(this);
		Climber::getInstance();		// the very first time we call it will init() the climber

		//udp_server.serverInit();
		//std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("vision");
	//		 Intake::init();
	//		 DriveBase::init();
//		DriveBase::switchGear(false);
		CameraServer::GetInstance()->StartAutomaticCapture();
//		CameraServer::GetInstance()->StartAutomaticCapture(1);
	//		 CameraServer::GetInstance()->StartAutomaticCapture();
		Copernicus::setMode(Copernicus::Mode::DISABLED);
	}

	void TeleopInit(){
		Teleop::init();
		Copernicus::setMode(Copernicus::Mode::TELEOP);
	}
	void TeleopPeriodic(){
		Teleop::run(0.0);
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
		DriveBase::disableBrake();
		Copernicus::update();
	}

	void ValueChanged(ITable* source, llvm::StringRef key, std::shared_ptr<nt::Value> value, bool isNew) override{
		if(key == "horz_angle"){
			double newAngle = value->GetDouble();
			if(newAngle != -666.0 && newAngle != 666.0){
				Shooter::getInstance().setangle(newAngle);
			}else{
				Shooter::getInstance().setangle(0.0);
			}
		}
	}
};


START_ROBOT_CLASS(Robot)
