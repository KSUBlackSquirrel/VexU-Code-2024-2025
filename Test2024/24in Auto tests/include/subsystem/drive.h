#ifndef _DRIVE_H_
#define _DRIVE_H_

#include "lemlib/api.hpp"

namespace drive{

void init();

lemlib::Pose pos();

void autonomous();

// drive controls
void opcontrol(pros::Controller& controller);

}

#endif