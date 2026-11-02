#include "vex.h"

using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors. In VEXcode Pro V5, you can do this using the graphical          */
/*  configurer port icon at the top right. In the VSCode extension, you'll   */
/*  need to go to robot-config.cpp and robot-config.h and create the         */
/*  motors yourself by following the style shown. All motors must be         */
/*  properly reversed, meaning the drive should drive forward when all       */
/*  motors spin forward.                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your motors.                                     */
/*---------------------------------------------------------------------------*/

Drive chassis(

//Pick your drive setup from the list below:
//ZERO_TRACKER_NO_ODOM
//ZERO_TRACKER_ODOM
//TANK_ONE_FORWARD_ENCODER
//TANK_ONE_FORWARD_ROTATION
//TANK_ONE_SIDEWAYS_ENCODER
//TANK_ONE_SIDEWAYS_ROTATION
//TANK_TWO_ENCODER
//TANK_TWO_ROTATION
//HOLONOMIC_TWO_ENCODER
//HOLONOMIC_TWO_ROTATION
//OVERRIDE_APRIL_TAGS
//
//Write it here:
ZERO_TRACKER_NO_ODOM,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
motor_group(LeftFront, LeftBack),

//Right Motors:
motor_group(RightFront, RightBack),

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT5,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
3.25,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
0.6,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
360,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
-PORT1,    PORT3,

//LB:      //RB: 
-PORT2,    PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
3,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2.75,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
-2,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
1,

//Sideways tracker diameter (reverse to make the direction switch):
-2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
5.5

);

int current_auton_selection = 0;
bool auto_started = false;
bool drifting_mode = false;

/**
 * Function before autonomous. It prints the current auton number on the screen
 * and tapping the screen cycles the selected auton by 1. Add anything else you
 * may need, like resetting pneumatic components. You can rename these autons to
 * be more descriptive, if you like.
 */

void pre_auton() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();
  //tuning motors
  liftRot.setPosition(0, deg);
  Lift.setStopping(brake);
  Lift.setMaxTorque(100, pct);
  Lift.setVelocity(100, pct);
  LeftFront.setStopping(coast);
  RightFront.setStopping(coast);
  LeftBack.setStopping(brake);
  RightBack.setStopping(brake);
  dihtrain.setVelocity(65, pct);
  dihtrain.setMaxTorque(100, pct);
  LeftBack.setVelocity(55, pct);
  RightBack.setVelocity(55, pct);
  ClawToggled = true;
  // ClawMotor1.setPosition(0, deg);
  // closeClaw();
}

/**
 * Auton function, which runs the selected auton. Case 0 is the default,
 * and will run in the brain screen goes untouched during preauton. Replace
 * drive_test(), for example, with your own auton function you created in
 * autons.cpp and declared in autons.h.
 */

void autonomous(void) {
  auto_started = true;
  autonblue();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
// void toggleClaw() {
//   ClawToggled = !ClawToggled;
//   if (ClawToggled == true) {
//     closeClaw();
//   } else if (ClawToggled == false) {
//     openClaw();
//   }
// }
void toggleLiftSpeed() {
  lift_slowed = !lift_slowed;
  if (lift_slowed) {
    LiftSpeed = 75;
    Controller.Screen.clearScreen();
    Controller.Screen.setCursor(1, 1);
    Controller.Screen.print("Lift: Slow");
  } else {
    LiftSpeed = 100;
    Controller.Screen.clearScreen();
    Controller.Screen.setCursor(1, 1);
    Controller.Screen.print("Lift: Normal");
  }
}
void usercontrol(void) {
  // User control code here, inside the loop
  // once you get motors, set stopping to whatever is necesarry(coast, brake, or hold)
  // Controller.ButtonB.pressed(toggleClaw);
  Controller.ButtonY.pressed(toggleLiftSpeed);
  while (1) {
    // LeftLift.setStopping(hold); 
    // RightLift.setStopping(hold);
    chassis.control_arcade();
    // if (Controller.ButtonY.pressing())
    // {
    //   drifting_mode = !drifting_mode;
    //   Controller.rumble("-..");
    // } 
    // if (drifting_mode)
    // {
    //   chassis.control_drifting();
    // } else {
    //   chassis.control_arcade();
    // }
    // if (Controller.ButtonX.pressing()){
    //   ClawToggled = !ClawToggled;
    // }
    // if (Controller.ButtonL2.pressing()){
    //   Lift.spin(reverse, 100, pct);
    // }
    // if (Controller.ButtonR2.pressing()){
    //   Lift.spin(forward, 100, pct);
    // }
    if (Controller.ButtonR1.pressing()) {
        usingLiftTarget = false;
        LeftLift.spin(forward, LiftSpeed, pct);
        RightLift.spin(forward, LiftSpeed, pct);
      } else {
        if (!usingLiftTarget && !Controller.ButtonR1.pressing() && !Controller.ButtonR2.pressing()) {
          LeftLift.stop(hold);
          RightLift.stop(hold);
        }
      }
    if (Controller.ButtonR2.pressing()) {
        usingLiftTarget = false;
        LeftLift.spin(reverse, (LiftSpeed - 25), pct);
        RightLift.spin(reverse, (LiftSpeed - 25), pct);
      } else {
        if (!usingLiftTarget && !Controller.ButtonR1.pressing() && !Controller.ButtonR2.pressing()) {
          LeftLift.stop(hold);
          RightLift.stop(hold);
        }
      }
    
    // Set lift target.
    // Controller.ButtonA.pressed([] {
    //   usingLiftTarget = true;
    //   target = target + 180;
    // });

    // Controller.ButtonB.pressed([] {
    //   usingLiftTarget = true;
    //   target = target - 180;
    // });

    // // Compute PID.
    // if (usingLiftTarget){
    //   double error = target - liftRot.position(deg);
    //   double power = LiftPID.compute(error);
    //   Lift.spin(forward, power, percent);
    // }
    wait(7, msec);// Sleep the task for a short, amount of time to prevent wasted resources.
  }
}
//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(2, msec);
  }
}
