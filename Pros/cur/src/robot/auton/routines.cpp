#include "robot/auton/routines.hpp"
#include "robot/auton/selection.hpp"

#include "robot/control/systems/drive.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/puncher.hpp"

namespace auton{
  namespace drive=drive::auton;
  namespace intake=intake::auto;
  namespace lift=lift;
  namespace puncher=puncher::auton;
  namespace routines{
    void doubleShotFront(){
      puncher::fire(true);
      puncher::charge(false);
      lift::set_target(lift::punFront2,lift::vUp,true);
      puncher::wait();
      lift::wait();
      int timer=0;
      while(!intake::Balls::get_puncherActual() && timer<40){
        timer++;
        pros::delay(5);
      }
      // puncher::wait();
      pros::delay(100);
      puncher::fire(true);
      lift::set_target(lift::down,lift::vDown,true);
    }
    void doubelShotBack(){
      puncher::charge(false);
      lift::set_target(lift::punBack1,lift::vUp,true);
      lift::wait();
      puncher::fire(true);
      puncher::charge(false);
      lift::set_target(lift::punBack2);
      lift::wait();
      int timer=0;
      while(!intake::Balls::get_puncherActual() && timer<40){
        timer++;
        pros::delay(5);
      }
      puncher::wait();
      pros::delay(200);
      puncher::fire(true);
      puncher::wait(50);
      lift::set_target(lift::down,lift::vDown,true);
    }
    namespace Red{
      namespace Front{
        void NorMid(int flag=2){//-2=hold,0=bot,1=top,2=both
          drive::drive(28,200,-1);
          drive::drive(10,50,1);

          drive::drive(-25,200,-1);
          drive::drive(-10,50,1);

          puncher::charge(false);
          drive::turnEnc(-80,100,0);
          // drive::turnEnc(2,50,1)

          drive::drive(2,100,0);

          doubleShotFront();

          // drive::driveS(-2,50,1);
          drive::turnEnc(-2, 100, 1);

          drive::drive(35,200,-1);
          drive::drive(-5, 100, 1);

          drive::turnEnc(-45,100,1);

          drive::drive(-23,200,-1);
          lift::set_target(lift::up, 200, true);
          drive::drive(-5,200,1);
          // lift::wait(200);
          lift::set_target(lift::down, 200, true);

          puncher::charge();
          drive::turnEnc(77, 200, 1);

          doubleShotFront();
        }
        void midBoth()  { NorMid(2);  }
        void midHold()  { NorMid(-2); }
        void midTop()   { NorMid(1);  }
        void midBottom(){ NorMid(0);  }
      }
      namespace Back{
        void farPark(){
          // while(!lift::get_calabrated()){
          //   pros::delay(5);
          // }
          drive::drive(31,200,-1);
          drive::drive(12,50,1);

          puncher::charge();
          drive::turnEnc(-54, 50, 0);

          drive::drive(-3,50,1);
          doubelShotBack();

        }
        void farCap(){

        }
        void farAll(){

        }
        void midCap(){

        }
      }
    }
    namespace Blue{
      namespace Front{
        void NorMid(int flag=2){//-2=hold,0=bot,1=top,2=both//add to a game defs file
          drive::drive(28,200,-1);
          drive::drive(10,50,1);

          drive::drive(-25,200,-1);
          drive::drive(-10,50,1);

          puncher::charge(false);
          drive::turnEnc(85,100,0);
          // drive::turnEnc(2,50,1)

          drive::drive(3,50,0);

          doubleShotFront();

          // drive::driveS(-2,50,1);
          drive::turnEnc(2, 50, 1);

          drive::drive(35,200,-1);
          drive::drive(-5, 100, 1);

          drive::turnEnc(45,100,1);

          drive::drive(-25,200,-1);
          lift::set_target(lift::up, 200, true);
          drive::drive(-5,100,1);
          // lift::wait(200);
          lift::set_target(lift::down, 200, true);

          puncher::charge();
          drive::turnEnc(-80, 200, 1);

          doubleShotFront();
        }
        void midBoth()  { NorMid(2);  }
        void midHold()  { NorMid(-2); }
        void midTop()   { NorMid(1);  }
        void midBottom(){ NorMid(0);  }
      }
      namespace Back{
        void farPark(){

        }
        void farCap(){

        }
        void farAll(){

        }
        void midCap(){

        }
      }
    }
    void skills(){
      drive::drive(28,200,-1);
      drive::drive(10,50,1);

      drive::drive(-24,200,-1);
      drive::drive(-10,50,1);

      drive::turnEnc(-85, 100, 1);

      drive::drive(35, 200, -1);
      puncher::charge(false);
      drive::drive(10, 100, 1);

      doubleShotFront();

      drive::turnEnc(-3, 50, 1);

      drive::drive(35,200,-1);
      drive::drive(-20, 200, 1);

      drive::driveReconS(-200,750);

      drive::driveS(3,100,1);

      drive::turnEnc(85, 100, 1);

      drive::drive(40,200,-1);
      intake::disable();
      drive::drive(20,50,-1);
      intake::enable();
      drive::drive(-5,100,1);

      drive::driveReconS(200, 500);

      drive::driveS(-5,100);

      drive::turnEnc(-85, 100,1);

      puncher::charge(false);
      // drive::drive(10,100,1);

      doubleShotFront();

      drive::turnEnc(85,100,1);

      drive::driveReconS(200,500);

      drive::driveS(-2,100);

      drive::drive(-25,200,1);

      drive::driveS(13,200,1);
      //
      drive::driveRecon(200,2250);
      //
      // drive::drive(-10,100,1);
      //
      // drive::drive(90,200,1);
    }
    void testR(){

    }
    void testB(){

    }
    void defaultSelection(){  Red::Back::farPark();  }
  }
}
