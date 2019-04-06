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
    controllerMaster.setText(1,0,"Mode:");
    controllerMaster.setText(1,10,"BP");
    controllerMaster.setText(2,10,"RP");
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
  drive::front_left_motor.moveVelocity(0);
  drive::front_right_motor.moveVelocity(0);
  drive::back_left_motor.moveVelocity(0);
  drive::back_right_motor.moveVelocity(0);
  puncher::motor.moveVelocity(0);
  lift::motor.moveVelocity(0);
  intake::motor.moveVelocity(0);
}
void competition_initialize(void){
  // AutonTask.suspend();
  // auton::inAuton=false;
  // puncher::motor.tarePosition();
}
