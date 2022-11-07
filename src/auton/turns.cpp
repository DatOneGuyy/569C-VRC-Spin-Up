#include "main.h"
#include "okapi/api.hpp"
#include "auton/turns.hpp"
#include "functions.hpp"

using namespace okapi;

void turn_right(double angle, double slew_rate, double threshold, double timeout) {
	MotorGroup left({-3, -11, -12});
	MotorGroup right({10, 18, 19});

	left.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
	right.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
	left.setBrakeMode(AbstractMotor::brakeMode::hold);
	right.setBrakeMode(AbstractMotor::brakeMode::hold);
	left.tarePosition();
	right.tarePosition();

	IMU inertial(16, IMUAxes::z);
	inertial.reset(0);

	double error = angle;
	double power = 0;
	double kp = fmax(fmin(angle / 40, 3), 0.6);//reducing '40' makes higher speed
	double kd = 0;
	double past_error = 0;

	int slew_count = 0;
	int step = 2;

	while (error > threshold && slew_count * step < timeout) {
		error = angle - abs(inertial.getRemapped(-180, 180));
		power = kp * error;
		power = c(-100, 100, power);
		power = slew(slew_rate, slew_count, power, 35);
		power = fmax(power + kd * (error - past_error), 35);

		left.moveVoltage(120 * power);
		right.moveVoltage(-120 * power);

		pros::screen::print(pros::E_TEXT_MEDIUM, 1, "%f", power);

		slew_count++;
		past_error = error;

		pros::delay(step);
	}
	left.moveVoltage(0);
	right.moveVoltage(0);
}

void turn_left(double angle, double slew_rate, double threshold, double timeout) {
	MotorGroup left({-3, -11, -12});
	MotorGroup right({10, 18, 19});

	left.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
	right.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
	left.setBrakeMode(AbstractMotor::brakeMode::hold);
	right.setBrakeMode(AbstractMotor::brakeMode::hold);
	left.tarePosition();
	right.tarePosition();

	IMU inertial(16, IMUAxes::z);
	inertial.reset(0);

	double error = angle;
	double power = 0;
	double kp = fmax(fmin(angle / 40, 3), 0.6);
	double past_error = 0;
	double kd = 0;

	int slew_count = 0;
	int step = 2;

	while (error > threshold && slew_count * step < timeout) {
		error = angle - abs(inertial.getRemapped(-180, 180));
		power = kp * error;
		power = c(-100, 100, power);
		power = slew(slew_rate, slew_count, power, 35);
		power = power + kd * (error - past_error);

		left.moveVoltage(-120 * power);
		right.moveVoltage(120 * power);

		slew_count++;
		past_error = error;

		pros::delay(step);
	}

	left.moveVoltage(0);
	right.moveVoltage(0);
}

void turn(double angle, bool direction, double p, double d, double slew_rate, double threshold, double timeout) {
	if (direction) {
		turn_right(angle, slew_rate, threshold, timeout);
	} else {
		turn_left(angle, slew_rate, threshold, timeout);
	}
}

void point_right(double distance) {
	MotorGroup right({10, 18, 19});
	right.moveRelative(distance, 70);
}