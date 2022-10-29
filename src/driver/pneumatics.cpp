#include "main.h"
#include "okapi/api.hpp"
#include "driver/pneumatics.hpp"

using namespace okapi;

void catapults_task(void*) {
	ControllerButton LEFT(ControllerDigital::left);
	pros::ADIPort catapults('B', pros::E_ADI_DIGITAL_OUT);
	pros::ADIPort catapults2('D', pros::E_ADI_DIGITAL_OUT);

	bool pneumatics_extended = false;

	while (true && driving) {
		if (LEFT.changedToPressed()) {
			pneumatics_extended = !pneumatics_extended;
			catapults.set_value(pneumatics_extended);
			catapults2.set_value(pneumatics_extended);
		}
		pros::delay(20);
	}
}

void intake_lift_task(void*) {
	ControllerButton DOWN(ControllerDigital::down);
	pros::ADIPort lift('C', pros::E_ADI_DIGITAL_OUT);

	bool pneumatics_extended = false;
	while (true && driving) {
		if (DOWN.changedToPressed()) {
			pneumatics_extended = !pneumatics_extended;
			lift.set_value(pneumatics_extended);
		}
		pros::delay(20);
	}
}