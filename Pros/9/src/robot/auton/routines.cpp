#include "robot/auton/routines.hpp"

#include "robot/control/systems/drive.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/puncher.hpp"

#include "main.h"
namespace Auton{
  namespace Routines{
    void doubleShotFront(void* test){
      Puncher::Auton::charge(true);
        if(!Puncher::BtnCharge.isPressed())  return;
      Puncher::Auton::fire(true);

        if(!Puncher::BtnCharge.isPressed())  return;
      Puncher::Auton::charge(false);
        // if(!Puncher::BtnCharge.isPressed())  return;
      Lift::set_target(Lift::UpPun,Lift::VMove,true);
        if(!Puncher::BtnCharge.isPressed())  return;
      Puncher::Auton::wait();
        if(!Puncher::BtnCharge.isPressed())  return;
      Lift::Auton::wait();
      while(!Intake::Auto::Balls::get_puncherActual()){
        pros::delay(5);
      }
      pros::delay(50);
        if(!Puncher::BtnCharge.isPressed())  return;
      Puncher::Auton::fire(true);
        if(!Puncher::BtnCharge.isPressed())  return;
      Lift::set_target(Lift::Down,Lift::VMove,true);
    }
    void skills(){

    }
    void defaultSelection(){

    }

    namespace Red{
      namespace Front{
        void midBoth(){}
        void midHold(){}
        void midTop(){}
        void midBottom(){}
      }
    }
    namespace Blue{
      namespace Front{
        void midBoth(){}
        void midHold(){}
        void midTop(){}
        void midBottom(){}
      }
    }

  }
}
