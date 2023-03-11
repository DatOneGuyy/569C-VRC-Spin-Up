#include "main.h"
#include "okapi/api.hpp"
#include "auton/autons.hpp"

using namespace okapi;

void clear_screen(void) {
	pros::screen::set_pen(COLOR_BLACK);
	pros::screen::fill_rect(0, 0, 480, 240);
}

void right_auton(void) {//non roller start
	target_speed = 64;
	start_intake();
	drive(320);
	turn(19, r, 0.4);
	shoot(3);
	target_speed = 60;
	turn(66, l);
	drive(420);
	pros::delay(400);
	drive(-250);
	turn(72, r);
	drive(100);
	pros::delay(500);
	shoot(3);
	stop_intake();
	turn(66, l);
	drive(-570, 0.8, 5, 0);
	turn(36, r);
	drive(-50);
	pressure_rev(200, 20, 100);
}

void left_auton(void) { //roller start
	target_speed = 67;
	pressure_rev(300, 20, 50);
	start_intake();
	swing_right_inertial(45, 0.3);
	pros::delay(200);
	drive(-50);
	turn(34, r);
	shoot(3);
	target_speed = 59;
	turn(60, r);
	drive(600, 0.05);
	turn(82, l);
	shoot(3);
	target_speed = 58;
	drive(100);
	pros::delay(2000);
	shoot(1);
	/*
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
	shoot(3);*/
}

void skills(void) {
	target_speed = 59;
	pressure(0, 20, 300);
	start_intake();
	drive(50);
	turn(45, l);
	pros::delay(200);
	//drive(200);
	drive(305, 0.3);
	pros::delay(200);
	turn(135, r, 0.4);
	stop_intake();
	//drive(-100);
	drive(-100, 0.1);
	pressure(300, 15, 300);
	angle_error = 0;
	drive(100, 0.3, 5, 0);
	start_intake();
	pros::delay(500);
	turn(89, l, 0.4);
	drive(155, 0.8, 5, 0);
	shoot(3);
	target_speed = 53;
	turn(47, r, 0.4);
	start_intake();
	drive(700);
	turn(90, l, 0.4);
	pros::delay(400);
	shoot(3);
	target_speed = 58;
	turn(89, r, 0.4);
	drive(840, 0.03);
	turn(135, l, 0.4);
	shoot(2);
	pros::delay(300);
	shoot(1);
	stop_intake();
	pros::delay(500);
	distance_reverse(840, 15);
	turn(88, l, 0.4);
	drive(-90, 0.8, 5, 10.0, 500);
	pressure(0, 15, 350);
	target_speed = 58;
	drive(100);
	start_intake();
	drive(150, 0.4);
	drive(150, 0.3);
	turn(17, l, 0.4);
	pros::delay(1500);
	shoot(3);
	target_speed = 53;
	drive(200);
	turn(60, r, 0.4);
	drive(450);
	turn(91, l, 0.4);
	shoot(3);
	target_speed = 58;
	turn(92, r, 0.4);
	drive(700, 0.05);
	turn(133, l, 0.4);
	pros::delay(1000);
	shoot(3);
	turn(135, l);
	drive(500, 0.01);
	drive(-250);
	turn(25, r, 0.4);
	shoot(3);
	target_speed = 54;
	turn(65, r, 0.4);
	drive(1500, 0.8, 5, 0);
	turn(115, l, 0.4);
	shoot(3);
	turn(100, r);
	drive(-2000);
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
