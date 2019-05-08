#include "robot/control/systems/intake.hpp"
#include "robot/config/controller_config.hpp"
#include "robot/config/motor_config.hpp"
#include "robot/control/modes/flag.hpp"

namespace intake {
  // vars
  Controllers controller = Controllers::NONE;

  const int vMove = 600;
  const int vIn = vMove;
  const int vOut = -vMove;
  const int vStop = 0;
  const int vOver = -vMove / 2;
  int V = vStop;

  bool doubleShotTaskEnabled = false;
  // vars FUNCTIONS
  Controllers get_controller() { return controller; }
  void set_controller(Controllers c) {
    if (c == Controllers::MANUAL) automatic::disable();
    controller = c;
  }
  int get_v() { return V; }
  void set_v(int v) { V = v; }
  void set_VSetting(int v) { set_v(v); }
  void set_VSetting(int v, bool m) {
    set_v(v);
    if (m)
      set_controller(Controllers::MANUAL);
  }

  // methods
  void execute() {
    automatic::execute();
    control::execute();
    if (get_controller() == Controllers::NONE)
      motor.moveVelocity(vStop);
  }
  namespace control {
    void combo() {
      static okapi::Timer t;
      using namespace okapi::literals;

      if (btnCombo.changed()) {
        if (btnCombo.isPressed()) { // init
          // init time; used to measure delta time
          t.placeMark();                    // log this time;
        } else {                            // deinit
          if (t.getDtFromMark() < 200_ms) { // short press
            set_controller(Controllers::AUTO);
            automatic::toggle();
          } else { // long press
            set_controller(Controllers::NONE);
            set_v(vStop);
          }
        }
      } else if (btnCombo.isPressed()) { // hold
        if (t.getDtFromMark() > 200_ms) {
          set_controller(Controllers::MANUAL);
          set_v(vOut);
        }
      } else { // released
      }
    }
    void feedOut() {
      static bool pressedWas;
      if (btnOut.changed()) {
        if (btnOut.isPressed()) {              // init
          set_controller(Controllers::MANUAL); //
        } else {                               // deint
          set_controller(Controllers::NONE);
        }
      } else if (btnOut.isPressed()) {                                                                      // hold
        set_v(vOut);                                                                                        //
      } else if (controllerSlave.get_digital(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R2) == 1) { // pressed
        pressedWas = true;
        set_controller(Controllers::MANUAL);
        set_v(vOut);
      } else if (pressedWas) {
        pressedWas = false;
        set_controller(Controllers::NONE);
        set_v(0);
      }
    }

    void feedIn() {
      static bool pressedWas;
      if (btnIn.changed()) {
        if (btnIn.isPressed()) { // init
          set_controller(Controllers::MANUAL);
        } else { // deinit
          set_controller(Controllers::NONE);
        }
      } else if (btnIn.isPressed()) { // hold
        set_v(vIn);
      } else if (controllerSlave.get_digital(
                     pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R1) ==
                 1) { // pressed
        pressedWas = true;
        set_controller(Controllers::MANUAL);
        set_v(vIn);
      } else if (pressedWas) {
        pressedWas = false;
        set_controller(Controllers::NONE);
        set_v(0);
      }
    }
    void toggle() {
      static bool pressedWas;
      if (btnTog.changed()) {
        if (btnTog.isPressed()) { // init
          flag::init();           // go to flag mode
          set_controller(Controllers::AUTO);
          automatic::toggle();
        } else { // deinit
        }
      } else if (btnTog.isPressed()) { // hold
      }
      // else
      // if(controllerSlave.get_digital(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L1)==1){//pressed
      //   pressedWas=true;
      //     // flag::init();//go to flag mode
      //     set_controller(Controllers::AUTO);
      //     automatic::toggle();
      //   }
      // else if(pressedWas){
      //   pressedWas=false;
      // }
    }
    void execute() {
      if (get_controller() == Controllers::MANUAL)
        motor.moveVelocity(get_v());
    }
  } // namespace control
  namespace automatic {
    // vars
    const int feed1BallTal = 2500; // sensor tollerance values
    const int feed2BallTal = 2500; // sensor tollerance values
    const int overBallTal = 2500;  // sensor tollerance values
    const int puncBallTal = 2500;  // sensor tollerance values

    // const int ComRumTime=10;//100 loops
    // int puncherTimer=0;
    // int overTimer=0;
    // bool comRum=false;

    Modes mode;           // control mode
    bool enabled = false; //
    bool enabledWas = false;

    bool overMode = false;
    bool overEnabled = true;
    // vars FUNCTIONS
    Modes get_mode() { return mode; }
    void set_mode(Modes m) { mode = m; }
    bool get_enabled() { return enabled; }
    void set_enabled(bool b) {
      enabledWas = enabled;
      enabled = b;
    }
    namespace balls {
      // vars
      bool puncBallActual = false;
      bool puncBall = false;
      bool overBallActual = false;
      bool overBall = false;
      bool feedBall = false;
      bool feed2Ball = false;
      bool feed1Ball = false;
      // vars FUNCTIONS
      bool get_puncherActual() { return puncBallActual; }
      bool get_puncher() { return puncBall; }
      void set_puncher(bool p) { puncBall = p; }
      bool get_overBallActual() { return overBallActual; }
      bool get_over() { return overBall; }
      void set_over(bool o) { overBall = o; }
      bool get_overEnabled() { return overEnabled; }
      void set_overEnabled(bool e) { overEnabled = e; }
      bool get_feedTop() { return feed2Ball; }
      bool get_feedBottom() { return feed1Ball; }
      bool get_feed() {
        if (get_feedTop())
          return true;
        if (get_feedBottom())
          return true;
        return false;
      }

      // methods
      void updateVars() {
        // Puncher UpDate
        static okapi::Timer puncherTimer;
        static okapi::Timer overTimer;
        using namespace okapi::literals;
        if (puncher.get_value() < puncBallTal) { // if there is pysicaly a ball
          puncherTimer.placeMark();              // init
          // PuncherTimer=0;//reset timer
          puncBall = puncBallActual = true;
          // comRum=false;
        } else { // if ball not present
          puncBallActual = false;
          if (/*PuncherRuning*/ false)
            puncBall = false; // if the punc in running and there is
                              // not a ball physicaly present
          else {              // delay for posible ball return
            using namespace okapi::literals;
            if (puncherTimer.getDtFromMark() > 0_ms)
              puncBall = false;
            // else if(puncherTimer.getDtFromMark()>100_ms)
            // comRum=true;
          }
        }
        // feedBall UpDate
        if (over.get_value() < overBallTal) {
          overTimer.placeMark();
          overBallActual = true;
        } else
          overBallActual = false;

        if (!get_overEnabled() && overTimer.getDtFromMark() > 100_ms)
          set_overEnabled(true); // timer

        if (get_overEnabled())
          overBall = overBallActual; // set if enabled
        else
          overBall = false;

        if (bottom.get_value() < feed1BallTal)
          feed1Ball = true;
        else
          feed1Ball = false;

        if (top.get_value() < feed2BallTal)
          feed2Ball = true;
        else
          feed2Ball = false;
      }

    } // namespace balls
    // methods
    void toggle() { // toogle the current enabled state
      if (get_enabled())
        disable();
      else if (!get_enabled())
        enable();
    }
    void enable() { // set to enabled state
      set_enabled(true);
      set_controller(Controllers::AUTO);
    }
    void disable() { // set to disabled state
      set_enabled(false);
      set_controller(Controllers::NONE); //test
    }
    void calcV() {
      static okapi::Timer timer;
      if (get_enabled()) {
        enabledWas = true;
        if (overMode) {
          using namespace okapi::literals;
          set_v(vOver);
          if (balls::get_feedTop() || balls::get_feedBottom() ||
              timer.getDtFromMark() > 1.5_s)
            overMode = false;
        } else {
          if (!balls::get_puncher())
            set_v(vIn);
          else {                     // if punball
            if (balls::get_over()) { // init over mode
              overMode = true;
              timer.placeMark(); // init the timer
              set_v(vOver);
            } else { //! overflow
              if (!balls::get_feedTop()) {
                if (!balls::get_feedBottom())
                  set_v(vIn);
                else
                  set_v(vIn / 4);
              } else
                set_v(vStop); // if punball && !Overball && feed2ball
            }
          }
        }
      } else if (enabledWas) { // first loop disabled
        set_v(vStop);
        enabledWas = false;
      }
    }
    void execute() {
      balls::updateVars();
      if (get_controller() == Controllers::AUTO) {
        calcV();
        motor.moveVelocity(get_v());
      }
    }
    // void User_Control(){//not needed here combine all inside of the controlmodes
    //   Toggle_Control();
    // }
  } // namespace automatic
  // methods
} // namespace intake