#pragma once

void turn_right(double angle,
                double slew_rate = 0.6,
                double threshold = 2,
                double timeout = 3000,
                int threshold_time = 200);
void turn_left(double angle,
               double slew_rate = 0.6,
               double threshold = 2,
               double timeout = 3000,
               int threshold_time = 200);
void turn(double angle,
          bool direction,
          double slew_rate = 0.9, 
          double threshold = 0.8,
          double timeout = 5000,
          int threshold_time = 100);
void swing_right_inertial(double angle,
                double slew_rate = 0.6,
                double threshold = 2,
                double timeout = 3000,
                int threshold_time = 200);
void swing_left_inertial(double angle,
               double slew_rate = 0.6,
               double threshold = 2,
               double timeout = 3000,
               int threshold_time = 200);
void swing_turn(double angle,
                bool direction,
                double slew_rate = 0.9,
                double threshold = 0.8,
                double timeout = 5000,
                int threshold_time = 100);
