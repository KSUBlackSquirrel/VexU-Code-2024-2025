#ifndef PULSE_H_
#define PULSE_H_

#include "commandBase.h"
#include "custom/subsystem/motorSubsystem.h"

class Pulse : public CommandBase {
public:
    Pulse(MotorSubsystem* sub) { 
        subsystem = sub; 
        addRequirements(subsystem);
    }

    inline void execute() override {
        if (subsystem->getPosition() >= 150.0) {
            subsystem->backward();
        } else if (subsystem->getPosition() <= -150.0) {
            subsystem->forward();
        }
    }

    inline void end() override {
        subsystem->stop();
    }

    inline void interrupted() override {
        subsystem->stop();
    }

    inline bool isFinished() override {
        return false;
    }

    inline void periodic() override { subsystem->periodic(); }

    inline CommandBase* clone() const override {
        return new Pulse(*this);
    }

private:
    MotorSubsystem* subsystem;
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
