#include "robot/api/auto.hpp"
#include "robot/control/systems/drive.hpp"
#include "main.h"
void autonomous(){

  pros::Motor testm(20,pros::motor_gearset_e::E_MOTOR_GEARSET_18,false,pros::motor_encoder_units_e::E_MOTOR_ENCODER_DEGREES);
  pros::motor_pid_full_s_t pid = pros::Motor::convert_pid_full(0, 250, 0,0, 0, 1, 1, 10);
pros::delay(500);
  testm.set_vel_pid_full(pid);
  pros::delay(500);

  testm.move_relative(720,200);
//   Drive::front_left_motor.tarePosition();
//   Drive::front_right_motor.tarePosition();
//   Drive::back_left_motor.tarePosition();
//   Drive::back_right_motor.tarePosition();
//   Drive::set_brakeMode(okapi::Motor::brakeMode::hold);
//
//   Drive::front_left_motor.setVelPIDFull (0, 0.01, 0.001, 0.1, 0.25, 1, 1, 2000);
//   Drive::front_right_motor.setVelPIDFull(0, 0.01, 0.001, 0.1, 0.25, 1, 1, 2000);
//   Drive::back_left_motor.setVelPIDFull  (0, 0.01, 0.001, 0.1, 0.25, 1, 1, 2000);
//   Drive::back_right_motor.setVelPIDFull (0, 0.01, 0.001, 0.1, 0.25, 1, 1, 2000);
//   Drive::Auton::drive(1000);
// while(Drive::front_left_motor.getPosition()<995){
//   pros::delay(5);
// }
// pros::delay(250);
//   Drive::set_v(0,0,0,0);
//   // Drive::Auton::AbsolutelyRelative(-12,0,0);
}
