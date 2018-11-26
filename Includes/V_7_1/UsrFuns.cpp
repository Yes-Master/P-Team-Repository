void LiftControl(){
    if(Controller1.ButtonRight.pressing())      LiftSMS(100);
    else if(Controller1.ButtonLeft.pressing())  LiftSMS(-100);
    else                                        LiftSMS(0);
}
//
//rstet timer if ball in puncher or
void IntakeAutoUpDate(){//UpDate Sensors Code
    //Puncher UpDate
    if(PuncSen.value(vex::analogUnits::pct)<PuncBallTal){
        GlobTime=0;//reset timer
        PuncBall=true;
        ComRum=false;
    }  
    else{
        if(PuncherControlEnabled)           PuncBall=false;
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
        if(DriveMotorInverted==true){//if in fliper
            DriveMotorInverted=false;//set drive dir for baller
            FliperRequested=FliperPosUp;//put fliper up
        }
    }
    else if(!Controller1.ButtonA.pressing() && APressed)    APressed=false;

    IntakeAuto();
}
void IntakeManualControl(){//Controller Manual OverRide
    if(Controller1.ButtonR2.pressing()){
        IntakeManualControlEnabled=true;
        IntakeSetting=IntakePctOut;
    }
    else if(Controller1.ButtonR1.pressing()){
        IntakeManualControlEnabled=true;   
        IntakeSetting=IntakePctIn;
    }
    else if(IntakeManualControlEnabled){//first loop disabled
        IntakeAutoEnabled=false;
        IntakeManualControlEnabled=false;
        IntakeSetting=IntakePctStop;
    }
}
void IntakeControl(){//OverRide Control Code
    IntakeManualControl();
    if(!IntakeManualControlEnabled) IntakeAutoControl();
    IntakeSMS(IntakeSetting);
}
//
void PuncherControl(){
    if(Controller1.ButtonX.pressing()){
        PuncherControlEnabled=true;
        IntakeSetting=IntakePctStop;
        if(FliperRequested==FliperPosUp) FliperRequested=FliperPosMid;
        PuncherSMS(100);
    }
    else if(PuncherControlEnabled){//first loop not enabled
        PuncherSMS(0);
        if(FliperRequested==FliperPosMid)    FliperRequested=FliperPosUp;
        IntakeTimeEnabled=true;
        PuncherControlEnabled=false;
    }
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
    if(FliperRequested==FliperPosUp){
        FliperRequested=FliperPosDown;
        if(DriveMotorInverted==false){//if in baller mode; acts as toggle
            DriveMotorInverted=true;//set drive dir to flipper
            IntakeAutoEnabled=false;//disable auto intake
        }
    }
    else if(FliperRequested==FliperPosMid)   FliperRequested=FliperPosDown;
    else if(FliperRequested==FliperPosDown)  FliperRequested=FliperPosUp;
}
void FliperPosControl(){
    if(Controller1.ButtonL1.pressing() && !L1Pressed){
        L1Pressed=true;
        FliperFlip();
        FliperPosControlEnabled=true;
    }
    if(!Controller1.ButtonL1.pressing() && L1Pressed)   L1Pressed=false;

    if(FliperPosControlEnabled){
        FlipMotor.startRotateTo(FliperRequested,vex::rotationUnits::deg,100,vex::velocityUnits::pct);
    }
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
        DriveBrake=!DriveBrake;
    }
    else if(!Controller1.ButtonL2.pressing() && L2Pressed)   L2Pressed=false;

    if(DriveBrake){
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
    if(Controller1.ButtonUp.pressing() && !UpPressed){
        UpPressed=true;
        DriveMotorInverted=!DriveMotorInverted;
        if(DriveMotorInverted==true)    IntakeAutoEnabled=false;//disable intake auto when switching to cap drive dir
    }
    else if(!Controller1.ButtonUp.pressing() && UpPressed)  UpPressed=false;
}
void DriveManualControl(){
    LJoy=Controller1.Axis3.value();
    RJoy=Controller1.Axis2.value();

    if(std::abs(LJoy)<5)    LJoy=0;
    if(std::abs(RJoy)<5)    RJoy=0;
    
    if(LJoy!=0 || RJoy!=0){
        DriveManualControlEnabled=true;
        DriveSMS(DriveMotorInverted ? -RJoy : LJoy,DriveMotorInverted ? -LJoy : RJoy);
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