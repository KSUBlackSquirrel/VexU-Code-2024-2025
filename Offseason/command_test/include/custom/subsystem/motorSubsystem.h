#ifndef MOTORSUBSYSTEM_H_
#define MOTORSUBSYSTEM_H_

#include "custom/subsystem/subsystemBase.h"

class MotorSubsystem : public SubsystemBase {
public:
    inline MotorSubsystem() : motor(GlobalMotor::motorId, GlobalMotor::motorColor) {
        motor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    }

    inline void forward() {
        motor.move_velocity(MotorTools::percentToVelocity(30, GlobalMotor::motorColor));
    }

    inline void backward() {
        motor.move_velocity(-MotorTools::percentToVelocity(30, GlobalMotor::motorColor));
    }

    inline void stop() {
        motor.brake();
    }

    inline double getPosition() {
        return motor.get_position();
    }

    inline void periodic() override { }

private:
    pros::Motor motor;
};

#endif
