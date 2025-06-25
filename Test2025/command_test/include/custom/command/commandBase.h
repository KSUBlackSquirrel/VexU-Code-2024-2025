#ifndef COMMANDBASE_H_
#define COMMANDBASE_H_

#include "custom/globals.h"

class CommandBase {
public:
    CommandBase() {}

    virtual void execute() = 0;
    virtual void end() = 0;
    virtual bool isFinished() = 0;

    virtual void periodic() {}

    virtual CommandBase* clone() const = 0;
};

#endif
