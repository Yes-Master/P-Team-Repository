#include "robot/config/controller_config.hpp"

okapi::Controller master_controller(okapi::ControllerId::master);
namespace Flow{
  okapi::ControllerButton BtnTog = master_controller[okapi::ControllerDigital::up];
  okapi::ControllerButton BtnToCaps = master_controller[okapi::ControllerDigital::L1];
}
namespace Drive{
  okapi::ControllerButton BtnBrake = master_controller[okapi::ControllerDigital::L2];
}
namespace Intake{
  okapi::ControllerButton BtnCombo = master_controller[okapi::ControllerDigital::R2];
  okapi::ControllerButton BtnIn = master_controller[okapi::ControllerDigital::X];
  okapi::ControllerButton BtnOut = master_controller[okapi::ControllerDigital::Y];
  okapi::ControllerButton BtnTog = master_controller[okapi::ControllerDigital::A];
}
namespace Lift{
  okapi::ControllerButton BtnUp = master_controller[okapi::ControllerDigital::R1];
  okapi::ControllerButton BtnDown = master_controller[okapi::ControllerDigital::R2];
  okapi::ControllerButton BtnPosTog = master_controller[okapi::ControllerDigital::L1];
}
namespace Puncher{
  okapi::ControllerButton BtnCharge = master_controller[okapi::ControllerDigital::R1];
}
