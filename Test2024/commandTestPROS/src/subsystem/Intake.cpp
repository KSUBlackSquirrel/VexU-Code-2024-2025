#include "intake.h"


IntakeSubsystem::IntakeSubsystem() : intakeMotor(globalIntake::intakeMotorID, globalIntake::intakeColor) {
    intakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}


void IntakeSubsystem::IntakeUp(int speed) {
    intakeMotor.move(speed);
}
void IntakeSubsystem::IntakeDown(int speed) {
    intakeMotor.move(-speed);
}
void IntakeSubsystem::IntakeStop() {
    intakeMotor.brake();
}
