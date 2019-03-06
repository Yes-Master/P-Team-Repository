#include "robot/config/motor_config.hpp"
namespace Drive{
  okapi::Motor front_left_motor(12,false,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
  okapi::Motor front_right_motor(13,true,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
  okapi::Motor back_left_motor(19,false,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
  okapi::Motor back_right_motor(20,true,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
}
namespace Puncher{
  okapi::Motor Motor(17,false,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
}
namespace Lift{
  okapi::Motor Motor(16,false,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
}
namespace Intake{
  okapi::Motor Motor(18,true,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
   pros::ADIAnalogIn Puncher(1);
   pros::ADIAnalogIn Over(2);
   pros::ADIAnalogIn Top(3);
   pros::ADIAnalogIn Bottom(4);

}
