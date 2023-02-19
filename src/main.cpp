#include "main.h"
#include "okapi/api.hpp"
#include "pros/screen.h"

using namespace okapi;

bool driving;

double flywheel_speed;
double target_speed;
double flywheel_voltage;

int smoothing = 10;
double speeds[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

double angle_error = 0;
bool last_turn_direction;

double intake_voltage;
bool changing = false;
double speed = 20;

bool r = true;
bool l = false;

bool selected;
int program;

bool flywheel_idle;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize(void) {
	pros::Task run_intake_handler(intake_handler);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled(void) {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize(void) {}

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
void autonomous(void) {
	program = 4; 

	bool driving = false;

	//clear_screen();

	pros::Task flywheel_auton(flywheel_task);
	//pros::Task grapher_task(grapher);

	if (program == 0 || program == 1) {
		right_auton();
	} else if (program == 2 || program == 3) {
		left_auton();
	} else if (program == 4) {
		skills();
	} else if (program == 5 || program == 6) {
		//run bozo code here
	} else if (program == 7) {
		flywheel_test();
	}
	flywheel_auton.suspend();
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
void opcontrol(void) {
	driving = true;
	pros::Task grapher_task(grapher);
	pros::Task run_indexer(indexer_task);
	pros::Task run_intake(intake_task);
	pros::Task run_catapults(catapults_task);
	pros::Task run_drive(drive_task);
	pros::Task run_angle_changer(angle_changer_task);

	driving = true;
}
