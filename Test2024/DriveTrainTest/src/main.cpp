/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       the5l                                                     */
/*    Created:      10/30/2024, 8:13:44 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include <cmath>

using namespace vex;

// A global instance of competition
competition Competition;


// define your global instances of motors and other devices here
enum Cartridge {
  RED,   // 100 rpm
  GREEN, // 200 rpm
  BLUE   // 600 rom
};

motor RMotor1 = motor(PORT11, false);
motor RMotor2 = motor(PORT20, false);
motor RMotor3 = motor(PORT15, false);

motor LMotor1 = motor(PORT1, true);
motor LMotor2 = motor(PORT10, true);
motor LMotor3 = motor(PORT5, true);

motor_group RDriveTrain = motor_group(RMotor1, RMotor2, RMotor3);
motor_group LDriveTrain = motor_group(LMotor1, LMotor2, LMotor3);

Cartridge DriveTrainColor = GREEN;  
controller Controller = controller();

int LAxis = 0;
int RAxis = 0;
int const DEADZONE = 10;

brain Brain;
int printTime = 0;
int pressed = 0;

int colorToRPM(Cartridge color) {return (color == RED) ? 100 : ((color == GREEN) ? 200 : (color == BLUE) ? 600 : 0);}

void drive_config() {
  //drivetrain Drivetrain = drivetrain(LDriveTrain, RDriveTrain, 259.34, 320, 40, mm, 1); // sets all default, :cry:

  Brain.Screen.print("robot_config "); 

  RDriveTrain.setStopping(brake);
  LDriveTrain.setStopping(brake);

  RDriveTrain.setVelocity(colorToRPM(GREEN), rpm);
  LDriveTrain.setVelocity(colorToRPM(GREEN), rpm);
}

void printInfo() {
  if(printTime == 2) {
    Brain.Screen.clearLine();
    Brain.Screen.print("pressed:");
    Brain.Screen.print(pressed);
    Brain.Screen.print(" LAxis:");
    Brain.Screen.print(LAxis);
    Brain.Screen.print(" RAxis:");
    Brain.Screen.print(RAxis);
    printTime = 0;
  } else {
    printTime++;
  }
}

void AtriggerPressed() {
  pressed = (pressed+1) % 4;

  Brain.Screen.print("controller button A pressed");
}

void BtriggerPressed() {
  pressed = 0;

  Brain.Screen.print("controller button B pressed");
}

void XtriggerPressed() {
  pressed = 1;

  Brain.Screen.print("controller button X pressed");
}

void YtriggerPressed() {
  pressed = 2;

  Brain.Screen.print("controller button Y pressed");
}

double controllerMod(int stick, Cartridge color) {
  // x = stick; m = color; s = 100
  // https://www.desmos.com/calculator/ju01k7ni16
  switch (pressed) {
    case 0:
      return ((pow((stick*colorToRPM(color)),3))/(pow((colorToRPM(color)*100),2)))/100;                                                                                                                                                                       // ((x*m)^3/(m*s)^2)/s      | exponential slow ramp   | domain [-100,100]             | range [-200,200]
    case 1:
      return (stick>=0.0) ? (((pow((stick*colorToRPM(color)),2))/(colorToRPM(color)*100))/100) : -(((pow((stick*colorToRPM(color)),2))/(colorToRPM(color)*100))/100);                                                                                         // (((x*m)^2)/(m*s))/s      | exponential faster ramp | domain [-100,0)U[0,100]       | range [-200,0)U[0,200]
    case 2:
      return (stick==0.0) ? 0.0 : ((stick>0.0) ? (((pow((colorToRPM(color)*(pow(stick,2))),3))/((pow((stick*colorToRPM(color)*100),2))))/pow(100,2)) : -(((pow((colorToRPM(color)*(pow(stick,2))),3))/((pow((stick*colorToRPM(color)*100),2))))/pow(100,2))); // (((mx^2)^3/(msx)^2))/s^2 | exponential faster ramp | domain [-100,0)U[0,0]U(0,100] | range [-200,0)U[0,0]U(0,200]
    case 3:
      return (stick*colorToRPM(color))/100; //I like it :(                                                                                                                                                                                                    // (x*m)/s                  | linear                  | domain [-100,100]             | range [-200,200]
  }
  Brain.Screen.print("**********DRIVE ERROR**********");
  return 0.0;
}

void defineButtons() {
  Controller.ButtonA.pressed(AtriggerPressed);
  Controller.ButtonB.pressed(BtriggerPressed);
  Controller.ButtonX.pressed(XtriggerPressed);
  Controller.ButtonY.pressed(YtriggerPressed);
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
  // Runs any motor configs necessary to drive
  defineButtons();
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    
    //******************drive control//******************//
    LAxis = Controller.Axis3.position();
    RAxis = Controller.Axis2.position();

    if (LAxis >= DEADZONE || LAxis <= -DEADZONE) {
      LDriveTrain.spin(forward, controllerMod(LAxis, GREEN), rpm);
    }else{
      LDriveTrain.stop();
    }

    if (RAxis >= DEADZONE || RAxis <= -DEADZONE) {
      RDriveTrain.spin(forward, controllerMod(RAxis, GREEN), rpm);
    }else {
      RDriveTrain.stop();
      }
  //******************drive control//******************//

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
    printInfo();
    wait(100, msec);
  }
}
