#include "robot/control/modes/flow.hpp"
#include "robot/control/modes/flag.hpp"
#include "robot/control/modes/caps.hpp"

#include "robot/control/systems/drive.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/puncher.hpp"

namespace Flow{
  //vars
  Modes Mode=Modes::FLAG;
  //vars FUNCTIONS
  Modes get_mode(){
    return Mode;
  }
  void set_mode(){

  }
  //methods
  void execute(){
    Drive::execute();
    Intake::execute();
    Lift::execute();
    // Puncher::execute();
  }
  void user(){
    switch (get_mode()) {
      case Modes::FLAG:
        Flag::user();
      break;
      case Modes::CAPS:
        // Caps::user();
      break;
      case Modes::DEBUG:
        //debug
      break;
      case Modes::NONE:
        //nothing is going on here
      break;
    }
    execute();
  }
}
