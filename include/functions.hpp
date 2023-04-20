#pragma once

double controller_map(double i);
double ptv(double percent);
double avg(double a, double b);
double c(double min, double max, double value);
double slew(double rate, int count, double target, double base);
double sign(double x);
void shift(void);
double average_speed(void);
double circle(double radius, double value);
double quadratic_profile(double initial, double final, double maximum, double position, bool inverted = false);
double dist(double x1, double y1, double x2, double y2);
double transform_angle(double angle, bool radians = true);