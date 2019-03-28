#include "robot/control/systems/puncher.hpp"
#include "robot/control/systems/drive.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/systems/lift.hpp"
// #include "robot/auton/routines.hpp"
namespace Puncher{
  // pros::Mutex DoubleShotTaskMutex();

  //vars
  Controllers Controller=Controllers::NONE;
  bool DoubleShot=false;

  const int VMove=100;
  const int VStop=0;

  int V=VStop;
  bool Charged=false;

  //vars FUNCTIONS
  Controllers get_controller(){
    return Controller;
  }
  void set_controller(Controllers c){
    Controller=c;
  }
  bool get_doubleShot(){
    return DoubleShot;
  }
  void set_doubleShot(bool d){
    DoubleShot=d;
  }
  int get_v(){
    return V;
  }
  void set_v(int v){
    V=v;
  }
  bool get_charged(){
    return Charged;
  }
  void set_charged(bool c){
    Charged=c;
  }
  //OnOffCon
  //methods
  namespace OnOffCon{
    //vars
    const int ReleasedtoCharged=175;
    const int ChargedToReleased=65;
    double Target=0;
    bool Run=false;
    bool Enabled=false;
    //vars FUNCTIONS
    bool get_run(){
      return Run;
    }
    void set_run(bool r){
      Run=r;
    }
    bool get_enabled(){
      return Enabled;
    }
    void set_enabled(bool e){
      Enabled=e;
    }
    double get_target(){
      return Target;
    }
    void set_target(double t){
      Target=t;
    }
    void set_targetRel(double t){
      Target+=t;
    }
    //methods
    void execute(){
      if(motor.getPosition()<get_target() && get_run()){//outside of tal
        set_controller(Controllers::POSITION);
        // Dir=SGN(Tar-Punchermotor.rotation(vex::rotationUnits::deg));
        set_v(VMove);//set the motor to spin in the correct direction
      }
      else if(get_controller()==Controllers::POSITION){//if in tar zone and was enabled; fist not enabled
        set_controller(Controllers::NONE);
        set_v(0);
        set_run(false);//stop after it has been hit
      }
    }
  }
  void Changer(){
    // ComRumerFun();
    if(!get_charged()){//Charging
      OnOffCon::set_targetRel(OnOffCon::ReleasedtoCharged);
      OnOffCon::set_run(true);
      set_charged(true);
    }
    else if(get_charged()){//Fireing
      OnOffCon::set_targetRel(OnOffCon::ChargedToReleased);
      OnOffCon::set_run(true);
      set_charged(false);
      Intake::Auto::Balls::set_puncher(false);
      Intake::Auto::Balls::set_overEnabled(false);
    }
  }
  void execute(){
    OnOffCon::execute();
    if(get_controller()==Controllers::POSITION){
      motor.moveVelocity(get_v());
    }
    else if(get_controller()==Controllers::NONE){
      motor.moveVelocity(VStop);
    }
  }

  namespace Control{
    okapi::Motor::brakeMode initBrakeMode = okapi::Motor::brakeMode::coast;

    int timeDelta(int &timer){// move to utils
      int delta=pros::millis()-timer;
      timer=pros::millis();
      return delta;
    }

    void doubleShotFront(void* why){
      Puncher::Auton::charge(true);
      if(!get_doubleShot())  return;
      Puncher::Auton::fire(true);
      if(!get_doubleShot())  return;
      Puncher::Auton::charge(false);
      Lift::set_target(Lift::UpPun,Lift::VMove,true);
      if(!get_doubleShot())  return;

      Lift::Auton::wait();//wait for the lift
      int timerInit=pros::millis();
      while(!Intake::Auto::Balls::get_puncherActual() && timeDelta(timerInit)<500){
        pros::delay(5);
      }
      pros::delay(150);
      Puncher::Auton::wait();//wait for the puncher

      if(!get_doubleShot())  return;
      Puncher::Auton::fire(true);
      if(!get_doubleShot())  return;
      Lift::set_target(Lift::Down,Lift::VMove,true);

      set_doubleShot(false);
      Drive::set_brakeMode(initBrakeMode);
      Lift::set_target(Lift::Down,Lift::VDown);

    }

    void doubleShotBack(void* why){
      Puncher::Auton::charge(false);
      Lift::set_target(Lift::DownPun,Lift::VMove,true);
      Lift::wait();
      if(!get_doubleShot())  return;
      Puncher::Auton::fire(true);
      if(!get_doubleShot())  return;
      Puncher::Auton::charge(false);
      Lift::set_target(Lift::UpPun);
      Lift::wait();//wait for the lift
      int timerInit=pros::millis();
      while(!Intake::Auto::Balls::get_puncherActual() && timeDelta(timerInit)<500){
        pros::delay(5);
      }
      pros::delay(150);
      if(!get_doubleShot())  return;
      Puncher::Auton::fire(true);
      if(!get_doubleShot())  return;
      //deinit
      pros::delay(50);//just in case
      Lift::set_target(Lift::Down);

      Drive::set_brakeMode(initBrakeMode);
      set_doubleShot(false);
    }
    void charge(){
      if(BtnCharge.changed()){
        if(BtnCharge.isPressed()){//inti
          initBrakeMode = Drive::get_brakeMode();
          Intake::Auto::enable();
          Drive::set_brakeMode(okapi::Motor::brakeMode::hold);
          set_doubleShot(true);
          pros::Task DoubleShotTask (doubleShotFront,(void*)"why", TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT, "DoubleShotTask");
          // Changer();
        }
        else{//deInit
          set_doubleShot(false);
          Drive::set_brakeMode(initBrakeMode);
          Lift::set_target(Lift::Down,Lift::VDown);
        }
      }
      else if(BtnCharge.isPressed()){//hold

      }
      else{

      }
    }
    void doubleBack(){
      if(BtnDoubleBack.changed()){
        if(BtnDoubleBack.isPressed()){//inti
          initBrakeMode = Drive::get_brakeMode();
          Intake::Auto::enable();
          Drive::set_brakeMode(okapi::Motor::brakeMode::hold);
          set_doubleShot(true);
          pros::Task DoubleShotTask (doubleShotBack,(void*)"why", TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT, "DoubleShotTask");
          // Changer();
        }
        else{//deInit

        }
      }
      else if(BtnDoubleBack.isPressed()){//hold

      }
      else{

      }
    }
    void doubleFront(){
      if(BtnDoubleFront.changed()){
        if(BtnDoubleFront.isPressed()){//inti
          initBrakeMode = Drive::get_brakeMode();
          Intake::Auto::enable();
          Drive::set_brakeMode(okapi::Motor::brakeMode::hold);
          set_doubleShot(true);
          pros::Task DoubleShotTask (doubleShotFront,(void*)"why", TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT, "DoubleShotTask");
        }
        else{//deInit

        }
      }
      else if(BtnDoubleFront.isPressed()){//hold

      }
      else{

      }
    }
  }
  namespace Auton{
    void wait(int w){
      while(OnOffCon::get_run()){//wait for the motor to hit its target pos
        pros::delay(5);
      }
      pros::delay(w);
    }
    void charge(bool w){
      if(!get_charged())  Changer();//charge
      if(w)  wait();
    }
    void fire(bool w){
      Auton::charge(false);//verify charghed dont wait
      Changer();//fire
      if(w)  wait();
      Intake::Auto::Balls::set_puncher(false);
      Intake::Auto::Balls::set_overEnabled(false);
    }
  }
}
