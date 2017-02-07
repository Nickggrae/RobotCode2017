//Liav here - put a #pragma once and include guard

//FOR HEADERS THAT ALL COMPONENTS USE
#include <WPILib.h>
#include <CANTalon.h>
#include <cmath>

//FOR DEBUG
#include <SmartDashboard/SmartDashboard.h>
const int turrentTable = 2;
const int leftDriveFront = 11;
const int leftDriveBack = 3;
const int rightDriveFront = 8;
const int rightDriveBack = 10;
const int climber = 4;
//Liav here - rename this to the actual new names (conveyor, feed, intake)
const int floorIntake = 12; //actual intake
const int shooterIntake = 9; //reverse
const int polycordIntake = 13; //reverse
const int flyWheels = 14;

//inverse the metering wheel shooter intake
