#include "robot/api/init.hpp"
#include "main.h"
#include "robot/control/systems/lift.hpp"
#include "display/lvgl.h"
void initialize(){
  // pros::lcd::initialize();
  lv_init();
  hal_init();

	lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_align(btn1,NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

  Puncher::motor.tarePosition();
  Lift::motor.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  Intake::motor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
}
