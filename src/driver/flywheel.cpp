#include "main.h"
#include "okapi/api.hpp"
#include "driver/flywheel.hpp"

using namespace okapi;

void indexer_task(void*) {
	ControllerButton L1(ControllerDigital::L1);
	ControllerButton L2(ControllerDigital::L2);
	ControllerButton UP(ControllerDigital::up);
	ControllerButton RIGHT(ControllerDigital::right);
	ControllerButton A(ControllerDigital::A);

	Controller controller;

	pros::ADIPort indexer('A', pros::E_ADI_DIGITAL_OUT);
	Motor flywheel(13);

	double rate = 5.1;

	bool flywheel_idle = true;
	bool run_flywheel = true;
	double idle = 55;
	double active = 65;

	indexer.set_value(false);

	while (true) {
		if (A.changedToPressed()) {
			run_flywheel = !run_flywheel;
		}
		if (run_flywheel) {
			if (angled_up) {
				active = 65;
			} else {
				active = 65;
			}
			
			if (flywheel_idle) {
				flywheel.moveVoltage(ptv(idle));
			} else {
				flywheel.moveVoltage(ptv(active));
				controller.rumble(".");
			}

			if (L2.changedToPressed()) {
				flywheel_idle = !flywheel_idle;
			}
			if (L1.changedToPressed() && !flywheel_idle) {
				flywheel.moveVoltage(ptv(100));
				for (int i = 0; i < 3; i++) {
					indexer.set_value(true);
					pros::delay(1000 / rate * 0.3);

					indexer.set_value(false);
					pros::delay(1000 / rate * 0.7);
				}
				pros::delay(250);

				flywheel_idle = true;
			}
			if (UP.changedToPressed()) {
				indexer.set_value(true);
				pros::delay(1000 / rate * 0.3);

				indexer.set_value(false);
				pros::delay(1000 / rate * 0.7);

				flywheel.moveVoltage(ptv(idle));
			}
			if (RIGHT.changedToPressed()) {
				if (active == 65) {
					active = 95;
				} else {
					active = 65;
				}
			}
		} else {
			flywheel.moveVoltage(0);
		}
		pros::delay(10);
	}
}
