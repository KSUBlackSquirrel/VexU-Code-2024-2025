#include "conveyor.h"

namespace conveyor{

pros::Motor conveyorMotor(-globalConveyor::conveyorMotorID, globalConveyor::conveyorColor);
STATE currentState = RUNNING;

void init() {
    conveyorMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}


void IntakeUp() {
    conveyorMotor.move_velocity(500);
}
void IntakeDown() {
    conveyorMotor.move_velocity(-500);
}
void IntakeStop() {
    conveyorMotor.brake();
}
void IntakeStuck() {
    conveyorMotor.move(-700);
    currentState = STOP;
}

void command(STATE state) {
    currentState = state;
}

void running() {
    switch(currentState){
        case RUNNING:
            IntakeUp();
            if (conveyorMotor.get_efficiency() == 0) { //TODO
                currentState = STUCK;
            }
            break;
        case INVERTED:
            IntakeDown();
            break;
        case STOP:
            IntakeStop();
            break;
        case STUCK:
            IntakeStuck();
            break;
    }    
}


} //namespace drive