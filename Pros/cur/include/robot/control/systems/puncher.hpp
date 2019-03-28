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
  namespace OnOffCon{
    bool get_run();
  }
  namespace Control{
    void charge();
    void doubleBack();
    void doubleFront();
  }
  namespace Auton{
    void wait(int w=0);
    void charge(bool w=false);
    void fire(bool w=true);
  }
}
#endif /* end of include guard: PUNCHER_HPP */
