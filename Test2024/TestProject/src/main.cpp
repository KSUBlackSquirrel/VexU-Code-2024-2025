/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Ian Laptop                                                */
/*    Created:      10/16/2024, 8:45:01 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;


// define your global instances of motors and other devices here
enum Cartridge {
  RED,   // 100 rpm
  GREEN, // 200 rpm
  BLUE   // 600 rom
};

motor Motor1 = motor(PORT11);
motor DriveMotor{Motor1};
Cartridge Motor1Color = GREEN;
brain Brain;

void drive_config() {
  Brain.Screen.print("robot_config ");
  Brain.Screen.print("color:" + (Motor1Color == RED) ? 100 : ((Motor1Color == GREEN) ? 200 : (Motor1Color == BLUE) ? 600 : 0)); Brain.Screen.newLine();
  Motor1.setStopping(brake);
  Motor1.setVelocity((Motor1Color == RED) ? 100 : ((Motor1Color == GREEN) ? 200 : (Motor1Color == BLUE) ? 600 : 0), rpm);
}

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
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  Brain.Screen.print("pre_auton"); Brain.Screen.newLine();
  
  // Runs any motor configs necessary to drive
  drive_config();
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
  Brain.Screen.print("autonomous ");
  
  Brain.Screen.print("forward ");
  Motor1.spin(forward);
  wait(4, sec);
  Brain.Screen.print("break ");
  Motor1.stop();
  wait(2, sec);
  Brain.Screen.print("reverse ");
  Motor1.spin(reverse);
  wait(5, sec);
  Brain.Screen.print("break"); Brain.Screen.newLine();
  Motor1.stop();
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
  Brain.Screen.print("usercontrol"); Brain.Screen.newLine();
  // User control code here, inside the loop
  while (1) {
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
