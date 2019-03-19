#include "main.h"
#include "robot/api/user.hpp"
#include "robot/api/init.hpp"

#include "robot/control/modes/flow.hpp"

void opcontrol(){
  SystemInit();
  Flow::init();
    while(1){
    Flow::user();
    pros::delay(20);
  }
}
