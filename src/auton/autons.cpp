#include "main.h"
#include "okapi/api.hpp"
#include "auton/autons.hpp"

using namespace okapi;

void clear_screen() {
	pros::screen::set_pen(COLOR_BLACK);
	pros::screen::fill_rect(0, 0, 480, 240);
}

void right_auton() {//non roller start
	target_speed = 77;
	start_intake();
	drive(600);
	pros::delay(200);
	turn(15, r, 0.1, 1);
	shoot(3);
	turn_left(67);
	extend_indexer();
	pros::delay(200);
	drive(700);
	pros::delay(500);
	drive(-1000);
	turn(47, r);
	retract_indexer();
	pros::delay(500);
	shoot(2);
	target_speed = 15;
	turn(75, l);
	drive(-390);
	turn(28, r);
	pressure(300, 30);
}

void left_auton() { //roller start
	target_speed = 75;
	start_intake();
	drive(300);
	shoot(2);
	target_speed = 76;
	extend_indexer();
	lift_pneumatics();
	point_right(420);
	small(110);
	lower_pneumatics();
	pros::delay(1500);
	lift_pneumatics();
	pros::delay(300);
	lower_pneumatics();
	pros::delay(1500);
	retract_indexer();
	point_right(-330);
	pros::delay(1200);
	shoot(3);
	target_speed = 15;
	stop_intake();
	turn(55, r);
	pros::delay(300);
	drive(-380);
	turn(55, l, 0.3, 4);
	pressure(700, 50);
}

void skills() {
	target_speed = 75;
	start_intake();
	drive(300);
	shoot(2);
	target_speed = 76;
	extend_indexer();
	lift_pneumatics();
	point_right(420);
	small(110);
	lower_pneumatics();
	pros::delay(1500);
	lift_pneumatics();
	pros::delay(300);
	lower_pneumatics();
	pros::delay(1500);
	retract_indexer();
	point_right(-330);
	pros::delay(1200);
	shoot(3);
	target_speed = 15;
	stop_intake();
	turn(55, r);
	pros::delay(300);
	drive(-380);
	turn(55, l, 0.3, 4);
	pressure(1000, 30);
	drive(400);
	turn(45, r);
	drive(-200);
	expand();
}

void win_point() {
	target_speed = 78;
	pressure(130, 20);
	drive(150);
	turn(45, r);
	pros::delay(200);
	toggle_intake();
	drive(500);
	turn(73, l, 0.05);
	pros::delay(1000);
	shoot(3);
	stop_intake();
	target_speed = 15;
	turn(61, r, 0.05, 0.4);
	pros::delay(200);
	reverse_intake();
	drive(2270);
	turn(165, l);
	pressure(900, 60);
	reverse_intake();
	point_right(-400);
	stop_intake();
}

void flywheel_test() {
	target_speed = 78;
}