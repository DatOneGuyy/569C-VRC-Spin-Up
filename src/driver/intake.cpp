#include "main.h"
#include "okapi/api.hpp"
#include "driver/intake.hpp"

using namespace okapi;

void intake_task(void*) {
	ControllerButton R1(ControllerDigital::R1);
	ControllerButton R2(ControllerDigital::R2);
	Motor intake(-9);
	OpticalSensor optical(14);
	bool active = false;

	while (true) {
		if (R1.changedToPressed()) {
			active = !active;
		}
		if (!R2.isPressed()) {
			intake.moveVoltage(12000 * (active ? 1 : 0));
		} else if (R2.isPressed()) {
			if (optical.getHue() < 10 || optical.getHue() > 340) {
				intake.moveVoltage(0);
			} else {
				intake.moveVoltage(-12000);
			}
		} else {
			intake.moveVoltage(0);
		}
	}
}