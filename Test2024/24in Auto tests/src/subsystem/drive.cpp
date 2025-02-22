#include "drive.h"

// 15 right motor id 12,13 | left drive motor id 19,20 | imu id 5 | wheel diameter NEW_325 | wheel track 11.625 | width 14 | lenght 14.55 | wheel rpm 400
// 24  motor id  |  drive motor id  | imu id  | wheel diameter NEW_325 | wheel track 13.625 | width 16 | lenght 18.235 | wheel rpm 400

namespace drive{

// input curve for throttle and steer inputs during driver control
lemlib::ExpoDriveCurve throttle_curve(
    globalControl::joystickDeadband, // joystick deadband out of 127
    globalControl::joystickDeadband, // minimum output where drivetrain will move out of 127  
    globalControl::expoCurve // expo curve gain
);
lemlib::ExpoDriveCurve steer_curve(
    globalControl::joystickDeadband, // joystick deadband out of 127
    globalControl::joystickDeadband, // minimum output where drivetrain will move out of 127
    globalControl::expoCurve // expo curve gain
);

pros::MotorGroup left_motor_group(globalDrive::leftMotorsID, globalDrive::driveTrainColor);    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
pros::MotorGroup right_motor_group(globalDrive::rightMotorsID, globalDrive::driveTrainColor);  // Creates a motor group with forwards port 5 and reversed ports 4 & 6
lemlib::Drivetrain drivetrain(
    &left_motor_group, // left motor group
    &right_motor_group, // right motor group
    globalDrive::wheelTrack, // track width
    globalDrive::wheelDiameter, // wheel diameter
    globalDrive::wheelRPM, // wheel rpm
    globalDrive::horizontalDrift // horizontal drift is 2 (for now)
);

// imu
pros::Imu imu(globalDrive::imuID);
// horizontal tracking wheel encoder
// pros::Rotation horizontal_encoder(20);
// // vertical tracking wheel encoder
// pros::adi::Encoder vertical_encoder('C', 'D', true);
// // horizontal tracking wheel
// lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_275, -5.75);
// // vertical tracking wheel
// lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_275, -2.5);

// odometry settings
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);


// lateral PID controller
lemlib::ControllerSettings lateral_controller(
    18, // proportional gain (kP)
    0, // integral gain (kI)
    6, // derivative gain (kD)
    0, // anti windup
    0, // small error range, in inches
    00, // small error range timeout, in milliseconds
    0, // large error range, in inches
    00, // large error range timeout, in milliseconds
    0 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(
    4, // proportional gain (kP)
    0, // integral gain (kI)
    29, // derivative gain (kD)
    0, // anti windup
    0, // small error range, in degrees
    00, // small error range timeout, in milliseconds
    0, // large error range, in degrees
    00, // large error range timeout, in milliseconds
    0 // maximum acceleration (slew)
);

// create the chassis
lemlib::Chassis chassis(
    drivetrain, // drivetrain settings
    lateral_controller, // lateral PID settings
    angular_controller, // angular PID settings
    sensors, // odometry sensors
    &throttle_curve, 
    &steer_curve
);


void init() {
    chassis.calibrate(); // calibrate sensors
}

lemlib::Pose pos(){
    return chassis.getPose();
}

ASSET(BigBotStart_txt);
void autonomous(){
    // Tune Angular PID
	//while(true){
        // set position to x:0, y:0, heading:0
        //chassis.setPose(0, 0, 0);
        // turn to face heading 90 with a very long timeout
        //chassis.turnToHeading(90, 1000000);
        
    
	// Tune Linear PID     
	// set position to x:0, y:0, heading:0
	 chassis.setPose(0, 0, 0);
	// move 48" forwards
    intake::IntakeUp();
    chassis.follow(BigBotStart_txt, 6, 20000);
    convayor::IntakeUp();
    pros::delay(400);


	// set chassis pose
    //chassis.setPose(-39, 39, 180);
    // lookahead distance: 15 inches
	// If you want the robot to follow the path more closely, decrease the lookahead distance
	// If you want the robot to follow the path more loosely, but faster, then increase the lookahead distance
    // timeout: 2000 ms
    //chassis.follow(path_txt, 6, 20000);
    // follow the next path, but with the robot going backwards
    // chassis.follow(example2_txt, 15, 2000, false);
    //}
}

void tankDrive(pros::Controller& controller, bool inverted){
    // move the robot
    chassis.tank(
        inverted ? -controller.get_analog(globalDrive::rightStickY) : controller.get_analog(globalDrive::leftStickY),
        inverted ?  -controller.get_analog(globalDrive::leftStickY) : controller.get_analog(globalDrive::rightStickY));
}






} //namespace drive