#pragma once

void forward(double distance, 
			double p = 0.15, 
			double g = 1.1, 
			double slew_rate = 0.3, 
			double threshold = 5, 
			double timeout = 3000);	
void backward(double distance, 
			  double p = 0.15, 
			  double g = 1.1, 
			  double slew_rate = 0.3, 
			  double threshold = 5, 
			  double timeout = 3000);
void drive(double distance, 
		   double p = 0.3, 
		   double g = 1.1, 
		   double slew_rate = 0.3, 
		   double threshold = 5, 
		   double timeout = 3000);
void small(double distance);