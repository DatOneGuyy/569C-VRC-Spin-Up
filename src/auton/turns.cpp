#include "main.h"
#include "okapi/api.hpp"
#include "auton/turns.hpp"
#include "functions.hpp"

using namespace okapi;

void turn_right(double angle, double slew_rate, double threshold, double timeout) {
	MotorGroup left({3, -11, -10});
	MotorGroup right({-2, 18, 4});

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
	double kp = fmax(fmin(angle / 70, 1.6), 0.6);
	double kd = 0.1;
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

		slew_count++;
		past_error = error;

		if (fabs(error) < 50 && fabs(power) < 10) {
			break;
		}

		pros::delay(step);
	}
	left.moveVoltage(0);
	right.moveVoltage(0);
}

void turn_left(double angle, double slew_rate, double threshold, double timeout) {
	MotorGroup left({3, -11, -10});
	MotorGroup right({-2, 18, 4});

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
	double kp = fmax(fmin(angle / 70, 1.6), 0.6);
	double past_error = 0;
	double kd = 0.1;

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

		if (fabs(error) < 50 && fabs(power) < 10) {
			break;
		}

		pros::delay(step);
	}

	left.moveVoltage(0);
	right.moveVoltage(0);
}

void turn(double angle, bool direction, double slew_rate, double threshold, double timeout) {
	if (direction) {
		turn_right(angle, slew_rate, threshold, timeout);
	} else {
		turn_left(angle, slew_rate, threshold, timeout);
	}
}

void swing_right(double distance, double speed) {
	MotorGroup right({-2, 18, 4});
	right.tarePosition();
	while (fabs(right.getPosition()) < fabs(distance)) {
		right.moveVelocity(speed * sign(distance));
		pros::delay(3);
	}
	right.moveVelocity(0);
}

void swing_left(double distance, double speed) {
	MotorGroup left({3, -11, -10});
	left.tarePosition();
	while (fabs(left.getPosition()) < fabs(distance)) {
		left.moveVelocity(speed * sign(distance));
		pros::delay(3);
	}
	left.moveVelocity(0);
}

void swing_right_inertial(double angle, double speed) {
	MotorGroup right({-2, 18, 4});
	IMU inertial(16, IMUAxes::z);
	IMU inertial2(12, IMUAxes::z);
	IMU inertial3(19, IMUAxes::z);
	inertial.reset(0);
	inertial2.reset(0);
	inertial3.reset(0);
	right.tarePosition();
	while ((fabs(inertial.get()) + fabs(inertial2.get()) + fabs(inertial3.get())) / 3 < fabs(angle)) {
		right.moveVelocity(speed * sign(angle));
		pros::delay(3);
	}
	right.moveVelocity(0);
}

void swing_left_inertial(double angle, double speed) {
	MotorGroup left({3, -11, -10});
	IMU inertial(16, IMUAxes::z);
	IMU inertial2(12, IMUAxes::z);
	IMU inertial3(19, IMUAxes::z);
	inertial.reset(0);
	inertial2.reset(0);
	inertial3.reset(0);
	left.tarePosition();
	while ((fabs(inertial.get()) + fabs(inertial2.get()) + fabs(inertial3.get())) / 3 < fabs(angle)) {
		left.moveVelocity(speed * sign(angle));
		pros::delay(3);
	}
	left.moveVelocity(0);
}