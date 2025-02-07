#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "lemlib/api.hpp"

namespace globalControl {
pros::Controller controller(pros::E_CONTROLLER_MASTER);
const static int joystickDeadband = 1;
const static double expoCurve = 1.0;
} // namespace control

namespace globalDrive {
const static pros::controller_analog_e_t leftStickY = pros::E_CONTROLLER_ANALOG_LEFT_Y;
const static pros::controller_analog_e_t rightStickY = pros::E_CONTROLLER_ANALOG_RIGHT_Y;

const static std::vector<std::int8_t> leftMotorsID = {-19,-20};
const static std::vector<std::int8_t> rightMotorsID = {12,13};
const static pros::v5::MotorGears driveTrainColor = pros::MotorGearset::green;
const static float wheelDiameter = lemlib::Omniwheel::NEW_325;
const static int wheelTrack = 11.625;
const static int wheelRPM = 400;
const static int horizontalDrift = 2;

const static int imuID = 5;
} // namespace drive

namespace globalIntake {
const static std::int8_t intakeMotorID = 3;
const static pros::v5::MotorGears intakeColor = pros::MotorGearset::blue;

static pros::controller_digital_e_t controllerMoveUp = pros::E_CONTROLLER_DIGITAL_L1;
static pros::controller_digital_e_t controllerMoveDown = pros::E_CONTROLLER_DIGITAL_L2;

} // namespace intake

namespace globalConveyor {
const static std::int8_t conveyorMotorID = 2;
const static pros::v5::MotorGears conveyorColor = pros::MotorGearset::blue;

const static pros::controller_digital_e_t controllerMoveUp = pros::E_CONTROLLER_DIGITAL_R2;
const static pros::controller_digital_e_t controllerMoveDown = pros::E_CONTROLLER_DIGITAL_R1;

} // namespace outtake

namespace globalClamp {
const static char pneumaticsID = 'F';

const static pros::controller_digital_e_t pneumaticsButton = pros::E_CONTROLLER_DIGITAL_X;
static bool pneumaticsState = false;

} // namespace clamp

namespace globalArm {
const static std::int8_t armMotorID = 7;
const static pros::MotorGears armColor = pros::MotorGearset::green;

const static pros::controller_digital_e_t controllerMoveUp = pros::E_CONTROLLER_DIGITAL_UP;
const static pros::controller_digital_e_t controllerMoveDown = pros::E_CONTROLLER_DIGITAL_DOWN;

} // namespace arm

#endif