#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "main.h"
#include "command/Command.h"


class Scheduler {
    public:
        Scheduler() {};

        // adds a subsystem to the scheduler to run periodic and runs the command until it is finished or interupted
        void add(Command* obj);
        // clears the scheduler list without running the end method
        void clear() {schedulerList.clear();};
        
        void run();

    private:
        std::vector<Command*> schedulerList;
};

#endif