#include "main.h"
#include "okapi/api.hpp"
#include "devices.hpp"
#include "auton/odom.hpp"
#include "functions.hpp"

using namespace okapi;

void start_odom(void) {
    IMU inertial(16, IMUAxes::z);
	IMU inertial2(12, IMUAxes::z);
	IMU inertial3(19, IMUAxes::z);
    /*
    chassis = ChassisControllerBuilder()
        .withMotors({3, -11, -10}, {-5, 18, 4})
        .withDimensions(AbstractMotor::gearset::blue, {{2.75_in, 14.5_in}, imev5BlueTPR})
        .withSensors(
            ADIEncoder{'A', 'B'},
            ADIEncoder{'C', 'D', true},
            ADIEncoder{'E', 'F'}
        )
        .withOdometry({{2.75_in, 11.5_in, 3_in, 2.75_in}, quadEncoderTPR})
        .buildOdometry();*/
        
       /*
        Create odometry chassis with external linkage
        2.75" wheels, 14.5" track width, 600rpm
        2.75" tracking wheels, 11.5" track width, 3" offset from tracking center
        */

    chassis_l.setPose(0, 0, pi, true);

	//chassis->setDefaultStateMode(StateMode::CARTESIAN); //Cartesian coordinate tracking, right: +x, forward: +y
	//chassis->setState({0_in, 0_in, 0_deg}); //Begin facing forward
    final_speed = 0; //Default starting speed target for initial slew rate

    inertial.reset(); //Reset inertials, maybe sensor fusion later
    inertial2.reset();
    inertial3.reset();
}

void drive_to(double target_x, double target_y, double target_speed, bool backwards, double threshold, double kp_angle, double angle_threshold) {    
    const double pi = 3.1415926535897932384626433832795;

    double x = chassis_l.getPose().x; //Coordinates
    double y = chassis_l.getPose().y;
    double angle = chassis_l.getPose().theta; //Absolute angle, degrees, counterclockwise is positive, [-pi, pi]
    const double distance = dist(target_x, target_y, x, y); //Euclidean distance to target from starting position
    const int sign = backwards ? -1 : 1; //-1 for backwards, 1 for forwards, used to reverse movement direction

    double base_voltage = 0; //Base voltage used for moving to target, [-1.0, 1.0]
    double turn_voltage = 0;
    double left_voltage = 0; //Adjusted voltages to turn to face target, [-1.0, 1.0]
    double right_voltage = 0;

    double angle_error = 0; //Angle error, if a left turn is needed, angle_error > 0 [-pi, pi]
    double distance_error = distance; //Euclidean distance to target from current position
    double position = 1 - distance_error / distance; //Fraction of distance currently traveled, [0.0, 1.0]

    double past_angle_error = 0; //Used for calculating derivative terms
    double past_position = 0;

    const double kd_angle = 2.5; //Kd constant, slows down turning

    double left_power = 0; //Final power sent to the motors, [-12000, 12000]
    double right_power = 0;

    while (distance_error > threshold) {
        x = chassis_l.getPose().x; //Update values
        y = chassis_l.getPose().y;
        angle = transform_angle(-chassis_l.getPose().theta); //Update angle and remap to [-pi, pi]

        /*
        * Start with inverse tangent of target point, finding the angle from the x-axis to the target
        * Take the current angle and subtract from this angle to find the angle error
        * Modify the target angle by pi radians if backwards is active to set target to the back
        * If backwards is false, then multiplier is 0 and is ignored
        */
        angle_error = atan2(target_y, target_x) - angle; //Subtract to find error
        angle_error = transform_angle(angle_error); //Remap to [-pi, pi]
        angle_error = transform_angle(angle_error + pi * backwards); //If backwards is true then modify target angle
        /*
        * transform_angle() can be composed with itself without making changes so the value is not modified if backwards
        * is set to false
        */

        distance_error = dist(target_x, target_y, x, y); //Compute distance between target and current position
        position = 1 - distance_error / distance; //Set position to fraction of distance traveled [0.0, 1.0]

        /*
        * Early exit condition if change in position is less than 0.5% and over 50% of distance has been traveled
        * Since not all movmeents end with a target speed of 0, the loop also ends early if over 50% of the distance
        * has been traveled and the difference between the actual and target voltage is less than 0.5%
        */
        if ((fabs(position - past_position) < 0.005 || fabs(base_voltage)) && position > 0.5) { 
            break;
        }
        
        /*
        * Base voltage uses a quadratic speed controller depending in the position [0.0, 1.0]
        * Input starting velocity is the larger of either the ending speed of the last movement or 35%
        * Quadratic profile can be inverted if backwards is true, with a final range between [-1.0, 1.0]
        * Base voltage is 0 if the angle error is less than the threshold, forcing the robot to turn on a point
        * when off by a large angle instead of making a wider arc
        */
        base_voltage = (fabs(angle_error) < angle_threshold) * quadratic_profile(fmax(final_speed, 0.35), target_speed, 1.0, position, backwards);
        turn_voltage = kp_angle * angle_error * circle(1, position) + kd_angle * (past_angle_error - angle_error);
        /*
        * Power is base power ± turn modifier
        * Turn modifier uses a PD controller for angle
        * Since a positive angle error requires a counterclockwise (left turn) then the right speed must be 
        * increased when angle error > 0, so it is added. The proportional constant is scaled down by sqrt(1 - x^2)
        * to prevent reaction to large angle changes as the robot approaches the target
        * 
        * If angle error is decreasing, then Δerror * kd_angle < 0 and can be added to the right_power to decrease it 
        * and slow down
        * The opposite applies for left turns when angle error is increasing and the right power is negative, thus
        * adding to right_power which has a negative base voltage and slows it down
        * Mirrors for left power
        * 
        * When moving backwards with a positive angle error, |right| < |left| and right < 0, and is overall turning left
        * Δerror * kd_angle < 0 and so in order to increase right drive speed (negative net change) and counteract the
        * turn, kd_angle must become negative, thus making Δerror * kd_angle positive if kd_angle > 0
        * Similarly, left speed must decrease (positive net change) to also counteract the turn, and Δerror * kd_angle < 0
        * means it should be subtracted to make that change
        * 
        * The ptv() function transforms from percentage to voltage. Since the input is instead between [-1.0, 1.0] it
        * is scaled again by 100x to reach the millivolt range [-12000mV, 12000mV]
        * Adding the kp and kd terms also means that the expression is no longer bounded by [-1.0, 1.0] so it needs to
        * be constrained again
        */
        left_power = c(-1, 1, ptv(base_voltage - turn_voltage)) * 100;
        right_power = c(-1, 1, ptv(base_voltage + turn_voltage)) * 100;
        chassis->getModel()->tank(left_power, right_power); //Standard tank drive input

        pros::screen::print(pros::E_TEXT_MEDIUM, 0, "Position: %f, %f", x, y);
        pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Angle: %f rad, %f deg", angle, angle * 180 / pi);
        pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Error: %f, %f deg", distance_error, angle_error);
        pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Base Voltage: %f", base_voltage);
        pros::screen::print(pros::E_TEXT_MEDIUM, 4, "Turn Voltage: %f", turn_voltage);
        pros::screen::print(pros::E_TEXT_MEDIUM, 5, "Distance Error: %f", distance_error);
        pros::screen::print(pros::E_TEXT_MEDIUM, 6, "Quadratic Profile: %f", quadratic_profile(fmax(final_speed, 0.35), target_speed, 1.0, position, backwards));
        pros::screen::print(pros::E_TEXT_MEDIUM, 7, "Position position: %f", position);
        if (isnan(turn_voltage) || isnan(base_voltage)) {
            pros::screen::print(pros::E_TEXT_MEDIUM, 8, "not a number :skull:");
            break;
        }

        past_angle_error = angle_error; //Update past angle for derivative calculations
        past_position = position; //Past position is only used for exit loop condition, not 
        pros::delay(10); //Update evey 10ms
    }
    
    //Set final speed once loop is exited to the target speed
    //If the final speed is zero, do a full stop instead of coasting
    if (final_speed) {
        chassis->getModel()->tank(ptv(target_speed * 100), ptv(target_speed * 100));
    } else {
        chassis->getModel()->stop();
    } 
    final_speed = target_speed; //Update for the next movement
}

/*
* A straight movement preceding a turn must have a final speed of zero
* This turn uses the inertial sensors to turn to an absolute angle
* Needs to be tested to see if it is more accurate to just turn using the odometry
* If the inertial is better
*/
void turn_to(double target_angle, double slew_rate, double threshold, double timeout, int threshold_time) {
    IMU inertial(16, IMUAxes::z);
	IMU inertial2(12, IMUAxes::z);
	IMU inertial3(19, IMUAxes::z);

	double target = target_angle;

	double error = target;
	double position = (inertial.get() + inertial2.get() + inertial3.get()) / -3;
	double power = 0;
	double kp = 3.7;

	double past_error = 0;
	double kd = 14;

	int slew_count = 0;
	int step = 10;
	int threshold_count = 0;

    bool turn_direction;

    if (position < target_angle) {
        turn_direction = l;
    } else {
        turn_direction = r;
    }

	while (slew_count * step < timeout && threshold_count * step < threshold_time) {
		position = (inertial.get() + inertial2.get() + inertial3.get()) / -3;
		error = target - fabs(position);
		power = kp * error;
		power = slew(slew_rate, slew_count, power, 35);
		power =  power + kd * (error - past_error);
		power = c(-100, 100, power);

        if (turn_direction == l) {
		    chassis->getModel()->tank(-power, power);
        } else {
            chassis->getModel()->tank(power, -power);
        }

		if (fabs(error) < threshold || fabs(error - past_error) < 0.1) {
			threshold_count++;
		} else {
			threshold_count = 0;
		}

		pros::screen::print(pros::E_TEXT_MEDIUM, 0, "Position: %f", position);
		pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Error: %f", error);
		pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Threshold count: %d", threshold_count);
		pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Power: %f", power);

		slew_count++;
		past_error = error;

		pros::delay(step);
	}
    
    chassis->getModel()->stop();
}