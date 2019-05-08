#include "robot/control/modes/flow.hpp"
#include "robot/control/modes/caps.hpp"
#include "robot/control/modes/flag.hpp"

#include "robot/api/auto.hpp"
// #include "robot/config/controller_config.hpp"

#include "robot/control/systems/drive.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/flipper.hpp"
#include "robot/control/systems/puncher.hpp"

namespace flow {
  //vars
  Modes mode = Modes::NONE;
  //vars FUNCTIONS
  Modes get_mode() {
    return mode;
  }
  void set_mode(Modes m) {
    mode = m;
  }
  //methods
  namespace control {
    void modeTog() {
      if (btnTog.changed()) {
        if (btnTog.isPressed()) {
          switch (get_mode()) {
          case Modes::FLAG:
            caps::init();
            break;
          case Modes::CAPS:
            flag::init();
            break;
          case Modes::DEBUG:
            flag::init();
            break;
          case Modes::NONE:
            break;
          }
        } else {
        }
      } else if (btnTog.isPressed()) {

      } else {
      }
    }
    void tocapsTog() {
      if (btnToCaps.changed()) {
        if (btnToCaps.isPressed()) {
          caps::init();
        } else {
        }
      } else if (btnToCaps.isPressed()) {

      } else {
      }
    }
  } // namespace control
  void init() {
    flag::init();
    auton::autonTask.suspend();
    drive::set_brakeMode(okapi::Motor::brakeMode::coast);
    intake::automatic::enable();
  }
  void execute() {
    drive::execute();
    intake::execute();
    lift::execute();
    flipper::execute();
    puncher::execute();
  }
  void user() {
    drive::feedback::rumble();
    lift::feedback::rumble();
    // control::modeTog();

    lift::control::calabrate();
    lift::control::manual();
    lift::control::position();

    flipper::control::position();

    if (!drive::get_inverted()) { puncher::control::charge(); }
    puncher::control::backMid();
    puncher::control::backTop();

    // intake::control::feedIn();
    intake::control::feedOut();
    intake::control::toggle();

    drive::control::manual();
    drive::control::hold();
    drive::control::dir();
    // switch (get_mode()) {
    //   case Modes::FLAG:
    //     control::tocapsTog();
    //     flag::user();
    //   break;
    //   case Modes::CAPS:
    //     caps::user();
    //   break;
    //   case Modes::DEBUG:
    //     //debug
    //   break;
    //   case Modes::NONE:
    //     //nothing is going on here
    //   break;
    // }
    execute();
  }
} // namespace flow
