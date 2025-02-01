#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "lemlib/api.hpp"

namespace globalControl {
pros::Controller controller(pros::E_CONTROLLER_MASTER);
const int joystickDeadband = 1;
const double expoCurve = 1.0;
} // namespace control

namespace globalDrive {
const std::vector<std::int8_t> leftMotorsID = {-19,-20};
const std::vector<std::int8_t> rightMotorsID = {12,13};
const pros::v5::MotorGears driveTrainColor = pros::MotorGearset::green;
const float wheelDiameter = lemlib::Omniwheel::NEW_325;
const int wheelTrack = 11.625;
const int wheelRPM = 400;
const int horizontalDrift = 2;

const int imuID = 5;
} // namespace drive

namespace globalIntake {

} // namespace intake

namespace globalClamp {

} // namespace clamp

#endif