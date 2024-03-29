/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

vex::motor LeftMotor        = vex::motor( vex::PORT1 );
vex::motor RightMotor       = vex::motor( vex::PORT10, true );
vex::motor liftfrontright   = vex::motor( vex::PORT12);
vex::motor liftfrontleft    = vex::motor( vex::PORT1 );
vex::motor liftbackright    = vex::motor( vex::PORT1 );
vex::motor liftbackleft     = vex::motor( vex::PORT1 );
servo RightClaw = servo(Brain.ThreeWirePort.A);
servo LeftClaw = servo(Brain.ThreeWirePort.B);
vex::motor_group BackLift(liftbackright, liftbackleft);
vex::motor_group FrontLift(liftfrontright, liftfrontleft);

vex::controller Controller1 = vex::controller();
vex::controller Controller2 = vex::controller();
// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
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

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    LeftMotor.spin(vex::directionType::fwd, Controller1.Axis3.position(), vex::velocityUnits::pct);
    RightMotor.spin(vex::directionType::fwd, Controller1.Axis2.position(), vex::velocityUnits::pct);
    BackLift.spin(vex::directionType::fwd, Controller2.Axis2.position(), vex::velocityUnits::pct);
    FrontLift.spin(vex::directionType::fwd, Controller2.Axis3.position(), vex::velocityUnits::pct);
    if(Controller2.ButtonR1.pressing() ){
      RightClaw.setPosition(75, vex::pct);
      LeftClaw.setPosition(-75, vex::pct);
    } else if(Controller2.ButtonL1.pressing() ){
        RightClaw.setPosition(100, vex::pct);
        LeftClaw.setPosition(-100, vex::pct);
    }
    
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
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
    wait(100, msec);
  }
}
