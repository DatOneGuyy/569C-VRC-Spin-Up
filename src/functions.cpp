#include "main.h"
#include "functions.hpp"

double controller_map(double i) {
	double sign = i == 0 ? 0 : fabs(i) / i;
    double input = fabs(i * 100);
    double output = 0;

    if (input < 5) {
        output = 0;
    } else if (input < 100.0 / 1.3) {
        output = input * 1.3;
    } else {
        output = 100;
    }

    return output / 100 * sign;
}

double ptv(double percent) {
	return percent * 120;
}

double avg(double a, double b) {
  return (a + b) / 2;
}

double c(double min, double max, double value) {
  if (value < min) {
    return min;
  } else if (value > max) {
    return max;
  } else {
    return value;
  }
}

double slew(double rate, int count, double target, double base) {
	if (fabs(base + rate * count) < fabs(target)) {
		return base + rate * count;
	} else {
		return target;
	}
}

double sign(double x) {
  if (x == 0) {
    return 0;
  } else {
    return fabs(x) / x;
  }
}

void shift(void) {
  for (int i = 0; i < smoothing - 1; i++) {
    speeds[i] = speeds[i + 1];
  }
  speeds[smoothing - 1] = speeds[smoothing - 2];
}

double average_speed(void) {
  double sum = 0;
  for (int i = 0; i < smoothing; i++) {
    sum += speeds[i] * (i + 1);
  }
  return sum / ((smoothing * (smoothing + 1.0)) / 2.0);
}

double circle(double radius, double value) {
  return sqrt(radius * radius - value * value);
}

double quadratic_profile(double initial, double final, double maximum, double position, bool inverted) {
  double n = 0;
  const double f = 1.5; //sharpness of velocity curve, roughly equivalent to slew rate
  const double degree = 3.6; //sharpness of deceleration curve
  double p = 0;
  double A = 0;
  double B = 0;
  double pos = position;

  double output = 0;

  if (position < 0) {
    pos = 0;
  }

  if (final < initial) {
    output = (initial - final) * pow(1 - pow(pos, degree), 1 / degree) + final;
  } else {
    n = fmin(initial, final) / fmax(initial, final);
    n = n / (n + 1);
    p = f * initial * initial + f * final * final;
    A = (p - initial + n * (initial - final)) / (n * n - n);
    B = (initial - p + n * n * (final - initial)) / (n * n - n);
    
    output = fmin(A * pos * pos + B * pos + initial, maximum);
  }

  return output * (inverted ? -1 : 1);
}

double dist(double x1, double y1, double x2, double y2) {
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double positive_fmod(double a, double b) {
  double temp = 0;
  if (a < 0) {
    temp = a / b - ceil(a / b);
    return (b + temp * b == b) ? 0 : (b + temp * b);
  } else if (a > 0) {
    temp = a / b - floor(a / b);
    return temp * b == b ? 0 : (temp * b);
  } else {
    return 0;
  }
}

double transform_angle(double angle, bool radians) {
  double output = 0;
  if (radians) {
    output = positive_fmod(angle - okapi::pi, 2 * okapi::pi) - okapi::pi;
  } else {
    output = positive_fmod(angle - 180, 360) - 180;
  }
  return output;
}