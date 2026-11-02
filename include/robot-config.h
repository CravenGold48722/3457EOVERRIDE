#include "JAR-Template/PID.h"

using namespace vex;

extern brain Brain;

//To set up a motor called LeftFront here, you'd use
//extern motor LeftFront;

//Add your devices below, and don't forget to do the same in robot-config.cpp:

extern controller Controller;
extern aivision AIVision;
extern motor LeftFront;
extern motor LeftBack;
extern motor RightFront;
extern motor RightBack;
extern inertial Inertial;
extern motor LeftLift;
extern motor RightLift;
extern motor_group Lift;
extern PID LiftPID;
extern double target;
extern bool usingLiftTarget;
// extern motor ClawMotor1;
extern bool ClawToggled;
extern rotation liftRot;
extern motor_group dihtrain;
extern void closeClaw();
extern void openClaw();
extern double A;
extern double B;
extern double C;
extern bool lift_slowed;
extern int LiftSpeed;
extern bool NirvanMode;
extern bool ArhamMode;
extern bool DriverMode;

void  vexcodeInit( void );