#include "robot/control/systems/drive.hpp"
#include "custom/ramping.hpp"
double SGN(double var) {
  if (var > 0)
    return 1;
  else if (var < 0)
    return -1;
  else
    return 0;
}
namespace drive {
  // vars
  Controllers Controller = Controllers::NONE;
  const float WheelCir = 4 * M_PI;

  bool Inverted = false;
  bool InvertedWas = Inverted;
  // vars FUNCTIONS
  Controllers get_controller() { return Controller; }
  void set_controller(Controllers c) { Controller = c; }
  bool get_inverted() { return Inverted; }
  void set_inverted(bool i) {
    InvertedWas = get_inverted();
    Inverted = i;
  }
  // methods
  okapi::Motor::brakeMode get_brakeMode() {
    return front_left_motor.getBrakeMode();
  }
  void set_brakeMode(okapi::Motor::brakeMode b) {
    front_left_motor.setBrakeMode(b);
    front_right_motor.setBrakeMode(b);
    back_left_motor.setBrakeMode(b);
    back_right_motor.setBrakeMode(b);
  }
  void set_v(int v1, int v2, int v3, int v4) {
    front_left_motor.moveVelocity(v1);
    front_right_motor.moveVelocity(v2);
    back_left_motor.moveVelocity(v3);
    back_right_motor.moveVelocity(v4);
  }
  void tank(int j1, int j2, int j3, int j4) {
    int LF = j1;            // left
    int RF = j2;            // right
    int SD = (j3 + j4) / 2; // average
    if (std::abs(j3) > std::abs(j4))
      SD = j3;
    else
      SD = j4;

    set_v(LF + SD, RF - SD, LF - SD, RF + SD);
  }
  void arcade(int y, int x, int z) {
    set_v(y + x + z, y - x - z, y - x + z, y + x - z);
  }
  void execute() {}
  namespace feedback {
    // vars

    // vars FUNCTIONS

    // methods
    void rumble() {
      static okapi::Timer timer;
      if (get_brakeMode() != okapi::AbstractMotor::brakeMode::coast) {
        using namespace okapi::literals;
        if (timer.repeat(250_ms)) {
          controllerMaster.rumble(".");
        }
      }
    }
  } // namespace feedback
  namespace control {
    void manual() {
      int LHJoy =
          controllerMaster.getAnalog(okapi::ControllerAnalog::leftX) * 200;
      int LVJoy =
          controllerMaster.getAnalog(okapi::ControllerAnalog::leftY) * 200;
      int RVJoy =
          controllerMaster.getAnalog(okapi::ControllerAnalog::rightY) * 200;
      int RHJoy =
          controllerMaster.getAnalog(okapi::ControllerAnalog::rightX) * 200;

      if (std::abs(LVJoy) < 5)
        LVJoy = 0;
      if (std::abs(RVJoy) < 5)
        RVJoy = 0;
      if (std::abs(LHJoy) < 100)
        LHJoy = 0;
      if (std::abs(RHJoy) < 100)
        RHJoy = 0;

      if (LVJoy != 0 || RVJoy != 0 || LHJoy != 0 || RHJoy != 0) {
        set_controller(Controllers::MANUAL);
        tank(get_inverted() ? -RVJoy : LVJoy, get_inverted() ? -LVJoy : RVJoy,
             get_inverted() ? -RHJoy : LHJoy, get_inverted() ? -LHJoy : RHJoy);
      } else {
        if (get_controller() == Controllers::MANUAL) {
          tank(0, 0, 0, 0); // Last loop before disableing; used to release
                            // drivemanualcontrol
          set_controller(Controllers::NONE);
        }
      }
    }
    void hold() {
      if (btnBrake.changed()) {
        if (btnBrake.isPressed()) { // init
          if (get_brakeMode() == okapi::Motor::brakeMode::coast)
            set_brakeMode(okapi::Motor::brakeMode::hold);
          else
            set_brakeMode(okapi::Motor::brakeMode::coast);
        } else { // deinti
        }
      } else if (btnBrake.isPressed()) { // hold
      } else {
      }
    }
    void dir() {
      if (btnDirTog.changed()) {
        if (btnDirTog.isPressed()) { // init
          if (get_inverted() == true)
            set_inverted(false);
          else
            set_inverted(true);
        } else { // deinit
        }
      } else if (btnDirTog.isPressed()) { // hold
      } else {
      }
    }
  } // namespace control
  namespace auton {
    void ramping() { // sets drive motors to spin
      LeftN.calculate();
      RightN.calculate();
      LeftS.calculate();
      RightS.calculate();
      set_v(LeftN.output() + LeftS.output(), RightN.output() - LeftS.output(),
            LeftN.output() - RightS.output(),
            RightN.output() + RightS.output());
    }
    void DRN(int l, int r) { // update the drive ramping requested values
      LeftN.request(l);
      RightN.request(r);
    }
    void DIN(int l, int r) { // drive instentaniouly
      LeftN.instant(l);
      RightN.instant(r);
      set_v(LeftN.output() + LeftS.output(), RightN.output() - LeftS.output(),
            LeftN.output() - RightS.output(),
            RightN.output() + RightS.output());
    }
    void DRS(int l,
             int r) { // update the drive ramping requested valuesttttttt
      LeftS.request(l);
      RightS.request(r);
    }
    void DIS(int l, int r) { // drive instentaniouly
      LeftS.instant(l);
      RightS.instant(r);
      set_v(LeftN.output() + LeftS.output(), RightN.output() - LeftS.output(),
            LeftN.output() - RightS.output(),
            RightN.output() + RightS.output());
    }

    bool isSettled(double v) {
      if (std::abs(front_left_motor.getActualVelocity()) > v)
        return false;
      if (std::abs(back_left_motor.getActualVelocity()) > v)
        return false;
      if (std::abs(front_right_motor.getActualVelocity()) > v)
        return false;
      if (std::abs(back_right_motor.getActualVelocity()) > v)
        return false;
      return true;
    }
    void wait(int endWait, double vSettled, int timeout) {
      if (endWait >= 0) { // default; set stop, wait for stop, wait for endwait;
        DRN(0, 0);
        DRS(0, 0);
        int tStart = pros::millis();
        while (!isSettled(vSettled) && pros::millis() < tStart + timeout) { //wait for the actual velocity to be acceptiable with in the time out window
          pros::delay(5);
        }
        pros::delay(endWait);
      } else { //stop no wait; junction
        DRN(0, 0);
      }
    }

    void driveAbs(int tar, int vel, int endWait, double vSettled, int timeout) { //absolute used to move smothly after normal move not
      double direction;
      double totalDeg = tar * 360 / WheelCir;
      direction = SGN(tar - back_left_motor.getPosition());
      int velocity = std::abs(vel) * direction;
      if (direction > 0) {
        while (back_left_motor.getPosition() < totalDeg) { // max error is 1/30 of an inch;//needs to recalc error
          DRN(velocity, velocity);
          pros::delay(5); // wait for the ramp task to execute, free up PU,wait for distance to be travled;
          // need to sync with ramping task
        }
      } else {
        while (back_left_motor.getPosition() > totalDeg) { // max error is 1/30 of an inch;
          DRN(velocity, velocity);
          pros::delay(5); // wait for the ramp task to execute, free up PU,wait
                          // for distance to be travled;
          // need to sync with ramping task
        }
      }
      wait(endWait, vSettled);
    }
    void drive(double tar, int vel, int endWait, double vSettled, int timeout) {
      double direction = SGN(tar);
      double totalDeg = tar * 360 / WheelCir;
      int velocity = std::abs(vel) * direction;

      back_left_motor.tarePosition();
      while (std::abs(back_left_motor.getPosition()) < std::abs(totalDeg)) { // max error is 1/30 of an inch;
        DRN(velocity, velocity);
        pros::delay(5); // wait for the ramp task to execute, free up PU,wait for distance to be travled;
        // need to sync with ramping task
      }

      wait(endWait, vSettled, timeout);
    }
    void driveRecon(int Pct, int Wait, int endWait, double vSettled, int timeout) {
      DRN(Pct, Pct);
      pros::delay(Wait);
      wait(endWait, vSettled, timeout);
    }
    void driveS(double tar, int vel, int endWait, double vSettled, int timeout) { // assumes velocity start = end = 0
      double direction = SGN(tar);
      double totalDeg = std::abs(tar) * 360 / WheelCir;
      int velocity = std::abs(vel) * direction;

      back_right_motor.tarePosition();
      while (std::abs(back_right_motor.getPosition()) < std::abs(totalDeg)) { // max error is 1/30 of an inch;
        DRS(velocity, velocity);
        pros::delay(5); // wait for the ramp task to execute, free up PU,wait for distance to be travled;
        // need to sync with ramping task
      }
      wait(endWait, vSettled, timeout);
    }
    void driveReconS(int Pct, int Wait, int endWait, double vSettled, int timeout) {
      DRS(Pct, Pct);
      pros::delay(Wait);
      wait(endWait, vSettled, timeout);
    }
    void turnEnc(double deg, int v, int endWait, double vSettled, int timeout) {
      int Dir = SGN(deg);
      int LPct = v * Dir;
      int RPct = v * Dir;

      front_left_motor.tarePosition();
      back_left_motor.tarePosition();
      front_right_motor.tarePosition();
      back_right_motor.tarePosition();

      // double
      // ZActual=(-front_left_motor.getPosition()+front_right_motor.getPosition()-back_left_motor.getPosition()+back_right_motor.getPosition())*(WheelCir/92)*180/M_PI;
      // //what the robots currant z is
      while (std::abs((-front_left_motor.getPosition() + front_right_motor.getPosition() - back_left_motor.getPosition() + back_right_motor.getPosition()) / 360) * (WheelCir / (39.5)) * 180 / M_PI < std::abs(deg)) {
        DIN(LPct, -RPct);
        pros::delay(5);
        // ZActual=(; //what the robots currant z is
      }
      DIN(0, 0);
      wait(endWait, vSettled, timeout);
    }
    // using namespace okapi::literals;

    // void wait(int endWait,okapi::QTime timeOut=-1_ms){
    //   okapi::Timer timeout;
    //   timeout.placeMark();
    //   timeout.getDtFromMark();
    //   using namespace okapi;
    //   okapi::QTime(timeOut);

    //   while (!isSettled() && ((timeOut>0_ms) ? timeout.getDtFromMark() < timeOut : true)) {
    //       pros::delay(5);
    //     }
    //     pros::delay(endWait);
    // }
    // namespace good{
    //   void calcDis(double forward, double strafe, double yaw){
    //     forwardSum+=forward;
    //     strafeSum+=strafe;
    //     yawSum+=yaw;
    //
    //     front_left_motor.set_target((forward-strafe-((Width+Length)/2)*(yaw*M_PI/180))/WheelCir);
    //     back_left_motor.set_target((forward+strafe+((Width+Length)/2)*(yaw*M_PI/180))/WheelCir);
    //     front_right_motor.set_target((forward+strafe-((Width+Length)/2)*(yaw*M_PI/180))/WheelCir);
    //     back_right_motor.set_target((forward-strafe+((Width+Length)/2)*(yaw*M_PI/180))/WheelCir);
    //   }
    //   void calcVelRatio(){
    //     double maxTargetDelta=std::max(front_left_motor.get_targetDelta(),
    //     std::max(back_left_motor.get_targetDelta(),
    //     std::max(front_right_motor.get_targetDelta(),
    //     back_right_motor.get_targetDelta())));
    //
    //     front_left_motor.set_RPM(front_left_motor.get_targetDelta()*maxRPM/maxTargetDelta);
    //     back_left_motor.set_RPM(back_left_motor.get_targetDelta()*maxRPM/maxTargetDelta);
    //     front_right_motor.set_RPM(front_right_motor.get_targetDelta()*maxRPM/maxTargetDelta);
    //     back_right_motor.set_RPM(back_right_motor.get_targetDelta()*maxRPM/maxTargetDelta);
    //   }
    //   void Absolute(double forward, double strafe, double yaw){
    //     calcDis(forward, strafe, yaw);
    //     calcVelRatio();
    //
    //     front_left_motor.moveAbsolute(front_left_motor.get_target(),front_left_motor.get_RPM());
    //     back_left_motor.moveAbsolute(back_left_motor.get_target(),back_left_motor.get_RPM());
    //     front_right_motor.moveAbsolute(front_right_motor.get_target(),front_right_motor.get_RPM());
    //     back_right_motor.moveAbsolute(back_right_motor.get_target(),back_right_motor.get_RPM());
    //   }
    //   void AbsolutelyRelative(double forward, double strafe, double yaw){
    //     forward+=forwardSum;
    //     strafe+=strafeSum;
    //     yaw+=yawSum;
    //     calcDis(forward, strafe, yaw);
    //     calcVelRatio();
    //
    //     front_left_motor.moveAbsolute(front_left_motor.get_target(),front_left_motor.get_RPM());
    //     back_left_motor.moveAbsolute(back_left_motor.get_target(),back_left_motor.get_RPM());
    //     front_right_motor.moveAbsolute(front_right_motor.get_target(),front_right_motor.get_RPM());
    //     back_right_motor.moveAbsolute(back_right_motor.get_target(),back_right_motor.get_RPM());
    //   }
    // }
  } // namespace auton
} // namespace drive
