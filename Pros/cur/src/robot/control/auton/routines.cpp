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
    void doubleShotBack(double pos1 = 110, double pos2 = Lift::punBack2, int timeDelay = 150) {
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
    void multiFlagSelect(double top, double mid, int time, selection::Flags f) {
      switch (f) {
      case selection::Flags::BOTH:
        doubleShotBack(top, mid, time);
        break;
      case selection::Flags::TOP:
        Puncher::charge(false);
        Lift::set_target(top, Lift::vUp, true);
        Lift::wait();
        Puncher::fire(true);
        Lift::set_target(lift::down);
        break;
      case selection::Flags::MID:
        Puncher::charge(false);
        Lift::set_target(mid, Lift::vUp, true);
        Lift::wait();
        Puncher::fire(true);
        Lift::set_target(lift::down);
        break;
      case selection::Flags::HOLD:
        lift::set_target(lift::down, 200, true);
        break;
      case selection::Flags::NONE:
        break;
      };
    }
    namespace red {
      namespace front {
        void start(selection::Shoots s, selection::Flags f, selection::Options o) { //-2=hold,0=bot,1=top,2=both
          Drive::drive(32, 200, -1);
          Drive::driveAbs(16, 200, 1);

          Puncher::charge(false);
          Drive::turnEnc(-97, 150, 1);

          doubleShotBack(lift::punFront1, lift::punFront2 + 40, 150);

          Drive::drive(33, 200, -1);
          Drive::driveAbs(35, 200, 0);
        }
        void endShoots(selection::Shoots s, selection::Flags f, selection::Options o) {
          switch (s) {
          case selection::Shoots::FAR:
            Drive::turnEnc(-55, 150);

            // Lift::set_target(Lift::down + 10, 50, true);
            Drive::drive(-25, 200, -1);
            Drive::driveAbs(-30, 100, -1);
            Lift::set_target(200, 50, true);
            Drive::driveAbs(-32, 200, 1);
            // Lift::wait(100);
            // Lift::set_target(Lift::down, 200, true);
            Puncher::charge();
            Drive::turnEnc(134, 150);

            switch (o) { //par
            case selection::Options::PARK:
              multiFlagSelect(75, 160, 150, f);

              Drive::driveS(8, 200);

              Drive::turnEnc(-75, 200);

              Lift::set_target(lift::up, 200, true);
              Drive::drive(-25, 200);
              break;
            case selection::Options::NPARK:
              lift::set_target(lift::down, 200, true);
              pros::delay(2500);
              multiFlagSelect(75, 160, 150, f);
              break;
            case selection::Options::NONE:
              break;
            };
            break;
          case selection::Shoots::MID:
            Drive::turnEnc(-55, 100, 1);

            Drive::drive(-15, 200, -1);
            // Drive::driveAbs(-22, 100, -1);
            Lift::set_target(200, 200, true);
            Drive::driveAbs(-20, 150, 1);
            // Lift::wait(100);
            // Lift::set_target(Lift::down, 200, true);

            if (f != selection::Flags::NONE) { Puncher::charge(); } //if not shooting any flags dont charge
            Drive::turnEnc(117, 150, 1);
            // Drive::drive(-2, 200, 1);
            switch (o) { //par
            case selection::Options::PARK:
              multiFlagSelect(lift::down, 140, 150, f);

              Drive::driveS(15, 200);

              Drive::turnEnc(-60, 200);

              Lift::set_target(lift::up, 200, true);
              Drive::drive(-30, 200);
              break;
            case selection::Options::NPARK:
              lift::set_target(lift::down, 200, true);
              pros::delay(2500);
              multiFlagSelect(lift::down, 140, 150, f);
              break;
            case selection::Options::NONE:
              break;
            };
            break;
          case selection::Shoots::NONE:
            break;
          };
        }
        void all(selection::Shoots s, selection::Flags f, selection::Options o) {
          start(s, f, o);
          endShoots(s, f, o);
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

            Drive::turnEnc(-68, 50, 2500);

            switch (o) {
            case selection::Options::PARK:
              multiFlagSelect(125, 220, 150, f);

              Drive::drive(-4, 200);

              Drive::turnEnc(165, 150);

              Intake::disable();
              Lift::set_target(lift::up, lift::vUp, true);
              Drive::drive(-42, 200);

              Lift::set_target(lift::down, lift::vUp, true);
              break;
            case selection::Options::NPARK:
              pros::delay(2500);
              multiFlagSelect(125, 220, 150, f);
              break;
            case selection::Options::NONE:
              break;
            };

            break;
          case selection::Shoots::MID:
            Drive::driveReconS(-100, 300);
            Drive::driveS(3, 150);

            Drive::drive(-5, 200);

            Drive::turnEnc(-89, 150);
            switch (o) {
            case selection::Options::PARK:
              multiFlagSelect(115, 180, 150, f);

              Drive::driveS(2, 200);

              Drive::turnEnc(180, 200, 0, 1);

              Intake::disable();
              Lift::set_target(lift::up, lift::vUp, true);
              Drive::drive(-35, 200);

              Lift::set_target(lift::down, lift::vUp, true);
              break;
            case selection::Options::NPARK:
              pros::delay(2500);
              multiFlagSelect(115, 180, 150, f);
              break;
            case selection::Options::NONE:
              break;
            };
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
          Drive::driveAbs(16, 200, 1);

          Puncher::charge(false);
          Drive::turnEnc(99, 100, 1);

          doubleShotBack(lift::down, 170, 150);

          // Drive::turnEnc(2, 50);

          Drive::drive(33, 200, -1);
          Drive::driveAbs(34, 200, 1);
        }
        void endShoots(selection::Shoots s, selection::Flags f, selection::Options o) { //-2=hold,0=bot,1=top,2=both
          switch (s) {
          case selection::Shoots::FAR:
            Drive::turnEnc(55, 150);

            // Lift::set_target(Lift::down + 10, 50, true);
            Drive::drive(-20, 200, -1);
            Drive::driveAbs(-25, 100, -1);
            Lift::set_target(200, 50, true);
            Drive::driveAbs(-28, 200, 1);
            // Lift::wait(100);
            // Lift::set_target(Lift::down, 200, true);
            Puncher::charge();
            Drive::turnEnc(-138, 150);

            switch (o) { //par
            case selection::Options::PARK:
              lift::set_target(lift::down, 200, true);
              Lift::wait(50);
              multiFlagSelect(85, 220, 150, f);

              Drive::driveS(-11, 200);

              Drive::turnEnc(73, 200);

              Lift::set_target(lift::up, 200, true);
              Intake::disable();
              Drive::drive(-28, 200);
              Lift::set_target(lift::down, 200, true);
              break;
            case selection::Options::NPARK:
              lift::set_target(lift::down, 200, true);
              Lift::wait(2500);
              multiFlagSelect(75, 160, 150, f);
              break;
            case selection::Options::NONE:
              break;
            };
            break;
          case selection::Shoots::MID:
            Drive::turnEnc(55, 100, 1);

            // Lift::set_target(Lift::down + 10, 50, true);
            Drive::drive(-20, 150, -1);
            Lift::set_target(200, 200, true);
            Drive::driveAbs(-30, 150, 1);
            // Lift::wait(100);
            Lift::set_target(Lift::down, 200, true);

            if (f != selection::Flags::NONE) Puncher::charge(); //only charge if going to shoot
            Drive::turnEnc(-115, 150, 1);
            switch (o) {
            case selection::Options::PARK:
              lift::set_target(lift::down, 200, true);
              Lift::wait(50);
              multiFlagSelect(50, 150, 150, f);

              Drive::driveS(-11, 200);

              Drive::turnEnc(55, 200);

              Lift::set_target(lift::up, 200, true);
              Intake::disable();
              Drive::drive(-30, 200);
              Lift::set_target(lift::down, 200, true);
              break;
            case selection::Options::NPARK:
              lift::set_target(lift::down, 200, true);
              Lift::wait(2500);
              multiFlagSelect(50, 150, 150, f);
              break;
            case selection::Options::NONE:
              break;
            };
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

            if (f != selection::Flags::NONE) Puncher::charge(); //only charge if going to shoot
            Drive::turnEnc(80, 100);

            switch (o) {
            case selection::Options::PARK:
              multiFlagSelect(90, 170, 150, f);

              Drive::driveS(-9, 200);

              Drive::turnEnc(-180, 200, 0, 1);

              Intake::disable();
              Lift::set_target(lift::up, lift::vUp, true);
              Drive::drive(-32, 200);

              Lift::set_target(lift::down, lift::vUp, true);
              break;
            case selection::Options::NPARK:
              pros::delay(2500);
              multiFlagSelect(90, 170, 150, f);
              break;
            case selection::Options::NONE:
              break;
            };
            break;
          case selection::Shoots::MID:
            Drive::drive(-10, 200, 0, 5, 50000);

            if (f != selection::Flags::NONE) Puncher::charge(); //charge if going to shoot
            Drive::turnEnc(80, 100);

            switch (o) {
            case selection::Options::PARK:
              multiFlagSelect(90, 170, 150, f);

              Drive::driveS(-9, 200);

              Drive::turnEnc(-180, 200, 0, 1);

              Intake::disable();
              Lift::set_target(lift::up, lift::vUp, true);
              Drive::drive(-32, 200);

              Lift::set_target(lift::down, lift::vUp, true);
              break;
            case selection::Options::NPARK:
              pros::delay(2500);
              multiFlagSelect(90, 170, 150, f);
              break;
            case selection::Options::NONE:
              break;
            };
            break;
          default:
            break;
          }
        }
        void all(selection::Shoots s, selection::Flags f, selection::Options o) {
          start(s, f, o);
          endShoots(s, f, o);
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