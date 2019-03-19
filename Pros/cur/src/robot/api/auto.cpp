#include "robot/api/auto.hpp"
#include "robot/control/modes/auton.hpp"
#include "robot/api/init.hpp"

#include "robot/control/systems/drive.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/puncher.hpp"

#include "robot/auton/routines.hpp"
#include "main.h"

pros::Task AutonTask (::Auton::Task,(void*)"test", TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT, "AutonTask");

void autonomous(){
  // Puncher::motor.tarePosition();
  SystemInit();
    Auton::set_auton(true);
  AutonTask.resume();

  Drive::set_brakeMode(okapi::Motor::brakeMode::hold);

Auton::Routines::execute();
}
