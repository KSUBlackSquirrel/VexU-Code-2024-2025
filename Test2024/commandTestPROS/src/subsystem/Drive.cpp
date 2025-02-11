#include "drive.h"


DriveSubsystem::DriveSubsystem() :
    // input curve for throttle and steer inputs during driver control
    throttle_curve(
        globalControl::joystickDeadband, // joystick deadband out of 127
        globalControl::joystickDeadband, // minimum output where drivetrain will move out of 127
        globalControl::expoCurve // expo curve gain
    ),
    steer_curve(
        globalControl::joystickDeadband, // joystick deadband out of 127
        globalControl::joystickDeadband, // minimum output where drivetrain will move out of 127
        globalControl::expoCurve // expo curve gain
    ),

    left_motor_group(globalDrive::leftMotorsID, globalDrive::driveTrainColor),    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
    right_motor_group(globalDrive::rightMotorsID, globalDrive::driveTrainColor),  // Creates a motor group with forwards port 5 and reversed ports 4 & 6
    drivetrain(
        &left_motor_group, // left motor group
        &right_motor_group, // right motor group
        globalDrive::wheelTrack, // track width
        globalDrive::wheelDiameter, // wheel diameter
        globalDrive::wheelRPM, // wheel rpm
        globalDrive::horizontalDrift // horizontal drift is 2 (for now)
    ),

    // imu
    imu(globalDrive::imuID),
    // horizontal tracking wheel encoder
    // pros::Rotation horizontal_encoder(20);
    // // vertical tracking wheel encoder
    // pros::adi::Encoder vertical_encoder('C', 'D', true);
    // // horizontal tracking wheel
    // lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_275, -5.75);
    // // vertical tracking wheel
    // lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_275, -2.5);

    // odometry settings
    sensors(nullptr, // vertical tracking wheel 1, set to null
                                nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                                nullptr, // horizontal tracking wheel 1
                                nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                                &imu // inertial sensor
    ),


    // lateral PID controller
    lateral_controller(
        9, // proportional gain (kP)
        0, // integral gain (kI)
        6, // derivative gain (kD)
        0, // anti windup
        1, // small error range, in inches
        100, // small error range timeout, in milliseconds
        3, // large error range, in inches
        500, // large error range timeout, in milliseconds
        0 // maximum acceleration (slew)
    ),

    // angular PID controller
    angular_controller(
        5, // proportional gain (kP)
        0, // integral gain (kI)
        45, // derivative gain (kD)
        0, // anti windup
        1, // small error range, in degrees
        100, // small error range timeout, in milliseconds
        3, // large error range, in degrees
        500, // large error range timeout, in milliseconds
        0 // maximum acceleration (slew)
    ),

    // create the chassis
    chassis(
        drivetrain, // drivetrain settings
        lateral_controller, // lateral PID settings
        angular_controller, // angular PID settings
        sensors, // odometry sensors
        &throttle_curve, 
        &steer_curve
    ) {

    
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.calibrate(); // calibrate sensors
}

lemlib::Pose DriveSubsystem::pos() {
    return chassis.getPose();
}

ASSET(path_txt);
void DriveSubsystem::autonomous() {
    // Tune Angular PID
	// set position to x:0, y:0, heading:0
	// chassis.setPose(0, 0, 0);
	// turn to face heading 90 with a very long timeout
	// chassis.turnToHeading(90, 1000000);

	// Tune Linear PID     
	// set position to x:0, y:0, heading:0
	// chassis.setPose(0, 0, 0);
	// move 48" forwards
	// chassis.moveToPoint(0, 48, 100000);

	// set chassis pose
    chassis.setPose(-39, 39, 180);
    // lookahead distance: 15 inches
	// If you want the robot to follow the path more closely, decrease the lookahead distance
	// If you want the robot to follow the path more loosely, but faster, then increase the lookahead distance
    // timeout: 2000 ms
    chassis.follow(path_txt, 6, 20000);
    // follow the next path, but with the robot going backwards
    // chassis.follow(example2_txt, 15, 2000, false);
}

void DriveSubsystem::tankDrive(pros::Controller& controller, bool inverted){
    // move the robot
    chassis.tank(
        inverted ? -controller.get_analog(globalDrive::rightStickY) : controller.get_analog(globalDrive::leftStickY),
        inverted ?  -controller.get_analog(globalDrive::leftStickY) : controller.get_analog(globalDrive::rightStickY));
}
