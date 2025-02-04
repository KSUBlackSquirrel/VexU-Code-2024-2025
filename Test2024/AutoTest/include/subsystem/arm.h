#ifndef _ARM_H_
#define _ARM_H_

#include "lemlib/api.hpp"
#include "globals.h"

namespace arm{

void init();

void armUp();
void armDown();

void print(pros::Controller& controller);

// drive controls
void opcontrol(pros::Controller& controller);

}

#endif