#include "main.h"
#include "okapi/api.hpp"
#include "auton/autons.hpp"

using namespace okapi;

void clear_screen() {
	pros::screen::set_pen(COLOR_BLACK);
	pros::screen::fill_rect(0, 0, 480, 240);
}

void right_auton() {//non roller start
	target_speed = 65;
	start_intake();
	drive(360);
	pros::delay(200);
	turn(11.5, r, 0.05, 0.4);
	shoot(3);
	target_speed = 68;
	turn(64, l, 0.05, 1);
	extend_indexer();
	pros::delay(200);
	drive(420, 0.2, 0.2, 0.03);
	pros::delay(500);
	drive(-600);
	turn(43.5, r, 0.05, 0.4);
	retract_indexer();
	pros::delay(800);
	shoot(2);
	stop_intake();
	target_speed = 15;
	turn(65.5, l);
	pros::delay(200);
	drive(-150, 0.3, 1.1, 0.3, 5, 1500);
	turn(40, r);
	pressure(280, 40, 180);
}

void left_auton() { //roller start
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

void skills() {
	target_speed = 72;
	pressure(100, 20, 150);
	pros::delay(50);
	start_intake();
	swing_right_inertial(44, 30);
	small(100, 30);
	pros::delay(400);
	small(-100, 30);
	pros::delay(200);
	swing_right_inertial(-33, 25);
	pros::delay(700);
	shoot(3);
	target_speed = 61;
	turn(45, r, 0.05, 0.4);
	pros::delay(300);
	drive(600);
	small(350, 30);
	pros::delay(2500);
	turn(83, l, 0.05, 0.4);
	pros::delay(1500);
	shoot(3);
	stop_intake();
	target_speed = 15;
	turn(115, l, 0.05, 0.4);
	pros::delay(500);
	drive(400);
	small(500, 50);
	pros::delay(1500);
	small(-150);
	turn(77, l, 0.05, 0.4);
	pros::delay(500);
	drive(-700);
	pressure(500, 20, 230);
	drive(200);
	turn(45, l);
	expand();
}

void flywheel_test() {
	target_speed = 78;
}