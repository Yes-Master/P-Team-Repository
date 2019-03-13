#include "robot/api/auto.hpp"
#include "robot/control/systems/drive.hpp"
void autonomous(){
  Drive::Auton::drive(360);
}
