#ifndef COMMANDBASE_H_
#define COMMANDBASE_H_

#include "custom/globals.h"
#include <vector>

class SubsystemBase;

class CommandBase {
public:
    CommandBase() {}

    virtual void execute() = 0;
    virtual void end() = 0;
    virtual bool isFinished() = 0;
    virtual void interrupted() {}

    virtual void periodic() {}

    virtual CommandBase* clone() const = 0;
    
    // Add a subsystem requirement - this will interrupt any commands using the same subsystem
    inline void addRequirements(SubsystemBase* subsystem) {
        if (subsystem != nullptr) {
            requiredSubsystems.push_back(subsystem);
        }
    }
    
    // Get all required subsystems - non-virtual to prevent overriding
    inline const std::vector<SubsystemBase*>& getRequiredSubsystems() const {
        return requiredSubsystems;
    }

private:
    std::vector<SubsystemBase*> requiredSubsystems;
};

#endif
