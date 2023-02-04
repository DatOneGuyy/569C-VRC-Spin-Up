#include "main.h"
#include "okapi/api.hpp"
#include "auton/intake.hpp"

using namespace okapi;

void pressure(double time, double speed, double pressure_time) {
	MotorGroup left({3, -11, -10});
	MotorGroup right({-2, 18, 4});
	Motor intake(-9);

	left.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
	right.setEncoderUnits(AbstractMotor::encoderUnits::degrees);

	left.setBrakeMode(AbstractMotor::brakeMode::coast);
	right.setBrakeMode(AbstractMotor::brakeMode::coast);

	for (int i = 0; i < time / 10; i++) {
		left.moveVoltage(-speed * 120);
		right.moveVoltage(-speed * 120);
		pros::delay(10);
	}

	for (int i = 0; i < pressure_time / 10; i++) {
		intake_voltage = -12000;
		pros::delay(10);
	}
	
	left.moveVoltage(0);
	right.moveVoltage(0);
	intake_voltage = 0;
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
	ControllerButton R2(ControllerDigital::R2);
	intake.setGearing(AbstractMotor::gearset::blue);
	intake_voltage = 0;
	speed = 2;

	bool past_change = false;

	while (true) {
		if (!R2.isPressed()) {
			intake.moveVoltage(intake_voltage);
			if (fabs(intake.getActualVelocity()) < speed && fabs(intake_voltage) > 5000 && !changing)  {
				intake.moveVoltage(-12000);
				pros::delay(200);
				intake.moveVoltage(intake_voltage);
				pros::delay(500);
			}
		} else {
			intake.moveVoltage(-12000);
		}
		if (changing && !past_change) {
			pros::delay(700);
			changing = false;
		}
		past_change = changing;
		pros::delay(5);
	}
}