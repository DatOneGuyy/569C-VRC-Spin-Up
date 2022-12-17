#pragma once

void pressure(double time, double speed = 70);
void toggle_intake(bool reverse = false);
void start_intake();
void stop_intake();
void slow_intake();
void reverse_intake();
void intake_handler(void*);