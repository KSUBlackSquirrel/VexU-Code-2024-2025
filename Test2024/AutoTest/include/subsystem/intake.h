#ifndef _INTAKE_H_
#define _INTAKE_H_

#include "lemlib/api.hpp"

namespace intake{

void init();

// drive controls
void opcontrol(pros::Controller& controller);

}

#endif