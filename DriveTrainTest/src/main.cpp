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

motor RMotor1 = motor(PORT1);
motor RMotor2 = motor(PORT10);

motor_group RDriveTrain;

motor LMotor1 = motor(PORT11);
motor LMotor2 = motor(PORT20);

motor_group LDriveTrain;

Cartridge DriveTrainColor = GREEN;
controller Controller = controller();

int LAxis;
int RAxis;




brain Brain;


void drive_config() {
  Brain.Screen.print("robot_config "); 
  RMotor1.setReversed(true);
  RMotor2.setReversed(true);

  motor_group RDriveTrain = motor_group(RMotor1,RMotor2);

  LMotor1.setReversed(false);
  LMotor2.setReversed(false);

  motor_group LDriveTrain = motor_group(LMotor1,LMotor2);


  RDriveTrain.setStopping(brake);
  LDriveTrain.setStopping(brake);

  RDriveTrain.setVelocity((DriveTrainColor == RED) ? 100 : ((DriveTrainColor == GREEN) ? 200 : (DriveTrainColor == BLUE) ? 600 : 0), rpm);
  LDriveTrain.setVelocity((DriveTrainColor == RED) ? 100 : ((DriveTrainColor == GREEN) ? 200 : (DriveTrainColor == BLUE) ? 600 : 0), rpm);
  drivetrain Drivetrain = drivetrain(LDriveTrain, RDriveTrain, 259.34, 320, 40, mm, 1);
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
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    LAxis = Controller.Axis3.position();
    RAxis = Controller.Axis2.position();
    
    Brain.Screen.print("LAxis:" + LAxis);
    Brain.Screen.print("RAxis:" + RAxis); Brain.Screen.newLine();
    

    if (LAxis >= 10) {
        LDriveTrain.spin(forward);
    }else if (LAxis <= -10){
        LDriveTrain.spin(reverse);
    }else{
      LDriveTrain.stop();
    }

    if (RAxis >= 10) {
        RDriveTrain.spin(forward);
    }else if (RAxis <= -10){
        RDriveTrain.spin(reverse);
    }else{
      RDriveTrain.stop();
    }


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
