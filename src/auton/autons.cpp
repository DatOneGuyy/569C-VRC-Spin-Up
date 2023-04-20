#include "main.h"
#include "auton/odom.hpp"
#include "okapi/api.hpp"
#include "auton/autons.hpp"

using namespace okapi;

void clear_screen(void) {
	pros::screen::set_pen(COLOR_BLACK);
	pros::screen::fill_rect(0, 0, 480, 240);
}

void right_auton(void) {
	start_odom();
	drive_to(0, 1, 0);
}

void left_auton(void) {
	
}

void skills(void) { 
	
}
