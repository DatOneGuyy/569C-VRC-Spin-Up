#include "main.h"
#include "okapi/api.hpp"
#include "auton/straight.hpp"
#include "functions.hpp"

using namespace okapi;

void forward(double distance, double p, double g, double slew_rate, double threshold, double timeout) {
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

	double error = distance;
	double power = 0;
	double kp = p;
	double kg = g;
	double angle = 0;

	int slew_count = 0;
	int step = 5;

	while (fabs(error) > threshold && step * slew_count < timeout) {
		error = distance - avg(left.getPosition(), right.getPosition());
		angle = inertial.getRemapped();
		power = kp * error;
		power = c(-20, 100, power);
		power = slew(slew_rate, slew_count, power, 35);

		if (error > 200) {
			left.moveVoltage(120 * (power - angle * kg));
			right.moveVoltage(120 * (power + angle * kg));
		} else {
			left.moveVoltage(120 * (power - angle * kg * fabs(error) / 200));
			right.moveVoltage(120 * (power + angle * kg * fabs(error) / 200));
		}
		slew_count++;

		if (error < 50 && power < 4) {
			break;
		}

		pros::delay(step);
	}

	left.moveVelocity(0);
	right.moveVelocity(0);
}

void backward(double distance, double p, double g, double slew_rate, double threshold, double timeout) {
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

	double error = -distance;
	double power = 0;
	double kp = p;
	double kg = g;
	double angle = 0;

	int slew_count = 0;
	int step = 5;

	while (fabs(error) > threshold && step * slew_count < timeout) {
		error = -distance - avg(left.getPosition(), right.getPosition());
		angle = inertial.getRemapped();
		power = kp * error;
		power = c(-100, 20, power);
		power = slew(-slew_rate, slew_count, power, -35);

		if (error < -200) {
			left.moveVoltage(120 * (power - angle * kg));
			right.moveVoltage(120 * (power + angle * kg));
		} else {
			left.moveVoltage(120 * (power - angle * kg * fabs(error) / 200));
			right.moveVoltage(120 * (power + angle * kg * fabs(error) / 200));
		}
		slew_count++;

		if (fabs(error) < 50 && fabs(power) < 4) {
			break;
		}

		pros::delay(step);
	}

	left.moveVelocity(0);
	right.moveVelocity(0);
}

void drive(double distance, double p, double g, double slew_rate, double threshold, double timeout) {
	if (distance > 0) {
		forward(distance, p, g, slew_rate, threshold, timeout);
	} else {
		backward(-distance, p, g, slew_rate, threshold, timeout);
	}
}

void small(double distance, double speed) {
	MotorGroup left({3, -11, -10});
	MotorGroup right({-2, 18, 4});

	left.moveRelative(distance, speed);
	right.moveRelative(distance, speed);
} 