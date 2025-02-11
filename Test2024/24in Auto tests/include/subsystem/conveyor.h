#ifndef CONVEYOR_H_
#define CONVEYOR_H_

#include "lemlib/api.hpp"
#include "globals.h"

namespace conveyor{

enum STATE{
    RUNNING,
    INVERTED,
    STOP,
    STUCK
};

void init();

void conveyorUp();
void conveyorDown();
void conveyorStop();


void command(STATE state);\
void running();

}

#endif