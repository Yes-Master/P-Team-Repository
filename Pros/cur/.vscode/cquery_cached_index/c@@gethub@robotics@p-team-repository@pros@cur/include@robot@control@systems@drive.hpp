#ifndef DRIVE_HPP
#define DRIVE_HPP
#include "main.h"
namespace drive{
  //vars
  enum class Controllers{MANUAL,NONE};
  //vars FUNCTIONS
  // bool get_invert();
  /*
  * inverts the dirve
  */
  void set_inverted(bool i);
  //methods
  okapi::Motor::brakeMode get_brakeMode();
  void set_brakeMode(okapi::Motor::brakeMode b);
  void set_v(int v1,int v2,int v3,int v4);
  void execute();
  namespace feedBack{
    /*
    * rumbles the controller when
    * the drive is not in coast
    */
    void rumble();
  }
  namespace control{
    void manual();
    void hold();
  }
  namespace auton{
    void ramping();//sets drive motors to spin
    bool isSettled();
    void drive(double Dis,int Pct=50,int EndWait=1,int Correction=1);
    void driveRecon(int Pct,int Wait,int EndWait=250);
    void driveS(double Dis,int Pct=50,int EndWait=1,int Correction=1);
    void driveReconS(int Pct,int Wait,int EndWait=1);
    void turnEnc(double deg,int v,int endwait);


    // void drive(double in);
    // void Absolute(double forward, double strafe, double yaw);
    // void AbsolutelyRelative(double forward, double strafe, double yaw);
  }
}
#endif /* end of include guard: DRIVE_HPP */
