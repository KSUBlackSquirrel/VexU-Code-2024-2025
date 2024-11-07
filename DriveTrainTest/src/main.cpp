/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       the5l                                                     */
/*    Created:      10/30/2024, 8:13:44 PM                                    */
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

motor RMotor1 = motor(PORT11, true);
motor RMotor2 = motor(PORT20, true);

motor LMotor1 = motor(PORT1, false);
motor LMotor2 = motor(PORT10, false);

motor_group RDriveTrain = motor_group(RMotor1, RMotor2);
motor_group LDriveTrain = motor_group(LMotor1, LMotor2);

Cartridge DriveTrainColor = GREEN;
controller Controller = controller();

int LAxis = 0;
int RAxis = 0;

brain Brain;
int printTime = 0;
bool pressed = false;

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

void triggerPressed() {
  if (pressed) 
    pressed = false;
  else
    pressed = true;

  Brain.Screen.print("controller button pressed");
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
  drive_config(); 
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    LAxis = Controller.Axis3.position();
    RAxis = Controller.Axis2.position();

    Controller.ButtonA.pressed(triggerPressed);
    
    if(pressed) {
      //******************Linear Speed Increase*****************/
      if (LAxis >= 10 ) {
        LDriveTrain.spin(forward, (LAxis*colorToRPM(GREEN))/100, rpm);
      }else if ( LAxis <= -10) {
        LDriveTrain.spin(reverse, (LAxis*colorToRPM(GREEN))/100, rpm);
      }else{
        LDriveTrain.stop();
      }

      if (RAxis >= 10) {
        RDriveTrain.spin(forward, (RAxis*colorToRPM(GREEN))/100, rpm);
      }else if(RAxis <= -10) {
        RDriveTrain.spin(reverse, (RAxis*colorToRPM(GREEN))/100, rpm);
      }else {
        RDriveTrain.stop();
      }
    } else {
      //******************Exponetial Speed Increase*****************/
      if (LAxis >= 10) {
        LDriveTrain.spin(forward, ((((LAxis*colorToRPM(GREEN))*(LAxis*colorToRPM(GREEN)))/(colorToRPM(GREEN)*100))/100), rpm);
      }else if(LAxis <= -10) {
        LDriveTrain.spin(reverse, ((((LAxis*colorToRPM(GREEN))*(LAxis*colorToRPM(GREEN)))/(colorToRPM(GREEN)*100))/100), rpm);
      }else {
        LDriveTrain.stop();
      }

      if (RAxis >= 10) {
        RDriveTrain.spin(forward, ((((RAxis*colorToRPM(GREEN))*(RAxis*colorToRPM(GREEN)))/(colorToRPM(GREEN)*100))/100), rpm);
      }else if(RAxis <= -10) {
        RDriveTrain.spin(reverse, ((((RAxis*colorToRPM(GREEN))*(RAxis*colorToRPM(GREEN)))/(colorToRPM(GREEN)*100))/100), rpm);
      }else{
        RDriveTrain.stop();
      }
    }

    //******************Set to max speed*****************/
    // if (LAxis >= 10 || LAxis <= -10) {
    //   LDriveTrain.spin(forward, colorToRPM(GREEN), rpm);
    // }else{
    //   LDriveTrain.stop();
    // }

    // if (RAxis >= 10 || RAxis <= -10) {
    //   RDriveTrain.spin(forward, colorToRPM(GREEN),, rpm);
    // }else{
    //   RDriveTrain.stop();
    // }

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
