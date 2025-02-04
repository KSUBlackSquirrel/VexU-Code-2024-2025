#include "arm.h"
#include "globals.h"

namespace arm{

pros::Motor armMotor(globalArm::armMotorID, globalArm::armColor);

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

void print(pros::Controller& controller) {
    controller.print(0, 0, "arm pos: %d", armMotor.get_position());
}

// drive controls
void opcontrol(pros::Controller& controller) {
    if(controller.get_digital(globalArm::controllerMoveUp)){
        armUp();
    } else if(controller.get_digital(globalArm::controllerMoveDown)){
        armDown();
    } else {
        armMotor.move_velocity(0);
    }
}


} //namespace drive