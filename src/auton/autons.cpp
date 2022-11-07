#include "main.h"
#include "okapi/api.hpp"
#include "auton/autons.hpp"

using namespace okapi;

void right_auton() {//non roller start
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
}

void left_auton() {
	target_speed = 76;
	start_intake();
	lift_pneumatics();
	drive(250);
	shoot(2);
	point_right(300);
	lower_pneumatics();
	pros::delay(2500);
	point_right(-300);//swing
	shoot(3);
}