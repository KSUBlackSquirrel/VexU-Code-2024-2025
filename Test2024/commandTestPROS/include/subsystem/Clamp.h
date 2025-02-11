#ifndef CLAMP_SUBSYSTEM_H
#define CLAMP_SUBSYSTEM_H

#include "subsystem/Subsystem.h"

class ClampSubsystem : public Subsystem {
    public:
        ClampSubsystem() : pneumatic(globalClamp::pneumaticsID) {};

        void toggle() {
            globalClamp::pneumaticsState = !globalClamp::pneumaticsState;
            pneumatic.set_value(globalClamp::pneumaticsState);
        };
    
    private:
        pros::adi::DigitalOut pneumatic;
};

#endif