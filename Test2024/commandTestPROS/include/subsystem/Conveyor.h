#ifndef CONVEYOR_SUBSYSTEM_H
#define CONVEYOR_SUBSYSTEM_H

#include "subsystem/Subsystem.h"

class ConveyorSubsystem : public Subsystem {
    public:
        ConveyorSubsystem();

        void conveyorUp(int speed = 500);
        void conveyorDown(int speed = 500);
        void conveyorStop();
    
    private:
        pros::Motor conveyorMotor;
};

#endif