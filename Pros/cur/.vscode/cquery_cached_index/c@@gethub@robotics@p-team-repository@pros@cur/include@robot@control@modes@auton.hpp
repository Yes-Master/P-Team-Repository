#ifndef AUTON_HPP
#define AUTON_HPP
namespace Auton{
  extern const int DriveEndWait;
  extern const int TurnEndWait;
  extern const int PuncherEndWait;

  void set_auton(bool b);
  void Task(void* why);

  namespace Routines{

  }
}
#endif /* end of include guard: AUTON_HPP */
