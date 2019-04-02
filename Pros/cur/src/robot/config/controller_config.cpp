#include "robot/config/controller_config.hpp"

okapi::Controller master_controller(okapi::ControllerId::master);
namespace Flow{
  okapi::ControllerButton btnTog = master_controller[okapi::ControllerDigital::up];
  okapi::ControllerButton btnToCaps = master_controller[okapi::ControllerDigital::L1];
}
namespace drive{
  okapi::ControllerButton btnBrake = master_controller[okapi::ControllerDigital::L2];
}
namespace intake{
  okapi::ControllerButton btnCombo = master_controller[okapi::ControllerDigital::R2];
  okapi::ControllerButton btnIn = master_controller[okapi::ControllerDigital::X];
  okapi::ControllerButton btnOut = master_controller[okapi::ControllerDigital::Y];
  okapi::ControllerButton btnTog = master_controller[okapi::ControllerDigital::A];
}
namespace lift{
  okapi::ControllerButton btnUp = master_controller[okapi::ControllerDigital::R1];
  okapi::ControllerButton btnDown = master_controller[okapi::ControllerDigital::R2];
  okapi::ControllerButton btnPosTog = master_controller[okapi::ControllerDigital::L1];
  okapi::ControllerButton btnCal = master_controller[okapi::ControllerDigital::down];
}
namespace puncher{
  okapi::ControllerButton btnCharge = master_controller[okapi::ControllerDigital::R1];
  okapi::ControllerButton btnDoubleBack = master_controller[okapi::ControllerDigital::left];
  okapi::ControllerButton btnDoubleFront = master_controller[okapi::ControllerDigital::right];
}
