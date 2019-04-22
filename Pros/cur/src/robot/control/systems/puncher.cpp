#include "robot/control/systems/puncher.hpp"
#include "robot/control/systems/drive.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/systems/lift.hpp"
// #include "robot/auton/routines.hpp"
namespace puncher {
  // pros::Mutex DoubleShotTaskMutex();

  //vars
  Controllers Controller = Controllers::NONE;
  bool DoubleShot = false;

  const int VMove = 100;
  const int VStop = 0;

  int V = VStop;
  bool Charged = false;

  //vars FUNCTIONS
  Controllers get_controller() {
    return Controller;
  }
  void set_controller(Controllers c) {
    Controller = c;
  }
  bool get_doubleShot() {
    return DoubleShot;
  }
  void set_doubleShot(bool d) {
    DoubleShot = d;
  }
  int get_v() {
    return V;
  }
  void set_v(int v) {
    V = v;
  }
  bool get_charged() {
    return Charged;
  }
  void set_charged(bool c) {
    Charged = c;
  }
  //OnOffCon
  //methods
  namespace OnOffCon {
    //vars
    const int ReleasedtoCharged = 175;  //175
    const int ChargedToReleased = 65;   //65
    double Target = 0;
    bool Run = false;
    bool Enabled = false;
    //vars FUNCTIONS
    bool get_run() {
      return Run;
    }
    void set_run(bool r) {
      Run = r;
    }
    bool get_enabled() {
      return Enabled;
    }
    void set_enabled(bool e) {
      Enabled = e;
    }
    double get_target() {
      return Target;
    }
    void set_target(double t) {
      Target = t;
    }
    void set_targetRel(double t) {
      Target += t;
    }
    //methods
    void execute() {
      if (motor.getPosition() < get_target() && get_run()) {  //outside of tal
        set_controller(Controllers::POSITION);
        // Dir=SGN(Tar-Punchermotor.rotation(vex::rotationUnits::deg));
        set_v(VMove);                                          //set the motor to spin in the correct direction
      } else if (get_controller() == Controllers::POSITION) {  //if in tar zone and was enabled; fist not enabled
        set_controller(Controllers::NONE);
        set_v(0);
        set_run(false);  //stop after it has been hit
      }
    }
  }  // namespace OnOffCon
  void Changer() {
    // ComRumerFun();
    if (!get_charged()) {  //Charging
      OnOffCon::set_targetRel(OnOffCon::ReleasedtoCharged);
      OnOffCon::set_run(true);
      set_charged(true);
    } else if (get_charged()) {  //Fireing
      OnOffCon::set_targetRel(OnOffCon::ChargedToReleased);
      OnOffCon::set_run(true);
      set_charged(false);
      intake::automatic::balls::set_puncher(false);
      intake::automatic::balls::set_overEnabled(false);
    }
  }
  void execute() {
    OnOffCon::execute();
    if (get_controller() == Controllers::POSITION) {
      motor.moveVelocity(get_v());
    } else if (get_controller() == Controllers::NONE) {
      motor.moveVelocity(VStop);
    }
  }

  namespace control {
    // okapi::Motor::brakeMode initBrakeMode = okapi::Motor::brakeMode::coast;

    int timeDelta(int& timer) {  // move to utils
      int delta = pros::millis() - timer;
      timer = pros::millis();
      return delta;
    }

    // void doubleShotFront(void* why){
    //   puncher::auton::charge(true);
    //   if(!get_doubleShot())  return;
    //   puncher::auton::fire(true);
    //   if(!get_doubleShot())  return;
    //   puncher::auton::charge(false);
    //   lift::set_target(lift::punFront1,lift::vMove,true);
    //   if(!get_doubleShot())  return;
    //
    //   lift::auton::wait();//wait for the lift
    //   int timerInit=pros::millis();
    //   while(!intake::automatic::balls::get_puncherActual() && timeDelta(timerInit)<500){
    //     pros::delay(5);
    //   }
    //   pros::delay(150);
    //   puncher::auton::wait();//wait for the puncher
    //
    //   if(!get_doubleShot())  return;
    //   puncher::auton::fire(true);
    //   if(!get_doubleShot())  return;
    //   lift::set_target(lift::down,lift::vDown,true);
    //
    //   set_doubleShot(false);
    //   drive::set_brakeMode(initBrakeMode);
    //   lift::set_target(lift::down,lift::vDown);
    // }
    void doubleShotFront(void* why) {
      puncher::auton::charge(false);
      lift::set_target(lift::punFront1, 50, true);
      lift::wait();
      puncher::auton::wait();
      if (!get_doubleShot()) return;
      puncher::auton::fire(true);
      if (!get_doubleShot()) return;
      lift::set_target(lift::punFront2, 50, true);
      puncher::auton::charge(false);
      int timerInit = pros::millis();
      while (!intake::automatic::balls::get_puncherActual() && timeDelta(timerInit) < 500) {
        pros::delay(5);
      }
      lift::wait();      //wait for the lift
      pros::delay(100);  //ball wait
      if (!get_doubleShot()) return;
      puncher::auton::fire(true);
      if (!get_doubleShot()) return;
      //deinit
      pros::delay(50);  //just in case
      lift::set_target(lift::down, lift::vMove);

      // drive::set_brakeMode(initBrakeMode);
      set_doubleShot(false);
    }

    void doubleShotBack(void* why) {
      puncher::auton::charge(false);
      lift::set_target(lift::punBack1 + 10, 50, true);
      lift::wait();
      if (!get_doubleShot()) return;
      puncher::auton::fire(true);
      if (!get_doubleShot()) return;
      puncher::auton::charge(false);
      lift::set_target(lift::punBack2 + 60, 50);
      lift::wait();  //wait for the lift
      int timerInit = pros::millis();
      while (!intake::automatic::balls::get_puncherActual() && timeDelta(timerInit) < 500) {
        pros::delay(5);
      }
      pros::delay(100);  //ball wait
      if (!get_doubleShot()) return;
      puncher::auton::fire(true);
      if (!get_doubleShot()) return;
      //deinit
      pros::delay(50);  //just in case
      lift::set_target(lift::down, lift::vMove);

      // drive::set_brakeMode(initBrakeMode);
      set_doubleShot(false);
    }
    void backTop(void* why) {
      puncher::auton::charge(false);
      lift::set_target(lift::punBack1+2, 40, true);
      lift::wait();
      puncher::auton::fire(false);
      puncher::auton::wait(50);
      lift::set_target(lift::down);
    }
    void backMid(void* why) {
      puncher::auton::charge(false);
      lift::set_target(lift::punBack2+2, 40, true);
      lift::wait();
      puncher::auton::fire(false);
      puncher::auton::wait(50);
      lift::set_target(lift::down);
    }

    void charge() {
      if (btnCharge.changed()) {
        if (btnCharge.isPressed()) {  //inti
          // initBrakeMode = drive::get_brakeMode();
          intake::automatic::enable();
          // drive::set_brakeMode(okapi::Motor::brakeMode::hold);
          set_doubleShot(true);
          pros::Task DoubleShotTask(doubleShotFront, (void*)"why", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "DoubleShotTask");
          // Changer();
        } else {  //deInit
          set_doubleShot(false);
          // drive::set_brakeMode(initBrakeMode);
          lift::set_target(lift::down, lift::vDown);
        }
      } else if (btnCharge.isPressed()) {  //hold
      } else {
      }
    }
    void doubleBack() {
      if (btnDoubleBack.changed()) {
        if (btnDoubleBack.isPressed()) {  //inti
          // initBrakeMode = drive::get_brakeMode();
          intake::automatic::enable();
          // drive::set_brakeMode(okapi::Motor::brakeMode::hold);
          set_doubleShot(true);
          pros::Task DoubleShotTask(doubleShotBack, (void*)"why", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "DoubleShotTask");
          // Changer();
        } else {  //deInit
        }
      } else if (btnDoubleBack.isPressed()) {  //hold
      } else {
      }
    }
    void backTop() {
      if (btnBackTop.changedToPressed()) {
        pros::Task backTopTask(backTop, (void*)"why", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "backTopTask");
      }
    }
    void backMid() {
      if (btnBackMid.changedToPressed()) {
        pros::Task backMidTask(backMid, (void*)"why", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "backMidTask");
      }
    }  // namespace control
  }    // namespace control
  namespace auton {
    void wait(int w) {
      while (OnOffCon::get_run()) {  //wait for the motor to hit its target pos
        pros::delay(5);
      }
      pros::delay(w);
    }
    void charge(bool w) {
      if (!get_charged()) Changer();  //charge
      if (w) wait();
    }
    void fire(bool w) {
      auton::charge(false);  //verify charghed dont wait
      Changer();             //fire
      if (w) wait();
      intake::automatic::balls::set_puncher(false);
      intake::automatic::balls::set_overEnabled(false);
    }
    void fire(double shootPos, double endPos, bool endCharged, bool intakeEnable, int vLift) {
      if (intakeEnable) intake::automatic::enable();
      charge();
      lift::set_target(shootPos, vLift, true);
      lift::wait();
      puncher::auton::fire(false);
      puncher::auton::wait(50);
      lift::set_target(endPos, vLift, true);
    }
  }  // namespace auton
}  // namespace puncher