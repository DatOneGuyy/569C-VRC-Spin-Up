#include "main.h"
#include "okapi/api.hpp"
#include "auton/autons.hpp"

using namespace okapi;

void clear_screen(void) {
	pros::screen::set_pen(COLOR_BLACK);
	pros::screen::fill_rect(0, 0, 480, 240);
}

void right_auton(void) {//non roller start
	target_speed = 65.5;
	start_intake();
	drive(360);
	pros::delay(200);
	turn(13, r, 0.05, 0.4);
	shoot(3);
	target_speed = 68;
	turn(65, l, 0.05, 1);
	pros::delay(200);
	drive(420, 0.2, 0.2, 0.03);
	pros::delay(500);
	drive(-600);
	turn(42, r, 0.05, 0.4);
	pros::delay(800);
	shoot(2);
	stop_intake();
	target_speed = 15;
	turn(66.5, l);
	pros::delay(200);
	drive(-130, 0.3, 1.1, 0.3, 5, 1500);
	turn(40, r);
	pressure(280, 40, 180);
}

void left_auton(void) { //roller start
	target_speed = 71;
	pressure(100, 20, 110);
	pros::delay(50);
	start_intake();
	swing_right(450, 30);
	small(100, 30);
	pros::delay(400);
	small(-100, 30);
	pros::delay(200);
	swing_right(-400, 25);
	pros::delay(700);
	shoot(3);
	target_speed = 61;
	turn(45, r, 0.05, 0.4);
	pros::delay(300);
	drive(600);
	small(300, 30);
	pros::delay(2500);
	turn(83, l, 0.05, 0.4);
	pros::delay(1500);
	shoot(3);
}

void skills(void) {
	target_speed = 65;
	pressure(100, 20, 250);
	small(100, 30);
	swing_right_inertial(45, 30);
	small(400, 40);
	pros::delay(800);
	turn(135, r);
	pressure(100, 20, 250);
	small(100, 30);
	turn(80, l);
	drive(600);
	shoot(3);
	drive(-550);
	turn(40, r);
	drive(600);
}

void flywheel_test(void) {
	turn(90, l);
}
