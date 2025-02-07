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

void IntakeUp();
void IntakeDown();
void IntakeStop();


void command(STATE state);
void running();

}

#endif