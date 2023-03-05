#include "main.h"
#include "okapi/api.hpp"
#include "auton/straight.hpp"
#include "functions.hpp"

using namespace okapi;

void forward(double distance, double slew_rate, double threshold, double timeout, int threshold_time) {
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

	double error = distance * 150 / 151;
	double position = avg(fabs(left.getPosition()), fabs(right.getPosition()));
	double power_right = 0;
	double power_left = 0;
	double kp = fmin(1.0, 200.0 / distance);
	double kd = 3.3;
	double kg = 10.0;
	double angle = 0;
	double past_error = error;

	int slew_count = 0;
	int step = 10;
	int threshold_count = 0;

	while (threshold_count * step < threshold_time && step * slew_count < timeout) {
		position = avg(fabs(left.getPosition()), fabs(right.getPosition()));
		error = distance * 150 / 151 - position;
		angle = (inertial.get() + inertial2.get() + inertial3.get()) / 3;
		power_left = kp * error;
		power_right = kp * error;
		power_right = (error > 100) ? power_right + angle * kg : power_right;
		power_left = (error > 100) ? power_left - angle * kg : power_left;
		power_left = power_left + kd * (error - past_error);
		power_right = power_right + kd * (error - past_error);
		power_left = c(-100, 100, power_left);
		power_right = c(-100, 100, power_right);
		power_left = slew(slew_rate, slew_count, power_left, 35);
		power_right = slew(slew_rate, slew_count, power_right, 35);

		left.moveVoltage(power_left * 120);
		right.moveVoltage(power_right * 120);
		slew_count++;

		if (fabs(error - past_error) < 2 && fabs(error) < fabs(distance) / 5) {
			threshold_count++;
		} else {
			threshold_count = 0;
		}

		pros::screen::print(pros::E_TEXT_MEDIUM, 0, "Position: %f", position);
		pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Error: %f", error);
		pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Threshold count: %d", threshold_count);

		past_error = error;
		pros::delay(step);
	}

	last_turn_direction = r;
	angle_error = angle;

	left.moveVelocity(0);
	right.moveVelocity(0);
}

void backward(double distance, double slew_rate, double threshold, double timeout, int threshold_time) {
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

	double error = distance * 150 / 151;
	double position = avg(fabs(left.getPosition()), fabs(right.getPosition()));
	double power_right = 0;
	double power_left = 0;
	double kp = fmin(1.0, 200.0 / distance);
	double kd = 3.3;
	double kg = 10.0;
	double angle = 0;
	double past_error = error;

	int slew_count = 0;
	int step = 10;
	int threshold_count = 0;

	while (threshold_count * step < threshold_time && step * slew_count < timeout) {
		position = avg(fabs(left.getPosition()), fabs(right.getPosition()));
		error = distance * 150 / 151 - position;
		angle = (inertial.get() + inertial2.get() + inertial3.get()) / 3;
		power_left = kp * error;
		power_right = kp * error;
		power_right = (error > 100) ? power_right + angle * kg : power_right;
		power_left = (error > 100) ? power_left - angle * kg : power_left;
		power_left = power_left + kd * (error - past_error);
		power_right = power_right + kd * (error - past_error);
		power_left = c(-100, 100, power_left);
		power_right = c(-100, 100, power_right);
		power_left = slew(slew_rate, slew_count, power_left, 35);
		power_right = slew(slew_rate, slew_count, power_right, 35);

		left.moveVoltage(power_left * -120);
		right.moveVoltage(power_right * -120);
		slew_count++;

		if (fabs(error - past_error) < 2 && fabs(error) < fabs(distance) / 5) {
			threshold_count++;
		} else {
			threshold_count = 0;
		}

		pros::screen::print(pros::E_TEXT_MEDIUM, 0, "Position: %f", position);
		pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Error: %f", error);
		pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Threshold count: %d", threshold_count);

		past_error = error;
		pros::delay(step);
	}

	last_turn_direction = r;
	angle_error = angle;

	left.moveVelocity(0);
	right.moveVelocity(0);
}

void drive(double distance,double slew_rate, double threshold, double timeout, int threshold_time) {
	if (distance > 0) {
		forward(distance, slew_rate, threshold, timeout, threshold_time);
	} else {
		backward(-distance, slew_rate, threshold, timeout, threshold_time);
	}
}

void small(double distance, double speed) {
	MotorGroup left({3, -11, -10});
	MotorGroup right({-5, 18, 4});

	left.moveRelative(distance, speed);
	right.moveRelative(distance, speed);
} 