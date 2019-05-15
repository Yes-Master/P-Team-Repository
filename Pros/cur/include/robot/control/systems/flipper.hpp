#pragma once
#include "main.h"

namespace flipper {
  //vars
  enum class Controllers { MANUAL,
                           POSITION,
                           CALABRATE,
                           NONE };
  namespace targets {
    extern Target ScoopPlatform;
    extern Target Up;
    extern Target Down;
  } // namespace Targets
  
  //postition
  extern const double down;
  extern const double up;
  extern const double pScoop;
  extern const double limitMin;
  extern const double limitMax;

  //velocity
  extern const int vMove;
  extern const int vStop;
  extern const int vUp;
  extern const int vDown;
  extern const int vPos;
  extern const int vScoop;
  extern const int vCal;

  //vars FUNCTIONS
  // double get_target();
  void set_target(double t);
  void set_target(double t, bool p);
  void set_target(double t, int v, bool p);
  void set_target(Target t, bool p = true);
  bool get_calabrated();
  //methods
  void execute(int CalTimOut = 20);
  namespace feedback {
    /*
    * rumbles master_controller
    * when a cap is first inserted
    */
    void rumble();
  } // namespace feedback
  namespace control {
    void manual();
    void position();
    void calabrate();
  } // namespace control
  inline namespace auton {
    void wait(int w = 0);
  }
} // namespace flipper