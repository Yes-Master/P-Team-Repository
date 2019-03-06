#include "robot/auton/routines.hpp"

#include "robot/control/systems/drive.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/puncher.hpp"

namespace Auton{
  namespace Routines{
    void doubleShotFront(void* why){
      Puncher::Auton::fire();
        if(!Puncher::get_doubleShot())  return;
      Puncher::Auton::charge();
        if(!Puncher::get_doubleShot())  return;
      Lift::set_target(Lift::UpPun,Lift::VMove);
        if(!Puncher::get_doubleShot())  return;
      while(!Puncher::Motor.isStopped()){
        pros::delay(5);
      }
        if(!Puncher::get_doubleShot())  return;
      while(!Lift::Motor.isStopped()){//wait for lift to stop moving
        pros::delay(5);
      }
      while(!Intake::Auto::Balls::get_puncherActual()){
        pros::delay(5);
      }
        if(!Puncher::get_doubleShot())  return;
      Puncher::Auton::fire();
        if(!Puncher::get_doubleShot())  return;
      Lift::set_target(Lift::Down,Lift::VMove);
    }
  }
}
