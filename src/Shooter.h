#include "Shared.h"
 //#include <CANTalon.h>


class Shooter {
public:
	static CANTalon* shooter;
 	static CANTalon* angle;


 	static void init();


 	static void set(double rpm);


 	static double get();

 	static void setangle(double position);

 	static double getangle();
};


