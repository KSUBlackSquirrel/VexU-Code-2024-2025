#ifndef ARM_SUBSYSTEM_H
#define ARM_SUBSYSTEM_H

#include "subsystem/Subsystem.h"

class ArmSubsystem : public Subsystem {
    public:
        ArmSubsystem();

        void armUp();
        void armDown();

        void print();

        void periodic() override;
    
    private:
        pros::Motor armMotor;
};

#endif