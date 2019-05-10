#include "robot/api/init.hpp"
#include "main.h"
#include "robot/api/auto.hpp"
#include "robot/control/auton/selection.hpp"
#include "robot/control/modes/auton.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/puncher.hpp"

bool inited = false;
void systemInit() {  // custom robot init dont trust the reliability of
                     // initialize && competition_initialize
  if (!inited) {
    inited = true;

    drive::front_left_motor.tarePosition();
    drive::front_right_motor.tarePosition();
    drive::back_left_motor.tarePosition();
    drive::back_right_motor.tarePosition();
    drive::FL.set_limits(drive::FL.get_changeMsec(),-drive::FL.get_changeMsec(),0,0);
    drive::FR.set_limits(drive::FR.get_changeMsec(),-drive::FR.get_changeMsec(),0,0);
    drive::BL.set_limits(drive::BL.get_changeMsec(),-drive::BL.get_changeMsec(),0,0);
    drive::BR.set_limits(drive::BR.get_changeMsec(),-drive::BR.get_changeMsec(),0,0);
  }
}
void initialize() {
  auton::selection::screenInit();

  lift::motor.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  flipper::motor.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  intake::motor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
}
void disabled(void) {
  auton::autonTask.suspend();
  auton::set_auton(false);
  // drive::front_left_motor.moveVelocity(0);
  // drive::front_right_motor.moveVelocity(0);
  // drive::back_left_motor.moveVelocity(0);
  // drive::back_right_motor.moveVelocity(0);
  // puncher::motor.moveVelocity(0);
  // lift::motor.moveVelocity(0);
  // intake::motor.moveVelocity(0);
}
void competition_initialize(void) {
  // AutonTask.suspend();
  // auton::inAuton=false;
  // puncher::motor.tarePosition();
}
