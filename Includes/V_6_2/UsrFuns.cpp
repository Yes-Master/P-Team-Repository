void LiftControl(){
    if(Controller1.ButtonRight.pressing())      LiftSMS(100);
    else if(Controller1.ButtonLeft.pressing())  LiftSMS(-100);
    else                                        LiftSMS(0);
}
//
//rstet timer if ball in puncher or
void IntakePuncBools(bool PB,bool CR,bool RFB){
    PuncBall=PB;
    ComRum=CR;
    ReFeedBall=RFB;
}
void IntakeAutoUpDate(){//UpDate Sensors Code
    //Puncher UpDate
    if(PuncSen.value(vex::analogUnits::pct)<PuncBallTal){
        GlobTime=0;//reset timer
        IntakePuncBools(true,false,false);
    }  
    else{
        if(PuncherControlEnabled)               IntakePuncBools(false,false,false);
        else{
            if(GlobTime>PuncBallTimeWait)       IntakePuncBools(false,false,false);
            else if(GlobTime>ReFeedBallTime)    IntakePuncBools(true,true,true);
            GlobTime=GlobTime+1;//add one to timer
        } 
    }
    //FeedBall UpDate
    if(FeedSen1.value(vex::analogUnits::pct)<Feed1BallTal || FeedSen2.value(vex::analogUnits::pct)<Feed2BallTal)    FeedBall=true;
    else                                                                                                            FeedBall=false;
}
int ReFeed(){
    ReFeedBallWas=true;//used for toggle control
    ReFeedBall=false;
    int EndTimeSliceWait=10;//msec delay at end of time slice
    int PuncLoopOut=500/EndTimeSliceWait;//if the feed ball doesnt return in this number of code loops move on; mesured in msec
    int PuncLoopCount=0;//resets the loop counter
    int FeedLoopOut=500/EndTimeSliceWait;//if the feed ball doesnt return in this number of code loops move on; mesured in msec
    int FeedLoopCount=0;//resets the loop counter
    IntakeAutoEnabled=false;//stop intake logic control loop
    IntakeAutoEnabledWas=false;//ignore the clean up; stops form jurking
    Controller1.Screen.newLine();
    Controller1.Screen.print("Punc loop started");
    while(PuncSen.value(vex::analogUnits::pct)>PuncBallTal && PuncLoopCount<PuncLoopOut){//no puncher ball feed in till ball returns to puncher
        IntakeSetting=Intake(IN);
        FeedLoopCount++;
        vex::task::sleep(10);
    }
    Controller1.Screen.newLine();
    Controller1.Screen.print("Punc loop ended");
    Controller1.Screen.newLine();
    Controller1.Screen.print("Feed loop started");
    while(FeedSen1.value(vex::analogUnits::pct)>Feed1BallTal || FeedSen2.value(vex::analogUnits::pct)>Feed2BallTal){// && FeedLoopCount<FeedLoopOut//pucnher ball returned; return ball to feed holidng position by feeding out
        IntakeSetting=Intake(OUT);
        FeedLoopCount++;
        vex::task::sleep(10);
    }
    Controller1.Screen.newLine();
    Controller1.Screen.print("Feed loop ended");
    IntakeSetting=Intake(STOP);//both balls back
    IntakeAutoEnabled=true;//start back up intake logic control loop
    return 1;
}
void IntakeAuto(){//Autonomous Logic Control
    if(IntakeAutoEnabled){
        IntakeAutoEnabledWas=true;
        if(!PuncBall)       IntakeSetting=Intake(IN);
        else{
            if(!FeedBall)   IntakeSetting=Intake(IN);
            else if(ReFeedBall && !ReFeedBallWas) vex::task ReFeedBallTask(ReFeed); 
            else            IntakeSetting=Intake(STOP);
        }
    }
    else if(IntakeAutoEnabledWas){//first loop disabled
        IntakeSetting=Intake(STOP);
        IntakeAutoEnabledWas=false;
    }
    if(!ReFeedBall) ReFeedBallWas=false;//toggle refeedball
}

int IntakeStateUpDate(){//Task to UpDate IntakeAutoUpDate every second in the background
    while(1){
        IntakeAutoUpDate();
        IntakeAuto();
        vex::task::sleep(5);
    }
}
void IntakeAutoControl(){//Controller Input To control Autonomous Logic Control
    if(Controller1.ButtonA.pressing() && !APressed){
        APressed=true;
        IntakeAutoEnabled=!IntakeAutoEnabled;
    }
    else if(!Controller1.ButtonA.pressing() && APressed)    APressed=false;
}
void IntakeManualControl(){//Controller Manual OverRide
    if(Controller1.ButtonR2.pressing()){
        IntakeManualControlEnabled=true;
        IntakeSetting=Intake(OUT);
    }
    else if(Controller1.ButtonR1.pressing()){
        IntakeManualControlEnabled=true;   
        IntakeSetting=Intake(IN);

    }
    else if(IntakeManualControlEnabled){//first loop disabled
        IntakeAutoEnabled=false;
        IntakeManualControlEnabled=false;
        IntakeSetting=Intake(STOP);
    }
}
void IntakeControl(){//OverRide Control Code
    IntakeManualControl();
    if(!IntakeManualControlEnabled) IntakeAutoControl();
    IntakeSMS(IntakeSetting);
}
//
/*
int PuncherCal(){
    PuncherMotor.setTimeout(10,vex::timeUnits::msec);
    PuncherMotor.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
    while(PMIS){}
    PuncherMotor.setTimeout(250,vex::timeUnits::msec);
    PuncherMotor.resetRotation();
    PuncherMotor.startRotateFor(300,vex::rotationUnits::deg,100,vex::velocityUnits::pct);    
    return 1;
}
*/
void PuncherControl(){
    if(Controller1.ButtonX.pressing()){
        PuncherControlEnabled=true;
        IntakeSetting=Intake(STOP);
        if(FliperRequested==Fliper(UP)) FliperRequested=Fliper(MID);
        PuncherSMS(100);
    }
    else if(PuncherControlEnabled){//first loop not enabled
        PuncherSMS(0);
        if(FliperRequested==Fliper(MID))    FliperRequested=Fliper(UP);
        IntakeTimeEnabled=true;
        PuncherControlEnabled=false;
    }
}
//

int FliperCal(){
    FlipMotor.setTimeout(1,vex::timeUnits::msec);
    FlipMotor.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
    while(FlipMotor.isSpinning()){}
    FlipMotor.setTimeout(250,vex::timeUnits::msec);
    FlipMotor.resetRotation();
    return 1;
}
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
    if(FliperRequested==Fliper(UP)) FliperRequested=Fliper(DOWN);
    else if(FliperRequested==Fliper(MID))   FliperRequested=Fliper(DOWN);
    else if(FliperRequested==Fliper(DOWN))  FliperRequested=Fliper(UP);
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
int LD=0;
int RD=0;
void DriveUsrRequest(int L,int R){
    LD=L;
    RD=R;
}
void DriveManualControl(){
    if(Controller1.ButtonUp.pressing() && !DriveInvertConBtnPressed){
        DriveInvertConBtnPressed=true;
        DriveMotorInverted=!DriveMotorInverted;
    }
    else if(!Controller1.ButtonUp.pressing() && DriveInvertConBtnPressed){
        DriveInvertConBtnPressed=false;
    }
    LJoy=Controller1.Axis3.value();
    RJoy=Controller1.Axis2.value();

    if(LJoy!=0 || RJoy!=0){
        DriveManualControlEnabled=true;
        DriveUsrRequest(DriveMotorInverted ? -RJoy : LJoy,DriveMotorInverted ? -LJoy : RJoy);
    }
    else{
        if(DriveManualControlEnabled)  DriveUsrRequest(0,0);//Last loop before disableing; used to release drivemanualcontrol
        DriveManualControlEnabled=false;
    }
}
bool Drive2ManualControlEnabled=false;
void SecDriver(){
    LJoy=Controller2.Axis3.value();
    RJoy=Controller2.Axis2.value();

    if(LJoy!=0 || RJoy!=0){
        Drive2ManualControlEnabled=true;
        DriveUsrRequest(-RJoy,-LJoy);
    }
    else{
        if(Drive2ManualControlEnabled)  DriveUsrRequest(0,0);//Last loop before disableing; used to release drivemanualcontrol
        Drive2ManualControlEnabled=false;
    }
}
void DriveControl(){
    DriveManualControl();
    DriveHoldControl();
    if(!DriveManualControlEnabled)  SecDriver();
    DriveSMS(LD,RD);
}