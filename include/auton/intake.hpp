#pragma once

void pressure(double time, double speed = 70, double pressure_time = 120);
void pressure_rev(double time, double speed = 70, double pressure_time = 120);
void toggle_intake(bool reverse = false);
void start_intake(void);
void stop_intake(void);
void slow_intake(void);
void reverse_intake(void);
void intake_handler(void*);