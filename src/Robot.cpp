#include <WPILib.h>
#include "Teleop.h"
#include "Intake.h"
#include "Auton.h"
#include "Copernicus.h"
// #include "DriveBase.h"


class Robot: public IterativeRobot {
public:
	void RobotInit(){
		NetworkTable::Initialize();
		NetworkTable::SetServerMode();
		NetworkTable::SetTeam(5431);
		Auton::init();

		std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("vision");
	//		 Intake::init();
		Teleop::init();
	//		 DriveBase::init();
//		DriveBase::switchGear(false);
//		CameraServer::GetInstance()->StartAutomaticCapture();
//		CameraServer::GetInstance()->StartAutomaticCapture(1);
	//		 CameraServer::GetInstance()->StartAutomaticCapture();
	}
	void TeleopPeriodic(){
		Teleop::run();
		Copernicus::setMode(Copernicus::Mode::TELEOP);
		Copernicus::update();
	}
	void AutonomousPeriodic(){
		Auton::periodic();
		Copernicus::setMode(Copernicus::Mode::AUTON);
		Copernicus::update();
		SmartDashboard::PutNumber("Copernicus", 0.0);

	}
	void DisabledPeriodic(){
		Copernicus::setMode(Copernicus::Mode::DISABLED);
		Copernicus::update();
	}
};


START_ROBOT_CLASS(Robot)
