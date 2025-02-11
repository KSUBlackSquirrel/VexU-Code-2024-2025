#include "intake.h"

namespace intake{

pros::Motor intakeMotor(globalIntake::intakeMotorID, globalIntake::intakeColor);
STATE currentState = RUNNING;

void init() {
    intakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}


void IntakeUp() {
    intakeMotor.move_velocity(600);
}
void IntakeDown() {
    intakeMotor.move_velocity(-600);
}
void IntakeStop() {
    intakeMotor.brake();
}

void command(STATE state) {
    currentState = state;
}

// drive controls
void running() {
    switch(currentState) {
        case RUNNING:
            IntakeUp();
            break;
        case INVERTED:
            IntakeDown();
            break;
        case STOP:
            IntakeStop();
            break;
    }
}


} //namespace drive