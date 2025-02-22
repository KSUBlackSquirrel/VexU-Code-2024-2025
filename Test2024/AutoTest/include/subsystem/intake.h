#ifndef INTAKE_H_
#define INTAKE_H_

#include "lemlib/api.hpp"
#include "globals.h"

namespace intake{

enum STATE{
    RUNNING,
    INVERTED,
    STOP
};

void init();

void intakeUp(int velocity);
void intakeDown(int velocity);
void intakeStop();


void command(STATE state);
void running();

}

#endif