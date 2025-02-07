#include "conveyor.h"


ConveyorSubsystem::ConveyorSubsystem() : conveyorMotor(globalConveyor::conveyorMotorID, globalConveyor::conveyorColor) {
    conveyorMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void ConveyorSubsystem::conveyorUp() {
    conveyorMotor.move(127);
}
void ConveyorSubsystem::conveyorDown() {
    conveyorMotor.move(-127);
}
void ConveyorSubsystem::conveyorStop() {
    conveyorMotor.brake();
}
