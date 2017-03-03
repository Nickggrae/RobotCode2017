#include <Auton.hpp>
#include <Shared.hpp>
#include <Climber.hpp>
#include <Intake.hpp>
#include <Shooter.hpp>
#include <DriveBase.hpp>
#include <Teleop.hpp>
#include <Copernicus.h>


class Robot: public IterativeRobot, public ITableListener {
public:
	std::shared_ptr<NetworkTable> table;


	void RobotInit(){
		DriveBase::init();	// the very first time we call it will init()
		Shooter::init(); //Initialize the shooter
		Intake::init();
		Climber::init();		// the very first time we call it will init() the climber
		Teleop::init();
		Auton::init();

		NetworkTable::SetClientMode();
		NetworkTable::SetTeam(5431);
		table = NetworkTable::GetTable("vision");
		table->AddTableListener(this);

		CameraServer::GetInstance()->StartAutomaticCapture();
		Copernicus::setMode(Copernicus::Mode::DISABLED);
	}

	void TeleopInit(){
		Copernicus::setMode(Copernicus::Mode::TELEOP);
	}

	void TeleopPeriodic(){
		Teleop::run();
		Copernicus::update();
	}

	void AutonomousInit(){
		Auton::init(); //first call will create and instance and call init
		Copernicus::setMode(Copernicus::Mode::AUTON);
	}

	void AutonomousPeriodic(){
		Auton::RedLeftAuton();
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
			if(newAngle != -666 && newAngle != 666){
				Shooter::setangle(newAngle);
			}
		}
	}
};


START_ROBOT_CLASS(Robot)
