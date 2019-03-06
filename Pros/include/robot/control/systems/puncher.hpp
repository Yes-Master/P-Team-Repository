#ifndef PUNCHER_HPP
#define PUNCHER_HPP
#include "main.h"
namespace Puncher{
  //vars
  enum class Controllers{POSITION,NONE};

  extern const int VMove;
  extern const int VStop;
  //vars FUNCTIONS
  bool get_doubleShot();
  bool get_charged();
  //methods
  void execute();
  namespace Control{
    void charge();
  }
  namespace Auton{
    void charge(bool wait=false);
    void fire(bool wait=true);
  }
}
#endif /* end of include guard: PUNCHER_HPP */
