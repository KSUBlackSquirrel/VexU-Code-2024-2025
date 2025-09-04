#ifndef CONTROLLERSCREENSUBSYSTEM_H_
#define CONTROLLERSCREENSUBSYSTEM_H_

#include "custom/subsystem/subsystemBase.h"
#include "custom/controller.h"

class ControllerScreenSubsystem : public SubsystemBase {
public:
    inline ControllerScreenSubsystem(Controller* con) : controller(con), count(0), countPulse(0) {
        controller->clear();
        debugPrint = true;
    }

    inline void tick() {
        ++count;
        debugPrint = true;
    }

    inline void tickPulse() {
        ++countPulse;
        debugPrint = true;
    }

    inline void periodic() override {
        updateScreen();

    }

private:
    Controller* controller;
    uint16_t count;
    uint16_t countPulse;
    bool debugPrint;
    
    inline void updateScreen() {
        if(debugPrint) {
            printf("Debug: count=%d, countPulse=%d\n", count, countPulse);
            bool result1 = controller->print(0, 0, "Seconds: %d", count);
            pros::delay(50); // added for print buffer
            bool result2 = controller->print(1, 0, "Pulse: %d", countPulse);
            pros::delay(50); // added for print buffer
            printf("Print results: line0=%d, line1=%d\n", result1, result2);
            debugPrint = false;
        }
    }
};

#endif
