#include "robot/config/motor_config.hpp"
#include "custom/ramping.hpp"
// #include "custom/mecanum_drive.hpp"
namespace Drive{
  okapi::Motor front_left_motor(9,false,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
  okapi::Motor front_right_motor(1,true,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
  okapi::Motor back_left_motor(7,false,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
  okapi::Motor back_right_motor(10,true,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
  // MecanumDrive Chassis(
  //   front_left_motor,
  //   back_left_motor,
  //   front_right_motor,
  //   back_right_motor,
  //   4*M_PI,11.5,8);

  Ramping LeftN (2,5,200);
  Ramping RightN(2,5,200);
  Ramping LeftS (2,5,200);
  Ramping RightS(2,5,200);
}
namespace Puncher{
  okapi::Motor motor(20,false,okapi::AbstractMotor::gearset::red,okapi::AbstractMotor::encoderUnits::degrees);
}
namespace Lift{
  okapi::Motor left_mtr(8,false,okapi::AbstractMotor::gearset::red,okapi::AbstractMotor::encoderUnits::degrees);
  okapi::Motor right_mtr(6,true,okapi::AbstractMotor::gearset::red,okapi::AbstractMotor::encoderUnits::degrees);
  // std::vector<okapi::Motor> motors = {left_mtr,right_mtr};
  okapi::MotorGroup motor({right_mtr,left_mtr});
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
