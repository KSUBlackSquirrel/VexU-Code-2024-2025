#ifndef CONVEYOR_SUBSYSTEM_H_
#define CONVEYOR_SUBSYSTEM_H_

#include "lemlib/api.hpp"
#include "subsystem/Subsystem.h"
#include "Globals.h"

class ConveyorSubsystem : public Subsystem {
    public:
        ConveyorSubsystem();

        void conveyorUp();
        void conveyorDown();
        void conveyorStop();

        pros::Motor conveyorMotor;
};

#endif