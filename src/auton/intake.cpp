#include "main.h"
#include "okapi/api.hpp"
#include "auton/intake.hpp"

using namespace okapi;

void pressure(double time, double speed) {
	MotorGroup left({-3, -11, -12});
	MotorGroup right({10, 18, 19});
	Motor intake(-9);

	left.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
	right.setEncoderUnits(AbstractMotor::encoderUnits::degrees);

	left.moveVoltage(-speed * 120);
	right.moveVoltage(-speed * 120);

	for (int i = 0; i < time / 10; i++) {
		intake.moveVoltage(-12000);
		pros::delay(10);
	}

	intake.moveVoltage(0);
	left.moveVoltage(0);
	right.moveVoltage(0);
}

void toggle_intake(bool reverse) {
	Motor intake(-9);
	bool intake_active = false;

	if (intake.getActualVelocity() > 3) {
		intake_active = true;
	} else {
		intake_active = false;
	}

	if (intake_active) {
		intake_active = false;
		intake.moveVoltage(0);
	} else {
		intake_active = true;
		intake.moveVoltage(reverse ? -12000 : 12000);
	}
}

void start_intake() {
	Motor intake(-9);
	intake.moveVoltage(12000);
}

void stop_intake() {
	Motor intake(-9);
	intake.moveVoltage(0);
}

void slow_intake() {
	Motor intake(-9);
	intake.moveVoltage(8000);
}

void reverse_intake() {
	Motor intake(-9);
	intake.moveVoltage(-12000);
}