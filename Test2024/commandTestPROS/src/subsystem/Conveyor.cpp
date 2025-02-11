#include "conveyor.h"


ConveyorSubsystem::ConveyorSubsystem() : conveyorMotor(globalConveyor::conveyorMotorID, globalConveyor::conveyorColor) {
    conveyorMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void ConveyorSubsystem::conveyorUp(int speed = 500) {
    conveyorMotor.move_velocity(speed);
}
void ConveyorSubsystem::conveyorDown(int speed = 500) {
    conveyorMotor.move_velocity(-speed);
}
void ConveyorSubsystem::conveyorStop() {
    conveyorMotor.brake();
}
