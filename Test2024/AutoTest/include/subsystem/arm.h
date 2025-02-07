#ifndef ARM_H_
#define ARM_H_

#include "lemlib/api.hpp"
#include "globals.h"

namespace arm{

enum STATE{
    FORWARD,
    BACKWARD,
    STOP
};

void init();

void armUp();
void armDown();
void armStop();

void print(pros::Controller& controller);

void command(STATE state);
void running();

}

#endif