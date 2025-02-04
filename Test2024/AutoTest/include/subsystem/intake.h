#ifndef _INTAKE_H_
#define _INTAKE_H_

#include "lemlib/api.hpp"
#include "globals.h"

namespace intake{

void init();

void IntakeUp();
void IntakeDown();
void IntakeStop();


// drive controls
void opcontrol(pros::Controller& controller);

}

#endif