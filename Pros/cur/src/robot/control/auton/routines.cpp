#include "robot/control/auton/routines.hpp"
#include "robot/control/auton/selection.hpp"

#include "robot/control/systems/drive.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/puncher.hpp"

namespace auton {
  namespace Drive = drive::auton;
  namespace Intake = intake::automatic;
  namespace Lift = lift;
  namespace Puncher = puncher::auton;
  namespace routines {
    void doubleShotFront() { //remove
      Puncher::fire(true);
      Lift::set_target(Lift::punFront2, Lift::vUp, true);
      int timer = 0;
      while (!Intake::balls::get_puncherActual() && timer < 50) {
        timer++;
        pros::delay(5);
      }
      Puncher::charge(false);
      Puncher::wait();
      lift::wait();

      Puncher::wait();
      pros::delay(200);
      Puncher::fire(true);
      Lift::set_target(Lift::down, Lift::vDown, true);
    }
    void doubelShotBack(double pos1 = 110, double pos2 = Lift::punBack2, int timeDelay = 150) {
      Puncher::charge(false);
      Lift::set_target(pos1, Lift::vUp, true);
      Lift::wait();
      Puncher::fire(true);
      Lift::set_target(pos2);
      int timer = 0;
      while (!Intake::balls::get_puncherActual() && timer < 50) {
        timer++;
        pros::delay(5);
      }
      Puncher::charge(true);
      Lift::wait(timeDelay);
      Puncher::fire(true);
      Puncher::wait(50); //wait for the ball to fully exit the ride
      Lift::set_target(Lift::down, Lift::vDown, true);
    }
    namespace red {
      namespace front {
        void start(selection::Shoots s, selection::Flags f, selection::Options o) { //-2=hold,0=bot,1=top,2=both
          Drive::drive(32, 200, -1);
          Drive::driveAbs(15, 200, 1);

          Puncher::charge(false);
          Drive::turnEnc(-96, 100, 1);

          doubelShotBack(lift::punFront1, lift::punFront2+10, 200);

          Drive::turnEnc(-2, 50);

          Drive::drive(33, 200, -1);
          Drive::driveAbs(37, 200, 1);
        }
        void endShoots(selection::Shoots s, selection::Flags f, selection::Options o) {
          switch (s) {
          case selection::Shoots::FAR:
            break;
          case selection::Shoots::MID:
            Drive::turnEnc(-55, 100, 1);

            Lift::set_target(Lift::down + 10, 50, true);
            Drive::drive(-20, 200, -1);
            Lift::set_target(200, 200, true);
            Drive::driveAbs(-37, 150, 1);
            // Lift::wait(100);
            Lift::set_target(Lift::down, 200, true);

            Puncher::charge();
            Drive::turnEnc(120, 150, 1);
            // Drive::drive(-2, 200, 1);
            doubleShotFront();
            break;
          case selection::Shoots::NONE:
            break;
          };
        }
        void park(selection::Shoots s, selection::Flags f, selection::Options o) {
        }
        void cloFar() {
          // Drive::drive(32,200,0);
          // pros::delay(100);
          // Drive::drive(18,200,1,true);

          Drive::drive(32, 200, 1);
          Drive::drive(-27, 200, 1);

          Puncher::charge(false);
          Drive::turnEnc(-95, 100, 0);
          // Drive::turnEnc(2,50,1)

          // Drive::drive(2,100,0);

          doubleShotFront();

          Intake::disable();
          // Drive::driveS(-2,50,1);
          // Drive::turnEnc(-1, 100, 1);

          // Drive::drive(32,200,1);
          // Drive::drive(-29, 200, 1);

          Drive::turnEnc(-160, 100, 1);
          // Drive::driveS(1.4,100,1);

          Drive::drive(-9, 200, 0);
          Drive::drive(-10, 50, 1);

          // Intake::disable();
          Lift::set_target(lift::up, lift::vScoop, true);
          intake::set_VSetting(-75, true);
          Lift::wait(250);

          Drive::turnEnc(-176, 75, 0);

          Intake::enable();
          // Drive::driveS(-1,50,1);
          Lift::set_target(lift::down, lift::vDown, true);
          Lift::wait();

          doubelShotBack(96, lift::up, true);
        }
        void all(selection::Shoots s, selection::Flags f, selection::Options o) {
          start(s, f, o);
          endShoots(s, f, o);
          park(s, f, o);
        }
      } // namespace front
      namespace back {
        void start(selection::Shoots s, selection::Flags f, selection::Options o) {
          Drive::drive(32, 200, 500);
        }
        void endShoots(selection::Shoots s, selection::Flags f, selection::Options o) {
          switch (s) {
          case selection::Shoots::FAR:
            Drive::driveReconS(-100, 300);
            Drive::driveS(2.5, 100);

            Drive::turnEnc(-67, 50, 1500);

            doubelShotBack(90);

            Drive::drive(-5.5, 200);

            Drive::turnEnc(165, 150);

            Intake::disable();
            Lift::set_target(lift::up, lift::vUp, true);
            Drive::drive(-42, 200);

            Lift::set_target(lift::down, lift::vUp, true);
            break;
          case selection::Shoots::MID:
            Drive::driveReconS(-100, 300);
            Drive::driveS(3, 100);

            Drive::drive(-10, 200, 0, 5, 50000);

            Drive::turnEnc(-80, 100);

            doubelShotBack(90);

            Drive::driveS(9, 200);

            Drive::turnEnc(180, 200, 0, 1);

            Intake::disable();
            Lift::set_target(lift::up, lift::vUp, true);
            Drive::drive(-32, 200);

            Lift::set_target(lift::down, lift::vUp, true);
            break;
          default:
            break;
          }
        }
        void park(selection::Shoots s, selection::Flags f, selection::Options o) {
        }
        void all(selection::Shoots s, selection::Flags f, selection::Options o) {
          start(s, f, o);
          endShoots(s, f, o);
          park(s, f, o);
        }
      } // namespace back
    }   // namespace red
    namespace blue {
      namespace front {
        void start(selection::Shoots s, selection::Flags f, selection::Options o) {
          Drive::drive(32, 200, -1);
          Drive::driveAbs(15, 200, 1);

          Puncher::charge(false);
          Drive::turnEnc(97, 100, 1);

          doubelShotBack(lift::punFront1, lift::punFront2, 150);

          Drive::turnEnc(2, 50);

          Drive::drive(33, 200, -1);
          Drive::driveAbs(34, 200, 1);
        }
        void endShoots(selection::Shoots s, selection::Flags f, selection::Options o) { //-2=hold,0=bot,1=top,2=both
          switch (s) {
          case selection::Shoots::FAR:
            break;
          case selection::Shoots::MID:
            Drive::turnEnc(55, 100, 1);

            Lift::set_target(Lift::down + 10, 50, true);
            Drive::drive(-20, 150, -1);
            Lift::set_target(200, 200, true);
            Drive::driveAbs(-35, 150, 1);
            // Lift::wait(100);
            Lift::set_target(Lift::down, 200, true);

            Puncher::charge();
            Drive::turnEnc(-105, 150, 1);
            Drive::drive(-2, 200, 1);
            doubleShotFront();
            break;

          case selection::Shoots::NONE:

            break;
          }
        }
        void park(selection::Shoots s, selection::Flags f, selection::Options o) {
        }
        void all(selection::Shoots s, selection::Flags f, selection::Options o) {
          start(s, f, o);
          endShoots(s, f, o);
          park(s, f, o);
        }
      } // namespace front
      namespace back {
        void start(selection::Shoots s, selection::Flags f, selection::Options o) {
          Drive::drive(32, 200, 500);
        }
        void endShoots(selection::Shoots s, selection::Flags f, selection::Options o) {
          switch (s) {
          case selection::Shoots::FAR:
            Drive::driveReconS(100, 350);
            Drive::driveS(-2.5, 100);

            Drive::drive(-10, 200, 0, 5, 50000);

            Drive::turnEnc(80, 100);

            doubelShotBack(90);

            Drive::driveS(-9, 200);

            Drive::turnEnc(-180, 200, 0, 1);

            Intake::disable();
            Lift::set_target(lift::up, lift::vUp, true);
            Drive::drive(-32, 200);

            Lift::set_target(lift::down, lift::vUp, true);
            break;
          case selection::Shoots::MID:
            Drive::drive(-10, 200, 0, 5, 50000);

            Drive::turnEnc(80, 100);

            doubelShotBack(90);

            Drive::driveS(-9, 200);

            Drive::turnEnc(-180, 200, 0, 1);

            Intake::disable();
            Lift::set_target(lift::up, lift::vUp, true);
            Drive::drive(-32, 200);

            Lift::set_target(lift::down, lift::vUp, true);
            break;
          default:
            break;
          }
        }
        void park(selection::Shoots s, selection::Flags f, selection::Options o) {
        }
        void all(selection::Shoots s, selection::Flags f, selection::Options o) {
          start(s, f, o);
          endShoots(s, f, o);
          park(s, f, o);
        }
      } // namespace back
    }   // namespace blue
    void skills() {
    }
    void testR() {
      Drive::drive(24, 200, -1);
      Drive::driveAbs(24, 200, 0);
    }
    void testB() {
    }
    void defaultSelection() {}
  } // namespace routines
} // namespace auton