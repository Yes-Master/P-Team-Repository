#include "robot/control/auton/routines.hpp"
#include "robot/control/auton/selection.hpp"

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
      Lift::set_target(Lift::punFront2,Lift::vUp,true);
      int timer=0;
      while(!Intake::balls::get_puncherActual() && timer<50){
        timer++;
        pros::delay(5);
      }
      Puncher::charge(false);
      Puncher::wait();
      lift::wait();

      // Puncher::wait();
      // pros::delay(350);
      Puncher::fire(true);
      Lift::set_target(Lift::down,Lift::vDown,true);
    }
    void doubelShotBack(double pos1=110,double pos2=Lift::punBack2,int timeDelay=250){
      Puncher::charge(false);
      Lift::set_target(pos1,Lift::vUp,true);
      Lift::wait();
      Puncher::fire(true);
      Lift::set_target(pos2);
      int timer=0;
      while(!Intake::balls::get_puncherActual() && timer<50){
        timer++;
        pros::delay(5);
      }
      Puncher::charge(true);
      Lift::wait(timeDelay);
      Puncher::fire(true);
      Puncher::wait(50); //wait for the ball to fully exit the ride
      Lift::set_target(Lift::down,Lift::vDown,true);
    }
    namespace red{
      namespace front{
        void norMid(int flag=2){//-2=hold,0=bot,1=top,2=both
          Drive::drive(32,200,1);

          Drive::drive(-27,200,1);

          Puncher::charge(false);

          Drive::turnEnc(-96,100,1);

          doubleShotFront();

          // Intake::disable();

          // Drive::driveS(-2,50,1);
          Drive::turnEnc(-2, 50, 1);

          Drive::drive(33,200,1);
          Drive::drive(-3, 150, 1);

          Drive::turnEnc(-55,100,1);

          Lift::set_target(Lift::down+10,50,true);
          Drive::drive(-25,150,-1);
          Lift::set_target(200, 200, true);
          Drive::drive(-5,150,1);
          // Lift::wait(100);
          Lift::set_target(Lift::down, 200, true);

          Puncher::charge();
          Drive::turnEnc(85, 150, 1);
          Drive::drive(-2,200,1);
          doubleShotFront();
        }
        void midBoth()  { norMid(2);  }
        void midHold()  { norMid(-2); }
        void midTop()   { norMid(1);  }
        void midBottom(){ norMid(0);  }
        void cloFar(){
          // Drive::drive(32,200,0);
          // pros::delay(100);
          // Drive::drive(18,200,1,true);

          Drive::drive(32,200,1);
          Drive::drive(-27,200,1);

          Puncher::charge(false);
          Drive::turnEnc(-95,100,0);
          // Drive::turnEnc(2,50,1)

          // Drive::drive(2,100,0);

          doubleShotFront();

          Intake::disable();
          // Drive::driveS(-2,50,1);
          // Drive::turnEnc(-1, 100, 1);

          // Drive::drive(32,200,1);
          // Drive::drive(-29, 200, 1);

          Drive::turnEnc(-160,100,1);
          // Drive::driveS(1.4,100,1);

          Drive::drive(-9,200,0);
          Drive::drive(-10, 50, 1);

          // Intake::disable();
          Lift::set_target(lift::up,lift::vScoop,true);
          intake::set_VSetting(-75,true);
          Lift::wait(250);

          Drive::turnEnc(-176,75,0);
                    
          Intake::enable();
          // Drive::driveS(-1,50,1);
          Lift::set_target(lift::down,lift::vDown,true);
          Lift::wait();

          doubelShotBack(96,lift::up,true);
        }
      }
      namespace back{
        void mid(){

        }
        void farPark(){
          Drive::drive(32,200,500);

          Drive::driveReconS(-100,350,1);
          Drive::driveS(5,50,1);

          Drive::turnEnc(-70,50,1500);

          doubelShotBack(110,150);

          Drive::drive(-5,200,1);

          Drive::turnEnc(150,150,1);

          Intake::disable();
          Lift::set_target(lift::up+50,lift::vUp,true);
          Drive::drive(-35,200,1);
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
          Drive::drive(32,200,1);

          Drive::drive(-27,200,1);

          Puncher::charge(false);

          Drive::turnEnc(96,100,1);

          doubleShotFront();

          // Intake::disable();

          // Drive::driveS(-2,50,1);
          Drive::turnEnc(2, 50, 1);

          Drive::drive(33,200,1);
          Drive::drive(-5, 150, 1);

          Drive::turnEnc(55,100,1);

          Lift::set_target(Lift::down+5);
          Drive::drive(-25,150,-1);
          Lift::set_target(120, 200, true);
          Drive::drive(-5,150,1);
          // Lift::wait(100);
          Lift::set_target(Lift::down, 200, true);

          Puncher::charge();
          Drive::turnEnc(-80, 150, 1);
          Drive::drive(-2,200,1);
          doubleShotFront();
        }
        void midBoth()  { NorMid(2);  }
        void midHold()  { NorMid(-2); }
        void midTop()   { NorMid(1);  }
        void midBottom(){ NorMid(0);  }
        void cloFar(){
                    // Drive::drive(32,200,0);
          // pros::delay(100);
          // Drive::drive(18,200,1,true);

          Drive::drive(32,200,1);
          Drive::drive(-27,200,1);

          Puncher::charge(false);
          Drive::turnEnc(97,25,5000);
          // Drive::turnEnc(2,50,1)

          // Drive::drive(2,100,0);

          doubleShotFront();

          Intake::disable();

        }
      }
      namespace back{
        void farPark(){
          Drive::drive(32,200,500);

          Drive::driveReconS(100,350,1);
          Drive::driveS(-3,50,1);

          Drive::turnEnc(67,50,1500);

          doubelShotBack();

          Drive::drive(-6,200,1);

          Drive::turnEnc(-170,150,1);

          Intake::disable();
          Lift::set_target(lift::up,lift::vUp,true);
          Drive::drive(-40,200,1);
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
    void defaultSelection(){  blue::back::farPark();  }
  }
}
