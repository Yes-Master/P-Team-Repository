#ifndef DRIVE_HPP
#define DRIVE_HPP
#include "main.h"
int SGN(double var);
namespace drive {
  // vars
  enum class Controllers {
    MANUAL,
    NONE
  };
  // vars FUNCTIONS
  bool get_inverted();
  void set_inverted(bool i);
  // methods
  okapi::Motor::brakeMode get_brakeMode();
  void set_brakeMode(okapi::Motor::brakeMode b);
  void set_v(int v1, int v2, int v3, int v4);
  void execute();
  namespace feedback {
    /*
    * rumbles the controller when
    * the drive is not in coast
    */
    void rumble();
  } // namespace feedback
  namespace control {
    void manual();
    void hold();
    void dir();
  } // namespace control
  namespace auton {
    //add to namespace ramping
    void ramping();         // sets drive motors to spin
    void DIN(int l, int r); // drive instentaniouly
    void DIS(int l, int r); // drive instentaniouly
    //end namespace ramping

    bool isSettled(double v = 0);
    /*
    * v < -1 junction
    * v >= 0 normal end wait
    */
    void wait(int endWait = 0, double vSettled = 0, int timeout = 250);
    /*
    * drive with out tareing motors position
    * use after drive for smooth precise direction reverse
    */
    void driveAbs(int tar, int vel, int endWait, double vSettled = 0,int timeout = 250);
    /*
    * does not take into acount velocitys ramp down
    * assumes velocity vStart = vEnd = 0
    * abs mode needs to be moved to new function
    */
    void drive(double tar, int vel, int endWait = 0, double vSettled = 0, int timeout = 250);
    void driveRecon(int Pct, int Wait, int endWait = 0, double vSettled = 0, int timeout = 250);
    void driveS(double tar, int vel, int EndWait = 0, double vSettled = 0, int timeout = 250);
    void driveReconS(int Pct, int Wait, int EndWait = 0, double vSettled = 0, int timeout = 250);
    void turnEnc(double deg, int v, int endWait = 0, double vSettled = 0, int timeout = 250);
  } // namespace auton
} // namespace drive
#endif /* end of include guard: DRIVE_HPP */
