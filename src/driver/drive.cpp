#include "main.h"
#include "okapi/api.hpp"
#include "driver/drive.hpp"

using namespace okapi;

void drive_task(void*) {
	Controller controller;

	double left, right;

	std::shared_ptr<ChassisController> drive =
		ChassisControllerBuilder()
			.withMotors({3, -11, -10}, {-1, 18, 4})
			.withDimensions({AbstractMotor::gearset::blue, (60.0 / 84.0)}, {{4.125_in, 16_in}, imev5BlueTPR})
			.build();

	drive->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);

	while (true && driving) {
		left = controller.getAnalog(ControllerAnalog::leftY);
		right = controller.getAnalog(ControllerAnalog::rightY);

		drive->getModel()->tank(controller_map(left), controller_map(right));

		pros::delay(3);
	}
}