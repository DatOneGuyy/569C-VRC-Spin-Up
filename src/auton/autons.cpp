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
	target_speed = 59;
	pressure(300, 20, 220);
	start_intake();
	swing_right_inertial(45, 0.4);
	pros::delay(200);
	//drive(200);
	drive(270, 0.01, 2);
	pros::delay(200);
	turn(135, r, 0.4);
	stop_intake();
	//drive(-100);
	drive(-80);
	pros::delay(200);
	pressure(50, 20, 350);
	drive(60);
	start_intake();
	pros::delay(500);
	turn(89, l);
	shoot(3);
	target_speed = 53;
	swing_left_inertial(45, 0.9);
	start_intake();
	drive(750);
	turn(90, l, 0.2);
	pros::delay(400);
	shoot(2);
	pros::delay(300);
	shoot(1);
	target_speed = 59;
	turn(88, r, 0.2);
	drive(820, 0.01);
	turn(135, l);
	shoot(2);
	pros::delay(300);
	shoot(1);
	stop_intake();
	drive(-50);
	turn(90, l);
	drive(-70);
	pressure(100, 10, 350);
	drive(50);
	start_intake();
	drive(400, 0.02);
	turn(20, l);
	pros::delay(500);
	shoot(3);
	drive(-50);
	turn(110, r);
	drive(-300);
	pressure(200, 10, 350);
	drive(70);
	start_intake();
	turn(43, l);
	drive(800);
	turn(90, l);
	shoot(3);
	turn(92, r);
	drive(750, 0.01);
	turn(145, l);
	shoot(3);
	turn(145, l);
		/*
	pros::delay(200);
	drive(500);
	shoot(3);
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
	for (int i = 0; i < 4; i++) {
		swing_turn(90, r);
	}
	for (int i = 0; i < 4; i++) {
		swing_turn(90, l);
	}
}	
