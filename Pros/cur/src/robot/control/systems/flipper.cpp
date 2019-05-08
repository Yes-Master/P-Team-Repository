#include "robot/control/systems/flipper.hpp"
#include "robot/control/systems/lift.hpp"
namespace flipper {
  //vars
  Controllers controller = Controllers::NONE;

  //position
  const double up = 70;         //all the way up and in
  const double pLift = 130;     //positon for when the lift is up
  const double pScoop = 305;    //position to scoop the balls off a cap
  const double down = 375;      //at ground//375
                                // NOTE: only stops velocity requests, not built in position or voltage
                                // limit vars are only relocated here to keep all position configuration in one place;
  const double limitMin = up;   //min pos where motor stops spinning via velocity;
  const double limitMax = down; //max pos where motor stops spinning via velocity;
  double P = down;              //position setting; used for storage and sync

  //velocity
  const int vMove = 100;        //rpm of the motor; here to help remember rpm
                                //NOTE: all velocitys sould be dependent on vMove
  const int vStop = 0;          //stoping vlocity
  const int vUp = vMove;        //velocity when moving up
  const int vDown = -vMove;     //velocity when moving down
  const int vPos = vMove / 2;   //velocity when moving via position
  const int vScoop = vMove / 4; //velcoity when moving for Scoop
  const int vCal = -vMove / 2;  //velcoity when calibrating
  int V = vStop;                //velocity setting; used for storage and sync

  //calabrate
  const int calabrateTimeOut = 400; //how long the system hits the endstop
  bool Calabrated = false;          //tracks if the systems encoder is accurate

  //vars FUNCTIONS
  Controllers get_controller() {
    return controller;
  }
  void set_controller(Controllers c) {
    controller = c;
  }
  int get_v() {
    return V;
  }
  void set_v(int v) {
    V = v;
  }
  double get_target() {
    return P;
  }
  void set_target(double t) {
    P = t;
  }
  void set_target(double t, bool p) {
    P = t;
    if (p) set_controller(Controllers::POSITION);
  }
  void set_target(double t, int v) {
    set_target(t);
    set_v(v);
  }
  void set_target(double t, int v, bool p) {
    set_target(t);
    set_v(v);
    if (p) set_controller(Controllers::POSITION);
  }
  bool get_calabrated() {
    return Calabrated;
  }
  //methods
  void positionChanger(int v = vMove) {
    if (get_target() == up) {
      set_target(down, -vPos, true);
    } else if (get_target() == down) {
      set_target(up, vPos, true);
    } else if (get_target() == pLift) {
      set_target(down, vMove, true);
    } else {
      set_target(up, vUp, true);
    }
  }

  void calabrate() {
    static const int start = pros::millis(); //get cur time
    if (pros::millis() > start + calabrateTimeOut) {
      motor.moveVelocity(0);
      motor.tarePosition();
      Calabrated = true;
      set_target(up, vMove, true);
      motor.setLimitPositons(limitMin, limitMax);
    } else {
      motor.moveVelocity(vCal);
    }
  }

  void execute(int CalTimOut) {
    if (!Calabrated) {
      calabrate();
    } else {
      if (get_target() == up && lift::get_positon() > lift::pFlipper + 5) { //tol of 5 total tol of +- 10 deg
        set_target(pLift, vMove, true);
      } else if (get_target() == pLift && lift::get_positon() < lift::pFlipper - 5) {
        set_target(up, vMove, true);
      }
      switch (get_controller()) {
      case Controllers::MANUAL:
        motor.moveVelocity(get_v());
        break;
      case Controllers::POSITION:
        motor.moveAbsolute(get_target(), get_v());
        break;
      case Controllers::CALABRATE:
        motor.moveVelocity(vCal);
        break;
      case Controllers::NONE:
        motor.moveVelocity(vStop); //stop the motor
        break;
      };
    }
  }
  namespace feedback {
  } // namespace feedback
  namespace control {
    // void manual() {
    //   if (btnDown.isPressed()) {
    //     set_controller(Controllers::MANUAL);
    //     set_v(vDown);
    //   } else if (btnUp.isPressed()) {
    //     set_controller(Controllers::MANUAL);
    //     set_v(vUp);
    //   } else if (get_controller() == Controllers::MANUAL) { //deinti
    //     set_controller(Controllers::NONE);
    //     set_v(0);
    //   }
    // }
    void position() {
      if (btnPosTog.changed()) {
        if (btnPosTog.isPressed()) { //init
          // set_controller(Controllers::POSITION);
          positionChanger();
        } else { //deInit
        }
      } else if (btnPosTog.isPressed()) { //hold

      } else {
      }
    }
    void calabrate() {
      if (btnCal.changed()) {
        if (btnCal.isPressed()) { //init
          set_controller(Controllers::CALABRATE);
          motor.setLimitPositionDisabled();
          set_v(vCal);
        } else { //deInit
          motor.tarePosition();
          motor.setLimitPositionsEnabled();
          set_target(down, vMove, true);
        }
      } else if (btnCal.isPressed()) { //hold

      } else {
      }
    }
  } // namespace control
  inline namespace auton {
    void wait(int w) {
      while (std::abs(motor.getPosition() - get_target()) > 2) {
        pros::delay(5);
      }
      pros::delay(w);
    }
  } // namespace auton
} // namespace flipper
