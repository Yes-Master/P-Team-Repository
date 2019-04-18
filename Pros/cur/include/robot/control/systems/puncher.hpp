#ifndef PUNCHER_HPP
#define PUNCHER_HPP
#include "main.h"
#include "robot/control/systems/lift.hpp"
namespace puncher {
  //vars
  enum class Controllers { POSITION,
                           NONE };

  extern const int VMove;
  extern const int VStop;
  //vars FUNCTIONS
  bool get_doubleShot();
  bool get_charged();
  //methods
  void execute();
  namespace OnOffCon {
    bool get_run();
  }
  namespace control {
    void charge();
    void doubleBack();
    void backTop();
    void backMid();
  }  // namespace control
  namespace auton {
    void wait(int w = 0);
    void charge(bool w = false);
    void fire(bool w = true);
    void fire(double shootPos, double endPos = lift::down, bool endCharged = false, bool intakeEnable = true, int vLift = lift::vMove);
  }  // namespace auton
}  // namespace puncher
#endif /* end of include guard: PUNCHER_HPP */
