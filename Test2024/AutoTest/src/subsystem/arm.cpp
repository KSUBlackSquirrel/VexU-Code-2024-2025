#include "arm.h"

namespace arm{

pros::Motor armMotor(-globalArm::armMotorID, globalArm::armColor);
STATE currentState = STOP;

void init() {
    armMotor.tare_position(); // sets the position of the arm to 0
    armMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void armUp() {
    armMotor.move_velocity(100);
}
void armDown() {
    armMotor.move_velocity(-100);
}
void armStop() {
    armMotor.brake();
}


void command(STATE state) {
    currentState = state;
}

// drive controls
void running() {
    switch(currentState) {
        case FORWARD:
            armUp();
            break;
        case BACKWARD:
            armDown();
            break;
        case STOP:
            armMotor.move_velocity(0);
            break;
    }
}


} //namespace drive