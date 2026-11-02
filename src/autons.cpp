#include "vex.h"

/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(12, 1, 0, 5, 0);
  // chassis.set_heading_constants(6, 1, 0, 3, 0);
  chassis.set_heading_constants(6, 1, 0, 3, 0);
  chassis.set_turn_constants(6, 1, 0, 3, 0);
  chassis.set_swing_constants(6, 1, 0, 3, 0);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1, 500, 550);
  chassis.set_turn_exit_conditions(0.1, 750, 1000);
  chassis.set_swing_exit_conditions(0.25, 750, 1000);
}

/**
 * Sets constants to be more effective for odom movements.  
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */

void odom_constants(){
  default_constants();
  chassis.heading_max_voltage = 10;
  chassis.drive_max_voltage = 12;
  chassis.drive_settle_error = 3;
  chassis.boomerang_lead = .5;
  chassis.drive_min_voltage = 0;
}
/**
 * A little of this, a little of that; it should end roughly where it started.
 */

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

/**
 * Doesn't drive the robot, but just prints coordinates to the Brain screen 
 * so you can check if they are accurate to life. Push the robot around and
 * see if the coordinates increase like you'd expect.
 */

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(10);
  }
}
void autonblue(){
  // closeClaw();
  dihtrain.setVelocity(100, pct);
  chassis.set_coordinates(0, 170, 180);
  wait(250, msec);
  chassis.drive_distance(-8, 180);
  chassis.drive_stop(brake);
  wait(50, msec);
  Lift.spin(forward, 100, pct);
  wait(650, msec);
  Lift.stop(brake);
  wait(50, msec);
  Lift.spin(reverse, 100, pct);
  wait(650, msec);
  Lift.stop(coast);
  chassis.drive_distance(10, 180);
  wait(10, msec);
  chassis.drive_distance(-8, 180);
  wait(10, msec);
  chassis.drive_distance(10, 180);
  wait(10, msec);
  chassis.set_drive_exit_conditions(0.1, 500, 750);
  chassis.set_drive_constants(12, 1, 0, 10, 0);
  chassis.drive_distance(-13.5, 180);
  chassis.drive_stop(brake);
  wait(50, msec);
  chassis.turn_to_angle(90);
  chassis.drive_stop(brake);
  Lift.spin(forward, 100, pct);
  wait(300, msec);
  Lift.stop(hold);
  chassis.drive_distance(12, 90);
  chassis.drive_stop(coast);
  Lift.spin(reverse, 100, pct);
  wait(300, msec);
  Lift.stop(coast);
  // openClaw();
  chassis.drive_stop(hold);
  wait(250, msec);
  chassis.set_drive_exit_conditions(0.1, 500, 600);
  chassis.set_drive_constants(12, 1, 0, 10, 0);
  chassis.drive_distance(-11, 90);
  chassis.drive_distance(-3, 90);
  chassis.drive_stop(brake);
  // closeClaw();
  chassis.turn_to_angle(45);
  chassis.drive_distance(18, 45);
  // closeClaw();
  chassis.drive_distance(12, 45);
  chassis.drive_stop(coast);
  wait(350, msec);
  chassis.drive_distance(4, 45);
  Lift.spin(forward, 100, pct);
  wait(450, msec);
  Lift.stop(hold);
  chassis.turn_to_angle(180);
  chassis.drive_distance(15.5, 180);
  chassis.drive_stop(coast);
  Lift.spin(reverse, 100, pct);
  wait(470, msec);
  Lift.stop(coast);
  // openClaw();
  //scuffed auton

  // closeClaw();
  // chassis.set_coordinates(170, 0, 45);
  // wait(100, msec);
  // Lift.spin(forward, 100, pct);
  // wait(750, msec);
  // Lift.stop(hold);
  // chassis.drive_distance(15, 45);
  // chassis.drive_stop(hold);
  // wait(50, msec);
  // Lift.spin(reverse, 100, pct);
  // wait(750, msec);
  // Lift.stop(coast);
  // wait(250, msec);
  // openClaw();
  // wait(250, msec);
  // chassis.drive_distance(-5.5, 45);
  // chassis.right_swing_to_angle(180);
  // chassis.drive_stop(hold);

}
void autonred(){
  // closeClaw();
  // chassis.set_coordinates(0, 170, 180);
  // wait(250, msec);
  // chassis.drive_distance(-6, 180);
  // chassis.drive_stop(brake);
  // Lift.spin(forward, 100, pct);
  // wait(100, msec);
  // Lift.stop(coast);
  // wait(50, msec);
  // Lift.spin(reverse, 100, pct);
  // wait(100, msec);
  // Lift.stop(coast);
  // chassis.drive_distance(8, 180);
  // chassis.drive_distance(-6, 180);
  // chassis.drive_distance(8, 180);
  // chassis.set_drive_exit_conditions(1, 500, 750);
  // chassis.set_drive_constants(18, 1, 0, 10, 0);
  // chassis.drive_distance(-13.75, 180);
  // chassis.drive_stop(brake);
  // wait(50, msec);
  // chassis.turn_to_angle(90);
  // chassis.drive_stop(brake);
  // Lift.spin(forward, 100, pct);
  // wait(300, msec);
  // Lift.stop(hold);
  // chassis.drive_distance(18, 90);
  // chassis.drive_stop(coast);
  // Lift.spin(reverse, 100, pct);
  // wait(310, msec);
  // Lift.stop(hold);
  // //past this = untested
  // openClaw();
  // chassis.drive_stop(hold);
  // chassis.set_drive_exit_conditions(0.5, 500, 600);
  // chassis.set_drive_constants(18, 1, 0, 10, 0);
  // wait(250, msec);
  // chassis.drive_distance(-11, 0);
  // chassis.drive_stop(brake);
  // ClawMotor2.spin(forward, 100, pct);
  // chassis.turn_to_angle(33.5);
  // dihtrain.setStopping(coast);
  // chassis.drive_distance(18, 33.5);
  // toggleAKIntaking();
  // ClawMotor2.spin(forward, 100, pct);
  // chassis.drive_distance(10.5, 33.5);
  // chassis.drive_stop(coast);
  // LeftBack.setStopping(brake);
  // RightBack.setStopping(brake);
  // wait(300, msec);
  // closeClaw();
  // wait(100, msec);
  // chassis.drive_distance(4, 33.5);
  // Lift.spin(forward, 100, pct);
  // wait(450, msec);
  // Lift.stop(hold);
  // chassis.turn_to_angle(180);
  // chassis.drive_distance(15.5, 180);
  // chassis.drive_stop(coast);
  // Lift.spin(reverse, 100, pct);
  // wait(480, msec);
  // Lift.stop(coast);
  // openClaw();
}