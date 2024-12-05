/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Ian Laptop                                                */
/*    Created:      11/21/2024, 7:06:38 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
controller Controller = controller();
brain Brain;

// define your global instances of motors and other devices here
enum Cartridge {
  RED,   // 100 rpm
  GREEN, // 200 rpm
  BLUE   // 600 rom
};

motor ConveyorMotor = motor(PORT2, false);
Cartridge ConveyorMotorCartridge = BLUE;
motor IntakeMotor = motor(PORT3, false);
Cartridge IntakeMotorCartridge = BLUE;

int LAxis = 0;
int RAxis = 0;
int const DEADZONE = 10;
double conveyorRPM = 0.0;

motor RMotor1 = motor(PORT11, false);
motor RMotor2 = motor(PORT12, false);

motor LMotor1 = motor(PORT19, true);
motor LMotor2 = motor(PORT20, true);

motor_group RDriveTrain = motor_group(RMotor1, RMotor2);
motor_group LDriveTrain = motor_group(LMotor1, LMotor2);
Cartridge DriveTrainColor = GREEN;

//spneumatic Pnuematic = pneumatic(PORT4);


int colorToRPM(Cartridge color) {return (color == RED) ? 100 : ((color == GREEN) ? 200 : (color == BLUE) ? 600 : 0);}
double controllerMod(int stick, Cartridge color) {return (stick*colorToRPM(color))/100;}

void printInfo() {
  //Brain.Screen.clearScreen(color(0,0,0));
  //Brain.Screen.setCursor(0,0);
  Brain.Screen.clearLine();
  Brain.Screen.print("Conveyor Motor Velocity:");
  Brain.Screen.print(conveyorRPM); //TODO not recording ???
  // Brain.Screen.newLine();
  // Brain.Screen.print("RAxis/X/Y To Spin");
  // Brain.Screen.newLine();
  // Brain.Screen.print("DpadDown Sets Speed From LAxis");
  // Brain.Screen.newLine();
  // Brain.Screen.print("Motor Cartridge:");
  // printCartridge(singleMotorCartridge);
  // Brain.Screen.newLine();
  // Brain.Screen.print("Button Speed:");
  // Brain.Screen.print(buttonSpeed);

}
void conveyorUp() {ConveyorMotor.spin(forward, colorToRPM(ConveyorMotorCartridge), rpm);}
void conveyorDown() {ConveyorMotor.spin(reverse, colorToRPM(ConveyorMotorCartridge), rpm);}
void conveyorStop() {ConveyorMotor.stop();}
void IntakeUp() {IntakeMotor.spin(forward, colorToRPM(IntakeMotorCartridge), rpm);}
void IntakeDown() {IntakeMotor.spin(reverse, colorToRPM(IntakeMotorCartridge), rpm);}
void IntakeStop() {IntakeMotor.stop();}
void defineButtons() {
  Controller.ButtonL2.pressed(IntakeUp);
  Controller.ButtonL1.pressed(IntakeDown);
  Controller.ButtonL2.released(IntakeStop);
  Controller.ButtonL1.released(IntakeStop);
  Controller.ButtonR2.pressed(conveyorUp);
  Controller.ButtonR1.pressed(conveyorDown);
  Controller.ButtonR2.released(conveyorStop);
  Controller.ButtonR1.released(conveyorStop);
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
  Controller.Screen.clearScreen();
  Controller.Screen.print("hello world");
  // User control code here, inside the loop
  defineButtons();
  while (1) {
    conveyorRPM = ConveyorMotor.velocity(rpm);
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
      LDriveTrain.spin(forward, controllerMod(LAxis, DriveTrainColor), rpm);
    } else {
      LDriveTrain.stop();
    }

    if (RAxis >= DEADZONE || RAxis <= -DEADZONE) {
      RDriveTrain.spin(forward, controllerMod(RAxis, DriveTrainColor), rpm);
    } else {
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
    wait(100, msec);
    printInfo();
  }
}
