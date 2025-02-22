#include "conveyor.h"

namespace conveyor{

pros::Motor conveyorMotor(-globalConveyor::conveyorMotorID, globalConveyor::conveyorColor);
STATE currentState = RUNNING;

void init() {
    conveyorMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}


void conveyorUp(int velocity) {
    conveyorMotor.move_velocity(velocity);
}
void conveyorDown(int velocity) {
    conveyorMotor.move_velocity(-velocity);
}
void conveyorStop() {
    conveyorMotor.brake();
}
void conveyorStuck() {
    conveyorMotor.move(-700);
    currentState = STOP;
}

void command(STATE state) {
    currentState = state;
}

void running() {
    switch(currentState){
        case RUNNING:
            conveyoreUp(500);
            // if (conveyorMotor.get_efficiency() == 0) { //TODO
            //     currentState = STUCK;
            // }
            break;
        case INVERTED:
            conveyorDown(500);
            break;
        case STOP:
            conveyorStop();
            break;
        case STUCK:
            conveyoreStuck();
            break;
    }    
}


} //namespace drive