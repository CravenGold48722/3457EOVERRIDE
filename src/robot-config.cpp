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
motor ClawMotor1 = motor(PORT19, ratio18_1, false);
motor ClawMotor2 = motor(PORT14, ratio18_1, true);
motor_group Claw = motor_group(ClawMotor1, ClawMotor2);
PID LiftPID = PID(0,0.5,0,0.25,0);
double target = 0;
rotation liftRot = rotation(PORT9);
bool usingLiftTarget = false;
bool ClawToggled = true;
bool IntakeToggled = true;
bool AKIntakeToggled = true;
bool lift_slowed = false;
int LiftSpeed = 100;
bool NirvanMode = false;
bool ArhamMode = true;
bool DriverMode = true;
//BELOW IS IMPORTANT, REMEMBER IT
/*
ClawMotor1 is what opens/closes the hold claw, and ClawMotor2 is what spins the flexwheels inside the claw. The claw is closed when ClawMotor1 spins forward, and open when it spins in reverse. The flexwheels spin inwards, sucking pins/cones in when ClawMotor2 spins forward, and they spit pins/cups out(NOT RECOMMENDED, DO NOT USE) when ClawMotor2 spins in reverse.
ClawMotor1 is what opens/closes the hold claw, and ClawMotor2 is what spins the flexwheels inside the claw. The claw is closed when ClawMotor1 spins forward, and open when it spins in reverse. The flexwheels spin inwards, sucking pins/cones in when ClawMotor2 spins forward, and they spit pins/cups out(NOT RECOMMENDED, DO NOT USE) when ClawMotor2 spins in reverse.
ClawMotor1 is what opens/closes the hold claw, and ClawMotor2 is what spins the flexwheels inside the claw. The claw is closed when ClawMotor1 spins forward, and open when it spins in reverse. The flexwheels spin inwards, sucking pins/cones in when ClawMotor2 spins forward, and they spit pins/cups out(NOT RECOMMENDED, DO NOT USE) when ClawMotor2 spins in reverse.
*/
//ABOVE IS IMPORTANT, REMEMBER IT
void closeClaw() {
  ClawMotor1.setStopping(hold);
  ClawMotor1.spin(reverse, 100, pct);
  // ClawMotor1.spinFor(reverse, 35, degrees);

}
void openClaw() {
  ClawMotor1.spin(forward, 100, pct);
}
void toggleIntaking(){
  IntakeToggled = !IntakeToggled;
  if (IntakeToggled == true) {
    ClawMotor2.spin(forward, 100, pct);
  } else if (IntakeToggled == false) {
    ClawMotor2.stop(hold);
  }
}
void toggleAKIntaking(){
  ClawMotor2.spin(forward, 100, pct);
  ClawMotor1.spinFor(reverse, 25, degrees);
}
void vexcodeInit( void ) {
  // nothing to initialize  
}