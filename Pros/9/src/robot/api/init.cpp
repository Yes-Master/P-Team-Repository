#include "robot/api/init.hpp"
#include "main.h"
#include "robot/control/systems/lift.hpp"
void initialize(){
  pros::lcd::initialize();
  Puncher::motor.tarePosition();
  Lift::motor.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  Intake::motor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
}
