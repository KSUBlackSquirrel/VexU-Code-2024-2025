#include "Scheduler.h"

void Scheduler::add(Command* obj) {
    // Check if the instance already exists in the list
    for (auto command : schedulerList) {
        if (command == obj) {
            return;  // Prevent duplicate entry
        }
    }
    schedulerList.push_back(obj);
}

void Scheduler::run() {
    if (!schedulerList.empty()) {
        auto it = schedulerList.begin();  // Use iterator-based loop
        while (it != schedulerList.end()) {
            Command* command = *it;
            if (command->isFinished() || command->getInterrupted()) {
                command->end(command->getInterrupted());
                it = schedulerList.erase(it);  // Safely remove and advance the iterator
            } else {
                try {
                    command->execute();
                } catch (const std::exception& e) {
                    command->interrupt();
                }
                ++it;
            }
        }
    }
}
