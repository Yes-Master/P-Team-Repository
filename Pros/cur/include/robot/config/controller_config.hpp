#ifndef CONTROLLER_CONFIG_HPP
#define CONTROLLER_CONFIG_HPP

#include "okapi/api.hpp"

extern okapi::Controller master_controller;

namespace Flow{
  extern okapi::ControllerButton BtnTog;
  extern okapi::ControllerButton BtnToCaps;
}
namespace Drive{
  extern okapi::ControllerButton BtnBrake;
}
namespace Intake{
  extern okapi::ControllerButton BtnCombo;
  extern okapi::ControllerButton BtnIn;
  extern okapi::ControllerButton BtnOut;
  extern okapi::ControllerButton BtnTog;
}
namespace Lift{
  extern okapi::ControllerButton BtnUp;
  extern okapi::ControllerButton BtnDown;
  extern okapi::ControllerButton BtnPosTog;
  extern okapi::ControllerButton BtnCal;
}
namespace Puncher{
  extern okapi::ControllerButton BtnCharge;
  extern okapi::ControllerButton BtnDoubleBack;
  extern okapi::ControllerButton BtnDoubleFront;
}
#endif /* end of include guard: CONTROLLER_CONFIG_HPP */
