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

    inline ButtonBinder& setButtonCommand(pros::controller_digital_e_t button, const CommandBase* cmd);

    inline JoystickBinder& setJoystickCommand(pros::controller_analog_e_t stick, int threshold, const CommandBase* cmd);

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
    ButtonBinder(Controller* ctrl, pros::controller_digital_e_t btn, const CommandBase* cmd)
        : controller(ctrl), button(btn), command(cmd), edge(Edge::None) {}

    ButtonBinder& onTrue()    { edge = Edge::Rising;  return *this; }
    ButtonBinder& onFalse()   { edge = Edge::Falling; return *this; }

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
    JoystickBinder(Controller* ctrl, pros::controller_analog_e_t stick, int threshold, const CommandBase* cmd)
        : controller(ctrl), stick(stick), threshold(threshold), command(cmd), prev(false), edge(Edge::None) {}

    JoystickBinder& onTrue()  { edge = Edge::Rising;  return *this; }
    JoystickBinder& onFalse() { edge = Edge::Falling; return *this; }

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

inline ButtonBinder& Controller::setButtonCommand(pros::controller_digital_e_t button, const CommandBase* cmd) {
    buttonBinders.emplace_back(this, button, cmd);
    return buttonBinders.back();
}

inline JoystickBinder& Controller::setJoystickCommand(pros::controller_analog_e_t stick, int threshold, const CommandBase* cmd) {
    joystickBinders.emplace_back(this, stick, threshold, cmd);
    return joystickBinders.back();
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
