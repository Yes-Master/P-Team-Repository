#ifndef LIFT_HPP
#define LIFT_HPP
#include "main.h"

namespace Lift{
  //vars
  extern const double Down;
  extern const double DownPun;//back
  extern const double UpPun;//front
  extern const double Up;
  extern const double MinLimit;
  extern const double MaxLimit;

  extern const int VMove;
  extern const int VDown;
  extern const int VUpov;
  extern const int VStop;


  enum class Controllers{MANUAL,POSITION,NONE};
  //vars FUNCTIONS
  // double get_target();
  void set_target(double t,bool p);
  void set_target(double t,int v,bool p);
  //methods
  void execute();
  namespace Control{
    void manual();
    void position();
  }
  namespace Auton{
    void wait(int w=0);
  }
}

#endif /* end of include guard: LIFT_HPP */
