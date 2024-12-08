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
competition COMPETITION;
controller CONTROLLER = controller();
brain BRAIN;

// define your global instances of motors and other devices here
enum Cartridge {
  RED,   // 100 rpm
  GREEN, // 200 rpm
  BLUE   // 600 rom
};

motor conveyorMotor = motor(PORT2, false);
Cartridge conveyorMotorCartridge = GREEN;
motor intakeMotor = motor(PORT3, false);
Cartridge intakeMotorCartridge = BLUE;

int leftAxis = 0;
int rightAxis = 0;
int const DEADZONE = 10;
double conveyorRPM = 0.0;

motor rightMotor1 = motor(PORT11, false);
motor rightMotor2 = motor(PORT12, false);

motor leftMotor1 = motor(PORT19, true);
motor leftMotor2 = motor(PORT20, true);

motor_group rightDriveTrain = motor_group(rightMotor1, rightMotor2);
motor_group leftDriveTrain = motor_group(leftMotor1, leftMotor2);
Cartridge driveTrainColor = GREEN;

digital_out pneumatic = digital_out(BRAIN.ThreeWirePort.F);
bool pneumaticState = false;

int colorToRPM(Cartridge color) {return (color == RED) ? 100 : ((color == GREEN) ? 200 : (color == BLUE) ? 600 : 0);}
double controllerMod(int stick, Cartridge color) {return (stick*colorToRPM(color))/100;}

void recordInfo() {
  conveyorRPM = conveyorMotor.velocity(rpm);
}
void printInfo() {
  //******************Controller Screen******************//
  CONTROLLER.Screen.clearScreen();
  CONTROLLER.Screen.setCursor(0,0);
  CONTROLLER.Screen.print("Conveyor Velocity:");
  CONTROLLER.Screen.print(conveyorRPM);
  //******************Controller Screen******************//


  //******************Brain Screen******************//
  BRAIN.Screen.clearScreen(color(0,0,0));
  BRAIN.Screen.setCursor(0,0);
  BRAIN.Screen.print("Conveyor Velocity:");
  BRAIN.Screen.print(conveyorRPM);
  BRAIN.Screen.newLine();
  BRAIN.Screen.print("pneumaticState:");
  BRAIN.Screen.print(pneumaticState);
  // BRAIN.Screen.newLine();
  // BRAIN.Screen.print("DpadDown Sets Speed From leftAxis");
  // BRAIN.Screen.newLine();
  // BRAIN.Screen.print("Motor Cartridge:");
  // printCartridge(singleMotorCartridge);
  // BRAIN.Screen.newLine();
  // BRAIN.Screen.print("Button Speed:");
  // BRAIN.Screen.print(buttonSpeed);
  //******************Brain Screen******************//

}
void conveyorUp() {conveyorMotor.spin(forward, colorToRPM(conveyorMotorCartridge), rpm);}
void conveyorDown() {conveyorMotor.spin(reverse, colorToRPM(conveyorMotorCartridge), rpm);}
void conveyorStop() {conveyorMotor.stop();}
void IntakeUp() {intakeMotor.spin(forward, colorToRPM(intakeMotorCartridge), rpm);}
void IntakeDown() {intakeMotor.spin(reverse, colorToRPM(intakeMotorCartridge), rpm);}
void IntakeStop() {intakeMotor.stop();}
void pneumaticToggle() {pneumaticState=!pneumaticState; pneumatic.set(pneumaticState);}
void defineButtons() {
  CONTROLLER.ButtonL2.pressed(IntakeUp);
  CONTROLLER.ButtonL1.pressed(IntakeDown);
  CONTROLLER.ButtonL2.released(IntakeStop);
  CONTROLLER.ButtonL1.released(IntakeStop);
  CONTROLLER.ButtonR2.pressed(conveyorUp);
  CONTROLLER.ButtonR1.pressed(conveyorDown);
  CONTROLLER.ButtonR2.released(conveyorStop);
  CONTROLLER.ButtonR1.released(conveyorStop);
  CONTROLLER.ButtonX.pressed(pneumaticToggle);
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
  defineButtons();
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    //******************drive control******************//
    leftAxis = CONTROLLER.Axis3.position();
    rightAxis = CONTROLLER.Axis2.position();

    if (leftAxis >= DEADZONE || leftAxis <= -DEADZONE) {
      leftDriveTrain.spin(forward, controllerMod(leftAxis, driveTrainColor), rpm);
    } else {
      leftDriveTrain.stop();
    }

    if (rightAxis >= DEADZONE || rightAxis <= -DEADZONE) {
      rightDriveTrain.spin(forward, controllerMod(rightAxis, driveTrainColor), rpm);
    } else {
      rightDriveTrain.stop();
    }
    //******************drive control******************//

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  COMPETITION.autonomous(autonomous);
  COMPETITION.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
    recordInfo();
    printInfo();
  }
}
