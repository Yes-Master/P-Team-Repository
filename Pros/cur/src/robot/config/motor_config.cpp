#include "robot/config/motor_config.hpp"
#include "custom/ramping.hpp"
namespace drive {
  okapi::Motor front_left_motor(6, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
  okapi::Motor front_right_motor(3, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
  okapi::Motor back_left_motor(7, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
  okapi::Motor back_right_motor(10, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
  // MecanumDrive Chassis(
  //   front_left_motor,
  //   back_left_motor,
  //   front_right_motor,
  //   back_right_motor,
  //   4*M_PI,11.5,8);
  Ramping FL(1.75, 5, 200, -200);
  Ramping FR(1.75, 5, 200, -200);
  Ramping BL(1.75, 5, 200, -200);
  Ramping BR(1.75, 5, 200, -200);
} // namespace drive

namespace puncher {
  okapi::Motor motor(5, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);
} // namespace puncher

namespace lift {
  okapi::Motor motor(8, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);
  okapi::ADIButton CapBump(4, false);
} // namespace lift

namespace flipper {
  okapi::Motor motor(9, true, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);
} // namespace flipper

namespace intake {
  okapi::Motor motor(11, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
  namespace automatic {
    namespace balls {
      pros::ADIAnalogIn puncher(8);
      pros::ADIAnalogIn over(7);
      pros::ADIAnalogIn top(6);
      pros::ADIAnalogIn bottom(5);
    } // namespace balls
  }   // namespace automatic
} // namespace intake