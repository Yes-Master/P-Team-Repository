#include "robot/control/systems/drive.hpp"
#include "custom/ramping.hpp"
double SGN(double var){
  if(var>0) return 1;
  else if(var<0)  return -1;
  else return 0;
}
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

    set_v(LF+SD,RF-SD,LF-SD,RF+SD);
  }
  void arcade(int y,int x,int z){
    set_v(y+x+z,y-x-z,y-x+z,y+x-z);
  }
  void execute(){

  }
  namespace Control{
    void manual(){
      int LHJoy=master_controller.getAnalog(okapi::ControllerAnalog::leftX)*200;
      int LVJoy=master_controller.getAnalog(okapi::ControllerAnalog::leftY)*200;
      int RVJoy=master_controller.getAnalog(okapi::ControllerAnalog::rightY)*200;
      int RHJoy=master_controller.getAnalog(okapi::ControllerAnalog::rightX)*200;


      if(std::abs(LVJoy)<5)    LVJoy=0;
      if(std::abs(RVJoy)<5)    RVJoy=0;
      if(std::abs(LHJoy)<100)    LHJoy=0;
      if(std::abs(RHJoy)<100)    RHJoy=0;

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
    namespace Auton{
      // namespace Ramp{
      //   void Calc(){
      //     Ya.Calculate();
      //     Xa.Calculate();
      //     Za.Calculate();
      //
      //     Yv.Calculate(Ya.Output());//ramp yv by ya's output
      //     Xv.Calculate(Xv.Output());
      //     Zv.Calculate(Za.Output());
      //
      //     arcade(Yv.Output(), Xa.Output(), Zv.Output());//output velocitys to motor
      //   }
      //   void move(double y,double x,int maxV=200){//y=forward distance inches,x=forward distance inches,z=yaw=turnRight degrees
      //     int yMaxV=y*maxV/(std::abs(y)+std::abs(x));//relitive y max velocity to hit target at the same time
      //     int xMaxV=x*maxV/(std::abs(y)+std::abs(x));//relitive x max velocity to hit target at the same time
      //
      //     Yv.set_limits(std::abs(yMaxV), -std::abs(yMaxV));//limit to max velocitys
      //     Xv.set_limits(std::abs(xMaxV), -std::abs(xMaxV));//limit to max velocitys
      //
      //     Ya.Request(25*SGN(y));//accelerate in target direction
      //     Xa.Request(25*SGN(x));//accelerate in target direction
      //     double RampDistance=0;
      //     while(y-yactural)
      //   }
      // }
      // int maxRPM=200;
      // double Width=11.5;//distance between left to right wheels
      // double Length=8;//distance between front to back wheels
      // double WheelCir=4*M_PI;
      //
      // double forwardSum=0;
      // double strafeSum=0;
      // double yawSum=0;

      void drive(double in){
        front_left_motor.moveRelative(in,200);
        back_left_motor.moveRelative(in,200);
        front_right_motor.moveRelative(in,200);
        back_right_motor.moveRelative(in,200);
      }
      bool isSettled(){
        if(front_left_motor.getActualVelocity()>0) return false;
        if(back_left_motor.getActualVelocity()>0) return false;
        if(front_right_motor.getActualVelocity()>0) return false;
        if(back_right_motor.getActualVelocity()>0) return false;
        return true;
      }
      void DriveRamping(void* why){//sets drive motors to spin
        LeftN.Enabled=true;
        while(LeftN.Enabled){
          LeftN.Calculate();
          RightN.Calculate();
          LeftS.Calculate();
          RightS.Calculate();
          set_v(LeftN.Output()+LeftS.Output(),RightN.Output()-LeftS.Output(),LeftN.Output()-RightS.Output(),RightN.Output()+RightS.Output());
        }
      }
      void DRN(int l,int r){//update the drive ramping requested values
        LeftN.Request(l);
        RightN.Request(r);
      }
      void DIN(int l,int r){//drive instentaniouly
        LeftN.Instant(l);
        RightN.Instant(r);
        set_v(LeftN.Output()+LeftS.Output(),RightN.Output()-LeftS.Output(),LeftN.Output()-RightS.Output(),RightN.Output()+RightS.Output());
      }
      void DRS(int l,int r){//update the drive ramping requested values
        LeftS.Request(l);
        RightS.Request(r);
      }
      void DIS(int l,int r){//drive instentaniouly
        LeftS.Instant(l);
        RightS.Instant(r);
        set_v(LeftN.Output()+LeftS.Output(),RightN.Output()-LeftS.Output(),LeftN.Output()-RightS.Output(),RightN.Output()+RightS.Output());
      }
      void Drive(double Dis,int Pct=50,int EndWait=1,int Correction=1){
        double Dir=SGN(Dis);
        double Rev=std::abs(Dis)/WheelCir;
        int Pct1=0;
        int Pct2=0;
        front_left_motor.tarePosition();
        back_left_motor.tarePosition();
        front_right_motor.tarePosition();
        back_right_motor.tarePosition();

        while(std::abs(front_left_motor.getPosition())<std::abs(Rev)){
          double Input1=front_left_motor.getPosition();
          double Input2=front_right_motor.getPosition();
          if(std::abs(Input1)>std::abs(Input2)){
            Pct1=Pct-Correction;
            Pct2=Pct;
          }
          else if(std::abs(Input1)<std::abs(Input2)){
            Pct1=Pct;
            Pct2=Pct-Correction;
          }
          else if(std::abs(Input1)==std::abs(Input2)){
            Pct1=Pct;
            Pct2=Pct;
          }
          Pct1=Pct1*Dir;
          Pct2=Pct2*Dir;
          DRN(Pct1,Pct2);
          pros::delay(5);
        }
        if(EndWait==-1){//                                                          Junction
          //only use if another drive command fallows
        }
        else if(EndWait>0){//default; set stop, wait for stop, wait for endwait;    StopWait
          //QDRS();//quick drive ramp stop
          DRN(0,0);
          while(!isSettled()){pros::delay(5);}
          pros::delay(EndWait);
        }
        else{//>=0,!=-1; set stop dont wait;                                        Stop
          DRN(0,0);
        }
      }
      void DriveRecon(int Pct,int Wait,int EndWait=250){
        DRN(Pct,Pct);
        pros::delay(Wait);
        if(EndWait>0){
          DRN(0,0);
          while(!isSettled()){pros::delay(5);}
        }
        else if(EndWait==0){
        }
      }
      void DriveS(double Dis,int Pct=50,int EndWait=1,int Correction=1){
        double Dir=SGN(Dis);
        double Rev=std::abs(Dis)/WheelCir;
        int Pct1=0;
        int Pct2=0;
        front_left_motor.tarePosition();
        back_left_motor.tarePosition();
        front_right_motor.tarePosition();
        back_right_motor.tarePosition();
        while(std::abs(front_right_motor.getPosition())<std::abs(Rev)){
          double Input1=front_right_motor.getPosition();
          double Input2=back_right_motor.getPosition();
          if(std::abs(Input1)>std::abs(Input2)){
            Pct1=Pct-Correction;
            Pct2=Pct;
          }
          else if(std::abs(Input1)<std::abs(Input2)){
            Pct1=Pct;
            Pct2=Pct-Correction;
          }
          else if(std::abs(Input1)==std::abs(Input2)){
            Pct1=Pct;
            Pct2=Pct;
          }
          Pct1=Pct1*Dir;
          Pct2=Pct2*Dir;
          DRS(Pct1,Pct2);
          pros::delay(5);
        }
        if(EndWait==-1){//                                                          Junction
          //only use if another drive command fallows
        }
        else if(EndWait>0){//default; set stop, wait for stop, wait for endwait;    StopWait
          //QDRS();//quick drive ramp stop
          DRS(0,0);
          while(!isSettled()){pros::delay(5);}
          pros::delay(EndWait);
        }
        else{//>=0,!=-1; set stop dont wait;                                        Stop
          DRS(0,0);
        }
      }
      void DriveReconS(int Pct,int Wait,int EndWait=1){
        DRS(Pct,Pct);
        pros::delay(Wait);
        if(EndWait>0){
          DRS(0,0);
          while(!isSettled()){pros::delay(5);}
        }
        else if(EndWait==0){
        }
      }
      void TurnEnc(double deg,int v,int endwait){
        int Dir=SGN(deg);
        int LPct=v*Dir;
        int RPct=v*Dir;

        front_left_motor.tarePosition();
        back_left_motor.tarePosition();
        front_right_motor.tarePosition();
        back_right_motor.tarePosition();

        double ZActual=(-front_left_motor.getPosition()+front_right_motor.getPosition()-back_left_motor.getPosition()+back_right_motor.getPosition())*(WheelCir/40)*180/M_PI; //what the robots currant z is
        while(std::abs(ZActual)<std::abs(deg)){
          DIN(LPct,-RPct);
          pros::delay(5);
          ZActual=(-front_left_motor.getPosition()+front_right_motor.getPosition()-back_left_motor.getPosition()+back_right_motor.getPosition())*(WheelCir/40)*180/M_PI; //what the robots currant z is
        }
        DIN(0,0);
        pros::delay(endwait);
      }
      // namespace good{
      //   void calcDis(double forward, double strafe, double yaw){
      //     forwardSum+=forward;
      //     strafeSum+=strafe;
      //     yawSum+=yaw;
      //
      //     front_left_motor.set_target((forward-strafe-((Width+Length)/2)*(yaw*M_PI/180))/WheelCir);
      //     back_left_motor.set_target((forward+strafe+((Width+Length)/2)*(yaw*M_PI/180))/WheelCir);
      //     front_right_motor.set_target((forward+strafe-((Width+Length)/2)*(yaw*M_PI/180))/WheelCir);
      //     back_right_motor.set_target((forward-strafe+((Width+Length)/2)*(yaw*M_PI/180))/WheelCir);
      //   }
      //   void calcVelRatio(){
      //     double maxTargetDelta=std::max(front_left_motor.get_targetDelta(), std::max(back_left_motor.get_targetDelta(), std::max(front_right_motor.get_targetDelta(), back_right_motor.get_targetDelta())));
      //
      //     front_left_motor.set_RPM(front_left_motor.get_targetDelta()*maxRPM/maxTargetDelta);
      //     back_left_motor.set_RPM(back_left_motor.get_targetDelta()*maxRPM/maxTargetDelta);
      //     front_right_motor.set_RPM(front_right_motor.get_targetDelta()*maxRPM/maxTargetDelta);
      //     back_right_motor.set_RPM(back_right_motor.get_targetDelta()*maxRPM/maxTargetDelta);
      //   }
      //   void Absolute(double forward, double strafe, double yaw){
      //     calcDis(forward, strafe, yaw);
      //     calcVelRatio();
      //
      //     front_left_motor.moveAbsolute(front_left_motor.get_target(),front_left_motor.get_RPM());
      //     back_left_motor.moveAbsolute(back_left_motor.get_target(),back_left_motor.get_RPM());
      //     front_right_motor.moveAbsolute(front_right_motor.get_target(),front_right_motor.get_RPM());
      //     back_right_motor.moveAbsolute(back_right_motor.get_target(),back_right_motor.get_RPM());
      //   }
      //   void AbsolutelyRelative(double forward, double strafe, double yaw){
      //     forward+=forwardSum;
      //     strafe+=strafeSum;
      //     yaw+=yawSum;
      //     calcDis(forward, strafe, yaw);
      //     calcVelRatio();
      //
      //     front_left_motor.moveAbsolute(front_left_motor.get_target(),front_left_motor.get_RPM());
      //     back_left_motor.moveAbsolute(back_left_motor.get_target(),back_left_motor.get_RPM());
      //     front_right_motor.moveAbsolute(front_right_motor.get_target(),front_right_motor.get_RPM());
      //     back_right_motor.moveAbsolute(back_right_motor.get_target(),back_right_motor.get_RPM());
      //   }
      // }
    }
  }
