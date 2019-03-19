#ifndef MOTOR_CONFIG_HPP
#define MOTOR_CONFIG_HPP
//intagrate into systems files
#include "okapi/api.hpp"
#include "custom/ramping.hpp"
namespace Drive{
  extern okapi::Motor front_left_motor;
  extern okapi::Motor front_right_motor;
  extern okapi::Motor back_left_motor;
  extern okapi::Motor back_right_motor;

  extern Ramping LeftN;
  extern Ramping RightN;
  extern Ramping LeftS;
  extern Ramping RightS;
}
namespace Puncher{
  extern okapi::Motor motor;
}

namespace Lift{
  // extern okapi::Motor motor0;
  extern okapi::Motor motor;
  // extern okapi::MotorGroup motor;
  // extern Ramping ramp;
}

namespace Intake{
  extern okapi::Motor motor;
  namespace Auto{
    namespace Balls{
      extern pros::ADILineSensor Puncher;
      extern pros::ADILineSensor Over;
      extern pros::ADILineSensor Top;
      extern pros::ADILineSensor Bottom;
    }
  }
}
#endif /* end of include guard: MOTOR_CONFIG_HPP */
