#ifndef INSTANTCOMMAND_H_
#define INSTANTCOMMAND_H_

#include "commandBase.h"
#include <functional>

class InstantCommand : public CommandBase  {
public:
    InstantCommand(std::function<void()> func) : action(func) {}

    inline void execute() override { if (action) action(); }

    inline bool isFinished() override { return true; }

    inline void end() override {}

    inline CommandBase* clone() const override { return new InstantCommand(action); }

private:
    std::function<void()> action;
};

#endif
