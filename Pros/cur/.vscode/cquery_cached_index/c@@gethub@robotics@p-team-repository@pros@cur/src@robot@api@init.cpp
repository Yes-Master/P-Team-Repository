#include "robot/api/init.hpp"
#include "main.h"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/puncher.hpp"
#include "robot/api/auto.hpp"
bool inited=false;
void SystemInit(){
  if(!inited){
    inited=true;
    Puncher::motor.tarePosition();
  }
}
void initialize(){
  // Puncher::motor.tarePosition();

  pros::lcd::initialize();
  pros::lcd::register_btn0_cb(Auton::Selection::on_left_btn);
  pros::lcd::register_btn1_cb(Auton::Selection::on_center_btn);
  pros::lcd::register_btn2_cb(Auton::Selection::on_right_btn);

  pros::lcd::set_text(1,"BLUE");
  master_controller.setText(1, 1, "BLUE");

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
