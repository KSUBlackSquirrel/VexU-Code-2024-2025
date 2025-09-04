#include "intake.h"

namespace intake{

pros::Motor intakeMotor(globalIntake::intakeMotorID, globalIntake::intakeColor);
STATE currentState = RUNNING;

void init() {
    intakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}


void intakeUp(int velocity) {
    intakeMotor.move_velocity(velocity);
}
void intakeDown(int velocity) {
    intakeMotor.move_velocity(-velocity);
}
void intakeStop() {
    intakeMotor.brake();
}

void command(STATE state) {
    currentState = state;
}

// drive controls
void running() {
    switch(currentState) {
        case RUNNING:
            intakeUp(600);
            break;
        case INVERTED:
            intakeDown(600);
            break;
        case STOP:
            intakeStop();
            break;
    }
}


} //namespace drive