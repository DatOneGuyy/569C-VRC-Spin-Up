#include "okapi/api.hpp"
#include "lemlib/api.hpp"

#pragma once

extern std::shared_ptr<okapi::ChassisController> chassis;
extern lemlib::Chassis chassis_l;
extern okapi::IMU inertial;
extern okapi::IMU inertial2;
extern okapi::IMU inertial3;