#ifndef PULSE_H_
#define PULSE_H_

#include "commandBase.h"
#include "custom/subsystem/motorSubsystem.h"
#include "custom/subsystem/controllerScreenSubsystem.h"

class Pulse : public CommandBase {
public:
    Pulse(MotorSubsystem* motorSub, ControllerScreenSubsystem* conSub) { 
        motorSubsystem = motorSub;
        controllerSubsystem = conSub;
        addRequirements(motorSubsystem);           // Motor needs to be required for interruption
        addUsedSubsystem(controllerSubsystem);     // Screen just needs periodic updates

        toggle = false;
        lastToggleTime = 15;
    }

    inline void execute() override {
        uint32_t currentTime = pros::millis();
        
        if (motorSubsystem->getPosition() >= 150.0) {
            motorSubsystem->backward();
            // Only toggle if enough time has passed
            if (currentTime - lastToggleTime >= delay) {
                toggle = true;
                lastToggleTime = currentTime;
            }
        } else if (motorSubsystem->getPosition() <= -150.0) {
            motorSubsystem->forward();
            // Only toggle if enough time has passed
            if (currentTime - lastToggleTime >= delay) {
                toggle = true;
                lastToggleTime = currentTime;
            }
        }
        
        if(toggle) {
            controllerSubsystem->tickPulse();
            toggle = false;
        }
    }

    inline void end() override {
        motorSubsystem->stop();
    }

    inline void interrupted() override {
        printf("pulse stopped\n");
        motorSubsystem->stop();
    }

    inline bool isFinished() override {
        return false;
    }

    inline CommandBase* clone() const override {
        return new Pulse(*this);
    }

private:
    MotorSubsystem* motorSubsystem;
    ControllerScreenSubsystem* controllerSubsystem;

    bool toggle;
    uint32_t lastToggleTime;
    int delay = 200;
};

#endif

// #ifndef PULSE_H_
// #define PULSE_H_

// #include "commandBase.h"
// #include "custom/subsystem/motorSubsystem.h"

// class Pulse : public CommandBase {
// public:
//     Pulse(MotorSubsystem* sub) { subsystem = sub; lastDirection = 0; }

//     inline void execute() override {
//         double pos = subsystem->getPosition();
//         if (pos >= 150.0 && lastDirection != -1) {
//             subsystem->backward();
//             tick++;
//             lastDirection = -1;
//         } else if (pos <= -150.0 && lastDirection != 1) {
//             subsystem->forward();
//             tick++;
//             lastDirection = 1;
//         }
//     }

//     inline void end() override {
//         subsystem->stop();
//         tick = 0;
//         lastDirection = 0;
//     }

//     inline bool isFinished() override {
//         return tick>10;
//     }

//     inline void periodic() override { subsystem->periodic(); }

// private:
//     MotorSubsystem* subsystem;
//     static int tick;
//     int lastDirection; // 1 for forward, -1 for backward, 0 for none
// };

// #endif

// inline int Pulse::tick = 0;
