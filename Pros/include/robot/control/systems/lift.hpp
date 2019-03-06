#ifndef LIFT_HPP
#define LIFT_HPP
#include "main.h"

namespace Lift{
  //vars
  extern const int Down;
  extern const int DownPun;//back
  extern const int UpPun;//front
  extern const int Up;

  extern const int VMove;
  extern const int VDown;
  extern const int VUpov;
  extern const int VStop;


  enum class Controllers{MANUAL,POSITION,NONE};
  //vars FUNCTIONS
  // double get_target();
  void set_target(int t);
  void set_target(int t,int v);
  //methods
  void execute();
  namespace Control{
    void manual();
    void position();
  }
}

#endif /* end of include guard: LIFT_HPP */
