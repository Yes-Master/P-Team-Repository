#include "robot/api/init.hpp"
#include "main.h"
void initialize(){
  pros::lcd::initialize();
  Puncher::motor.tarePosition();
  Lift::motor.tarePosition();
  Lift::motor.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  Intake::motor.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
}
