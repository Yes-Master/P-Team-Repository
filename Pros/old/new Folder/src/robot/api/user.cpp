#include "robot/api/user.hpp"
#include "main.h"
#include "robot/api/init.hpp"

#include "robot/control/modes/flow.hpp"

void opcontrol() {
  systemInit();
  flow::init();
  
  while (1) {
    flow::user();
    pros::delay(20);
  }
}
