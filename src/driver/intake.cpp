#include "main.h"
#include "okapi/api.hpp"
#include "driver/intake.hpp"

using namespace okapi;

void intake_task(void*) {
	ControllerButton R1(ControllerDigital::R1);
	ControllerButton R2(ControllerDigital::R2);
	Motor intake(-9);
	bool active = false;

	while (true && driving) {
		if (R1.changedToPressed()) {
			active = !active;
			changing = true;
		}
		if (!R2.isPressed()) {
			intake_voltage = 12000 * (active ? 1 : 0);
		} else {
			intake_voltage = 0;
		}
	}
}