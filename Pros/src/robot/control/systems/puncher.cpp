#include "robot/control/systems/puncher.hpp"
#include "robot/control/systems/drive.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/auton/routines.hpp"
namespace Puncher{
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
    const int ReleasedtoCharged=260;
    const int ChargedToReleased=100;
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
      if(Motor.getPosition()<get_target() && get_run()){//outside of tal
        set_controller(Controllers::NONE);
        // Dir=SGN(Tar-PuncherMotor.rotation(vex::rotationUnits::deg));
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
    }
  }
  void execute(void* t){
    OnOffCon::execute();
    if(get_controller()==Controllers::POSITION){
      Motor.moveVelocity(get_v());
    }
    else if(get_controller()==Controllers::NONE){
      Motor.moveVelocity(VStop);
    }
  }
  namespace Control{
    void charge(){
      if(BtnCharge.changed()){
        if(BtnCharge.isPressed()){//inti
          Intake::Auto::enable();
          Drive::set_brakeMode(okapi::Motor::brakeMode::hold);
          set_doubleShot(true);
          Intake::Auto::enable();
          pros::Task DoubleShotTask (::Auton::Routines::doubleShotFront,(void*)"why", TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT, "DoubleShotTask");
        }
        else{//deInit
          set_doubleShot(false);
          Drive::set_brakeMode(okapi::Motor::brakeMode::coast);
          Lift::set_target(Lift::Down,Lift::VDown);
        }
      }
      else if(BtnCharge.isPressed()){//hold

      }
    }
  }
  namespace Auton{
    void charge(){
      if(!get_charged())  OnOffCon::set_targetRel(OnOffCon::ReleasedtoCharged);
    }
    void fire(){
      if(!get_charged())  Auton::charge();
      OnOffCon::set_targetRel(OnOffCon::ChargedToReleased);
    }
  }
}
