#include <WPILib.h>
#include "Teleop.h"
#include "Intake.h"
#include "Auton.h"
#include "Copernicus.h"
#include "Shooter.h"

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/chrono.hpp>
// #include "DriveBase.h"


class Robot: public IterativeRobot {
public:
	void RobotInit(){
//		NetworkTable::Initialize();
//		NetworkTable::SetServerMode();
//		NetworkTable::SetTeam(5431);
		DriveBase::init();
		Shooter::init();
		Intake::init();
		Climber::init();

		NetworkTable::Initialize();
		NetworkTable::SetServerMode();
		NetworkTable::SetTeam(5431);


		//udp_server.serverInit();
		//std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("vision");
	//		 Intake::init();
	//		 DriveBase::init();
//		DriveBase::switchGear(false);
//		CameraServer::GetInstance()->StartAutomaticCapture();
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
		Auton::init();
		Copernicus::setMode(Copernicus::Mode::AUTON);
	}
	void AutonomousPeriodic(){
		Auton::RedRightAuton();
		Copernicus::update();
	}

	void DisabledInit(){
		Copernicus::setMode(Copernicus::Mode::DISABLED);
	}

	void DisabledPeriodic(){
		DriveBase::disableBrake();
		Copernicus::update();
	}
};


START_ROBOT_CLASS(Robot)
