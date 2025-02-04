#ifndef _CONVEYOR_H_
#define _CONVEYOR_H_

#include "lemlib/api.hpp"

namespace conveyor{

void init();

void conveyorUp();
void conveyorDown();
void conveyorStop();


// drive controls
void opcontrol(pros::Controller& controller);

}

#endif