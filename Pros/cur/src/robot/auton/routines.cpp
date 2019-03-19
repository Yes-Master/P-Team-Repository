#include "robot/auton/routines.hpp"

#include "robot/control/systems/drive.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/puncher.hpp"

namespace Auton{
  namespace drive=Drive::Auton;
  namespace intake=Intake::Auto;
  namespace lift=Lift;
  namespace puncher=Puncher::Auton;

  namespace Routines{
    void doubleShotFront(){
      puncher::fire(true);
      puncher::charge(false);
      lift::set_target(Lift::UpPun,Lift::VMove,true);
      puncher::wait();
      lift::wait();
      while(!intake::Balls::get_puncherActual()){
        pros::delay(5);
      }
      pros::delay(50);
      puncher::fire(true);
      lift::set_target(lift::Down,lift::VMove,true);
    }
    void doubelShotBack();
    namespace Red{
      namespace Front{
        void normal(bool park=false){}
        void norMid(int flag=2){//0=bot,1=top,2=both//add to a game defs file
          drive::Drive(29,200,-1);
          drive::Drive(3,100,1);


          drive::Drive(-20,200,1);
          drive::TurnEnc(-90, 100, 1);

          puncher::charge(false);
          drive::Drive(2,25,1);

          doubleShotFront();

          drive::TurnEnc(-2, 100, 1);

          drive::Drive(36,200,0);
          drive::Drive(-4, 100, 1);

          drive::TurnEnc(-45,100,1);

          drive::Drive(-6,200,0);
          lift::set_target(100, 200, true);
          drive::Drive(-7,200,1);

          lift::set_target(lift::Down, 200, true);

          puncher::charge();
          drive::TurnEnc(84, 200, 1);

          doubleShotFront();
        }
      }
      namespace Back{

      }
    }
    namespace Blue{
      namespace Front{

      }
      namespace Back{

      }
    }
    void frontRed(){
    }
    void execute(){
      frontRed();
    }

  }
}
