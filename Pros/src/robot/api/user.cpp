#include "main.h"
#include "robot/api/user.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/modes/flow.hpp"
void opcontrol(){
  Flow::init();
  while(1){
    Flow::user();
    pros::delay(20);
  }
}
