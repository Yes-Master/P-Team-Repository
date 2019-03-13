#include "robot/config/motor_config.hpp"
#include "custom/ramping.hpp"
namespace Drive{
  okapi::Motor front_left_motor(9,false,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
  okapi::Motor front_right_motor(1,true,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
  okapi::Motor back_left_motor(7,false,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
  okapi::Motor back_right_motor(10,true,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
  Ramping test(1,2);
}
namespace Puncher{
  okapi::Motor motor(20,false,okapi::AbstractMotor::gearset::red,okapi::AbstractMotor::encoderUnits::degrees);
}
namespace Lift{
  okapi::Motor left_mtr(8,false,okapi::AbstractMotor::gearset::red,okapi::AbstractMotor::encoderUnits::degrees);
  okapi::Motor right_mtr(6,true,okapi::AbstractMotor::gearset::red,okapi::AbstractMotor::encoderUnits::degrees);
  okapi::MotorGroup motor = okapi::MotorGroup{left_mtr,right_mtr};
}
namespace Intake{
  okapi::Motor motor(11,false,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
  namespace Auto{
    namespace Balls{
      pros::ADIAnalogIn Puncher(8);
      pros::ADIAnalogIn Over(7);
      pros::ADIAnalogIn Top(6);
      pros::ADIAnalogIn Bottom(5);
    }
  }
}
