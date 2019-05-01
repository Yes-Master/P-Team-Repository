#pragma once
#include "okapi/api.hpp"

extern okapi::Controller controllerMaster;
extern pros::Controller controllerSlave;

namespace flow {
  extern okapi::ControllerButton btnTog;
  extern okapi::ControllerButton btnToCaps;
} // namespace flow

namespace drive {
  extern okapi::ControllerButton btnBrake;
  extern okapi::ControllerButton btnDirTog;
} // namespace drive

namespace intake {
  extern okapi::ControllerButton btnCombo;
  extern okapi::ControllerButton btnIn;
  extern okapi::ControllerButton btnOut;
  extern okapi::ControllerButton btnTog;

  extern okapi::ControllerButton btnOut2;
} // namespace intake

namespace lift {
  extern okapi::ControllerButton btnUp;
  extern okapi::ControllerButton btnDown;
  extern okapi::ControllerButton btnPosTog;
  extern okapi::ControllerButton btnCal;
} // namespace lift

namespace flipper {
  // extern okapi::ControllerButton btnUp;
  // extern okapi::ControllerButton btnDown;
  extern okapi::ControllerButton btnPosTog;
  extern okapi::ControllerButton btnCal;
} // namespace flipper

namespace puncher {
  extern okapi::ControllerButton btnCharge;
  extern okapi::ControllerButton btnDoubleBack;
  extern okapi::ControllerButton btnBackTop;
  extern okapi::ControllerButton btnBackMid;
} // namespace puncher