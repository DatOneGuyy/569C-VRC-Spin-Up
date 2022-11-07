#include "main.h"
#include "okapi/api.hpp"
#include "auton/flywheel.hpp"

using namespace okapi;

void shoot(int count) {
	pros::ADIPort indexer('A', pros::E_ADI_DIGITAL_OUT);
	double shot_1, shot_2, shot_3;
	for (int i = 0; i < count; i++) {
		while (fabs(flywheel_speed - target_speed) > 0.3) {
			pros::delay(1);
			pros::screen::print(pros::E_TEXT_MEDIUM_CENTER, 4, "flywheel error: %f", abs(flywheel_speed - target_speed));
		}
		indexer.set_value(true);
		pros::screen::print(pros::E_TEXT_MEDIUM_CENTER, 5 + i, "shot: %f", abs(flywheel_speed));

		pros::delay(200);
		indexer.set_value(false);
		pros::delay(400);
	}
}

void flywheel_task(void*) {
	ControllerButton R2(ControllerDigital::R2);
	Motor flywheel(13);

	flywheel.setGearing(AbstractMotor::gearset::red);

	double target = target_speed;
	double speed = 0;
	double kp = 5;
	double error = target;
	double voltage = target * 120;

	while (true && !driving) {
		target = target_speed;
		error = target - flywheel.getActualVelocity();
		pros::screen::print(pros::E_TEXT_MEDIUM_CENTER, 0, "error: %f, speed: %f, voltage: %f", error, flywheel.getActualVelocity(), voltage);
		voltage += kp * error;
		voltage = c(0, 12000, voltage);
		flywheel.moveVoltage(voltage);
		flywheel_speed = flywheel.getActualVelocity();
		pros::screen::print(pros::E_TEXT_MEDIUM_CENTER, 3, "speed: %f, voltage: %f", flywheel.getActualVelocity(), voltage);
		pros::delay(5);
	}
}