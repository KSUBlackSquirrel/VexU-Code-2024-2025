#include "intake.h"
#include "globals.h"

namespace intake{

pros::Motor intakeMotor(globalIntake::intakeMotorID, globalIntake::intakeColor);


void init() {
    intakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}


void IntakeUp() {
    intakeMotor.move(127);
}
void IntakeDown() {
    intakeMotor.move(-127);
}
void IntakeStop() {
    intakeMotor.brake();
}


// drive controls
void opcontrol(pros::Controller& controller) {
    if(controller.get_digital(globalIntake::controllerMoveUp)){
        IntakeUp();
    } else if(controller.get_digital(globalIntake::controllerMoveDown)){
        IntakeDown();
    } else {
        IntakeStop();
    }
}


} //namespace drive