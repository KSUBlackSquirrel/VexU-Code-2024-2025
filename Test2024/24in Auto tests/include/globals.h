#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "lemlib/api.hpp"

namespace globalControl {
const static int joystickDeadband = 1;
const static double expoCurve = 1.0;
} // namespace control  

namespace globalDrive {
const static pros::controller_analog_e_t leftStickY = pros::E_CONTROLLER_ANALOG_LEFT_Y;
const static pros::controller_analog_e_t rightStickY = pros::E_CONTROLLER_ANALOG_RIGHT_Y;

const static std::vector<std::int8_t> leftMotorsID = {-1,-20,-19};
const static std::vector<std::int8_t> rightMotorsID = {10,11,12};
const static pros::v5::MotorGears driveTrainColor = pros::MotorGearset::green;
const static float wheelDiameter = lemlib::Omniwheel::NEW_325;
const static int wheelTrack = 13.625;
const static int wheelRPM = 400;
const static int horizontalDrift = 2;

const static int imuID = 2;
} // namespace drive

#endif