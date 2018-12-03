int GlobTime=0;
//
bool LiftPosControlEnabled=false;
int LiftRequested=0;
int LiftUp=5;
int LiftTal=5;
//
bool PuncherControlEnabled=false;
//
bool APressed=false;//auto intake toggle
bool IntakeManualControlEnabled=false;
bool IntakeToggleControlEnabled=false;
bool IntakeTimeEnabled=false;
int IntakePctOut=-100;
int IntakePctStop=0;
int IntakePctIn=100;
//enum Intake{OUT=-100,STOP=0,IN=100};
int IntakeSetting=IntakePctStop;
bool IntakeBallsEnabled=false;
bool IntakeStateUpDateEnabled=true;
int PuncBallTimeWait=1000;
int ComRumTime=150;
bool ComRumerEnabled=false;
bool ComRum=false;
//
bool FliperManualControlEnabled=false;
bool FliperPosControlEnabled=true;
bool L1Pressed=false;
int FliperPosIn=-10;
int FliperPosInPun=-60;
int FliperPosUpMid=-250;
int FliperPosDown=-450;
int FliperPosTal=5;
//enum Fliper{UP=-10,DOWN=-450,MID=-60,TAL=5};
int FliperRequested=FliperPosIn;
//
bool FeedBall=false;
bool PuncBall=false;
int Feed1BallTal=60;
int Feed2BallTal=60;
int PuncBallTal=60;

bool IntakeAutoEnabledWas=false;
bool IntakeAutoEnabled=false;
//
bool DriveMotorInverted=false;
bool DriveMotorInvertedWas=false;
bool UpPressed=false;//Drive Dir toggle pressed
bool DriveManualControlEnabled=false;
bool L2Pressed=false;//brake toggle pressed
bool DriveBrake=false;
int LJoy=0;
int RJoy=0;
//auto
enum class AutoMoveStop{//control of auto functions ending
    StopWait,//Stop move and wait for move to finish
    Stop,//stop move don't wait for move to finish
    Junction//don't stop move or wait for move to finish
    };//there is still an EndWait after this block
int DriveEndWait=100;
int TurnEndWait=250;
int PuncherEndWait=250;
int FliperEndWait=250;
bool DriveRampingEnabled=true;//task
bool IntakeAutonEnabled=true;//task
bool ControllerScreenEnabled=true;//task
bool StartEnabled=false;//task
bool BrainPressed=false;
//end auto
//calibration
int FliperCalTime=0;
int PuncherCalTime=0;
int GyroCalTime=0;
//end calibration