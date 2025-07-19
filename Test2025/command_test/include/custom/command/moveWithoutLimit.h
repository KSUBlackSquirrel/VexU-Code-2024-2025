#ifndef MOVEWITHOUTLIMIT_H_
#define MOVEWITHOUTLIMIT_H_

#include "commandBase.h"
#include "custom/subsystem/motorSubsystem.h"

class MoveWithoutLimit : public CommandBase {
public:
    MoveWithoutLimit(MotorSubsystem* sub, bool fwd) : dir(fwd) { 
        subsystem = sub; 
        addRequirements(subsystem);
    }

    inline void execute() override {
        if(dir) {
            subsystem->forward();
        } else {
            subsystem->backward();
        }
    }

    inline void end() override {
        subsystem->stop();
    }

    inline void interrupted() override {
        printf("MoveWithoutLimit stopped\n");
        subsystem->stop();
    }

    inline bool isFinished() override {
        return false;
    }

    inline CommandBase* clone() const override {
        return new MoveWithoutLimit(*this);
    }

private:
    MotorSubsystem* subsystem;
    bool dir;
};

#endif
