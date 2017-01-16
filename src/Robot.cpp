#pragma once
#include <WPILib.h>
#include "DriveBase.h"

/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're inexperienced,
 * don't. Unless you know what you are doing, complex code will be much more difficult under
 * this system. Use IterativeRobot or Command-Based instead if you're new.
 */
class Robot: public frc::SampleRobot {
//	CANTalon* shooter;  // robot drive system
	frc::Joystick stick { 0 };  // only joystick
//	CANTalon* fl;
//	CANTalon* ml;
//	CANTalon* rl;
//	CANTalon* fr;
//	CANTalon* mr;
//	CANTalon* rr;
//	RobotDrive* robotDrive;
public:
	Robot() {
		DriveBase::init();
//		shooter = new CANTalon(5);
////		shooter->Set (0.0);
//		shooter ->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
//		shooter->ConfigNominalOutputVoltage(+0., -0.);
//		shooter->ConfigPeakOutputVoltage(+12., -12.);
//		shooter->SetAllowableClosedLoopErr(0);
//		shooter->SelectProfileSlot(0);
//		shooter ->SetPID(0.2,0.00015,0.0011);
////		shooter ->SetPID(0.2,0.0001,0.001);
//		SmartDashboard::init();
////		SmartDashboard::PutNumber("SET VALUE", 0);
//		shooter->SetControlMode(CANSpeedController::kSpeed);
	}

	/**
	 * Runs the motors with arcade steering.
	 */
	void OperatorControl() {
		while (IsOperatorControl() && IsEnabled()) {
			frc::Wait(0.005);			// wait for a motor update time
			DriveBase::drive(stick.GetY(), stick.GetRawAxis(5));
//			shooter-> Set (SmartDashboard::GetNumber("SET VALUE", 0));
//			SmartDashboard::PutNumber("Shooter Power", shooter->Get());

		}
	}
};

START_ROBOT_CLASS(Robot)
