#include "robot/control/systems/lift.hpp"

namespace Lift{
  //vars
  const double Down=0;
  const double DownPun=0;//back
  const double UpPun=100;//front
  const double Up=3020;

  const int VMove=100;
  const int VDown=-VMove;
  const int VUp=VMove;
  const int VStop=0;

  Controllers controller=Controllers::NONE;

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
    set_controller(Controllers::POSITION);
    set_target(t);
    set_v(v);
  }
  //methods
  void execute(){
    switch(get_controller()){
      case Controllers::MANUAL:
      motor.moveVelocity(get_v());
      break;
      case Controllers::POSITION:
      motor.moveAbsolute(get_target(), get_v());
      break;
      case Controllers::NONE:
      motor.moveVelocity(0);//stop the motor
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
  namespace Auton{
    void wait(int w){
      while(motor.getPosition()-get_target()>5){
        pros::delay(5);
      }
      pros::delay(w);
    }
  }
}
