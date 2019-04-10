#include "robot/api/auto.hpp"
#include "robot/control/auton/routines.hpp"
#include "robot/control/auton/selection.hpp"

#include "robot/api/init.hpp"
#include "robot/control/modes/auton.hpp"

#include "robot/control/systems/drive.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/puncher.hpp"

#include "main.h"
namespace auton{
pros::Task autonTask(::auton::Task, (void*)"test", TASK_PRIORITY_DEFAULT,
                     TASK_STACK_DEPTH_DEFAULT, "AutonTask");
}
void autonomous() {
  // puncher::motor.tarePosition();
  systemInit();
  auton::set_auton(true);
  auton::autonTask.resume();

  drive::set_brakeMode(okapi::Motor::brakeMode::hold);
  intake::automatic::enable();
  auton::selection::execute();
}
