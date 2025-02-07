#ifndef SCHEDULER_H_
#define _SCHEDULER_H_

#include "command/Command.h"
#include "command/InstantCommand.h"
#include "Globals.h"


class Scheduler {
    public:
        Scheduler();

        bool addCommand(Command command);
        bool addCommand(InstantCommand command);
        bool removeCommand(Command command);
        bool removeCommand(InstantCommand command);
        void run();

        // void printList();

    private:
        int m_commandCount = 0;
        Command m_commands[20]; // Fixed size array
};


#endif