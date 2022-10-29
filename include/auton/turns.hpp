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
          double p = 1.0, 
          double d = 0.25, 
          double slew_rate = 0.4, 
          double threshold = 2, 
          double timeout = 3000);