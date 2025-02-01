#ifndef _CLAMP_H_
#define _CLAMP_H_

#include "lemlib/api.hpp"

namespace clamp{

void init();

void toggle();

// drive controls
void opcontrol(pros::Controller& controller);

}

#endif