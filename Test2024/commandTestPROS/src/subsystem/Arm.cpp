#include "Arm.h"


ArmSubsystem::ArmSubsystem() : armMotor(globalArm::armMotorID, globalArm::armColor) {
    armMotor.tare_position(); // sets the position of the arm to 0
    armMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

/**
 * +-100 for E_MOTOR_GEARSET_36 | red
 * +-200 for E_MOTOR_GEARSET_18 | green
 * +-600 for E_MOTOR_GEARSET_6  | blue
 */
void ArmSubsystem::armUp() {
    armMotor.move_velocity(100);
}
void ArmSubsystem::armDown() {
    armMotor.move_velocity(-100);
}

void ArmSubsystem::print() {
    globalControl::controller.print(0, 0, "arm pos: %d", armMotor.get_position());
}

void ArmSubsystem::periodic() {
    this->print();
}
