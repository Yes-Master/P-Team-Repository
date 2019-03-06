#include "robot/control/systems/drive.hpp"
// #include "robot/vars.hpp"
namespace Drive{
  //vars
  Controllers Controller=Controllers::NONE;
  const float WheelCir=4*M_PI;

  bool Inverted=false;
  bool InvertedWas=Inverted;
  //vars FUNCTIONS
  Controllers get_controller(){
    return Controller;
  }
  void set_controller(Controllers c){
    Controller=c;
  }
  bool get_inverted(){
    return Inverted;
  }
  void set_inverted(bool i){
    InvertedWas=get_inverted();
    Inverted=i;
  }
  //methods
  okapi::Motor::brakeMode get_brakeMode(){
    return front_left_motor.getBrakeMode();
  }
  void set_brakeMode(okapi::Motor::brakeMode b){
    front_left_motor.setBrakeMode(b);
    front_right_motor.setBrakeMode(b);
    back_left_motor.setBrakeMode(b);
    back_right_motor.setBrakeMode(b);
  }
  void set_v(int v1,int v2,int v3,int v4){
    front_left_motor.moveVelocity(v1);
    front_right_motor.moveVelocity(v2);
    back_left_motor.moveVelocity(v3);
    back_right_motor.moveVelocity(v4);
  }
  void tank(int j1,int j2,int j3,int j4){
    int LF=j1;//left
    int RF=j2;//right
    int SD=(j3+j4)/2;//average
    if(std::abs(j3)>std::abs(j4))   SD=j3;
    else                            SD=j4;

    set_v(LF+SD,LF-SD,RF-SD,RF+SD);
  }
  void execute(){

  }
  namespace Control{
    void manual(){
      int LHJoy=master_controller.getAnalog(okapi::ControllerAnalog::leftX)*200;
      int LVJoy=master_controller.getAnalog(okapi::ControllerAnalog::leftX)*200;
      int RVJoy=master_controller.getAnalog(okapi::ControllerAnalog::leftX)*200;
      int RHJoy=master_controller.getAnalog(okapi::ControllerAnalog::leftX)*200;


      if(std::abs(LVJoy)<5)    LVJoy=0;
      if(std::abs(RVJoy)<5)    RVJoy=0;
      if(std::abs(LHJoy)<5)    LHJoy=0;
      if(std::abs(RHJoy)<5)    RHJoy=0;

      if(LVJoy!=0 || RVJoy!=0 || LHJoy!=0 || RHJoy!=0){
        set_controller(Controllers::MANUAL);
        tank(
          get_inverted() ?  -RVJoy : LVJoy,
          get_inverted() ?  -LVJoy : RVJoy,
          get_inverted() ?  -RHJoy : LHJoy,
          get_inverted() ?  -LHJoy : RHJoy);
        }
        else{
          if(get_controller()==Controllers::MANUAL)  tank(0,0,0,0);//Last loop before disableing; used to release drivemanualcontrol
          set_controller(Controllers::NONE);
        }
      }
      void hold(){
        if(BtnBrake.changed()){
          if(BtnBrake.isPressed()){//init
            if(get_brakeMode()==okapi::Motor::brakeMode::coast) set_brakeMode(okapi::Motor::brakeMode::hold);
            else set_brakeMode(okapi::Motor::brakeMode::coast);
          }
          else{//deinti

          }
        }
        else if(BtnBrake.isPressed()){//hold

        }
        else{

        }
      }
    }
  }
