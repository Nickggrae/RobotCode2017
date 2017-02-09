#include <WPILib.h>
#include "Teleop.h"
#include "Intake.h"
#include "Auton.h"
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
	}
	void AutonomousPeriodic(){
		Auton::periodic();
		SmartDashboard::PutNumber("Gayisnick", 0.0)
	}
};


START_ROBOT_CLASS(Robot)
