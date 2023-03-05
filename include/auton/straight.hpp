#pragma once

void forward(double distance, 
			double slew_rate = 0.3, 
			double threshold = 5, 
			double timeout = 3000,
			int threshold_time = 100);	
void backward(double distance, 
			  double slew_rate = 0.3, 
			  double threshold = 5, 
			  double timeout = 3000,
			  int threshold_time = 100);
void drive(double distance, 
		   double slew_rate = 0.8, 
		   double threshold = 5, 
		   double timeout = 3000,
		   int threshold_time = 50);
void small(double distance, double speed = 50);