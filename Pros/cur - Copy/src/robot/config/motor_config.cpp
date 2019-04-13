// #include "robot/config/motor_config.hpp"
// #include "custom/ramping.hpp"
// // #include "custom/mecanum_drive.hpp"
// namespace drive{
//   okapi::Motor front_left_motor(12,false,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
//   okapi::Motor front_right_motor(13,true,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
//   okapi::Motor back_left_motor(19,false,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
//   okapi::Motor back_right_motor(20,true,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
//   // MecanumDrive Chassis(
//   //   front_left_motor,
//   //   back_left_motor,
//   //   front_right_motor,
//   //   back_right_motor,
//   //   4*M_PI,11.5,8);
//
//   Ramping LeftN (2,5,200);
//   Ramping RightN(2,5,200);
//   Ramping LeftS (2,5,200);
//   Ramping RightS(2,5,200);
// }
// namespace puncher{
//   okapi::Motor motor(17,false,okapi::AbstractMotor::gearset::red,okapi::AbstractMotor::encoderUnits::degrees);
// }
// namespace lift{
//   okapi::Motor motor(16,true,okapi::AbstractMotor::gearset::red,okapi::AbstractMotor::encoderUnits::degrees);
//   // okapi::Motor right_mtr(6,true,okapi::AbstractMotor::gearset::red,okapi::AbstractMotor::encoderUnits::degrees);
//   // // std::vector<okapi::Motor> motors = {left_mtr,right_mtr};
//   // okapi::MotorGroup motor({right_mtr,left_mtr});
// }
// namespace intake{
//   okapi::Motor motor(18,true,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
//   namespace Auto{
//     namespace Balls{
//       pros::ADIAnalogIn Puncher(1);
//       pros::ADIAnalogIn Over(2);
//       pros::ADIAnalogIn Top(3);
//       pros::ADIAnalogIn Bottom(4);
//     }
//   }
// }
// // 9
// 10
#include "robot/config/motor_config.hpp"
#include "custom/ramping.hpp"
// #include "custom/mecanum_drive.hpp"
namespace drive{
  okapi::Motor front_left_motor(12,false,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
  okapi::Motor front_right_motor(13,true,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
  okapi::Motor back_left_motor(19,false,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
  okapi::Motor back_right_motor(20,true,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
  // MecanumDrive Chassis(
  //   front_left_motor,
  //   back_left_motor,
  //   front_right_motor,
  //   back_right_motor,
  //   4*M_PI,11.5,8);
  Ramping LeftN (1.75,5,200,-200);
  Ramping RightN(1.75,5,200,-200);
  Ramping LeftS (1.75,5,200,-200);
  Ramping RightS(1.75,5,200,-200);
}
namespace puncher{
  okapi::Motor motor(17,false,okapi::AbstractMotor::gearset::red,okapi::AbstractMotor::encoderUnits::degrees);
}
namespace lift{
  // okapi::Motor left_mtr(8,false,okapi::AbstractMotor::gearset::red,okapi::AbstractMotor::encoderUnits::degrees);
  okapi::Motor motor(16,true,okapi::AbstractMotor::gearset::red,okapi::AbstractMotor::encoderUnits::degrees);
  // std::vector<okapi::Motor> motors = {left_mtr,right_mtr};
  // okapi::MotorGroup motor({right_mtr,left_mtr});
  okapi::ADIButton CapBump(8,false);
}
namespace intake{
  okapi::Motor motor(18,false,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
  namespace automatic{
    namespace balls{
      pros::ADIAnalogIn puncher(1);
      pros::ADIAnalogIn over(2);
      pros::ADIAnalogIn top(3);
      pros::ADIAnalogIn bottom(4);
    }
  }
}
