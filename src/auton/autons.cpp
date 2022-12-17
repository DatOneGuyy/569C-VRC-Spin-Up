#include "main.h"
#include "okapi/api.hpp"
#include "auton/autons.hpp"

using namespace okapi;

void clear_screen() {
	pros::screen::set_pen(COLOR_BLACK);
	pros::screen::fill_rect(0, 0, 480, 240);
}

void right_auton() {//non roller start
	target_speed = 77.6;
	start_intake();
	drive(360);
	pros::delay(200);
	turn(11, r, 0.1, 1);
	shoot(3);
	target_speed = 78.3;
	turn_left(66);
	extend_indexer();
	pros::delay(200);
	drive(420, 0.2, 0.2);
	pros::delay(500);
	drive(-600);
	turn(42, r, 0.05, 1);
	retract_indexer();
	pros::delay(800);
	shoot(2);
	target_speed = 15;
	turn(71, l);
	pros::delay(200);
	drive(-190, 0.3, 1.1, 0.3, 5, 1500);
	turn(45, r);
	pressure(240, 30);
}

void left_auton() { //roller start
	pros::Task grapher_task(grapher);
	speed = 5;
	target_speed = 78;
	start_intake();
	drive(180);
	shoot(2);
	target_speed = 77;
	extend_indexer();
	lift_pneumatics();
	pros::delay(200);
	point_right(252);
	small(65);
	lower_pneumatics();
	pros::delay(1000);
	lift_pneumatics();
	pros::delay(400);
	lower_pneumatics();
	pros::delay(1300);
	retract_indexer();
	point_right(-221);
	pros::delay(1200);
	shoot(3);
	target_speed = 15;
	stop_intake();
	turn(51, r);
	pros::delay(300);
	drive(-228);
	turn(55, l, 0.3, 4);
	pressure(190, 40);
}

void skills() {
	pros::Task grapher_task(grapher);
	target_speed = 78;
	start_intake();
	drive(180);
	shoot(2);
	target_speed = 76;
	extend_indexer();
	lift_pneumatics();
	pros::delay(200);
	point_right(252);
	small(100);
	lower_pneumatics();
	pros::delay(1000);
	lift_pneumatics();
	pros::delay(200);
	lower_pneumatics();
	pros::delay(1500);
	retract_indexer();
	point_right(-200);
	pros::delay(1200);
	shoot(3);
	target_speed = 15;
	stop_intake();
	turn(51, r);
	pros::delay(300);
	drive(-228);
	turn(55, l, 0.3, 4);
	pressure(420, 40);
	reverse_intake();
	drive(280);
	turn_right(70);
	pros::delay(200);
	drive(-280);
	pressure(270, 40);
	drive(300);
	turn_left(55);
	drive(-200);
}

void flywheel_test() {
	target_speed = 78;
}