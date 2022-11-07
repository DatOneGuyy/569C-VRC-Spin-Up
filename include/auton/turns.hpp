#pragma once

void turn_right(double angle, 
                double slew_rate = 0.6, 
                double threshold = 2, 
                double timeout = 3000);
void turn_left(double angle, 
               double slew_rate = 0.6, 
               double threshold = 2, 
               double timeout = 3000);
void turn(double angle, 
          bool direction, 
          double slew_rate = 0.1, 
          double threshold = 2, 
          double timeout = 3000);
void point_right(double distance);