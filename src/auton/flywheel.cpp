#include "main.h"
#include "okapi/api.hpp"
#include "auton/flywheel.hpp"
#include "functions.hpp"

using namespace okapi;

void shoot(int count) {
	pros::ADIPort indexer('A', pros::E_ADI_DIGITAL_OUT);
	double shot_1, shot_2, shot_3;
	for (int i = 0; i < count; i++) {
		while (fabs(average_speed() - target_speed) > 0.2) {
			pros::delay(1);
		}
		indexer.set_value(true);
		
		pros::delay(200);
		indexer.set_value(false);
		pros::delay(100);
	}
}

void grapher(void*) {
	Motor flywheel(13);
	flywheel.setGearing(AbstractMotor::gearset::red);
	pros::Controller master (pros::E_CONTROLLER_MASTER);
	master.clear();

	int counter = 0;
	pros::screen::set_pen(COLOR_WHITE);

	double velocity = 0;
	double last_velocity = 0;
	double voltage = 0;
	double last_voltage = 0;
	double average_velocity = 0;
	double last_average_velocity = 0;

	pros::screen::set_pen(COLOR_BLACK);
	pros::screen::draw_rect(0, 0, 480, 240);

	pros::screen::set_pen(COLOR_DARK_BLUE);
	for (int i = 1; i < 10; i++) {
		pros::screen::draw_line(0, 240 - i * 24, 480, 240 - i * 24);
	}

	pros::screen::set_pen(COLOR_GREEN);
	pros::screen::draw_line(0, 240 - target_speed * 2.4, 480, 240 - target_speed * 2.4);
	
	while (true) {
		while (counter < 480) {
			velocity = flywheel.getActualVelocity();
			voltage = flywheel_voltage;
			average_velocity = average_speed();

			pros::screen::set_pen(COLOR_RED);
			pros::screen::draw_line(counter, 240.0 - velocity * 2.4, counter - 1, 240.0 - last_velocity * 2.4);
			pros::screen::set_pen(COLOR_BLUE);
			pros::screen::draw_line(counter, 240.0 - voltage / 50, counter - 1, 240 - last_voltage / 50);
			pros::screen::set_pen(COLOR_YELLOW);
			pros::screen::draw_line(counter, 240 - average_velocity * 2.4, counter - 1, 240 - last_average_velocity * 2.4);

			pros::delay(10);
			counter++;

			last_velocity = velocity;
			last_voltage = voltage;
			last_average_velocity = average_velocity;
		}
		counter = 0;

		pros::screen::set_eraser(COLOR_BLACK);
		pros::screen::erase();

		pros::screen::set_pen(COLOR_DARK_BLUE);
		for (int i = 1; i < 10; i++) {
			pros::screen::draw_line(0, 240 - i * 24, 480, 240 - i * 24);
		}

		pros::screen::set_pen(COLOR_GREEN);
		pros::screen::draw_line(0, 240 - target_speed * 2.4, 480, 240 - target_speed * 2.4);
		
	}
}

void flywheel_task(void*) {
	ControllerButton R2(ControllerDigital::R2);
	Motor flywheel(13);
	pros::Controller master (pros::E_CONTROLLER_MASTER);

	flywheel.setGearing(AbstractMotor::gearset::red);

	double speed = 0;
	double kp = 15;
	double kd = 20;

	double error = target_speed;
	double past_error = error;
	double voltage = target_speed * 120;
	double past_voltage = voltage;

	int counter = 0;

	while (!driving) {
		shift();
		speeds[smoothing - 1] = flywheel.getActualVelocity();

		error = target_speed - average_speed();

		voltage += fmin(50, (error > 20) ? (sqrt(error) * 100) : (kp * error) + (error - past_error) * kd);
		voltage = c(0, 12000, voltage);

		flywheel.moveVoltage(voltage);
		flywheel_speed = flywheel.getActualVelocity();

		if (counter % 50 == 0) {
			master.print(0, 0, "speed: %f", flywheel.getActualVelocity());
		}

		flywheel_voltage = voltage;
		past_error = error;
		past_voltage = voltage;
		
		pros::delay(2);
	}
}