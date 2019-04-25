#include "robot/control/modes/caps.hpp"
#include "robot/control/modes/flow.hpp"

#include "robot/control/systems/drive.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/puncher.hpp"

namespace caps {
  void user() {
    drive::control::manual();
    drive::control::hold();

    intake::control::feedIn();
    intake::control::feedOut();
    intake::control::toggle();

    lift::control::manual();
    lift::control::position();
    lift::control::calabrate();
  }
  void init() {
    intake::automatic::disable();
    lift::set_target(lift::down, lift::vDown, true);
    drive::set_inverted(true);
    controllerMaster.setText(1, 5, "CAPS");
    flow::set_mode(flow::Modes::CAPS);
    lift::btnPosTog.changed();
  }
  void deInit() {
  }
} // namespace caps
