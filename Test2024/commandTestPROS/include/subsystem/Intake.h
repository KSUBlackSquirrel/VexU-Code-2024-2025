#ifndef INTAKE_SUBSYSTEM_H
#define INTAKE_SUBSYSTEM_H

#include "subsystem/Subsystem.h"

class IntakeSubsystem : public Subsystem {
    public:
        IntakeSubsystem();

        void IntakeUp(int speed = 600);
        void IntakeDown(int speed = 600);
        void IntakeStop();

    private:
        pros::Motor intakeMotor;
};

#endif