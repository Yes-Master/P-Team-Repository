#ifndef MOTOR_CONFIG_HPP
#define MOTOR_CONFIG_HPP
//intagrate into systems files
#include "custom/ramping.hpp"
#include "okapi/api.hpp"
namespace drive {
  extern okapi::Motor front_left_motor;
  extern okapi::Motor front_right_motor;
  extern okapi::Motor back_left_motor;
  extern okapi::Motor back_right_motor;

  extern Ramping LeftN;
  extern Ramping RightN;
  extern Ramping LeftS;
  extern Ramping RightS;
} // namespace drive

namespace puncher {
  extern okapi::Motor motor;
} // namespace puncher

namespace lift {
  extern okapi::Motor motor;
  extern okapi::ADIButton CapBump;
} // namespace lift

namespace flipper {
  extern okapi::Motor motor;
} // namespace flipper

namespace intake {
  extern okapi::Motor motor;
  namespace automatic {
    namespace balls {
      extern pros::ADILineSensor puncher;
      extern pros::ADILineSensor over;
      extern pros::ADILineSensor top;
      extern pros::ADILineSensor bottom;
    } // namespace balls
  }   // namespace automatic
} // namespace intake

#endif /* end of include guard: MOTOR_CONFIG_HPP */
