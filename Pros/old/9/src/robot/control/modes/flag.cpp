#include "robot/control/modes/flag.hpp"
#include "robot/control/modes/flow.hpp"

#include "robot/control/systems/drive.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/puncher.hpp"

namespace Flag{
  void user(){
    Drive::Control::manual();
    Drive::Control::hold();

    Intake::Control::combo();
    Intake::Control::feedIn();
    Intake::Control::feedOut();
    Intake::Control::toggle();

    // Lift::Control::

    Puncher::Control::charge();
  }
  void init(){
    Drive::set_inverted(false);
    Lift::set_target(Lift::Down,Lift::VDown,true);
    Flow::set_mode(Flow::Modes::FLAG);
  }
  void deInit(){

  }
}
