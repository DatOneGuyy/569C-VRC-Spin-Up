#include "main.h"
#include "okapi/api.hpp"
#include "auton/autons.hpp"

using namespace okapi;

bool r = true;
bool l = false;

void right_auton() {
	target_speed = 73;
	toggle_intake();
	drive(770);
	turn(17, r);
	shoot(3);
	toggle_intake();
	turn(68, l);
	target_speed = 40;
	drive(-900);
	turn(40, r);
	pressure(350, 50);
}

void left_auton() {
	target_speed = 74;
	pressure(200, 30);
	pros::delay(200);
	drive(150, 0.4, 1.1, 0.5, 20);
	turn(58, r, 0.6);
	toggle_intake();
	drive(600, 0.3, 0.5, 0.5, 20);
	turn(80, l);
	pros::delay(1000);
	shoot(4);
	turn(68, r);
	target_speed = 66;
	drive(640, 0.15, 0.5);
	turn(81, l);
	pros::delay(1000);
	shoot(4);
}