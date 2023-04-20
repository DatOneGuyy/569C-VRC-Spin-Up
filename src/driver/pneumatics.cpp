#include "main.h"
#include "okapi/api.hpp"
#include "driver/pneumatics.hpp"

using namespace okapi;

void catapults_task(void*) {
	ControllerButton LEFT(ControllerDigital::left);
	ControllerButton DOWN(ControllerDigital::down);
	ControllerButton B(ControllerDigital::B);
	pros::ADIPort catapults('B', pros::E_ADI_DIGITAL_OUT);
	pros::ADIPort catapults2('D', pros::E_ADI_DIGITAL_OUT);

	bool pneumatics_extended_left = false;
	bool pneumatics_extended_right = false;

	while (driving) {
		if (LEFT.changedToPressed()) {
			if (pneumatics_extended_left != pneumatics_extended_right) {
				pneumatics_extended_left = false;
				pneumatics_extended_right = false;
			} else {
				pneumatics_extended_left = !pneumatics_extended_left;
				pneumatics_extended_right = !pneumatics_extended_right;
			}
			catapults.set_value(pneumatics_extended_left);
			catapults2.set_value(pneumatics_extended_right);
		}

		if (DOWN.changedToPressed()) {
			pneumatics_extended_left = !pneumatics_extended_left;
			catapults.set_value(pneumatics_extended_left);
		}

		if (B.changedToPressed()) {
			pneumatics_extended_right = !pneumatics_extended_right;
			catapults2.set_value(pneumatics_extended_right);
		}
		pros::delay(20);
	}
}

void angle_changer_task(void*) {
	ControllerButton UP(ControllerDigital::up);
	pros::ADIPort angle_changer('E', pros::E_ADI_DIGITAL_OUT);
	angled_up = false;

	while (driving) {
		if (UP.changedToPressed()) {
			angled_up = !angled_up;
			angle_changer.set_value(angled_up);
		}
		pros::delay(20);
	}
}
