#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include "main.h"
#include <array>
#include <typeinfo>
#include <vector>

namespace scheduler {

class ButtonBinder;
class JoystickBinder;

class Controller : public pros::Controller {
public:
    Controller(pros::controller_id_e_t id, std::vector<std::unique_ptr<CommandBase>>* sch)
        : pros::Controller(id), scheduler(sch) {
        prevButtonStates.fill(false);
    }

    inline void addCommand(const CommandBase* cmd) { 
        for (const auto& existing : *scheduler) {
            if (typeid(*existing) == typeid(*cmd)) {
                return;
            }
        }
        scheduler->push_back(std::unique_ptr<CommandBase>(cmd->clone())); 
    }

    inline ButtonBinder setButtonCommand();

    inline JoystickBinder setJoystickCommand();

    inline void poll();

    std::array<bool, 12> prevButtonStates;
    std::vector<ButtonBinder> buttonBinders;
    std::vector<JoystickBinder> joystickBinders;

private:
    std::vector<std::unique_ptr<CommandBase>>* scheduler;
};

class ButtonBinder {
public:
    enum class Edge { None, Rising, Falling };
    ButtonBinder(Controller* ctrl) : controller(ctrl), edge(Edge::None) {}

    ButtonBinder& onTrue(pros::controller_digital_e_t btn, const CommandBase* cmd) {
        button = btn;
        command = cmd;
        edge = Edge::Rising;
        controller->buttonBinders.emplace_back(*this);
        return controller->buttonBinders.back();
    }
    ButtonBinder& onFalse(pros::controller_digital_e_t btn, const CommandBase* cmd) {
        button = btn;
        command = cmd;
        edge = Edge::Falling;
        controller->buttonBinders.emplace_back(*this);
        return controller->buttonBinders.back();
    }

    void poll() {
        if (edge == Edge::Rising)  { bool curr = controller->get_digital_new_press(button);    if (curr) controller->addCommand(command); }
        if (edge == Edge::Falling) { bool curr = controller->get_digital_new_release(button);  if (curr) controller->addCommand(command); }
    }

private:
    Controller* controller;
    pros::controller_digital_e_t button;
    const CommandBase* command;
    Edge edge;
};

class JoystickBinder {
public:
    enum class Edge { None, Rising, Falling };
    JoystickBinder(Controller* ctrl) : controller(ctrl), edge(Edge::None), prev(false) {}

    JoystickBinder& onTrue(pros::controller_analog_e_t stick, int threshold, const CommandBase* cmd) {
        this->stick = stick;
        this->threshold = threshold;
        this->command = cmd;
        edge = Edge::Rising;
        controller->joystickBinders.emplace_back(*this);
        return controller->joystickBinders.back();
    }
    JoystickBinder& onFalse(pros::controller_analog_e_t stick, int threshold, const CommandBase* cmd) {
        this->stick = stick;
        this->threshold = threshold;
        this->command = cmd;
        edge = Edge::Falling;
        controller->joystickBinders.emplace_back(*this);
        return controller->joystickBinders.back();
    }

    void poll() {
        int curr = controller->get_analog(stick);
        bool above = (threshold >= 0) ? (curr >= threshold) : (curr <= threshold);
        if (edge == Edge::Rising && above && !prev) controller->addCommand(command);
        if (edge == Edge::Falling && !above && prev) controller->addCommand(command);
        prev = above;
    }

private:
    Controller* controller;
    pros::controller_analog_e_t stick;
    int threshold;
    const CommandBase* command;
    bool prev;
    Edge edge;
};

inline ButtonBinder Controller::setButtonCommand() {
    return ButtonBinder(this);
}

inline JoystickBinder Controller::setJoystickCommand() {
    return JoystickBinder(this);
}

inline void Controller::poll() {
    for (auto& binder : buttonBinders) {
        binder.poll();
    }
    for (auto& binder : joystickBinders) {
        binder.poll();
    }
}

} // namespace scheduler

#endif
