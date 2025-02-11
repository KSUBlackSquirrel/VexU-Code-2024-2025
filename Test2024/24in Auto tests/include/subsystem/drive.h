#ifndef _DRIVE_H_
#define _DRIVE_H_

#include "lemlib/api.hpp"
#include "globals.h"

namespace drive{

void init();

lemlib::Pose pos();

void autonomous();

// drive controls
void tankDrive(pros::Controller& controller, bool inverted = false);

}

#endif