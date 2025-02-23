#include "drive.h"

// 15 right motor id 12,13 | left drive motor id 19,20 | imu id 5 | wheel diameter NEW_325 | wheel track 11.625 | width 14 | length 14.55 | wheel rpm 400
// 24  motor id  |  drive motor id  | imu id  | wheel diameter NEW_325 | wheel track 13.625 | width 16 | length 18.235 | wheel rpm 400

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
    9, // proportional gain (kP)
    0, // integral gain (kI)
    6, // derivative gain (kD)
    0, // anti windup
    1, // small error range, in inches
    100, // small error range timeout, in milliseconds
    3, // large error range, in inches
    500, // large error range timeout, in milliseconds
    0 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(
    5, // proportional gain (kP)
    0, // integral gain (kI)
    54, // derivative gain (kD)
    0, // anti windup
    1, // small error range, in degrees
    100, // small error range timeout, in milliseconds
    3, // large error range, in degrees
    500, // large error range timeout, in milliseconds
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
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.calibrate(); // calibrate sensors
}

lemlib::Pose pos(){
    return chassis.getPose();
}

// ASSET(sPath_txt);
// ASSET(forward1_txt);
// ASSET(quartCir1_txt);
// ASSET(quartCir2_txt);


// void s_loop(){

// 	// set chassis pose
//     chassis.setPose(-36, 36, 180);
//     // lookahead distance: 15 inches
// 	// If you want the robot to follow the path more closely, decrease the lookahead distance
// 	// If you want the robot to follow the path more loosely, but faster, then increase the lookahead distance
//     // timeout: 2000 ms

//     chassis.follow(sPath_txt, 6, 20000);
    
//     chassis.turnToHeading(180, 1000);

//     pros::delay(1000);

//     chassis.setPose(0, 0, 0);
//     chassis.turnToHeading(180, 1000);

//     pros::delay(1000);

//     chassis.setPose(-36, 36, 180);
//     chassis.follow(sPath_txt, 6, 20000);
//     chassis.turnToHeading(180, 2000);
// }

// void quartCir1(){

// 	// set chassis pose
//     chassis.setPose(0, 0, 0);
//     // lookahead distance: 15 inches
// 	// If you want the robot to follow the path more closely, decrease the lookahead distance
// 	// If you want the robot to follow the path more loosely, but faster, then increase the lookahead distance
//     // timeout: 2000 ms

//     chassis.follow(quartCir1_txt, 6, 20000, true);
//     clamp::toggle();
//     chassis.follow(quartCir2_txt, 6, 20000, false);
// }
// ;

// void idea1(){

// 	// set chassis pose
//     chassis.setPose(-64, 36, 0);
//     // lookahead distance: 15 inches
// 	// If you want the robot to follow the path more closely, decrease the lookahead distance
// 	// If you want the robot to follow the path more loosely, but faster, then increase the lookahead distance
//     // timeout: 2000 ms

//     chassis.follow(quartCir1_txt, 6, 20000, true);
//     chassis.follow(quartCir2_txt, 6, 20000, false);
//     chassis.follow(quartCir1_txt, 6, 20000, true);
// }

void AngularPID() {
    // Tune Angular PID
    // set position to x:0, y:0, heading:0
    // chassis.setPose(0, 0, 0);
    // turn to face heading 90 with a very long timeout
    // chassis.turnToHeading(90, 1000000);
    
    //*******for easy standard, set all paths to start at possition 0,0 with heading 0, and rotate path acordingly */
    
    // chassis.setPose(0, 0, 0);
    // chassis.follow(forward1_txt, 6, 20000, true);
    // pros::delay(1000);
    // chassis.setPose(0, 0, 180);
    
    // //chassis.turnToHeading(180, 1000);
    
    // pros::delay(1000);
    
    // chassis.follow(forward1_txt, 6, 20000, false);
}

// void LinearPID() {
    // Tune Linear PID     
    // set position to x:0, y:0, heading:0s
    // chassis.setPose(0, 0, 0);
    // move 48" forwards
    // chassis.moveToPoint(0, 48, 100000);
// }

ASSET(path1_txt);
ASSET(path2_txt);
ASSET(path3_txt);
ASSET(PushBackGoal_txt);
ASSET(path3Backwards_txt);

void autonomous(){
    chassis.setPose(-55, 30, 270);
    chassis.follow(path1_txt, 6, 2000, false);
    pros::delay(1500);
    clamp::toggle();
    pros::delay(500);
    conveyor::conveyorUp(550);
    intake::intakeUp(600);
    pros::delay(750);
    chassis.follow(path2_txt, 6, 2500, true);
    pros::delay(3200);
    conveyor::conveyorStop();
    chassis.turnToHeading(135, 1000);
    pros::delay(1000);
    clamp::toggle();
    chassis.follow(PushBackGoal_txt, 6, 900, false);

    pros::delay(900);

    //after corner
    chassis.moveToPose(chassis.getPose().x + 3, chassis.getPose().y - 3, chassis.getPose().theta, 3000);
    chassis.turnToHeading(135, 1000);
    chassis.moveToPose(-48, 48, 135, 3000);
    chassis.turnToHeading(90, 1000);
    chassis.moveToPose(20, 48, 90, 3000);
    chassis.turnToHeading(0, 1000);
    chassis.follow(path3Backwards_txt, 6, 2500, false);
    pros::delay(1000);
    clamp::toggle();
    pros::delay(1000);
    conveyor::conveyorUp(550);
    intake::intakeUp(600);


    // pros::delay(500);
    //chassis.follow(path3_txt, 6, 4000, true);
    //pros::delay(6000);




}

void tankDrive(pros::Controller& controller, bool inverted){
    // move the robot
    chassis.tank(
        inverted ? -controller.get_analog(globalDrive::rightStickY) : controller.get_analog(globalDrive::leftStickY),
        inverted ?  -controller.get_analog(globalDrive::leftStickY) : controller.get_analog(globalDrive::rightStickY));
}


} //namespace drive
