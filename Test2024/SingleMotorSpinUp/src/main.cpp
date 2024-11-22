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

// define your global instances of motors and other devices here
enum Cartridge {
  RED,   // 100 rpm
  GREEN, // 200 rpm
  BLUE   // 600 rom
};

motor singleMotor = motor(PORT1, false);
Cartridge singleMotorCartridge = RED;

controller Controller = controller();
int const DEADZONE = 10;
int RAxis = 0;
int buttonSpeed = 100;
bool updown = false;

brain Brain;

int colorToRPM(Cartridge color) {return (color == RED) ? 100 : ((color == GREEN) ? 200 : (color == BLUE) ? 600 : 0);}
double controllerMod(int stick, Cartridge color) {return (stick*colorToRPM(color))/100;}
void printCartridge(Cartridge color) {
  if(singleMotorCartridge == RED) {
    Brain.Screen.print("Red");
  } else if(singleMotorCartridge == GREEN) {
    Brain.Screen.print("Green");
  } else if(singleMotorCartridge == BLUE) {
    Brain.Screen.print("Blue");
  }
}

void printInfo() {
  Brain.Screen.clearScreen(color(0,0,0));
  Brain.Screen.setCursor(0,0);
  Brain.Screen.print("Port 1 Active");
  Brain.Screen.newLine();
  Brain.Screen.print("A To Switch Cartridge");
  Brain.Screen.newLine();
  Brain.Screen.print("RAxis/X/Y To Spin");
  Brain.Screen.newLine();
  Brain.Screen.print("DpadDown Sets Speed From LAxis");
  Brain.Screen.newLine();
  Brain.Screen.print("Motor Cartridge:");
  printCartridge(singleMotorCartridge);
  Brain.Screen.newLine();
  Brain.Screen.print("Button Speed:");
  Brain.Screen.print(buttonSpeed);

}

void switchMotorCartridge() {
  if(singleMotorCartridge == RED) {
    singleMotorCartridge = GREEN;
  } else if(singleMotorCartridge == GREEN) {
    singleMotorCartridge = BLUE;
  } else if(singleMotorCartridge == BLUE) {
    singleMotorCartridge = RED;
  }
  printInfo();
}
void changeSpeed() {
  buttonSpeed = updown ? buttonSpeed+1 : buttonSpeed-1;
  if(buttonSpeed >= 100) {
    updown = false;
  } else if (buttonSpeed <= 0) {
    updown = true;
  }
  printInfo();
}
void setSpeed() {
  buttonSpeed = abs(Controller.Axis3.value())>100 ? 100 : abs(Controller.Axis3.value());
  printInfo();
}
void setRAxisMax() {RAxis=buttonSpeed;}
void setRAxisRMax() {RAxis=-buttonSpeed;}
void setRAxisZero() {RAxis=0;}
void defineButtons() {
  Controller.ButtonA.pressed(switchMotorCartridge);
  Controller.ButtonY.pressed(setRAxisMax);
  Controller.ButtonY.released(setRAxisZero);
  Controller.ButtonX.pressed(setRAxisRMax);
  Controller.ButtonX.released(setRAxisZero);
  Controller.ButtonB.pressed(changeSpeed);
  Controller.ButtonDown.pressed(setSpeed);
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
  printInfo();
  defineButtons();
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................


    if(!Controller.ButtonY.pressing() && !Controller.ButtonX.pressing()) {
      RAxis = Controller.Axis2.position();
    }

    if (RAxis >= DEADZONE || RAxis <= -DEADZONE) {
      singleMotor.spin(forward, controllerMod(RAxis, singleMotorCartridge), rpm);
    } else {
      singleMotor.stop();
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
