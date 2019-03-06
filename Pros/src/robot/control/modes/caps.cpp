#include "robot/control/modes/caps.hpp"
#include "robot/control/modes/flow.hpp"

#include "robot/control/systems/drive.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/puncher.hpp"

namespace Caps{
  void user(){
    Drive::Control::manual();
    Drive::Control::hold();

    Intake::Control::feedIn();
    Intake::Control::feedOut();
    Intake::Control::toggle();

    Lift::Control::manual();
    Lift::Control::position();

    // Puncher::Control::
  }
  void init(){
    Flow::set_mode(Flow::Modes::FLAG);
  }
  void deInit(){

  }
}
