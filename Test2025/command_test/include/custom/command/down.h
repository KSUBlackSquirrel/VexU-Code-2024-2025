#ifndef DOWN_H_
#define DOWN_H_

#include "commandBase.h"
#include "custom/subsystem/motorSubsystem.h"

class Down : public CommandBase {
public:
    Down(MotorSubsystem* sub) : CommandBase() { 
        subsystem = sub; 
        addRequirements(subsystem);
    }

    inline void execute() override {
        subsystem->backward();
    }

    inline void end() override {
        subsystem->stop();
    }

    inline void interrupted() override {
        subsystem->stop();
    }

    inline bool isFinished() override {
        return subsystem->getPosition() <= 0.0;
    }

    inline CommandBase* clone() const override {
        return new Down(*this);
    }

private:
    MotorSubsystem* subsystem;
};

#endif
