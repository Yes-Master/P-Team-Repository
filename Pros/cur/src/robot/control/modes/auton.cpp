#include "robot/control/modes/auton.hpp"

#include "robot/control/systems/drive.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/flipper.hpp"
#include "robot/control/systems/puncher.hpp"
// DriveEndWait=0;
// TurnEndWait=0;
// PuncherEndWait=0;
namespace auton {
  bool inAuton = false;
  void set_auton(bool b) {
    inAuton = b;
  }
  void Task(void *why) {
    std::uint32_t test = pros::millis(); //init delay
    int beg=pros::millis();
    while (1) {
      if (inAuton) {
        drive::auton::ramping();
        puncher::execute();

        intake::execute();
        lift::execute(80);
        flipper::execute();
      }
      // std::cout << "T: "<< (pros::millis()-beg)/5 <<" BLv: " << drive::back_left_motor.get_actual_velocity() << std::endl;
      pros::Task::delay_until(&test, 5); //delay for 5 millis exact
    }
  }
} // namespace auton
