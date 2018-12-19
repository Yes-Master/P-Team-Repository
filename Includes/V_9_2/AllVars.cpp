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

//Basic Motor
    //Set To Spin
    bool PuncherSTS=false;
    bool PuncherPosSTS=false;
    bool IntakeSTS=false;
    bool FliperSTS=false;

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
bool L2Pressed=false;//DriveBrakeTog
bool R2Pressed=false;//Intake=Out
bool R1Pressed=false;//Intake=In

bool UpPressed=false;
bool DownPressed=false;
bool LeftPressed=false;
bool RightPressed=false;

bool YPressed=false;//DriveDir
bool APressed=false;//IntakeAutoEnabled

//Task Bools
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
bool DriveMotorInvertedWas=DriveMotorInverted;
bool DriveManualControlEnabled=false;
bool DriveHold=false;
bool DriveHoldWas=DriveHold;
int LJoy=0;
int RJoy=0;
int LSJoy=0;
int RSJoy=0;

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
int PuncherDeg=0;
int PuncherPctSetting=0;
bool Charged=false;//if the puncher is ready to fire
bool PuncherSpinToControlEnabled=false;//Puncher is charging or fireing

//PuncherPos
bool PuncherPosSpinToControlEnabled=false;
enum class PuncherPositions {ShortTop,ShortMid};
PuncherPositions PuncherPos=PuncherPositions::ShortTop;
int PuncherPosPctSetting=0;
bool PuncherSpinToControlRunEnabled=false;//dont continue to hit target
int PuncherPosDeg=10;
bool PuncherPosSpinToControlRunEnabled=false;

//Fliper
bool FliperManualControlEnabled=false;
bool FliperPosControlEnabled=true;
int FliperPosIn=-5;
int FliperPosInPun=-60;
int FliperPosUpMid=-200;
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
