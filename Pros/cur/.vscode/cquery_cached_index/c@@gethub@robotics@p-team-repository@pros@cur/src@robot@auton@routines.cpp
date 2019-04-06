#include "robot/auton/routines.hpp"
#include "robot/auton/selection.hpp"

#include "robot/control/systems/drive.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/puncher.hpp"

namespace auton{
  namespace Drive=drive::auton;
  namespace Intake=intake::automatic;
  namespace Lift=lift;
  namespace Puncher=puncher::auton;
  namespace routines{
    void doubleShotFront(){
      Puncher::fire(true);
      Puncher::charge(false);
      Lift::set_target(Lift::punFront2,Lift::vUp,true);
      Puncher::wait();
      Lift::wait();
      int timer=0;
      while(!Intake::balls::get_puncherActual() && timer<40){
        timer++;
        pros::delay(5);
      }
      // Puncher::wait();
      pros::delay(350);
      Puncher::fire(true);
      Lift::set_target(Lift::down,Lift::vDown,true);
    }
    void doubelShotBack(double pos1=Lift::punBack1,double pos2=Lift::punBack2,int timeDelay=350){
      Puncher::charge(false);
      Lift::set_target(pos1,Lift::vUp,true);
      Lift::wait();
      Puncher::fire(true);
      Puncher::charge(false);
      Lift::set_target(pos2);
      Lift::wait();
      int timer=0;
      while(!Intake::balls::get_puncherActual() && timer<40){
        timer++;
        pros::delay(5);
      }
      Puncher::wait();
      pros::delay(timeDelay);
      Puncher::fire(true);
      Puncher::wait(50);
      Lift::set_target(Lift::down,Lift::vDown,true);
    }
    namespace red{
      namespace front{
        void norMid(int flag=2){//-2=hold,0=bot,1=top,2=both
          Drive::drive(28,200,-1);
          Drive::drive(10,50,1);

          Drive::drive(-25,200,-1);
          Drive::drive(-10,50,1);

          Puncher::charge(false);
          Drive::turnEnc(-80,100,0);
          // Drive::turnEnc(2,50,1)

          Drive::drive(2,100,0);

          doubleShotFront();

          // Drive::driveS(-2,50,1);
          Drive::turnEnc(-2, 100, 1);

          Drive::drive(35,200,-1);
          Drive::drive(-5, 100, 1);

          Drive::turnEnc(-45,100,1);

          Drive::drive(-23,200,-1);
          Lift::set_target(Lift::up, 200, true);
          Drive::drive(-5,200,1);
          // Lift::wait(200);
          Lift::set_target(Lift::down, 200, true);

          Puncher::charge();
          Drive::turnEnc(77, 200, 1);

          doubleShotFront();
        }
        void midBoth()  { norMid(2);  }
        void midHold()  { norMid(-2); }
        void midTop()   { norMid(1);  }
        void midBottom(){ norMid(0);  }
      }
      namespace back{
        void farPark(){
          Drive::drive(31,200,1);
          // Drive::drive(12,50,1);
          Drive::DIS(-50,-50);
          Drive::driveReconS(-200,300,1);

          Drive::driveS(0.25,200,1);

          Drive::drive(-11,200,1);

          Puncher::charge();
          Drive::turnEnc(-80, 150, 0);

          // Puncher::charge();
          // Drive::drive(-1,50,0);

          doubelShotBack(75);

          Drive::turnEnc(-12, 150, 0);

          Drive::drive(-11,200,1);

          Drive::turnEnc(-95, 150, 0);

          Drive::drive(-10,200,-1);
          Drive::drive(-10,50,-1);
          Drive::DIN(0,0);


          Lift::set_target(Lift::up+50,50,true);

          // Drive::turnEnc(10,100,0);
          Drive::driveS(5.5,200,1);

          Lift::wait();

          // if(Lift::CapBump.isPressed()){//cap
          Drive::drive(31,200,-1);
          Intake::disable();
          Drive::driveRecon(100,250,1);
          Lift::set_target(Lift::limitMax-5,Lift::vMove,true);
          Lift::wait(250);

          Intake::enable();
          Drive::drive(-3,200,-1);
          Lift::set_target(Lift::down,Lift::vMove,true);
          // Drive::drive(-2,200,-1);
          Drive::turnEnc(90,200,1);


          // }
          // else{//park

          // }
          // Drive::drive(-5,200,1);
          //
          // Drive::turnEnc(-80,75,0);
          //
          // Drive::drive(-5,200,1);

        }
        void farCap(){

        }
        void farAll(){

        }
        void midCap(){

        }
      }
    }
    namespace blue{
      namespace front{
        void NorMid(int flag=2){//-2=hold,0=bot,1=top,2=both//add to a game defs file
          Drive::drive(28,200,-1);
          Drive::drive(10,50,1);

          Drive::drive(-25,200,-1);
          Drive::drive(-10,50,1);

          Puncher::charge(false);
          Drive::turnEnc(85,100,0);
          // Drive::turnEnc(2,50,1)

          Drive::drive(3,50,0);

          doubleShotFront();

          // Drive::driveS(-2,50,1);
          Drive::turnEnc(2, 50, 1);

          Drive::drive(35,200,-1);
          Drive::drive(-5, 100, 1);

          Drive::turnEnc(45,100,1);

          Drive::drive(-25,200,-1);
          Lift::set_target(Lift::up, 200, true);
          Drive::drive(-5,100,1);
          // Lift::wait(200);
          Lift::set_target(Lift::down, 200, true);

          Puncher::charge();
          Drive::turnEnc(-80, 200, 1);

          doubleShotFront();
        }
        void midBoth()  { NorMid(2);  }
        void midHold()  { NorMid(-2); }
        void midTop()   { NorMid(1);  }
        void midBottom(){ NorMid(0);  }
      }
      namespace back{
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
      Drive::drive(28,200,-1);
      Drive::drive(10,50,1);

      Drive::drive(-24,200,-1);
      Drive::drive(-10,50,1);

      Drive::turnEnc(-85, 100, 1);

      Drive::drive(35, 200, -1);
      Puncher::charge(false);
      Drive::drive(10, 100, 1);

      doubleShotFront();

      Drive::turnEnc(-3, 50, 1);

      Drive::drive(35,200,-1);
      Drive::drive(-20, 200, 1);

      Drive::driveReconS(-200,750);

      Drive::driveS(3,100,1);

      Drive::turnEnc(85, 100, 1);

      Drive::drive(40,200,-1);
      Intake::disable();
      Drive::drive(20,50,-1);
      Intake::enable();
      Drive::drive(-5,100,1);

      Drive::driveReconS(200, 500);

      Drive::driveS(-5,100);

      Drive::turnEnc(-85, 100,1);

      Puncher::charge(false);
      // Drive::drive(10,100,1);

      doubleShotFront();

      Drive::turnEnc(85,100,1);

      Drive::driveReconS(200,500);

      Drive::driveS(-2,100);

      Drive::drive(-25,200,1);

      Drive::driveS(13,200,1);
      //
      Drive::driveRecon(200,2250);
      //
      // Drive::drive(-10,100,1);
      //
      // Drive::drive(90,200,1);
    }
    void testR(){
      Drive::drive(12,50,1);
    }
    void testB(){

    }
    void defaultSelection(){  red::back::farPark();  }
  }
}
