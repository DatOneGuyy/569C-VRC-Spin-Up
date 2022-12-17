#include "main.h"
#include "okapi/api.hpp"
#include "auton/intake.hpp"

using namespace okapi;

void pressure(double time, double speed) {
	MotorGroup left({3, -11, -10});
	MotorGroup right({-1, 18, 4});
	Motor intake(-9);

	left.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
	right.setEncoderUnits(AbstractMotor::encoderUnits::degrees);

	left.moveVoltage(-speed * 120);
	right.moveVoltage(-speed * 120);

	for (int i = 0; i < time / 10; i++) {
		intake_voltage = -12000;
		pros::delay(10);
	}

	intake_voltage = 0;
	left.moveVoltage(0);
	right.moveVoltage(0);
}

void start_intake() {
	intake_voltage = 12000;
}

void stop_intake() {
	intake_voltage = 0;
}

void slow_intake() {
	intake_voltage = 8000;
}

void reverse_intake() {
	intake_voltage = -12000;
}

void intake_handler(void*) {
	Motor intake(-9);
	intake.setGearing(AbstractMotor::gearset::blue);
	intake_voltage = 0;
	speed = 20;

	bool past_change = false;

	while (true) {
		intake.moveVoltage(intake_voltage);
		if (fabs(intake.getActualVelocity()) < speed && fabs(intake_voltage) > 5000 && !changing)  {
			intake.moveVoltage(-12000);
			pros::delay(200);
			intake.moveVoltage(intake_voltage);
			pros::delay(500);
		}
		if (changing && !past_change) {
			pros::delay(700);
			changing = false;
		}
		pros::screen::print(pros::E_TEXT_SMALL, 0, "%f", intake.getActualVelocity());
		past_change = changing;
		pros::delay(5);
	}
}