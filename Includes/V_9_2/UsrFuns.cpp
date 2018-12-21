/*Need to
add enum class for charging fire or not moving
*/
/*Change Log
BtnX->BtnR1 Puncher Control && Post Punch enable auto intake if rotated more than 340 deg and there is not a ball in the puncher
add controller rumble every time charged or fired
add tollerances to puncher pos control && puncher fire lockout
*/
//
/*
Joy1    RightSide
Joy2    Right
Joy3    Left
Joy4    LeftSide
L1      HOLD:DriveBrake TOG:PuncherCharge
L2                      TOG:DriveBrakeTog
R1      HOLD:IntakeIn;  TOG:Fliper=In,DriveDir=Ball,IntakeAutoEnabled=false;
R2      HOLD:InkakeOut; TOG:Fliper=In,DriveDir=Ball,IntakeAutoEnabled=true;
Up                      TOG:PunPos=1;closeup    2
Down                    TOG:PunPos=4;fardown    4.25
Left                    TOG:PunPos=2;closedown  4
Right                   TOG:PunPos=3;farup      3.25
Y       NULL
B       NULL
X                       TOG:DriveDir
A                       TOG:IntakeAutoEnabled,Fliper=In,DriveDir=Ball
*/
//rstet timer if ball in puncher or
void IntakeAutoUpDate(){//UpDate Sensors Code
    //Puncher UpDate
    if(PuncSen.value(vex::analogUnits::pct)<PuncBallTal){
        GlobTime=0;//reset timer
        PuncBall=true;
        ComRum=false;
    }  
    else{
        if(PuncherSpinToControlEnabled)           PuncBall=false;
        else{
            if(GlobTime>PuncBallTimeWait)   PuncBall=false;
            else if(GlobTime>ComRumTime)    ComRum=true;
            GlobTime=GlobTime+1;//add one to timer
        } 
    }
    //FeedBall UpDate
    if(FeedSen1.value(vex::analogUnits::pct)<Feed1BallTal || FeedSen2.value(vex::analogUnits::pct)<Feed2BallTal)    FeedBall=true;
    else                                                                                                            FeedBall=false;
}
void IntakeAuto(){//Autonomous Logic Control
    if(IntakeAutoEnabled){
        IntakeAutoEnabledWas=true;
        if(!PuncBall)       IntakeSetting=IntakePctIn;
        else{
            if(!FeedBall)   IntakeSetting=IntakePctIn;
            else            IntakeSetting=IntakePctStop;
        }
    }
    else if(IntakeAutoEnabledWas){//first loop disabled
        IntakeSetting=IntakePctStop;
        IntakeAutoEnabledWas=false;
    }
}
int IntakeStateUpDate(){//Task to UpDate IntakeAutoUpDate every second in the background
    while(1){
        IntakeAutoUpDate();
        vex::task::sleep(5);
    }
}
void IntakeAutoControl(){//Controller Input To control Autonomous Logic Control
    if(Controller1.ButtonA.pressing() && !APressed){
        APressed=true;
        IntakeAutoEnabled=!IntakeAutoEnabled;//toggle intake auto enable
        FliperRequested=FliperPosIn;//put fliper in
        DriveMotorInverted=false;//set Ball DriveDir
    }
    else if(!Controller1.ButtonA.pressing() && APressed)    APressed=false;

    IntakeAuto();
}
//right down  hold(outfeed) && toggle(DriveMode=Baller,Autointake=true,FLiperrequested=fliperposin,)
void IntakeManualControl(){//Controller Manual OverRide
    if(Controller1.ButtonR2.pressing()){
        IntakeManualControlEnabled=true;//halt auto intake function from running
        IntakeSetting=IntakePctOut;//out feed the intake
        if(!R2Pressed){//Init
            R2Pressed=true;
            DriveMotorInverted=false;//Baller drive dir;
            FliperRequested=FliperPosIn;//put fliper in
            IntakeAutoEnabled=true;//Enable AutoIntake for after manual control
        }
    }
    else if(!Controller1.ButtonR2.pressing() && R2Pressed)  R2Pressed=false;//DeInit

    else if(Controller1.ButtonR1.pressing()){//btnR1
        IntakeManualControlEnabled=true;   
        IntakeSetting=IntakePctIn;
        if(!R1Pressed){//Init
            R1Pressed=true;
            DriveMotorInverted=false;//Baller drive dir;
            FliperRequested=FliperPosIn;//put fliper in
            IntakeAutoEnabled=false;//Disable Autointake for after manual control
        }
    }
    else if(!Controller1.ButtonR1.pressing() && R1Pressed)  R1Pressed=false;//DeInit

    else if(IntakeManualControlEnabled){//DeInit
        IntakeManualControlEnabled=false;
        if(!IntakeAutoEnabled)  IntakeSetting=IntakePctStop;//if not auto controlled stop intakeing
    }
}
void IntakeComRumer(){
    if(ComRum && IntakeAutoEnabled && IntakeSetting==IntakePctStop)  vex::task ComRumerTask(ComRumerFun);
}
void IntakeControl(){//OverRide Control Code
    IntakeManualControl();
    if(!IntakeManualControlEnabled) IntakeAutoControl();
    IntakeSMS(IntakeSetting);
    IntakeComRumer();
}

void PuncherChargeControl(){
    if(Controller1.ButtonL1.pressing() && !L1Pressed){
        L1Pressed=true;
        vex::task CompRumerTask(ComRumerFun);
        if(Charged && !PuncherPosSTS){//if charged && the puncherPos is not spining
            PuncherDeg+=90;
            PuncherSpinToControlRunEnabled=true;//enable puncherspinto
            Charged=false;
        }
        else if(!Charged){
            PuncherDeg+=270;
            PuncherSpinToControlRunEnabled=true;//enable puncherspinto
            Charged=true;
        }
    }
    else if(!Controller1.ButtonL1.pressing() && L1Pressed)  L1Pressed=false;

    PuncherSpinTo(PuncherDeg,true);//spin motor to puncherDeg && set motor to spin
}
void PuncherPosControl(){
    if(Controller1.ButtonUp.pressing() && !UpPressed){
            UpPressed=true;
            PuncherPosDeg=300;
            PuncherPosSpinToControlRunEnabled=true;
    }
    else if(!Controller1.ButtonUp.pressing() && UpPressed)          UpPressed=false;

    else if(Controller1.ButtonLeft.pressing() && !LeftPressed){
            LeftPressed=true;
            PuncherPosDeg=200;
            PuncherPosSpinToControlRunEnabled=true;
        }
    else if(!Controller1.ButtonLeft.pressing() && LeftPressed)      LeftPressed=false;

    else if(Controller1.ButtonRight.pressing() && !RightPressed){
            RightPressed=true;
            PuncherPosDeg=100;
            PuncherPosSpinToControlRunEnabled=true;
        }
    else if(!Controller1.ButtonRight.pressing() && RightPressed)    RightPressed=false;

    else if(Controller1.ButtonDown.pressing() && !DownPressed){
        DownPressed=true;
        PuncherPosDeg=500;
        PuncherPosSpinToControlRunEnabled=true;
    }
    else if(!Controller1.ButtonDown.pressing() && DownPressed)      DownPressed=false;

    PuncherPosSpinTo(PuncherPosDeg,true);//spin motor to && set motor to spin
}
void PuncherControl(){
    PuncherPosControl();
    PuncherChargeControl();
}
//
void FliperManualControl(){
    if(Controller1.ButtonRight.pressing()){
        FliperManualControlEnabled=true;
        FliperSMS(100);  
    }
    else if(Controller1.ButtonLeft.pressing()){
        FliperManualControlEnabled=true;
        FliperSMS(-100);
    }
    else if(FliperManualControlEnabled){//first loop
        FliperSMS(0);
        FliperManualControlEnabled=false;
    }
}
void FliperFlip(){
    if(FliperRequested==FliperPosIn || FliperRequested==FliperPosInPun){//getting out of baller
        FliperRequested=FliperPosDown;
        DriveMotorInverted=true;//set drive dir to flipper
        IntakeAutoEnabled=false;//disable auto intake
    }
    else if(FliperRequested==FliperPosUpMid)    FliperRequested=FliperPosDown;
    else if(FliperRequested==FliperPosDown)     FliperRequested=FliperPosUpMid;
    if(DriveMotorInverted==false)               FliperRequested=FliperPosIn;//if in baller be in
}
void FliperPosControl(){/*
    if(Controller1.ButtonL1.pressing() && !L1Pressed){
        L1Pressed=true;
        FliperFlip();
        FliperPosControlEnabled=true;
    }
    if(!Controller1.ButtonL1.pressing() && L1Pressed)   L1Pressed=false;

    if(FliperPosControlEnabled){
        FlipMotor.startRotateTo(FliperRequested,vex::rotationUnits::deg,100,vex::velocityUnits::pct);
    }*/
}
void FliperControl(){
    //FliperManualControl();
    //if(!FliperManualControlEnabled) FliperPosControl();
    FliperPosControl();
}
//
void DriveHoldControl(){
    if(Controller1.ButtonL2.pressing() && !L2Pressed){
        L2Pressed=true;
        DriveHold=!DriveHold;
    }
    else if(!Controller1.ButtonL2.pressing() && L2Pressed)   L2Pressed=false;

    if(DriveHold){
        FLDriveMotor.setStopping(vex::brakeType::hold);
        FRDriveMotor.setStopping(vex::brakeType::hold);
        BLDriveMotor.setStopping(vex::brakeType::hold);
        BRDriveMotor.setStopping(vex::brakeType::hold);
    }
    else{
        FLDriveMotor.setStopping(vex::brakeType::coast);
        FRDriveMotor.setStopping(vex::brakeType::coast);
        BLDriveMotor.setStopping(vex::brakeType::coast);
        BRDriveMotor.setStopping(vex::brakeType::coast); 
    }
}
void DriveDirToggle(){
    if(Controller1.ButtonX.pressing() && !XPressed){
        XPressed=true;
        DriveMotorInverted=!DriveMotorInverted;//false:Ball; true:cap;
        if(DriveMotorInverted==true)    IntakeAutoEnabled=false;//disable intake auto when switching out of BallDir
        FliperRequested=FliperPosIn;
    }
    else if(!Controller1.ButtonX.pressing() && XPressed)  XPressed=false;
}
void DriveManualControl(){
    LJoy=Controller1.Axis3.value();
    RJoy=Controller1.Axis2.value();
    LSJoy=Controller1.Axis4.value();
    RSJoy=Controller1.Axis1.value();

    if(std::abs(LJoy)<5)    LJoy=0;
    if(std::abs(RJoy)<5)    RJoy=0;
    if(std::abs(LSJoy)<15)  LSJoy=0;
    if(std::abs(RSJoy)<15)  RSJoy=0;
    
    if(LJoy!=0 || RJoy!=0 || LSJoy!=0 || RSJoy!=0){
        DriveManualControlEnabled=true;
        DriveTankSMS(
            DriveMotorInverted ? -RJoy : LJoy,
            DriveMotorInverted ? -LJoy : RJoy,
            DriveMotorInverted ? -RSJoy : LSJoy,
            DriveMotorInverted ? -LSJoy : RSJoy);
    }
    else{
        if(DriveManualControlEnabled)  DriveSMS(0,0);//Last loop before disableing; used to release drivemanualcontrol
        DriveManualControlEnabled=false;
    }
}
void DriveControl(){
    DriveDirToggle();
    DriveManualControl();
    DriveHoldControl();
}