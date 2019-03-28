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
    Puncher::motor.tarePosition();
  }
}
void initialize(){
  Auton::Selection::screenInit();

  Lift::motor.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  Intake::motor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
}
void disabled(void){
  AutonTask.suspend();
  Auton::set_auton(false);
}
void competition_initialize(void){
  // AutonTask.suspend();
  // Auton::inAuton=false;
  // Puncher::motor.tarePosition();
}
