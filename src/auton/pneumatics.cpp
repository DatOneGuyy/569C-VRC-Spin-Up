#include "main.h"
#include "okapi/api.hpp"
#include "auton/pneumatics.hpp"
#include "pros/adi.h"

void lift_pneumatics(void) {
    pros::ADIPort lift('C', pros::E_ADI_DIGITAL_OUT);
    lift.set_value(true);
}

void lower_pneumatics(void) {
    pros::ADIPort lift('C', pros::E_ADI_DIGITAL_OUT);
    lift.set_value(false);
}

void extend_indexer(void) {
    pros::ADIPort indexer('A', pros::E_ADI_DIGITAL_OUT);
    indexer.set_value(true);
}

void retract_indexer(void) {
    pros::ADIPort indexer('A', pros::E_ADI_DIGITAL_OUT);
    indexer.set_value(false);
}

void expand(void) {
    pros::ADIPort catapults('B', pros::E_ADI_DIGITAL_OUT);
	pros::ADIPort catapults2('D', pros::E_ADI_DIGITAL_OUT);
    catapults.set_value(true);
    catapults2.set_value(true);
}