#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen.
brain  Brain;
controller Controller = controller(primary);
aivision AIVision(6, aivision::ALL_TAGS);
//The motor constructor takes motors as (port, ratio, reversed), so for example
//motor LeftFront = motor(PORT1, ratio6_1, false);

motor LeftFront = motor(PORT1, ratio6_1, true);
motor LeftBack = motor(PORT2, ratio6_1, true);
motor RightFront = motor(PORT3, ratio6_1, false);
motor RightBack = motor(PORT4, ratio6_1, false);
inertial Inertial = inertial(PORT5);
motor LeftLift = motor(PORT10, ratio18_1, true);
motor RightLift = motor(PORT12, ratio18_1, false);
motor_group dihtrain = motor_group(LeftFront, LeftBack, RightFront, RightBack);
motor_group Lift = motor_group(LeftLift, RightLift);
// motor ClawMotor1 = motor(PORT19, ratio18_1, false);
PID LiftPID = PID(0,0.5,0,0.25,0);
double target = 0;
rotation liftRot = rotation(PORT9);
bool usingLiftTarget = false;
bool ClawToggled = true;
bool lift_slowed = false;
int LiftSpeed = 100;
bool NirvanMode = false;
bool ArhamMode = true;
bool DriverMode = true;
// void closeClaw() {
//   ClawMotor1.spin(reverse, 100, percent);

// }
// void openClaw() {
//   ClawMotor1.stop(hold);
// }
void vexcodeInit( void ) {
  // nothing to initialize  
}