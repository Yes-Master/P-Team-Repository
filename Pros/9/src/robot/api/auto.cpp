#include "robot/api/auto.hpp"
#include "robot/control/systems/drive.hpp"
#include "robot/auton/selection.hpp"
#include "main.h"
void autonomous(){
  pros::Task driveRamping (::Drive::Auton::DriveRamping,(void*)"test", TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT, "DriveRamping");

  Auton::Selection::execute();//executes the selected auton
}
