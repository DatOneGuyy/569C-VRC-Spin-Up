#include "main.h"
#include "okapi/api.hpp"
#include "driver/flywheel.hpp"

using namespace okapi;

void indexer_task(void*) {
	ControllerButton L1(ControllerDigital::L1);
	ControllerButton L2(ControllerDigital::L2);
	ControllerButton UP(ControllerDigital::up);
	ControllerButton RIGHT(ControllerDigital::right);

	pros::ADIPort indexer('A', pros::E_ADI_DIGITAL_OUT);
	Motor flywheel(13);

	double rate = 3.2;

	bool flywheel_idle = true;
	double idle = 40;
	double active = 77;

	indexer.set_value(false);

	while (true) {
		if (flywheel_idle) {
			flywheel.moveVoltage(ptv(idle));
		} else {
			flywheel.moveVoltage(ptv(active));
		}

		if (L2.changedToPressed()) {
			flywheel_idle = !flywheel_idle;
		}
		if (L1.changedToPressed() && !flywheel_idle) {
			for (int i = 0; i < 3; i++) {
				indexer.set_value(true);
				flywheel.moveVoltage(ptv(100));
				pros::delay(1000 / rate * 0.3);

				indexer.set_value(false);
				pros::delay(1000 / rate * 0.7);
			}

			pros::delay(500);

			flywheel_idle = true;
			flywheel.moveVoltage(ptv(idle));
			pros::delay(500);
		}
		if (UP.changedToPressed()) {
			indexer.set_value(true);
			flywheel.moveVoltage(ptv(100));
			pros::delay(1000 / rate * 0.3);

			indexer.set_value(false);
			pros::delay(1000 / rate * 0.7);
			
			flywheel.moveVoltage(ptv(idle));
		}
		if (RIGHT.changedToPressed()) {
			if (active == 85) {
				active = 100;
			} else {
				active = 85;
			}
		}
		pros::delay(10);
	}
}