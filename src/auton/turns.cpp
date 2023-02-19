#include "main.h"
#include "okapi/api.hpp"
#include "auton/turns.hpp"
#include "functions.hpp"

using namespace okapi;

void turn_right(double angle, double slew_rate, double threshold, double timeout, int threshold_time) {
	MotorGroup left({3, -11, -10});
	MotorGroup right({-2, 18, 4});

	left.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
	right.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
	left.setBrakeMode(AbstractMotor::brakeMode::hold);
	right.setBrakeMode(AbstractMotor::brakeMode::hold);
	left.tarePosition();
	right.tarePosition();

	IMU inertial(16, IMUAxes::z);
	IMU inertial2(12, IMUAxes::z);
	IMU inertial3(19, IMUAxes::z);
	inertial.reset(0);
	inertial2.reset(0);
	inertial3.reset(0);

	double error = angle;
	double position = (inertial.get() + inertial2.get() + inertial3.get()) / 3;
	double power = 0;
	double kp = 4.5;

	double past_error = 0;
	double kd = 50;

	int slew_count = 0;
	int step = 2;
	int threshold_count = 0;

	while (slew_count * step < timeout && threshold_count * step < threshold_time) {
		position = (inertial.get() + inertial2.get() + inertial3.get()) / 3;
		error = angle - fabs(position);
		power = kp * error;
		power = slew(slew_rate, slew_count, power, 35);
		power =  power + kd * (error - past_error);
		power = c(-100, 100, power);

		left.moveVoltage(120 * power);
		right.moveVoltage(-120 * power);

		if (fabs(error) < threshold || fabs(error - past_error) < 0.1) {
			threshold_count++;
		} else {
			threshold_count = 0;
		}

		pros::screen::print(pros::E_TEXT_MEDIUM, 0, "Position: %f", position);
		pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Error: %f", error);
		pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Threshold count: %d", threshold_count);
		pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Power: %f", power);

		slew_count++;
		past_error = error;

		pros::delay(step);
	}
	left.moveVelocity(0);
	right.moveVelocity(0);

	pros::screen::print(pros::E_TEXT_MEDIUM, 4, "Exited");
}

void turn_left(double angle, double slew_rate, double threshold, double timeout, int threshold_time) {
	/*
	angle: [0, 180]
	slew_rate: [0, 1] - 0.6
	threshold: [0, 5] - 2
	timeout: [2000+]
	*/
	MotorGroup left({3, -11, -10});
	MotorGroup right({-2, 18, 4});

	left.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
	right.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
	left.setBrakeMode(AbstractMotor::brakeMode::hold);
	right.setBrakeMode(AbstractMotor::brakeMode::hold);
	left.tarePosition();
	right.tarePosition();

	IMU inertial(16, IMUAxes::z);
	IMU inertial2(12, IMUAxes::z);
	IMU inertial3(19, IMUAxes::z);
	inertial.reset(0);
	inertial2.reset(0);
	inertial3.reset(0);

	double error = angle;
	double position = (inertial.get() + inertial2.get() + inertial3.get()) / 3;
	double power = 0;
	double kp = 4;

	double past_error = 0;
	double kd = 50;

	int slew_count = 0;
	int step = 2;
	int threshold_count = 0;

	while (slew_count * step < timeout && threshold_count * step < threshold_time) {
		position = (inertial.get() + inertial2.get() + inertial3.get()) / 3;
		error = angle - fabs(position);
		power = kp * error;
		power = slew(slew_rate, slew_count, power, 35);
		power =  power + kd * (error - past_error);
		power = c(-100, 100, power);

		left.moveVoltage(-120 * power);
		right.moveVoltage(120 * power);

		if (fabs(error) < threshold || fabs(error - past_error) < 0.1) {
			threshold_count++;
		} else {
			threshold_count = 0;
		}

		pros::screen::print(pros::E_TEXT_MEDIUM, 0, "Position: %f", position);
		pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Error: %f", error);
		pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Threshold count: %d", threshold_count);
		pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Power: %f", power);

		slew_count++;
		past_error = error;

		pros::delay(step);
	}
	left.moveVelocity(0);
	right.moveVelocity(0);

	pros::screen::print(pros::E_TEXT_MEDIUM, 4, "Exited");
}

void turn(double angle, bool direction, double slew_rate, double threshold, double timeout, int threshold_time) {
	if (direction) {
		turn_right(angle, slew_rate, threshold, timeout, threshold_time);
	} else {
		turn_left(angle, slew_rate, threshold, timeout, threshold_time);
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