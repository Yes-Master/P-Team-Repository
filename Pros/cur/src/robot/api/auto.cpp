#include "robot/api/auto.hpp"
#include "robot/control/auton/routines.hpp"
#include "robot/control/auton/selection.hpp"

#include "robot/api/init.hpp"
#include "robot/control/modes/auton.hpp"

#include "robot/control/systems/drive.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/puncher.hpp"

#include "main.h"
namespace auton {
  pros::Task autonTask(::auton::Task, (void *)"test", TASK_PRIORITY_DEFAULT,
                       TASK_STACK_DEPTH_DEFAULT, "AutonTask");
}

void autonomous() {
  // puncher::motor.tarePosition();
  systemInit();
  auton::set_auton(true);
  auton::autonTask.resume();

  drive::set_brakeMode(okapi::Motor::brakeMode::hold);
  // intake::automatic::enable();
  // auton::selection::execute();

  intake::automatic::disable();

  double slowDis = 0;
  double tar = 12;
  double totalDeg = tar * 360 / (4 * 3.14);
  int loop = 0;

  while (1) {
    int direction = SGN(tar - drive::back_left_motor.getPosition());
    int velocity = std::abs(200) * direction;
    if (direction > 0) {
      std::uint32_t loopStartTime = pros::millis();
      while (drive::back_left_motor.getPosition() < totalDeg - slowDis - 70) {
        drive::FL.calculate(velocity);
        drive::FR.calculate(velocity);
        drive::BL.calculate(velocity);
        drive::BR.calculate(velocity);
        pros::Task::delay_until(&loopStartTime, drive::FL.get_changeMsec());
        slowDis = drive::FL.triDistance(); //assumes all wheels are at the same velocity; needs to move to class
        std::cout << "velocity: " << velocity << " ouput: " << drive::FL.output() << std::endl;
        std::cout << "SD: " << slowDis << " TD: " << totalDeg << " MD: " << drive::back_left_motor.getPosition() << " LD: " << totalDeg - slowDis << std::endl;
        std::cout << "error: " << drive::back_left_motor.getPosition() - totalDeg << " loop: " << loop << std::endl;
        loop++;
      }
    } else {
      std::uint32_t loopStartTime = pros::millis();
      while (drive::back_left_motor.getPosition() > totalDeg - slowDis - 70) {
        drive::FL.calculate(velocity);
        drive::FR.calculate(velocity);
        drive::BL.calculate(velocity);
        drive::BR.calculate(velocity);
        pros::Task::delay_until(&loopStartTime, drive::FL.get_changeMsec());
        slowDis = drive::FL.triDistance(); //assumes all wheels are at the same velocity; needs to move to class
        std::cout << "velocity: " << velocity << " ouput: " << drive::FL.output() << std::endl;
        std::cout << "SD: " << slowDis << " TD: " << totalDeg << " MD: " << drive::back_left_motor.getPosition() << " LD: " << totalDeg - slowDis << std::endl;
        std::cout << "error: " << drive::back_left_motor.getPosition() - totalDeg << " loop: " << loop << std::endl;
        loop++;
      }
    }
  }
}
