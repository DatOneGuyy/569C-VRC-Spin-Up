#include "main.h"
#include "okapi/api.hpp"
#include "auton/autons.hpp"

using namespace okapi;

void clear_screen() {
	pros::screen::set_pen(COLOR_BLACK);
	pros::screen::fill_rect(0, 0, 480, 240);
}

void right_auton() {//non roller start
	/*
	target_speed = 73;//flywheel speed
	start_intake();//intake on stop_intake, reverse_intake
	drive(770);//rotation degrees
	turn(17, r);//r is right l is left 3.0, 0, 0.6
	shoot(3);//disk count # represents disc count
	stop_intake();
	turn(68, l);
	target_speed = 40;
	drive(-900);
	turn(40, r);
	pressure(350, 50);//time mm, speed 
	*/
	turn(40, r);
}

void left_auton() {
	target_speed = 72;
	start_intake();
	lift_pneumatics();
	drive(340);
	shoot(2);
	extend_indexer();
	point_right(440);
	small(100);
	lower_pneumatics();
	pros::delay(3000);
	retract_indexer();
	point_right(-380);
	shoot(3);
	stop_intake();
	turn(55, r);
	pros::delay(300);
	drive(-380, 0.3, 1.1, 0.6, 20);
	turn(50, l, 0.6, 10);
	pressure(500, 60);
}

void skills() {
	/*
	target_speed = 72;
	start_intake();
	lift_pneumatics();
	drive(340);
	shoot(2);
	extend_indexer();
	point_right(440);
	small(100);
	lower_pneumatics();
	pros::delay(3000);
	retract_indexer();
	point_right(-380);
	shoot(3);
	stop_intake();
	turn(55, r);
	pros::delay(300);
	drive(-380, 0.3, 1.1, 0.6, 20);
	turn(50, l, 1.2, 0.25, 0.6, 10);
	pressure(1000, 30);
	reverse_intake();
	pros::delay(1000);
	drive(200);
	pros::screen::print(pros::E_TEXT_MEDIUM_CENTER, 6, "done");
	turn(45, r);*/
	drive(300);
	turn(90, l);
}