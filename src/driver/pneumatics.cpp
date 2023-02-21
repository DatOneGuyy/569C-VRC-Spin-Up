#include "main.h"
#include "okapi/api.hpp"
#include "driver/pneumatics.hpp"

using namespace okapi;

void catapults_task(void*) {
	ControllerButton LEFT(ControllerDigital::left);
	pros::ADIPort catapults('B', pros::E_ADI_DIGITAL_OUT);
	pros::ADIPort catapults2('D', pros::E_ADI_DIGITAL_OUT);

	bool pneumatics_extended = false;

	while (driving) {
		if (LEFT.changedToPressed()) {
			pneumatics_extended = !pneumatics_extended;
			catapults.set_value(pneumatics_extended);
			catapults2.set_value(pneumatics_extended);
		}
		pros::delay(20);
	}
}

void angle_changer_task(void*) {
	ControllerButton DOWN(ControllerDigital::down);
	pros::ADIPort angle_changer('E', pros::E_ADI_DIGITAL_OUT);

	while (driving) {
		if (DOWN.changedToPressed()) {
			angled_up = !angled_up;
			angle_changer.set_value(angled_up);
		}
		pros::delay(20);
	}
}
