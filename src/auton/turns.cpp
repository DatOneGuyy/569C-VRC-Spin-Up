#include "main.h"
#include "okapi/api.hpp"
#include "auton/turns.hpp"
#include "functions.hpp"

using namespace okapi;

void turn_right(double angle, double slew_rate, double threshold, double timeout, int threshold_time) {
	MotorGroup left({3, -11, -10});
	MotorGroup right({-5, 18, 4});

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

	double target = angle;

	if (angle_error != 0) {
		if (last_turn_direction == r) {
			target += angle_error;
		} else {
			target -= angle_error;
		}
	}

	double error = target;
	double position = (inertial.get() + inertial2.get() + inertial3.get()) / 3;
	double power = 0;
	double kp = 3.7;

	double past_error = 0;
	double kd = 14;

	int slew_count = 0;
	int step = 10;
	int threshold_count = 0;

	while (slew_count * step < timeout && threshold_count * step < threshold_time) {
		position = (inertial.get() + inertial2.get() + inertial3.get()) / 3;
		error = target - fabs(position);
		power = kp * error;
		power = slew(slew_rate, slew_count, power, 35);
		power =  power + kd * (error - past_error);
		power = c(-100, 100, power);

		left.moveVoltage(120 * power);
		right.moveVoltage(-120 * power);

		if (fabs(error) < threshold || fabs(error - past_error) < 0.01) {
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

	angle_error = error;
	last_turn_direction = r;

	left.moveVelocity(0);
	right.moveVelocity(0);

	pros::screen::print(pros::E_TEXT_MEDIUM, 4, "Exited");
	pros::screen::print(pros::E_TEXT_MEDIUM, 5, "Overall error: %f", angle_error);
}

void turn_left(double angle, double slew_rate, double threshold, double timeout, int threshold_time) {
	/*
	angle: [0, 180]
	slew_rate: [0, 1] - 0.6
	threshold: [0, 5] - 2
	timeout: [2000+]
	*/
	MotorGroup left({3, -11, -10});
	MotorGroup right({-5, 18, 4});

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

	double target = angle;

	if (angle_error != 0) {
		if (last_turn_direction == r) {
			target += angle_error;
		} else {
			target -= angle_error;
		}
	}

	double error = target;
	double position = (inertial.get() + inertial2.get() + inertial3.get()) / 3;
	double power = 0;
	double kp = 3.7;

	double past_error = 0;
	double kd = 14;

	int slew_count = 0;
	int step = 10;
	int threshold_count = 0;

	while (slew_count * step < timeout && threshold_count * step < threshold_time) {
		position = (inertial.get() + inertial2.get() + inertial3.get()) / 3;
		error = target - fabs(position);
		power = kp * error;
		power = slew(slew_rate, slew_count, power, 35);
		power =  power + kd * (error - past_error);
		power = c(-100, 100, power);

		left.moveVoltage(-120 * power);
		right.moveVoltage(120 * power);

		if (fabs(error) < threshold || fabs(error - past_error) < 0.01) {
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

	angle_error = error;
	last_turn_direction = r;

	left.moveVelocity(0);
	right.moveVelocity(0);

	pros::screen::print(pros::E_TEXT_MEDIUM, 4, "Exited");
	pros::screen::print(pros::E_TEXT_MEDIUM, 5, "Overall error: %f", angle_error);
}

void turn(double angle, bool direction, double slew_rate, double threshold, double timeout, int threshold_time) {
	if (direction) {
		turn_right(angle, slew_rate, threshold, timeout, threshold_time);
	} else {
		turn_left(angle, slew_rate, threshold, timeout, threshold_time);
	}
}

void swing_right_inertial(double angle, double slew_rate, double threshold, double timeout, int threshold_time) {
	MotorGroup right({-5, 18, 4});

	right.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
	right.setBrakeMode(AbstractMotor::brakeMode::hold);
	right.tarePosition();

	IMU inertial(16, IMUAxes::z);
	IMU inertial2(12, IMUAxes::z);
	IMU inertial3(19, IMUAxes::z);
	inertial.reset(0);
	inertial2.reset(0);
	inertial3.reset(0);

	double target = angle;

	if (angle_error != 0) {
		if (last_turn_direction == r) {
			target -= angle_error;
		} else {
			target += angle_error;
		}
	}

	double error = target;
	double position = (inertial.get() + inertial2.get() + inertial3.get()) / 3;
	double power = 0;
	double kp = 4.8;

	double past_error = 0;
	double kd = 14;

	int slew_count = 0;
	int step = 10;
	int threshold_count = 0;

	while (slew_count * step < timeout && threshold_count * step < threshold_time) {
		position = (inertial.get() + inertial2.get() + inertial3.get()) / 3;
		error = target - fabs(position);
		power = kp * error;
		power = slew(slew_rate, slew_count, power, 35);
		power =  power + kd * (error - past_error);
		power = c(-100, 100, power);

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

	angle_error = error;
	last_turn_direction = l;

	right.moveVelocity(0);

	pros::screen::print(pros::E_TEXT_MEDIUM, 4, "Exited");
	pros::screen::print(pros::E_TEXT_MEDIUM, 5, "Overall error: %f", angle_error);
}

void swing_left_inertial(double angle, double slew_rate, double threshold, double timeout, int threshold_time) {
	MotorGroup left({3, -11, -10});

	left.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
	left.setBrakeMode(AbstractMotor::brakeMode::hold);
	left.tarePosition();

	IMU inertial(16, IMUAxes::z);
	IMU inertial2(12, IMUAxes::z);
	IMU inertial3(19, IMUAxes::z);
	inertial.reset(0);
	inertial2.reset(0);
	inertial3.reset(0);

	double target = angle;

	if (angle_error != 0) {
		if (last_turn_direction == r) {
			target += angle_error;
		} else {
			target -= angle_error;
		}
	}

	double error = target;
	double position = (inertial.get() + inertial2.get() + inertial3.get()) / 3;
	double power = 0;
	double kp = 4.8;

	double past_error = 0;
	double kd = 14;

	int slew_count = 0;
	int step = 10;
	int threshold_count = 0;

	while (slew_count * step < timeout && threshold_count * step < threshold_time) {
		position = (inertial.get() + inertial2.get() + inertial3.get()) / 3;
		error = target - fabs(position);
		power = kp * error;
		power = slew(slew_rate, slew_count, power, 35);
		power =  power + kd * (error - past_error);
		power = c(-100, 100, power);

		left.moveVoltage(120 * power);

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

	angle_error = error;
	last_turn_direction = r;

	left.moveVelocity(0);

	pros::screen::print(pros::E_TEXT_MEDIUM, 4, "Exited");
	pros::screen::print(pros::E_TEXT_MEDIUM, 5, "Overall error: %f", angle_error);
}

void swing_turn(double angle, bool direction, double slew_rate, double threshold, double timeout, int threshold_time) {
	if (!direction) {
		swing_right_inertial(angle, slew_rate, threshold, timeout, threshold_time);
	} else {
		swing_left_inertial(angle, slew_rate, threshold, timeout, threshold_time);
	}
}