#include "robot/control/systems/intake.hpp"
#include "robot/control/modes/flag.hpp"

namespace intake{
  //vars
  Controllers Controller=Controllers::NONE;

  const int VOut=-200;
  const int VStop=0;
  const int VIn=200;
  const int VOver=-100;

  int V=VStop;

  bool DoubleShotTaskEnabled=false;

  bool PuncBallActual=false;
  bool PuncBall=false;
  bool OverBallActual=false;
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
    automatic::execute();
    control::execute();
    if(get_controller()==Controllers::NONE) motor.moveVelocity(VStop);
  }
  namespace control{
    int timer=0;
    okapi::Timer t;
    void combo(){
      using namespace okapi::literals;

      if(btnCombo.changed()){
        if(btnCombo.isPressed()){//init
          //init time; used to measure delta time
          t.placeMark();//log this time;
        }
        else{//deinit
          if(t.getDtFromMark()<200_ms){//short press
            set_controller(Controllers::AUTO);
            automatic::toggle();
          }
          else{//long press
            set_controller(Controllers::NONE);
            set_v(VStop);
          }
          // timer=0;//reset timer; moved to init
        }
      }
      else if(btnCombo.isPressed()){//hold
        if(t.getDtFromMark()>200_ms){
          set_controller(Controllers::MANUAL);
          set_v(VOut);
        }
      }
      else{//released

      }
    }
    void feedOut(){
      if(btnOut.changed()){//
        if(btnOut.isPressed()){//init
          set_controller(Controllers::MANUAL);
        }
        else{//deint
          set_controller(Controllers::NONE);
        }
      }
      else if(btnOut.isPressed()){//hold
        set_v(VOut);
      }
      else{//null
        // set_controller(NONE);
      }
    }
    void feedIn(){
      if(btnIn.changed()){
        if(btnIn.isPressed()){//init
          set_controller(Controllers::MANUAL);
        }
        else{//deinit
          set_controller(Controllers::NONE);
        }
      }
      else if(btnIn.isPressed()){//hold
        set_v(VIn);
      }
      else{//null

      }

    }
    void toggle(){
      if(btnTog.changed()){
        if(btnTog.isPressed()){//init
          Flag::init();//go to flag mode
          set_controller(Controllers::AUTO);
          automatic::toggle();
        }
        else{//deinit

        }
      }
      else if(btnTog.isPressed()){//hold

      }
      else{//null

      }
    }
    void execute(){
      if(get_controller()==Controllers::MANUAL) motor.moveVelocity(get_v());
    }
  }
  namespace automatic{
    //vars
    const int PuncBallTimeWait=0;//puncher ball timeout value

    const int Feed1BallTal=2500;//sensor tollerance values
    const int Feed2BallTal=2500;//sensor tollerance values
    const int OverBallTal=2500;//sensor tollerance values
    const int PuncBallTal=2500;//sensor tollerance values

    const int ComRumTime=10;//100 loops
    int PuncherTimer=0;
    int OverTimer=0;
    bool ComRum=false;

    Modes Mode;//control mode
    bool Enabled=false;//
    bool EnabledWas=false;

    bool OverMode=false;
    bool OverEnabled=true;
    //vars FUNCTIONS
    namespace balls{
      //vars
      //vars FUNCTIONS
      bool get_puncherActual(){
        return PuncBallActual;
      }
      bool get_puncher(){
        return PuncBall;
      }
      void set_puncher(bool p){
        PuncBall=p;
      }
      bool get_over(){
        return OverBall;
      }
      void set_over(bool o){
        OverBall=o;
      }
      bool get_overEnabled(){
        return OverEnabled;
      }
      void set_overEnabled(bool e){
        OverEnabled=e;
      }
      bool get_feedTop(){
        return Feed2Ball;
      }
      bool get_feedBottom(){
        return Feed1Ball;
      }
      bool get_feed(){
        if(get_feedTop()) return true;
        if(get_feedBottom()) return true;
        return false;
      }

      //methods
      void updateVars(){
        //Puncher UpDate
        if(puncher.get_value()<PuncBallTal){//if there is pysicaly a ball
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
        if(Over.get_value()<OverBallTal)  OverBallActual=true;
        else  OverBallActual=false;
        if(!get_overEnabled() && OverTimer>4)  set_overEnabled(true);//timer
        else  OverTimer++;
        if(get_overEnabled())  OverBall=OverBallActual;//set if enabled
        else  OverBall=false;

        if(Bottom.get_value()<Feed1BallTal) Feed1Ball=true;
        else  Feed1Ball=false;

        if(Top.get_value()<Feed2BallTal)  Feed2Ball=true;
        else  Feed2Ball=false;
      }

    }//end Balls
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
    void calcV(){
      if(get_enabled()){
        EnabledWas=true;

        if(OverMode){
          set_v(VOver);
          if(Balls::get_feedTop() || Balls::get_feedBottom() || OverTimer>100) OverMode=false;
          else OverTimer++;
        }
        else{
          if(!Balls::get_puncher()) set_v(VIn);
          else{//if punball
            if(Balls::get_over()){//init over mode
              OverMode=true;
              OverTimer=0;//initialize timer for over mode
              set_v(VOver);
            }
            else{//!overflow
              if(!Balls::get_feedTop()){
                if(!Balls::get_feedBottom())  set_v(VIn);
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
      Balls::updateVars();
      if(get_controller()==Controllers::AUTO){
        calcV();
        motor.moveVelocity(get_v());
      }
    }

    // void User_Control(){//not needed here combine all inside of the controlmodes
    //   Toggle_Control();
    // }
  }//end Auto
  //methods
}
