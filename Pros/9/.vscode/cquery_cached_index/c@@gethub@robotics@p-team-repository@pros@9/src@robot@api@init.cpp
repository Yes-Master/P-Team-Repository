#include "robot/api/init.hpp"
#include "main.h"
#include "robot/control/systems/lift.hpp"
#include "robot/auton/selection.hpp"
void initialize(){
  // pros::lcd::initialize();
  // lv_init();
  Auton::Selection::screenInit();
  Puncher::motor.tarePosition();
  Lift::motor.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  Intake::motor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
}
