/*------------------------------------------------------------------------------||
|                                                                                |
| Copyright (C) 2017 by Titan Robotics                                           |
| License Date: 01/23/2017                                                       |
| Modifiers: none                                                                |
|                                                                                |
| Permission is hereby granted, free of charge, to any person obtaining a copy   |
| of this software and associated documentation files (the "Software"), to deal  |
| in the Software without restriction, including without limitation the rights   |
| to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      |
| copies of the Software, and to permit persons to whom the Software is          |
| furnished to do so, subject to the following conditions:                       |
|                                                                                |
| The above copyright notice and this permission notice shall be included in all |
| copies or substantial portions of the Software.                                |
|                                                                                |
| THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     |
| IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       |
| FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    |
| AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         |
| LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  |
| OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  |
| SOFTWARE.                                                                      |
|                                                                                |
||------------------------------------------------------------------------------*/

/**
 *
 * @file SensorMap.hpp
 * @date 03/02/2017
 * @brief Header that includes all Sensor mappings and definitions
 *
 * @details This header file includes all of the definitions for sensor mappings and PID values
 */

#ifndef INCLUDE_SENSORMAP_HPP_
#define INCLUDE_SENSORMAP_HPP_

/*
 * PID values and adjustments (For master flywheel turret motor controller)
 */

#define SENSOR_MAP_SHOOTER_MASTER_VOLTAGE_RAMP 	1 //Shooter master voltage ramp rate

//PID Specifics
#define SENSOR_MAP_SHOOTER_MASTER_PROFILE		0 //Shooter PID Profile id

#define SENSOR_MAP_SHOOTER_MASTER_PID_P 		1 //Shooter master PID P value (Proportional)
#define SENSOR_MAP_SHOOTER_MASTER_PID_I			0.0001//Shooter master PID I value (Integral)
#define SENSOR_MAP_SHOOTER_MASTER_PID_D			0.00001 //Shooter master PID D value (Derivative)


/*
 * Shooter angle adjustment motor controller
 */

#define SENSOR_MAP_SHOOTER_ANGLE_PROFILE		0 //Shooter PID Profile id

#define SENSOR_MAP_SHOOTER_ANGLE_PID_P 			0.0034 //Shooter master PID P value (Proportional)
#define SENSOR_MAP_SHOOTER_ANGLE_PID_I			0.0 //Shooter master PID I value (Integral)
#define SENSOR_MAP_SHOOTER_ANGLE_PID_D			0.00015 //Shooter master PID D value (Derivative)

/*
 * Drivebase encoder settings
 */

#define SENSOR_MAP_DRIVE_BASE_INCHES_PER_CLICK	0.003006602344

#endif /* INCLUDE_SENSORMAP_HPP_ */
