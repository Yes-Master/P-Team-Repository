#include "robot/control/systems/lift.hpp"

namespace Lift{
  //vars
  Controllers controller=Controllers::NONE;

  //position
  const double Down=37;
  const double DownPun=110;//back
  const double UpPun=125;//front
  const double Up=230;
  const double MinLimit=Down;
  const double MaxLimit=410;
  double P=Down;//position setting

  //velocity
  const int VMove=100;
  const int VDown=-VMove;
  const int VUp=VMove;
  const int VPos=50;
  const int VStop=0;
  const int VCal=-50;
  int V=VStop;//velocity setting

  //calabrate
  int CalabrateTimer=0;
  bool Calabrated=false;

  //vars FUNCTIONS
  Controllers get_controller(){
    return controller;
  }
  void set_controller(Controllers c){
    controller=c;
  }
  int get_v(){
    return V;
  }
  void set_v(int v){
    V=v;
  }
  double get_target(){
    return P;
  }
  void set_target(double t){
    P=t;
  }
  void set_target(double t,bool p){
    P=t;
    if(p) set_controller(Controllers::POSITION);
  }
  void set_target(double t,int v){
    set_target(t);
    set_v(v);
  }
  void set_target(double t,int v,bool p){
    set_target(t);
    set_v(v);
    if(p) set_controller(Controllers::POSITION);
  }
bool get_calabrated(){
  return Calabrated;
}
  //methods
  void PositionChanger(int v=VMove){
    set_v(v);
    if(get_controller()==Controllers::MANUAL){
      set_target(Down,VDown);
    }
    else if(get_target()==Up)       set_target(Down,-VPos);
    else if(get_target()==Down)     set_target(Up,VPos);
    else if(get_target()==UpPun)    set_target(Up,VPos);
    else if(get_target()==DownPun)  set_target(Down,-VPos);
    set_controller(Controllers::POSITION);
  }
  void Calabrate(int timeout=20){//20 loops
    if(CalabrateTimer>timeout){
      motor.moveVelocity(VStop);
      motor.tarePosition();
      Calabrated=true;
      set_target(Down, VUp, true);
      motor.setLimitPositons(Lift::MinLimit,Lift::MaxLimit);
    }
    else {
      motor.moveVelocity(VCal);
      CalabrateTimer++;
    }
  }
  void execute(int CalTimOut){
    if(!Calabrated){
      Calabrate(CalTimOut);
    }
    else{
      switch(get_controller()){
        case Controllers::MANUAL:
        motor.moveVelocity(get_v());
        break;
        case Controllers::POSITION:
        motor.moveAbsolute(get_target(), get_v());
        break;
        case Controllers::NONE:
        motor.moveVelocity(VStop);//stop the motor
        break;
      };
    }
  }
  namespace Control{
    void manual(){
      if(BtnDown.isPressed()){
        set_controller(Controllers::MANUAL);
        set_v(VDown);
      }
      else if(BtnUp.isPressed()){
        set_controller(Controllers::MANUAL);
        set_v(VUp);
      }
      else if(get_controller()==Controllers::MANUAL){//deinti
        set_controller(Controllers::NONE);
        set_v(0);
      }
    }
    void position(){
      if(BtnPosTog.changed()){
        if(BtnPosTog.isPressed()){//init
          // set_controller(Controllers::POSITION);
          PositionChanger();
        }
        else{//deInit

        }
      }
      else if(BtnPosTog.isPressed()){//hold

      }
      else{

      }
    }
    void calabrate(){
      if(BtnCal.changed()){
        if(BtnCal.isPressed()){//init
          set_controller(Controllers::MANUAL);
          motor.setLimitPositionDisabled();
          set_v(VCal);
        }
        else{//deInit
          set_v(VStop);
          motor.setLimitPositionsEnabled();
          motor.tarePosition();
        }
      }
      else if(BtnCal.isPressed()){//hold

      }
      else{

      }
    }
  }
inline  namespace Auton{
    void wait(int w){
      while(std::abs(motor.getPosition()-get_target())>2){
        pros::delay(5);
      }
      pros::delay(w);
    }
  }
}
