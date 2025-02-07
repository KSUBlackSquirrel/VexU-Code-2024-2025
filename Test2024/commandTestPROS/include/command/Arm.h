#ifndef ARM_COMMAND_H_
#define ARM_COMMAND_H_

#include "command/Command.h"
#include "subsystem/Arm.h"

class ArmCommand : public Command {
    public:
        ArmCommand(ArmSubsystem subsystem) : Command(), m_subsystem(subsystem) {};

        void initialize();
        void execute();
        void end(bool interrupted);
        bool isFinished();

        ArmSubsystem m_subsystem;
};


#endif