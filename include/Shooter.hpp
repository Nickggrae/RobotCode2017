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
 * @file Shooter.h
 * @date 03/02/2017
 * @brief Header that defines the global Shooter class
 *
 * @details All turret and shooter functions are located within Shooter.h and Shooter.cpp
 */

#ifndef INCLUDE_SHOOTER_HPP_
#define INCLUDE_SHOOTER_HPP_

#include <Shared.hpp>

namespace Shooter {

 	void resetAngle();
 	void init();
	void setangle(double angleToSet);
 	double getangle();
 	double get();
 	void set(double rpm);
 	void agitatorOn();
 	void agitatorOff();
 	double agitatorRPM();
 	void agitatorToggle();
 	bool agitatorIsOn();
 	CANTalon *getShooterCANTalon();

};

#endif /* INCLUDE_SHOOTER_HPP_ */
