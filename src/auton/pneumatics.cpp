#include "main.h"
#include "okapi/api.hpp"
#include "auton/pneumatics.hpp"
#include "pros/adi.h"

void lift_pneumatics() {
    pros::ADIPort lift('C', pros::E_ADI_DIGITAL_OUT);
    lift.set_value(true);
}

void lower_pneumatics() {
    pros::ADIPort lift('C', pros::E_ADI_DIGITAL_OUT);
    lift.set_value(false);
}

void extend_indexer() {
    pros::ADIPort indexer('A', pros::E_ADI_DIGITAL_OUT);
    indexer.set_value(true);
}

void retract_indexer() {
    pros::ADIPort indexer('A', pros::E_ADI_DIGITAL_OUT);
    indexer.set_value(false);
}