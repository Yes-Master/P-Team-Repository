#include "robot/control/systems/intake.hpp"
#include "robot/control/modes/flag.hpp"

namespace Intake{
  //vars
  Controllers Controller=Controllers::NONE;

  const int VOut=-600;
  const int VStop=0;
  const int VIn=600;
  const int VOver=-300;

  int V=VStop;

  bool DoubleShotTaskEnabled=false;

  bool PuncBallActual=false;
  bool PuncBall=false;
  bool OverBall=false;
  bool FeedBall=false;
  bool Feed2Ball=false;
  bool Feed1Ball=false;

  //vars FUNCTIONS
  Controllers get_controller(){
    return Controller;
  }
  void set_controller(Controllers c){
    Controller=c;
  }
  int get_v(){
    return V;
  }
  void set_v(int v){
    V=v;
  }
  //methods
  void execute(){
    Auto::execute();
    Control::execute();
    if(get_controller()==Controllers::NONE) Motor.moveVelocity(VStop);
  }
  namespace Control{
    int timer=0;
    void combo(){
      if(BtnCombo.changed()){
        if(BtnCombo.isPressed()){//init

        }
        else{//deinit
          if(timer<=10){
            set_controller(Controllers::AUTO);
            Auto::toggle();
          }
          else{
            set_controller(Controllers::NONE);
            set_v(VStop);
          }
          timer=0;//reset timer
        }
      }
      else if(BtnCombo.isPressed()){//hold
        if(timer>10){
          set_controller(Controllers::MANUAL);
          set_v(VOut);
        }
        timer++;//count loops
      }
      else{//null

      }

    }
    void feedOut(){
      if(BtnOut.changed()){//
        if(BtnOut.isPressed()){//init
          set_controller(Controllers::MANUAL);
        }
        else{//deint
          set_controller(Controllers::NONE);
        }
      }
      else if(BtnOut.isPressed()){//hold
        set_v(VOut);
      }
      else{//null
        // set_controller(NONE);
      }
    }
    void feedIn(){
      if(BtnIn.changed()){
        if(BtnIn.isPressed()){//init
          set_controller(Controllers::MANUAL);
        }
        else{//deinit
          set_controller(Controllers::NONE);
        }
      }
      else if(BtnIn.isPressed()){//hold
        set_v(VIn);
      }
      else{//null

      }

    }
    void toggle(){
      if(BtnTog.changed()){
        if(BtnTog.isPressed()){//init
          // Flag::Init();//go to flag mode
          set_controller(Controllers::AUTO);
          Auto::toggle();
        }
        else{//deinit

        }
      }
      else if(BtnTog.isPressed()){//hold

      }
      else{//null

      }
    }
    void execute(){
      if(get_controller()==Controllers::MANUAL) Motor.moveVelocity(get_v());
    }
  }
  namespace Auto{
    //vars
    const int PuncBallTimeWait=250;//puncher ball timeout value

    const int Feed1BallTal=2000;//sensor tollerance values
    const int Feed2BallTal=2000;//sensor tollerance values
    const int OverBallTal=2000;//sensor tollerance values
    const int PuncBallTal=2000;//sensor tollerance values

    const int ComRumTime=100;//100 loops
    int PuncherTimer=0;
    int OverTimer=0;
    bool ComRum=false;

    Modes Mode;//control mode
    bool Enabled=false;//
    bool EnabledWas=false;

    bool OverMode=false;
    //vars FUNCTIONS
    namespace Balls{
      bool get_puncherActual(){
        return PuncBallActual;
      }
      bool get_puncher(){
        return PuncBall;
      }
      bool get_over(){
        return OverBall;
      }
      bool get_feed(){
        return FeedBall;
      }
      bool get_feedTop(){
        return Feed2Ball;
      }
      bool get_feedBottom(){
        return Feed1Ball;
      }
    }
    Modes get_mode(){
      return Mode;
    }
    void set_mode(Modes m){
      Mode=m;
    }
    bool get_enabled(){
      return Enabled;
    }
    void set_enabled(bool b){
      EnabledWas=Enabled;
      Enabled=b;
    }
    //methods
    void toggle(){//toogle the current enabled state
      if(get_enabled()) disable();
      else if(!get_enabled()) enable();
    }
    void enable(){//set to enabled state
      set_enabled(true);
      set_controller(Controllers::AUTO);
    }
    void disable(){//set to disabled state
      set_enabled(false);
      set_controller(Controllers::NONE);
    }
    void updateVars(){
      //Puncher UpDate
      if(Puncher.get_value()<PuncBallTal){//if there is pysicaly a ball
        PuncherTimer=0;//reset timer
        PuncBall=PuncBallActual=true;
        ComRum=false;
      }
      else{//if ball not present
        PuncBallActual=false;
        if(/*PuncherRuning*/false)  PuncBall=false;//if the punc in running and there is not a ball physicaly present
        else{//delay for posible ball return
          if(PuncherTimer>PuncBallTimeWait)   PuncBall=false;
          else if(PuncherTimer>ComRumTime)    ComRum=true;
          PuncherTimer++;//add one to timer
        }

      }
      //FeedBall UpDate
      if(Over.get_value()<OverBallTal)    OverBall=true;
      else                                                    OverBall=false;

      if(Bottom.get_value()<Feed1BallTal)  Feed1Ball=true;
      else                                                    Feed1Ball=false;

      if(Top.get_value()<Feed2BallTal)  Feed2Ball=true;
      else                                                    Feed2Ball=false;

      if(Feed1Ball || Feed2Ball)  FeedBall=true;
      else                        FeedBall=false;
    }
    void calcV(){
      if(get_enabled()){
        EnabledWas=true;

        if(OverMode){
          set_v(VOver);
          if(OverBall){
            OverTimer=0;
          }
          else{
            if(Balls::get_feed() || OverTimer>100) OverMode=false;
            else OverTimer++;
          }
        }
        else{
          if(!Balls::get_puncher()) set_v(VIn);
          else{//if punball
            if(Balls::get_over()){
              OverMode=true;
              set_v(VOver);
            }
            else{//!overflow
              if(!Balls::get_feedTop()){
                if(!Balls::get_feedBottom())  set_v(VIn*7/8);
                else            set_v(VIn/4);
              }
              else              set_v(VStop);//if punball && !Overball && feed2ball
            }
          }
        }
      }
      else if(EnabledWas){//first loop disabled
        set_v(VStop);
        EnabledWas=false;
      }
    }
    void execute(){
      updateVars();
      if(get_controller()==Controllers::AUTO){
        calcV();
        // set_v(-10);
        Motor.moveVelocity(get_v());
      }
    }

    // void User_Control(){//not needed here combine all inside of the controlmodes
    //   Toggle_Control();
    // }
  }
  //methods
}
