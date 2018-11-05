#ifndef AllVars_cpp
#define AllVars_cpp
int GlobTime=0;
//
bool LiftPosControlEnabled=false;
int LiftRequested=0;
int LiftUp=5;
int LiftTal=5;
//
bool PuncherControlEnabled=false;
//
bool YPressed=false;//in
bool BPressed=false;//stop
bool APressed=false;//out
bool IntakeManualControlEnabled=false;
bool IntakeToggleControlEnabled=false;
bool IntakeTimeEnabled=false;
enum class IntakePct{OUT=-100,STOP=0,IN=100};
int IntakeSetting=int(IntakePct::STOP);
bool IntakeBallsEnabled=false;
bool IntakeStateUpDateEnabled=true;
//
bool DriveMotorInverted=false;
bool DriveInvertConBtnPressed=false;
//
bool FliperManualControlEnabled=false;
bool FliperPosControlEnabled=true;
bool L1Pressed=false;
enum class FliperPct{UP=-10,DOWN=-460,MID=-60,TAL=5};
int FliperRequested=int(FliperPct::UP);
//
bool FeedBall=false;
bool PuncBall=false;
int Feed1BallTal=65;
int Feed2BallTal=60;
int PuncBallTal=65;

bool IntakeAutoEnabledWas=false;
bool IntakeAutoEnabled=false;
//
bool DriveManualControlEnabled=false;
bool L2Pressed=false;//brake toggle pressed;
bool DriveBrake=false;
int LJoy=0;
int RJoy=0;
//auto
int DriveEndWait=250;
int TurnEndWait=250;
int PuncherEndWait=250;
int FliperEndWait=250;
int PuncherTorqueTal=1;//???????????????????????????????????
bool DriveRampingEnabled=true;//task
bool IntakeAutonEnabled=true;//task
//end auto
#endif