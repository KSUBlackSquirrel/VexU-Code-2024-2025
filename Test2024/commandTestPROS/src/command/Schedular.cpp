#include "command/Scheduler.h"

bool Scheduler::addCommand(Command command) {
    // for(Command i_command : m_commands) {
        // if(i_command.getName() == command.getName()) {
        //     return false;
        // }
    // }
    command.initialize();
    m_commands[m_commandCount++] = command;
    return true;
}

bool Scheduler::addCommand(InstantCommand command) {
    m_commands[m_commandCount++] = command;
    return true;
}

bool Scheduler::removeCommand(Command command) {
    m_commandCount--;
    return true;
}

bool Scheduler::removeCommand(InstantCommand command) {
    m_commandCount--;
    return true;
}

void Scheduler::run() {
    for(auto command : m_commands) {
        if(command.isFinished() || command.getInterrupted()) {
            command.end(command.getInterrupted());
            removeCommand(command);
        } else {
            try {
                command.getSubsystem().periodic();
                command.execute();
            } catch (const std::exception& e) {
                command.interrupt();
            }
        }
    }
}

// void Scheduler::printList() {
//     for(auto command : m_commands) {
//         globalControl::controller.clear();
//         int j=0;
//         for(int i=0; i<m_commands.size(); i++) {
//             globalControl::controller.print(i%2,j, "%f", m_commands[i].getName());
//             if(i%m_commands.size() == m_commands.size()/2) {
//                 j++;
//             }
//         }
//     }
// }