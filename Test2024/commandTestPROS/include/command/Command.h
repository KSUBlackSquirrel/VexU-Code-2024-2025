#ifndef COMMAND_H_
#define COMMAND_H_

#include "subsystem/Subsystem.h"
#include <string>

class Command {
    public:
        Command() {};
        Command(Subsystem subsystem) : m_subsystem(subsystem) {};

        // Called when the command is initially scheduled.
        void initialize() {};
        // Called every time the scheduler runs while the command is scheduled.
        void execute() {};
        // Called once the command ends or is interrupted.
        void end(bool interrupted) {};
        // Returns true when the command should end.
        bool isFinished() {return false;};

        void interrupt() {interrupted = true;};
        bool getInterrupted() {return interrupted;};
        // std::string getName() {return __func__ ;};

        Subsystem getSubsystem() {return m_subsystem;};

        Subsystem m_subsystem;
        
    protected:        
        
        bool interrupted = false;
};


#endif