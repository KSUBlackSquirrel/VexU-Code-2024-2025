#include "conveyor.h"

namespace conveyor{

pros::Motor conveyorMotor(globalConveyor::conveyorMotorID, globalConveyor::conveyorColor);


void init() {
    conveyorMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}


void IntakeUp() {
    conveyorMotor.move(127);
}
void IntakeDown() {
    conveyorMotor.move(-127);
}
void IntakeStop() {
    conveyorMotor.brake();
}


// drive controls
void opcontrol(pros::Controller& controller) {
    if(controller.get_digital(globalConveyor::controllerMoveUp)){
        IntakeUp();
    } else if(controller.get_digital(globalConveyor::controllerMoveDown)){
        IntakeDown();
    } else {
        IntakeStop();
    }
}


} //namespace drive