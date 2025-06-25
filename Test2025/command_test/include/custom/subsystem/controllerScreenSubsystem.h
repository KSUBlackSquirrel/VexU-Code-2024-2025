#ifndef CONTROLLERSCREENSUBSYSTEM_H_
#define CONTROLLERSCREENSUBSYSTEM_H_

#include "custom/subsystem/subsystemBase.h"
#include "custom/controller.h"

class ControllerScreenSubsystem : public SubsystemBase {
public:
    inline ControllerScreenSubsystem(scheduler::Controller* con) : controller(con), count(0) {
        controller->clear();
        controller->print(1, 0, "Seconds: %d", count);
    }

    inline void tick() {
        controller->print(1, 0, "Seconds: %d", ++count);
    }

    inline void periodic() override {
        tick();
    }

private:
    scheduler::Controller* controller;
    int count;
};

#endif
