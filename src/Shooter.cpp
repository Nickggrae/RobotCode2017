#include <Shooter.hpp>
#include <Intake.hpp>
#include <MotorMap.hpp>
#include <SensorMap.hpp>

namespace Shooter {

	CANTalon* shooterMaster;
	CANTalon* shooterSlave;
	CANTalon* angle;
	CANTalon* shooterIntake;
	bool initialized = false;

	void init() {
		if(initialized) return;


		/*
		 * Master turret flywheel motor controller
		 */

		shooterMaster = new CANTalon(MOTOR_MAP_SHOOTER_MASTER);
		shooterMaster->Set (0.0);
		shooterMaster->SetFeedbackDevice(CANTalon::EncRising);
		shooterMaster->SetStatusFrameRateMs(CANTalon::StatusFrameRate::StatusFrameRateFeedback, 1);
		shooterMaster->ConfigEncoderCodesPerRev(1024);
		shooterMaster->ConfigNominalOutputVoltage(+0., -0.);
		shooterMaster->ConfigPeakOutputVoltage(+12., -12.);
		shooterMaster->SetAllowableClosedLoopErr(0);
		shooterMaster->SetVoltageRampRate(SENSOR_MAP_SHOOTER_MASTER_VOLTAGE_RAMP);
		shooterMaster->SelectProfileSlot(SENSOR_MAP_SHOOTER_MASTER_PROFILE);
		shooterMaster->SetPID(
				SENSOR_MAP_SHOOTER_MASTER_PID_P,
				SENSOR_MAP_SHOOTER_MASTER_PID_I,
				SENSOR_MAP_SHOOTER_MASTER_PID_D);
		shooterMaster->SetControlMode(CANSpeedController::kSpeed);


		/*
		 * Slave turret flywheel motor controller
		 */

		shooterSlave = new CANTalon(MOTOR_MAP_SHOOTER_SLAVE);
		shooterSlave->SetControlMode(CANTalon::ControlMode::kFollower);
		shooterSlave->Set(shooterMaster->GetDeviceID());


		/*
		 * Horizontal turret angle motor controller
		 */

		angle = new CANTalon(MOTOR_MAP_SHOOTER_ANGLE);
		angle->Set (0.0);
		angle->SetFeedbackDevice(CANTalon::QuadEncoder);
		angle->ConfigEncoderCodesPerRev(1024);
		angle->ConfigNominalOutputVoltage(+0., -0.);
		angle->ConfigPeakOutputVoltage(+12., -12.);
		angle->SetAllowableClosedLoopErr(0.5);
		angle->SelectProfileSlot(SENSOR_MAP_SHOOTER_ANGLE_PROFILE);
		angle->SetPID(
				SENSOR_MAP_SHOOTER_ANGLE_PID_P,
				SENSOR_MAP_SHOOTER_ANGLE_PID_I,
				SENSOR_MAP_SHOOTER_ANGLE_PID_D);
		angle->SetControlMode(CANSpeedController::kPosition);
		angle->SetSensorDirection(true);

		/*
		 * Turret feed motor controller
		 */

		shooterIntake = new CANTalon(MOTOR_MAP_FEED_INTAKE);
		shooterIntake->Set(0.0);
		shooterIntake->SetFeedbackDevice(CANTalon::EncRising);
		shooterIntake->SetStatusFrameRateMs(CANTalon::StatusFrameRate::StatusFrameRateFeedback, 1);
		shooterIntake->SetClosedLoopOutputDirection(true);
		shooterIntake->SetSensorDirection(false);
		shooterIntake->ConfigEncoderCodesPerRev(1024);
		shooterIntake->ConfigNominalOutputVoltage(+0., -0.);
		shooterIntake->ConfigPeakOutputVoltage(+12., -12.);
		shooterIntake->SetAllowableClosedLoopErr(0);
		shooterIntake->SelectProfileSlot(0);
		shooterIntake->SetPID(1,0.002,0.0);
		shooterIntake->SetControlMode(CANSpeedController::kSpeed);

		initialized = true;
	}

	void set(double rpm){
		shooterMaster->Set(rpm);
	}

	double get(){
		return shooterMaster->GetSpeed();
	}

	//Set CANTalon rotations based on angle
	void setangle(double angleToSet){
		angle->Set(angleToSet);// * (0.007638888888889));f
	}
	double getangle(){
		return (angle->GetPosition());// / .00076388888888889);
	}

	void agitatorOn(){
		shooterIntake->Set(2400);
	}

	void agitatorOff(){
		shooterIntake->Set(0.0);
	}

	double agitatorRPM(){
		return shooterIntake->GetSpeed();
	}
	void resetAngle(){
		angle->Reset();
	}

	bool agitatorIsOn() {
		return (abs(shooterIntake->Get()) > 0.1); // Returns true if intake is on
	}

	CANTalon *getShooterCANTalon() {
		return shooterMaster;
	}

	void agitatorToggle() { // Used for toggle in Teleop
		if (agitatorIsOn()) {
			agitatorOff();
		} else {
			agitatorOn();
		}
	}

	int shoot(int shooterState, double rpm_flywheel){
		switch (shooterState) { //will fix error later
			case 10: {
				SmartDashboard::PutNumber("Wanted Flywheel Speed", rpm_flywheel);

				Shooter::set(rpm_flywheel);

				int flywheel_error =
						Shooter::getShooterCANTalon()->GetClosedLoopError();

				SmartDashboard::PutNumber("Flywheel closed loop error", flywheel_error);

				if (abs(flywheel_error) < 500) {
					Shooter::agitatorOn();
				}

				if (abs(flywheel_error) < 10) {
					shooterState = 20;
				}
			}
			break;

			case 20: {
				Intake::saladOn();
			}
			break;

			default: {
				return 0;
			}
			break;
		}
		return shooterState;
	}
}
