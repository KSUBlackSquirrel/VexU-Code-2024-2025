#ifndef ARM_COMMAND_H
#define ARM_COMMAND_H

#include "command/Command.h"


class ArmCommand : public Command {
    protected:
        static ArmCommand* instance;

        // Protected constructor to enforce singleton
        ArmCommand(ArmSubsystem& subsystem) : Command(subsystem) {}

    public:
        // Singleton instance creation for ArmCommand
        static ArmCommand* createInstance(ArmSubsystem& subsystem) {
            if (!instance) {
                instance = new ArmCommand(subsystem);
            }
            return instance;
        }

        static void destroyInstance() {
            delete instance;
            instance = nullptr;
        }

        void initialize() override;
        void execute() override;
        void end(bool interrupted) override;
        bool isFinished() override;
};

// Initialize the static member
ArmCommand* ArmCommand::instance = nullptr;

#endif