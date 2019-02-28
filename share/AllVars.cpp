//AllVars
    //Basic Motors
        bool MotorsCaled=false;
        float WheelCir=4*M_PI;
double DRMax=1;
bool DriveSide=false;//used for auton janky plz no
//Flow Control
    int IntakeTimer=0;//timer for the intake
    // enum class AutoMoveStop{//control of auto functions ending
    //     StopWait,//Stop move and wait for move to finish
    //     Stop,//stop move don't wait for move to finish
    //     Junction//don't stop move or wait for move to finish
    //     };//there is still an EndWait after this block
    enum class ControlModes {Flag,Caps,Debug};
    ControlModes ControlMode = ControlModes::Flag;

    enum class StartPos {FrontRed,BackRed,FrontBlue,BackBlue};
    enum class ProgPot {Pink,Green,Yellow};
    enum class Variant {White,Black,Purple};
    StartPos FeildPos = StartPos::FrontRed;
    ProgPot AutoProg = ProgPot::Green;
    Variant AVariant = Variant::Black;

    StartPos FeildPosBrainScreenSetColorLast = FeildPos;

    StartPos FeildPosControllerScreenPrintAutonosLast = FeildPos;
    ProgPot AutoProgControllerScreenPrintAutonosLast = AutoProg;
    Variant AVariantControllerScreenPrintAutonosLast = AVariant;
//Autonos
    int DriveEndWait=50;
    int TurnEndWait=100;
    int PuncherEndWait=0;
    int FliperEndWait=0;
    bool DriveRampingEnabled=true;//task
    bool IntakeAutonEnabled=true;//task
    bool ControllerScreenEnabled=true;//task
    bool StartEnabled=false;//task

//Controler Init
    int LVJoy=0;
    int RVJoy=0;
    int LHJoy=0;
    int RHJoy=0;
    bool L1Pressed=false;//lift     clamp
    bool L2Pressed=false;//brake    brake
    bool R2Pressed=false;//intake   liftdown
    bool R1Pressed=false;//puncher  liftup
    bool XPressed=false;//intake    intake
    bool YPressed=false;//intake    intake
    bool BPressed=false;//NULL      NULL
    bool APressed=false;//intake    intake
    bool UPressed=false;//caps      flag
    bool RPressed=false;//
    bool DPressed=false;//
    bool LPressed=false;//lift      lift
//Tog Bools
    bool ConModeTogBtnPressed=false;//mode tog
    bool Parked=false;//toggle for if lift is set to parking state
    // bool DrivePIDTAskEnabled=false;
//Task Bools
    bool PuncherControlEnabled=false;
    bool IntakeStateUpDateEnabled=true;
    bool ComRumerEnabled=false;
    bool BrainScreenStartFunEnabled=false;
    bool ControllerScreenStartFunEnabled=false;
    bool ControllerScreenUsrFunEnabled=false;
    bool BrainScreenUsrFunEnabled=false;
    bool StartInited=false;
    bool DoubleShotTaskEnabled=false;
    // bool LiftRampingEnabled=false;
    bool LiftA=false;
//Clamp
    //Positions
        int ClampPosIn=-75;
        int ClampPosUp=25;
        int ClampPosDown=250;
//Lift
    //Positions
        int LiftPosDown=10;
        int LiftPosPunDown=175/2;//back
        int LiftPosPunUp=160;//front
        int LiftPosUp=160;
        
//Puncher
    //Control
        bool PuncherCharged=false;//if the puncher is charged back
    //Positions
        int PunPosFromReleasedToCharged=240;//the number to add to get from released to charged pos
        int PunPosFromChargedToReleased=120;//the number to add to get form charged to released pos
        int PuncherPosSetting=0;//needs to be rel to last request; add to TMotors
//PuncherPos
    //Control
    //Positions
        int PuncherPosPosSetting=0;
        int PucherPosPos[4]={0,5,30,75};
    //Pct
        int PuncherPosPctSetting=0;
    //SpinTo
        //Auton

//Intake
    //Control
        bool IntakeManualControlEnabled=false;
        bool IntakeToggleControlEnabled=false;
        bool IntakeAutoEnabled=false;
        bool IntakeAutoEnabledWas=false;
        bool IntakeOverMode=false;
        int IntakeOverModeTimer=0;
    //Pct
        int IntakePctOut=-100;
        int IntakePctStop=0;
        int IntakePctIn=100;
        int IntakePctSetting=IntakePctStop;

    //IntakeAuto
        bool PuncBallActual=false;
        bool PuncBall=false;
        bool OverBall=false;
        bool Feed2Ball=false;
        bool Feed1Ball=false;
        int Feed1BallTal=65;
        int Feed2BallTal=65;
        int OverBallTal=65;
        int PuncBallTal=60;
        //Controller
            int PuncBallTimeWait=1000;
            int ComRumTime=150;
            bool ComRum=false;
    //Flag
        int IntakeFlagTimer=0;//local timer for R2
//Drive
        //Control
            vex::brakeType DriveBrakeType=vex::brakeType::coast;
            bool DriveMotorInverted=false;
            bool DriveMotorInvertedWas=false;
            bool DriveManualControlEnabled=false;
            bool DriveSlowEnabled=false;
        //Pct
            int FLDriveVSetting=0;
            int FRDriveVSetting=0;
            int BLDriveVSetting=0;
            int BRDriveVSetting=0;
//FlowControl
    //Screens
        //con
            ControlModes ControlModeConPrintWas = ControlMode;
            bool IntakeAutoEnabledConPrintWas=IntakeAutoEnabled;
            int BrainBatWas=Brain.Battery.capacity();
