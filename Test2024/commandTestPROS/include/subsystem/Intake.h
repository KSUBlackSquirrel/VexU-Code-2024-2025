#ifndef INTAKE_SUBSYSTEM_H_
#define INTAKE_SUBSYSTEM_H_

#include "lemlib/api.hpp"
#include "subsystem/Subsystem.h"
#include "Globals.h"

class IntakeSubsystem : public Subsystem {
    public:
        IntakeSubsystem();

        void IntakeUp(int speed);
        void IntakeDown(int speed);
        void IntakeStop();

        pros::Motor intakeMotor;
};

#endif