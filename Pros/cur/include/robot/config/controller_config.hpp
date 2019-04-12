#ifndef CONTROLLER_CONFIG_HPP
#define CONTROLLER_CONFIG_HPP

#include "okapi/api.hpp"

extern okapi::Controller controllerMaster;
extern pros::Controller controllerSlave;

namespace flow{
  extern okapi::ControllerButton btnTog;
  extern okapi::ControllerButton btnToCaps;
}
namespace drive{
  extern okapi::ControllerButton btnBrake;
}
namespace intake{
  extern okapi::ControllerButton btnCombo;
  extern okapi::ControllerButton btnIn;
  extern okapi::ControllerButton btnOut;
  extern okapi::ControllerButton btnTog;

  extern okapi::ControllerButton btnOut2;
}
namespace lift{
  extern okapi::ControllerButton btnUp;
  extern okapi::ControllerButton btnDown;
  extern okapi::ControllerButton btnPosTog;
  extern okapi::ControllerButton btnCal;
}
namespace puncher{
  extern okapi::ControllerButton btnCharge;
  extern okapi::ControllerButton btnDoubleBack;
  extern okapi::ControllerButton btnDoubleFront;
}
#endif /* end of include guard: CONTROLLER_CONFIG_HPP */
