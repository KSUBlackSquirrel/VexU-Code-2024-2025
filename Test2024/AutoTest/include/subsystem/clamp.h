#ifndef _CLAMP_H_
#define _CLAMP_H_

#include "lemlib/api.hpp"
#include "globals.h"

namespace clamp{

void init();

void toggle();

// drive controls
void opcontrol(pros::Controller& controller);

}

#endif