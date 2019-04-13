#include "robot/control/systems/lift.hpp"

namespace Lift{
  //vars
  Controllers controller=Controllers::NONE;

  //position
  const double Down=37;
  const double DownPun=35;//back
  const double UpPun=125;//front//100
  const double Up=230;
  const double MinLimit=Down;
  const double MaxLimit=385;
  double P=Down;//position setting

  //velocity
  const int VMove = 100;
  const int VDown=-VMove;
  const int VUp=VMove;
  const int VStop=0;
  const int VCal=-VMove/2;
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

  //methods
  void PositionChanger(int v=VMove){
    set_v(v);
    if(get_controller()==Controllers::MANUAL){
      set_target(Down,VDown);
    }
    else if(get_target()==Up)       set_target(Down,VDown);
    else if(get_target()==Down)     set_target(Up,VUp);
    else if(get_target()==UpPun)    set_target(Up,VUp);
    else if(get_target()==DownPun)  set_target(Down,VDown);
    set_controller(Controllers::POSITION);
  }
  // void Calabrate(int timeout=20){
  //   if(CalabrateTimer>timeout){
  //     std::cout <<"done caled "<< Calabrated << std::endl;

  //     motor.moveVelocity(VStop);
  //     motor.tarePosition();
  //     Calabrated=true;
  //     set_target(Down, VUp, true);
  //     motor.setPositonLimits(Lift::MinLimit,Lift::MaxLimit);
  //   }
  //   else {
  //     motor.moveVelocity(VCal);
  //     CalabrateTimer++;
  //   }

  // }
  bool caled=false;
  void cal(){
    const static int startTime = pros::millis();
    std::cout <<"starttime: "<< startTime << std::endl;
    if(pros::millis()>startTime+250){
      motor.moveVelocity(VStop);
      motor.tarePosition();
      caled=true;
      set_target(Down, VUp, true);
      motor.setPositonLimits(Lift::MinLimit,Lift::MaxLimit);
    }
    else{
      motor.moveVelocity(VCal);
    }
    
  }
  void execute(){
    if(!caled){
      // Calabrate(20);
      // cal();
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
        motor.moveVelocity(0);//stop the motor
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
        set_v(VStop);
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
