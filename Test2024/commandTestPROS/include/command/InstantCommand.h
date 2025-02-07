#ifndef INSTANT_COMMAND_H_
#define INSTANT_COMMAND_H_

#include "command/Command.h"
#include "subsystem/Subsystem.h"
#include <functional>


class InstantCommand : public Command {
    public:
        InstantCommand(std::function<void()> m_func) : Command(), m_func(m_func) {};

        void execute() {m_func(); m_hasRun = true;};
        bool isFinished() {return m_hasRun;};


    private:
        std::function<void()> m_func;
        bool m_hasRun = false;
};


#endif