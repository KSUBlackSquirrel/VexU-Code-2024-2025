#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep


pros::Controller controller(pros::E_CONTROLLER_MASTER);


void configureBindings() {
	// clamp controls
	if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
		clamp::toggle();
	}

	// if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){
	// 	conveyor::command(conveyor::RUNNING);
	// 	intake::command(intake::RUNNING);
	// }
	// if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
	// 	conveyor::command(conveyor::INVERTED);
	// 	intake::command(intake::INVERTED);
	// }
	// if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
	// 	conveyor::command(conveyor::STOP);
	// 	intake::command(intake::STOP);
	// }

	if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
		conveyor::command(conveyor::INVERTED);
	}else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
		conveyor::command(conveyor::RUNNING);
	} else {
		conveyor::command(conveyor::STOP);
	}
	
	if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
		intake::command(intake::INVERTED);
	} else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
		intake::command(intake::RUNNING);
	} else {
		intake::command(intake::STOP);
	}

	if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
		arm::command(arm::FORWARD);
	} else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
		arm::command(arm::BACKWARD);
	} else {
		arm::command(arm::STOP);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {	
	drive::init();
	clamp::init();
	intake::init();
	arm::init();
	conveyor::init();
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
 */// ASSET(example2_txt)
void autonomous() {
	drive::autonomous();
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
	pros::Task drive_task([&]() {
		while (true) {
			// drive the robot
			drive::tankDrive(controller, false/*controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)==1*/);
			// delay to save resources
			pros::delay(20);
		}
    });
	pros::Task button_task([&]() {
		while (true) {
			// listen for defined buttons pressed
			configureBindings();
			// delay to save resources
			pros::delay(20);
		}
    });
	pros::Task running_task([&]() {
		while (true) {
			conveyor::running();
			intake::running();
			arm::running();
			pros::delay(20);
		}
    });
}