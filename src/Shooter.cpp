#include "Shooter.h"


 CANTalon* Shooter::shooter;
 CANTalon* Shooter::angle;


 void Shooter::init() {
 	Shooter::shooter = new CANTalon(5);
 	Shooter::shooter->Set (0.0);
 	Shooter::shooter ->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
 	Shooter::shooter->ConfigNominalOutputVoltage(+0., -0.);
 	Shooter::shooter->ConfigPeakOutputVoltage(+12., -12.);
 	Shooter::shooter->SetAllowableClosedLoopErr(0);
 	Shooter::shooter->SelectProfileSlot(0);
 	Shooter::shooter ->SetPID(0.2,0.00015,0.0011);
 	Shooter::shooter->SetControlMode(CANSpeedController::kSpeed);

 	Shooter::angle = new CANTalon(7);
 	Shooter::angle->Set (0.0);
 	Shooter::angle ->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
 	Shooter::angle->ConfigNominalOutputVoltage(+0., -0.);
 	Shooter::angle->ConfigPeakOutputVoltage(+12., -12.);
 	Shooter::angle->SetAllowableClosedLoopErr(0.05);
 	Shooter::angle->SelectProfileSlot(0);
 	Shooter::angle ->SetPID(7,0,0);
 	Shooter::angle->SetControlMode(CANSpeedController::kPosition);
 	Shooter::angle->SetSensorDirection(true);
 }
 void Shooter::set(double rpm){
	 Shooter::shooter->Set(rpm);
 }

 double Shooter::get(){
 	return Shooter::shooter->Get();
 }

 //Set CANTalon rotations based on angle [aka ihatedavid]
 void Shooter::setangle(double ihatedavid){
	 Shooter::angle->Set((ihatedavid/42.1052631578947) * (18.0/23.0));

 }
 double Shooter::getangle(){
 	return Shooter::angle->Get() * 42.1052631578947 / (18.0/23.0);
 }
