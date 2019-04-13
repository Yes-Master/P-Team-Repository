#include "robot/api/user.hpp"
#include "main.h"
#include "robot/api/init.hpp"

#include "robot/control/modes/flow.hpp"

void opcontrol() {
                    std::cout<<"con inited"<<std::endl;

  systemInit();
                  std::cout<<"syst inited"<<std::endl;

  flow::init();
                  std::cout<<"flow inited"<<std::endl;

  while (1) {
    flow::user();
    pros::delay(20);
    static int loop;
    loop++;
    std::cout<<"user loop: "<<loop<<std::endl;
  }
}
