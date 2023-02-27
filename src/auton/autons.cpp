#include "main.h"
#include "okapi/api.hpp"
#include "auton/autons.hpp"

using namespace okapi;

void clear_screen(void) {
	pros::screen::set_pen(COLOR_BLACK);
	pros::screen::fill_rect(0, 0, 480, 240);
}

void right_auton(void) {//non roller start
	target_speed = 61;
	start_intake();
	drive(320);
	turn(21, r);
	shoot(3);
	target_speed = 55;
	turn_left(63, l);
	drive(420);
	turn(80, r);
	stop_intake();
	shoot(3);
	turn(82, l, 0.1);
	drive(-1700, 0.6, 1.1, 0.3);
	swing_right_inertial(-40, 80);
	pressure(200, 20);
}

void left_auton(void) { //roller start
	target_speed = 71;
	pressure(100, 20, 110);
	pros::delay(50);
	start_intake();
	swing_right_inertial(450, 30);
	small(100, 30);
	pros::delay(400);
	small(-100, 30);
	pros::delay(200);
	swing_right_inertial(-400, 25);
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
	target_speed = 58;
	pressure(100, 20, 220);
	small(100, 30);
	start_intake();
	swing_right_inertial(45, 80);
	small(550, 40);
	pros::delay(800);
	turn(125, r);
	small(-220, 40);
	pros::delay(500);
	pressure(300, 20, 150);
	small(200, 40);
	start_intake();
	pros::delay(500);
	turn(71.4, l, 0.3);
	small(350, 40);
	pros::delay(600);
	shoot(3);
	target_speed = 53;
	turn(45, r, 0.5);
	start_intake();
	drive(710, 0.3, 1.1, 0.3);
	turn(92, l);
	pros::delay(400);
	shoot(3);
	target_speed = 57;
	turn(91, r, 0.4);
	drive(700, 0.1);
	turn(130, l);
	shoot(3);
	turn(145, l);
	drive(500, 0.1, 1.1, 0.1);
	drive(-150);
	turn(40, r);
	shoot(3);
	drive(-370);
	pressure(300, 20, 350);
	/*
	pros::delay(200);
	drive(500);
	shoot(3);
	*/
	/*
	small(100, 30);
	turn(80, l);
	pros::delay(200);
	drive(600);
	shoot(3);
	drive(-550);
	turn(40, r);
	pros::delay(200);
	drive(600);
	turn(90, l);
	shoot(3);
	turn(90, r);
	pros::delay(200);
	drive(600);
	turn(130, l);
	pros::delay(200);
	drive(300);
	shoot(3);
	drive(-300);
	turn(90, r);
	small(500, 30);
	drive(-300);
	turn(90, r);
	pros::delay(200);
	drive(600);
	swing_right_inertial(-90, 50);
	stop_intake();
	pressure(300, 20, 250);
	drive(300);
	turn(90, r);
	small(300, 50);
	pressure(100, 20, 250);
	small(100);
	start_intake();
	drive(600);
	turn(90, l);
	shoot(3);
	turn(90, r);
	pros::delay(200);
	drive(600);
	turn(130, l);
	shoot(3);
	turn(90, r);
	small(300, 40);
	drive(-300);
	turn(90, r);
	pros::delay(200);
	drive(600);
	turn(90, r);
	pros::delay(200);
	drive(600);
	shoot(3);
	drive(-600);
	turn(45, r);
	pros::delay(200);
	drive(300);
	expand();
	drive(-300);
	*/
}

void flywheel_test(void) {
	swing_turn(45, l);
	swing_turn(45, r);
	swing_turn(45, r);
	swing_turn(45, l);
}	
