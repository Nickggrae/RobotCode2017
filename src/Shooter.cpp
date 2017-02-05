#include "Shooter.h"


 CANTalon* Shooter::shooter;
 CANTalon* Shooter::angle;
 CANTalon* Shooter::agitator;


 void Shooter::init() {
 	Shooter::shooter = new CANTalon(2);
 	Shooter::shooter->Set (0.0);
 	Shooter::shooter->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
 	Shooter::shooter->ConfigNominalOutputVoltage(+0., -0.);
 	Shooter::shooter->ConfigPeakOutputVoltage(+12., -12.);
 	Shooter::shooter->SetAllowableClosedLoopErr(0);
 	Shooter::shooter->SelectProfileSlot(0);
 	Shooter::shooter->SetPID(1,0,0);
 	Shooter::shooter->SetControlMode(CANSpeedController::kSpeed);


 	Shooter::angle = new CANTalon(6);
 	Shooter::angle->Set (0.0);
 	Shooter::angle ->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
 	Shooter::angle ->SetClosedLoopOutputDirection(true);
 	Shooter::angle->ConfigNominalOutputVoltage(+0., -0.);
 	Shooter::angle->ConfigPeakOutputVoltage(+12., -12.);
 	Shooter::angle->SetAllowableClosedLoopErr(0.05);
 	Shooter::angle->SelectProfileSlot(0);
 	Shooter::angle ->SetPID(.415,0,0);
 	Shooter::angle->SetControlMode(CANSpeedController::kPosition);
 	Shooter::angle->SetSensorDirection(true);
 }
 void Shooter::set(double rpm){
	 Shooter::shooter->Set(rpm);
 }

 double Shooter::get(){
 	return Shooter::shooter->GetEncVel();
 }

 //Set CANTalon rotations based on angle [aka ihatedavid]
 void Shooter::setangle(double ihatedavid){
	 Shooter::angle->Set(ihatedavid * (.007638888888889));

 }
 double Shooter::getangle(){
 	return (Shooter::angle->Get() / .0076388888888889);
 }

 void Shooter::agitatorOn(){
	 Shooter::agitator->Set(0.5);
 }
