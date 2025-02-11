#ifndef DRIVE_SUBSYSTEM_H
#define DRIVE_SUBSYSTEM_H

#include "subsystem/Subsystem.h"

// 15 right motor id 12,13 | left drive motor id 19,20 | imu id 5 | wheel diameter NEW_325 | wheel track 11.625 | width 14 | length 14.55 | wheel rpm 400
// 24  motor id  |  drive motor id  | imu id  | wheel diameter NEW_325 | wheel track 13.625 | width 16 | length 18.235 | wheel rpm 400

class DriveSubsystem : public Subsystem {
    public:
        DriveSubsystem();

        lemlib::Pose pos();

        void autonomous();

        void periodic() override {};

        void tankDrive(pros::Controller& controller, bool inverted);

    private:
        lemlib::ExpoDriveCurve throttle_curve;
        lemlib::ExpoDriveCurve steer_curve;
        pros::MotorGroup left_motor_group;
        pros::MotorGroup right_motor_group;
        lemlib::Drivetrain drivetrain;
        pros::Imu imu;
        lemlib::OdomSensors sensors;
        lemlib::ControllerSettings lateral_controller;
        lemlib::ControllerSettings angular_controller;
        lemlib::Chassis chassis;
};

#endif