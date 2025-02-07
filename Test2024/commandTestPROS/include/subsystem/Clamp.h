#ifndef CLAMP_SUBSYSTEM_H_
#define CLAMP_SUBSYSTEM_H_

#include "lemlib/api.hpp"
#include "subsystem/Subsystem.h"
#include "Globals.h"

class ClampSubsystem : public Subsystem {
    public:
        ClampSubsystem() : pneumatic(globalClamp::pneumaticsID) {};

        void toggle() {
            globalClamp::pneumaticsState = !globalClamp::pneumaticsState;
            pneumatic.set_value(globalClamp::pneumaticsState);
        };

        pros::adi::DigitalOut pneumatic;
};

#endif