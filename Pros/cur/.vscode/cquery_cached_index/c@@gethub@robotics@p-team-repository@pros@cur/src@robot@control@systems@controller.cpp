#include "robot/control/systems/controller.hpp"

#include "main.h"

#include "robot/control/systems/drive.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/puncher.hpp"

namespace Controller{
  //vars
  //vars FUNCTIONS
  //methods
  void driveRumble(){
    static int deltaMsec;
    if(Drive::get_brakeMode()!=okapi::Motor::brakeMode::coast && deltaMsec>=25){
      master_controller.rumble(".");
      deltaMsec=0;
    }
    else deltaMsec++;//in loop count need to add better
  }
  void liftRumble(){
    if(Lift::CapBump.changed()){
      if(Lift::CapBump.isPressed()){
        master_controller.rumble(".");
      }
    }
  }
}
