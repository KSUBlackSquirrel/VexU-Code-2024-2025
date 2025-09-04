#include "arm.h"

namespace arm{

pros::Motor armMotor(-globalArm::armMotorID, globalArm::armColor);
STATE currentState = STOP;

void init() {
    armMotor.tare_position(); // sets the position of the arm to 0
    armMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void armUp(int velocity) {
    armMotor.move_velocity(velocity);
}
void armDown(int velocity) {
    armMotor.move_velocity(-velocity);
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
            armUp(50);
            break;
        case BACKWARD:
            armDown(50);
            break;
        case STOP:
            armStop();
            break;
    }
}


} //namespace drive