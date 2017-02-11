#include <WPILib.h>
#include "Teleop.h"
#include "Intake.h"
#include "Auton.h"
#include "Copernicus.h"
#include "Shooter.h"

#include "udpServer.hpp"
#include "udpClient2.hpp"

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/chrono.hpp>
// #include "DriveBase.h"

void startLoop() {
	/*udp_server udp_servers;
	udp_servers.setPressure(0);
	udp_servers.setHighGear(false);
	udp_servers.setBottomIntake(false);
	udp_servers.setStream(false);
	udp_servers.setCrosshairOffset(0);
	udp_servers.setTurretAngle(0);
	udp_servers.setRPM(0);
	udp_servers.setTopIntake(false);
	udp_servers.setLeftRPM(0);
	udp_servers.setRightRPM(0);
	udp_servers.setHoldsGear(0);
	udp_servers.setMode(0);
	udp_servers.setPowered(0);
	udp_servers.createJson();
	udp_servers.serverInit();*/
	boost::asio::io_service io_service;
	udp_client udp_client(io_service);
	io_service.run();
}


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

		Auton::init();

		boost::thread startTruck(startLoop);
		//udp_server.serverInit();
		//std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("vision");
	//		 Intake::init();
		Teleop::init();
	//		 DriveBase::init();
//		DriveBase::switchGear(false);
//		CameraServer::GetInstance()->StartAutomaticCapture();
//		CameraServer::GetInstance()->StartAutomaticCapture(1);
	//		 CameraServer::GetInstance()->StartAutomaticCapture();
	}
	void TeleopPeriodic(){
		Teleop::run(udp_client.turretAngle);
		Copernicus::setMode(Copernicus::Mode::TELEOP);
		Copernicus::update();
	}
	void AutonomousPeriodic(){
		Auton::periodic();
	}
};


START_ROBOT_CLASS(Robot)
