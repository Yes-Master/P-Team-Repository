#include "robot/api/init.hpp"
#include "main.h"
#include "robot/auton/selection.hpp"
#include "robot/api/auto.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/puncher.hpp"

bool inited=false;
void systemInit(){//custom robot init dont trust the reliability of initialize && competition_initialize
  if(!inited){
    inited=true;
    puncher::motor.tarePosition();
  }
}
void initialize(){
  auton::selection::screenInit();

  lift::motor.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  intake::motor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
}
void disabled(void){
  autonTask.suspend();
  auton::set_auton(false);
}
void competition_initialize(void){
  // AutonTask.suspend();
  // auton::inAuton=false;
  // puncher::motor.tarePosition();
}
