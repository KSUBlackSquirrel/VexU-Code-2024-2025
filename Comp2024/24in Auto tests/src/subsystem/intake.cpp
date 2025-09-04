#include "intake.h"

namespace intake{

pros::Motor intakeMotor(globalIntake::intakeMotorID, globalIntake::intakeColor);
STATE currentState = RUNNING;

void init() {
    intakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}


void IntakeUp(int velocity) {
    intakeMotor.move_velocity(velocity);
}
void IntakeDown(int velocity) {
    intakeMotor.move_velocity(-velocity);
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
            IntakeUp(600);
            break;
        case INVERTED:
            IntakeDown(600);
            break;
        case STOP:
            IntakeStop();
            break;
    }
}


} //namespace drive