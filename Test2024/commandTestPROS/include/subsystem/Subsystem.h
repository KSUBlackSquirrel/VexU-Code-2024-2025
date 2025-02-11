#ifndef SUBSYSTEM_SUBSYSTEM_H
#define SUBSYSTEM_SUBSYSTEM_H

#include "main.h"
#include "lemlib/api.hpp"
#include "globals.h"

class Subsystem {
    public:
        Subsystem() {};

        // This method is called periodically by the Scheduler.
        virtual void periodic() {};
};


#endif