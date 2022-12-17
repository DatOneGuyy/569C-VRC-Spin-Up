#include "main.h"
#include "okapi/api.hpp"
#include "driver/intake.hpp"

using namespace okapi;

void intake_task(void*) {
	ControllerButton R1(ControllerDigital::R1);
	ControllerButton R2(ControllerDigital::R2);
	Motor intake(-9);
	OpticalSensor optical(7);
	bool active = false;

	while (true && driving) {
		if (R1.changedToPressed()) {
			active = !active;
			changing = true;
		}
		if (!R2.isPressed()) {
			if (optical.getSaturation() < 0.4) {
				intake_voltage = 12000 * (active ? 1 : 0);
			} else {
				if (program == 0 || program == 2 || program == 4 || program == 5) {
					if (optical.getHue() < 10 || optical.getHue() > 340) {
						intake_voltage = 0;
					} else {
						intake_voltage = 9000 * (active ? 1 : 0);
					}
				} else {
					if (optical.getHue() < 260 && optical.getHue() > 180) {
						intake_voltage = 0;
					} else {
						intake_voltage=  9000 * (active ? 1 : 0);
					}
				}
			}
		} else if (R2.isPressed()) {
			if (program == 0 || program == 2 || program == 4 || program == 5) {
				if (optical.getHue() < 10 || optical.getHue() > 340) {
					intake_voltage = 0;
				} else {
					if (optical.getSaturation() < 0.4) {
						intake_voltage = -12000;
					} else {
						intake_voltage = -7500;
					}
				}
			} else {
				if (optical.getHue() < 260 && optical.getHue() > 180) {
					intake_voltage = 0;
				} else {
					if (optical.getSaturation() < 0.4) {
						intake_voltage = -12000;
					} else {
						intake_voltage = -7500;
					}
				}
			}
		} else {
			intake_voltage = 0;
		}
	}
}