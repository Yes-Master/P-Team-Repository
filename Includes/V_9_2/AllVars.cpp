//need to find a place for

//Flow Control
int FliperCalTime=0;
int PuncherCalTime=0;
int GlobTime=0;
enum class AutoMoveStop{//control of auto functions ending
    StopWait,//Stop move and wait for move to finish
    Stop,//stop move don't wait for move to finish
    Junction//don't stop move or wait for move to finish
    };//there is still an EndWait after this block
enum class StartPos {FrontRed,BackRed,FrontBlue,BackBlue};
enum class ProgPot {Pink,Green,Yellow};
StartPos FeildPos = StartPos::FrontRed;
ProgPot AutoProg = ProgPot::Green;

StartPos FeildPosBrainScreenSetColorLast = FeildPos;

StartPos FeildPosControllerScreenPrintAutonosLast = FeildPos;
ProgPot AutoProgControllerScreenPrintAutonosLast = AutoProg;

//Autonos
int DriveEndWait=100;
int TurnEndWait=250;
int PuncherEndWait=250;
int FliperEndWait=250;
bool DriveRampingEnabled=true;//task
bool IntakeAutonEnabled=true;//task
bool ControllerScreenEnabled=true;//task
bool StartEnabled=false;//task
bool BrainPressed=false;

//Toggle Btns
bool R2Pressed=false;
bool R1Pressed=false;
bool APressed=false;//auto intake toggle
bool L1Pressed=false;
bool L2Pressed=false;//brake toggle pressed
bool UpPressed=false;//Drive Dir toggle pressed

//Task Bools
bool PuncherControlEnabled=false;
bool IntakeStateUpDateEnabled=true;
bool ComRumerEnabled=false;
bool IntakeAutoEnabled=false;
bool IntakeAutoEnabledWas=false;
bool BrainScreenStartFunEnabled=false;
bool ControllerScreenStartFunEnabled=false;
bool ControllerScreenUsrFunEnabled=false;
bool BrainScreenUsrFunEnabled=false;
//Drive
bool DriveMotorInverted=false;
bool DriveMotorInvertedWas=false;
bool DriveManualControlEnabled=false;
bool DriveHold=false;
int LJoy=0;
int RJoy=0;

//Intake
bool IntakeManualControlEnabled=false;
bool IntakeToggleControlEnabled=false;
bool IntakeTimeEnabled=false;
int IntakePctOut=-100;
int IntakePctStop=0;
int IntakePctIn=100;
int IntakeSetting=IntakePctStop;
bool IntakeBallsEnabled=false;

//Puncher


//Fliper
bool FliperManualControlEnabled=false;
bool FliperPosControlEnabled=true;
int FliperPosIn=-5;
int FliperPosInPun=-60;
int FliperPosUpMid=-250;
int FliperPosDown=-450;
int FliperPosTal=5;
int FliperRequested=FliperPosIn;

//Decaper
bool LiftPosControlEnabled=false;
int LiftRequested=0;
int LiftUp=5;
int LiftTal=5;

//AutoBall
bool FeedBall=false;
bool PuncBall=false;
int Feed1BallTal=60;
int Feed2BallTal=60;
int PuncBallTal=60;

int PuncBallTimeWait=1000;
int ComRumTime=150;
bool ComRum=false;
