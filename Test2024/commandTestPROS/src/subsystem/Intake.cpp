#include "intake.h"


IntakeSubsystem::IntakeSubsystem() : intakeMotor(globalIntake::intakeMotorID, globalIntake::intakeColor) {
    intakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}


void IntakeSubsystem::IntakeUp(int speed = 600) {
    intakeMotor.move_velocity(speed);
}
void IntakeSubsystem::IntakeDown(int speed = 600) {
    intakeMotor.move_velocity(-speed);
}
void IntakeSubsystem::IntakeStop() {
    intakeMotor.brake();
}
