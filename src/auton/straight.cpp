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
	left.setBrakeMode(AbstractMotor::brakeMode::coast);
	right.setBrakeMode(AbstractMotor::brakeMode::coast);
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
	double power = 0;
	double kp = fmin(1.0, 200.0 / distance);
	double kd = 3.3;
	double kg = 4.0;
	double angle = 0;
	double past_error = error;

	int slew_count = 0;
	int step = 10;
	int threshold_count = 0;

	while (threshold_count * step < threshold_time && step * slew_count < timeout) {
		position = avg(fabs(left.getPosition()), fabs(right.getPosition()));
		error = distance * 150 / 151 - position;
		angle = (inertial.get() + inertial2.get() + inertial3.get()) / 3;
		power = kp * error;
		power = (error > 10) ? power - angle * kg : power;
		power = power + kd * (error - past_error);
		power = c(-100, 100, power);
		power = slew(slew_rate, slew_count, power, 35);

		left.moveVoltage(power * 120);
		right.moveVoltage(power * 120);
		slew_count++;

		if (fabs(error - past_error) < 0.1 && fabs(error) < fabs(distance) / 2) {
			threshold_count++;
		} else {
			threshold_count = 0;
		}

		pros::screen::print(pros::E_TEXT_MEDIUM, 0, "Position: %f", position);
		pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Error: %f", error);
		pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Threshold count: %d", threshold_count);
		pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Power: %f", power);
		pros::screen::print(pros::E_TEXT_MEDIUM, 4, "Angle: %f", angle);

		std::cout << "Error: " << error << "Power: " << power << "Kp * error: " << kp * error << std::endl;

		past_error = error;
		pros::delay(step);
	}

	left.moveVelocity(0);
	right.moveVelocity(0);
}

void backward(double distance, double slew_rate, double threshold, double timeout, int threshold_time) {
	MotorGroup left({3, -11, -10});
	MotorGroup right({-5, 18, 4});

	left.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
	right.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
	left.setBrakeMode(AbstractMotor::brakeMode::coast);
	right.setBrakeMode(AbstractMotor::brakeMode::coast);
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
	double power = 0;
	double kp = fmin(1.0, 300.0 / distance);
	double kd = 3.3;
	double kg = 4.0;
	double angle = 0;
	double past_error = error;

	int slew_count = 0;
	int step = 10;
	int threshold_count = 0;

	while (threshold_count * step < threshold_time && step * slew_count < timeout) {
		position = avg(fabs(left.getPosition()), fabs(right.getPosition()));
		error = distance * 150 / 151 - position;
		angle = (inertial.get() + inertial2.get() + inertial3.get()) / 3;
		power = kp * error;
		power = (error > 10) ? power - angle * kg : power;
		power = power + kd * (error - past_error);
		power = c(-100, 100, power);
		power = slew(slew_rate, slew_count, power, 35);

		left.moveVoltage(-power * 120);
		right.moveVoltage(-power * 120);
		slew_count++;

		if (fabs(error - past_error) < 0.1 && fabs(error) < fabs(distance) / 2) {
			threshold_count++;
		} else {
			threshold_count = 0;
		}

		pros::screen::print(pros::E_TEXT_MEDIUM, 0, "Position: %f", position);
		pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Error: %f", error);
		pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Threshold count: %d", threshold_count);
		pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Power: %f", power);

		past_error = error;
		pros::delay(step);
	}

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