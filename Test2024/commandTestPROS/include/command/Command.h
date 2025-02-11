#ifndef COMMAND_H
#define COMMAND_H

#include "main.h"
#include "lemlib/api.hpp"
#include "globals.h"

class Command {
    protected:
        static Command* instance;
        bool interrupted;
        Subsystem m_subsystem;

        // Protected constructor to enforce singleton
        Command(Subsystem& subsystem) : m_subsystem(subsystem), interrupted(false) {}

    public:
        // Singleton instance creation
        static Command* newCommand(Subsystem& subsystem) {
            if (!instance) {
                instance = new Command(subsystem);
            }
            return instance;
        }

        static void destroyInstance() {
            delete instance;
            instance = nullptr;
        }

        // Command lifecycle methods
        virtual void initialize() {}
        virtual void execute() {}
        virtual void end(bool interrupted) {}
        virtual bool isFinished() {return false;}

        void interrupt() {interrupted = true;}
        bool getInterrupted() const {return interrupted;}

        Subsystem getSubsystem() const {return m_subsystem;}
};

// Initialize the static member
Command* Command::instance = nullptr;

#endif