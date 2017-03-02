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
 * @file MotorMap.hpp
 * @date 03/02/2017
 * @brief Header that includes all motor mappings
 *
 * @details This is the header file that includes all motor maps for the robot
 */

#ifndef INCLUDE_MOTORMAP_HPP_
#define INCLUDE_MOTORMAP_HPP_

/*
 *  CANTalon SRX ids
 */

// DRIVE BASE (LEFT | RIGHT)
#define MOTOR_MAP_LEFT_ONE 			4 //Drive base left side motors
#define MOTOR_MAP_LEFT_TWO 			5
#define MOTOR_MAP_RIGHT_ONE			2 //Drive base right side motors
#define MOTOR_MAP_RIGHT_TWO			3

// CLIMBER
#define MOTOR_MAP_CLIMBER 			11 //Climber motor can only go one direction

// INTAKES
#define MOTOR_MAP_FLOOR_INTAKE		10 //Picks up from the floor
#define MOTOR_MAP_SALAD_SPINNER 	13 //The one that loads from the magazine
#define MOTOR_MAP_FEED_INTAKE 		1 //The one that loads into the flywheels

// TURRET
#define MOTOR_MAP_SHOOTER_MASTER	6 //The motor with the encoder attached
#define MOTOR_MAP_SHOOTER_SLAVE 	9 //The slave set motor located near the pdp
#define MOTOR_MAP_SHOOTER_ANGLE		12 //The motor to adjust the shooter angle

#endif /* INCLUDE_MOTORMAP_HPP_ */
