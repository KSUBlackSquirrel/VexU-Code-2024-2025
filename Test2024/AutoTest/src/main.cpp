#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep

// 15 right motor id 12,13 | left drive motor id 19,20 | imu id 5 | wheel diameter NEW_325 | wheel track 11.625 | width 14 | lenght 14.55 | wheel rpm 400
// 24  motor id  |  drive motor id  | imu id  | wheel diameter NEW_325 | wheel track 13.625 | width 16 | lenght 18.235 | wheel rpm 400


pros::Controller controller(pros::E_CONTROLLER_MASTER);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttle_curve(
	1, // joystick deadband out of 127
	3, // minimum output where drivetrain will move out of 127
	1.0 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(
	1, // joystick deadband out of 127
	3, // minimum output where drivetrain will move out of 127
	1.0 // expo curve gain
);

pros::MotorGroup left_motor_group({-19,-20}, pros::MotorGearset::green);    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
pros::MotorGroup right_motor_group({12,13}, pros::MotorGearset::green);  // Creates a motor group with forwards port 5 and reversed ports 4 & 6
auto wheel_diameter = lemlib::Omniwheel::NEW_325;
int wheel_track = 11.625;
lemlib::Drivetrain drivetrain(
	&left_motor_group, // left motor group
	&right_motor_group, // right motor group
	wheel_track, // track width
	wheel_diameter, // wheel diameter
	400, // wheel rpm
	2 // horizontal drift is 2 (for now)
);

// imu
pros::Imu imu(5);
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
	45, // derivative gain (kD)
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

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
	chassis.calibrate(); // calibrate sensors

	// print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // delay to save resources
            pros::delay(20);
        }
    });

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
ASSET(path_txt);
// ASSET(example2_txt)
void autonomous() {
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

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	while (true) {
		// get left y and right y positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

        // move the robot
        chassis.tank(leftY, rightY);

        // delay to save resources
        pros::delay(25);
	}
}