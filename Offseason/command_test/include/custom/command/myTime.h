#ifndef MYTIME_H_
#define MYTIME_H_

#include "commandBase.h"
#include "custom/subsystem/controllerScreenSubsystem.h"

class MyTime : public CommandBase {
public:
    MyTime(ControllerScreenSubsystem* sub) { 
        subsystem = sub; 
        addUsedSubsystem(subsystem);  // Changed from addRequirements to addUsedSubsystem
    }

    inline void execute() override {
        subsystem->tick();
    }

    inline void end() override {}

    inline bool isFinished() override {
        return true;
    }

    inline CommandBase* clone() const override {
        return new MyTime(*this);
    }

private:
    ControllerScreenSubsystem* subsystem;
};

#endif
