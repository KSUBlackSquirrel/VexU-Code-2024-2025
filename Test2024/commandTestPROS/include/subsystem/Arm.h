#ifndef ARM_SUBSYSTEM_H_
#define ARM_SUBSYSTEM_H_

#include "lemlib/api.hpp"
#include "subsystem/Subsystem.h"
#include "Globals.h"

class ArmSubsystem : public Subsystem {
    public:
        ArmSubsystem();

        void armUp();
        void armDown();

        void print();

        void periodic();

        pros::Motor armMotor;
};

#endif