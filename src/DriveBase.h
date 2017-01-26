#include "Shared.h"
#include <Compressor.h>
#include <Solenoid.h>
#include <DoubleSolenoid.h>
//#include "DriveBase.cpp"

class DriveBase {
	static CANTalon* fl;
	static CANTalon* ml;
	static CANTalon* rl;
	static CANTalon* fr;
	static CANTalon* mr;
	static CANTalon* rr;
	static frc::RobotDrive* robotDrive;
	static DoubleSolenoid* solenoid;
	static int gearState;
public:
	static void init();

	static void drive(double left, double right); //tank drive robot drive with left and right side

	static void switchGear(bool gear); //set piston forward if true and reverse if false

	static int getGearState(); //check whether gear has been released or not
};

/**TODO:
 * Create DriveBase class that:
 * has a constructor that:
 *  - initializes all CANTalons used on DriveBase
 *  - initializes all sensors used on DriveBase (Encoders, Accel, Gyro)
 *  - resets sensors
 *  - configures CANTalons (Followers)
 * has a drive(double left, double right)
 *  - Drives the robot in TankDrive using the left/right provided
 * has a resetGyro()
 *  - resets the gyro
 * has a resetAccel()
 *  - resets the accel
 * has a resetEncoder()
 *  - resets the encoders
 * has a getGyro()
 *  - returns a DOUBLE with the current Gyro value
 * has a getAccel()
 *  - returns a DOUBLE with the current Accel value
 * has a getEncoder()
 *  - returns a DOUBLE with the current Encoder value
 * has a enable()
 *  - enables the DriveBase. TURNED ON BY DEFAULT
 * has a disable()
 *  - disables the DriveBase CANTalons
 *\]
 * QUESTIONS:
 *  - Have a PID mode to set position encoders/gyro/accel should be at?
 *    = would need a set(double position) function as well as a PIDMode() function and a VbusMode() function to swith between the two
 */
