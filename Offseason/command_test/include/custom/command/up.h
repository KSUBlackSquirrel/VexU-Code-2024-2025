#ifndef UP_H_
#define UP_H_

#include "commandBase.h"
#include "custom/subsystem/motorSubsystem.h"

class Up : public CommandBase {
public:
    Up(MotorSubsystem* sub) { 
        subsystem = sub; 
        addRequirements(subsystem);
    }

    inline void execute() override {
        subsystem->forward();
    }

    inline void end() override {
        subsystem->stop();
    }

    inline void interrupted() override {
        printf("up stopped\n");
        subsystem->stop();
    }

    inline bool isFinished() override {
        return subsystem->getPosition() >= 150.0;
    }

    inline CommandBase* clone() const override {
        return new Up(*this);
    }

private:
    MotorSubsystem* subsystem;
};

#endif
