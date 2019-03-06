#include "robot/control/systems/lift.hpp"

namespace Lift{
  //vars
  const int Down=70;
  const int DownPun=175;//back
  const int UpPun=320;//front
  const int Up=320;

  const int VMove=100;
  const int VDown=-VMove;
  const int VUp=VMove;
  const int VStop=0;

  Controllers controller;

  // const int VDown=-100;
  // const int VUp=100;
  // const int VStop=0;

  int V=VStop;

  double Target=Down;
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
    return Target;
  }
  void set_target(double t){
    Target=t;
  }
  void set_target(double t,int v){
    set_target(t);
    set_v(v);
  }
  //methods
  void execute(){
    switch(get_controller()){
      case Controllers::MANUAL:
      Motor.moveVelocity(get_v());
      break;
      case Controllers::POSITION:
      Motor.moveAbsolute(get_target(), get_v());
      break;
      case Controllers::NONE:
      Motor.moveVelocity(0);//stop the motor
      break;
    };
  }
  void PositionChanger(int v=VUp){
    set_v(v);
    if(get_controller()==Controllers::MANUAL){
      set_target(Down,VDown);
    }
    else if(get_target()==Up)       set_target(Down,VDown);
    else if(get_target()==Down)     set_target(Up,VUp);
    else if(get_target()==UpPun)    set_target(Up,VUp);
    else if(get_target()==DownPun)  set_target(Down,VDown);
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
          set_controller(Controllers::POSITION);
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
  }
}
