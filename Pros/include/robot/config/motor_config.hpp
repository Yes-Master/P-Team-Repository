#ifndef MOTOR_CONFIG_HPP
#define MOTOR_CONFIG_HPP
//intagrate into systems files
#include "okapi/api.hpp"
namespace Drive{
  extern okapi::Motor front_left_motor;
  extern okapi::Motor front_right_motor;
  extern okapi::Motor back_left_motor;
  extern okapi::Motor back_right_motor;
}

namespace Puncher{
  extern okapi::Motor Motor;
}

namespace Lift{
  extern okapi::Motor Motor;
}

namespace Intake{
  extern okapi::Motor Motor;

  extern pros::ADILineSensor Puncher;
  extern pros::ADILineSensor Over;
  extern pros::ADILineSensor Top;
  extern pros::ADILineSensor Bottom;
}
#endif /* end of include guard: MOTOR_CONFIG_HPP */
