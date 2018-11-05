#ifndef UsrFun_cpp
#define UsrFun_cpp
void DriveSMS(int left, int right){//add drive system
    LD.SMS(left);
    RD.SMS(right);
}
//

void LiftControl(){
    if(Controller1.ButtonRight.pressing())      Lift.SMS(100);
    else if(Controller1.ButtonLeft.pressing())  Lift.SMS(-100);
    else                                        Lift.SMS(0);
}
//
//rstet timer if ball in puncher or
void IntakeAutoUpDate(){//UpDate Sensors Code
    //Puncher UpDate
    if(PuncSen.value(vex::analogUnits::pct)<PuncBallTal){
        GlobTime=0;
        PuncBall=true;
    }  
    else{
        if(Puncher.IsSpining)           PuncBall=false;
        else{
            if(GlobTime>300)   PuncBall=false;
            else if(GlobTime>250)    Controller1.rumble(".");
            GlobTime=GlobTime+1;
        } 
    }
    //FeedBall UpDate
    if(FeedSen1.value(vex::analogUnits::pct)<Feed1BallTal || FeedSen2.value(vex::analogUnits::pct)<Feed2BallTal)    FeedBall=true;
    else                                                                                                            FeedBall=false;
}
void IntakeAuto(){//Autonomous Logic Control
    if(IntakeAutoEnabled){
        IntakeAutoEnabledWas=true;
        if(!PuncBall)       IntakeSetting=int(IntakePct::IN);
        else{
            if(!FeedBall)   IntakeSetting=int(IntakePct::IN);
            else            IntakeSetting=int(IntakePct::STOP);
        }
    }
    else if(IntakeAutoEnabledWas){//first loop disable
        IntakeSetting=int(IntakePct::STOP);
        IntakeAutoEnabledWas=false;
    }
}
int IntakeStateUpDate(){//Task to UpDate IntakeAutoUpDate every second in the background
    while(1){
        IntakeAutoUpDate();
        vex::task::sleep(1);
    }
}
void IntakeAutoControl(){//Controller Input To control Autonomous Logic Control
    if(Controller1.ButtonA.pressing() && !APressed){
        APressed=true;
        IntakeAutoEnabled=!IntakeAutoEnabled;
    }
    else if(!Controller1.ButtonA.pressing() && APressed)    APressed=false;

    IntakeAuto();
}
void IntakeManualControl(){//Controller Manual OverRide
    if(Controller1.ButtonR2.pressing()){
        IntakeManualControlEnabled=true;
        IntakeSetting=int(IntakePct::OUT);
    }
    else if(Controller1.ButtonR1.pressing()){
        IntakeManualControlEnabled=true;   
        IntakeSetting=int(IntakePct::IN);

    }
    else if(IntakeManualControlEnabled){//first loop disabled
        IntakeAutoEnabled=false;
        IntakeManualControlEnabled=false;
        IntakeSetting=int(IntakePct::STOP);
    }
}
void IntakeControl(){//OverRide Control Code
    IntakeManualControl();
    if(!IntakeManualControlEnabled) IntakeAutoControl();
    Intake.SMS(IntakeSetting);
}
//
/*  add to MotorSystem
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
        IntakeSetting=int(IntakePct::STOP);
        if(FliperRequested==int(FliperPct::UP)) FliperRequested=int(FliperPct::MID);
        Puncher.SMS(100);
    }
    else if(PuncherControlEnabled){//first loop not enabled
        Puncher.SMS(0);
        if(FliperRequested==int(FliperPct::MID))    FliperRequested=int(FliperPct::UP);
        IntakeTimeEnabled=true;
        PuncherControlEnabled=false;
    }
}
//
/*  add to MotorSystem
int FliperCal(){
    FlipMotor.setTimeout(1,vex::timeUnits::msec);
    FlipMotor.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
    while(FlipMotor.isSpinning()){}
    FlipMotor.setTimeout(250,vex::timeUnits::msec);
    FlipMotor.resetRotation();
    return 1;
}
*/
void FliperManualControl(){
    if(Controller1.ButtonRight.pressing()){
        FliperManualControlEnabled=true;
        Fliper.SMS(100);  
    }
    else if(Controller1.ButtonLeft.pressing()){
        FliperManualControlEnabled=true;
        Fliper.SMS(-100);
    }
    else if(FliperManualControlEnabled){//first loop
        Fliper.SMS(0);
        FliperManualControlEnabled=false;
    }
}
void FliperFlip(){
    if(FliperRequested==int(FliperPct::UP)) FliperRequested=int(FliperPct::DOWN);
    else if(FliperRequested==int(FliperPct::MID))   FliperRequested=int(FliperPct::DOWN);
    else if(FliperRequested==int(FliperPct::DOWN))  FliperRequested=int(FliperPct::UP);
}
void FliperPosControl(){
    if(Controller1.ButtonL1.pressing() && !L1Pressed){
        L1Pressed=true;
        FliperFlip();
        FliperPosControlEnabled=true;
    }
    if(!Controller1.ButtonL1.pressing() && L1Pressed)   L1Pressed=false;

    if(FliperPosControlEnabled){
        FlipMotor.startRotateTo(FliperRequested,vex::rotationUnits::deg,100,vex::velocityUnits::pct);//add to MotorSystem
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
        DriveSMS(DriveMotorInverted ? -RJoy : LJoy,DriveMotorInverted ? -LJoy : RJoy);
    }
    else{
        if(DriveManualControlEnabled)  DriveSMS(0,0);//Last loop before disableing; used to release drivemanualcontrol
        DriveManualControlEnabled=false;
    }
}
void DriveControl(){
    DriveManualControl();
    DriveHoldControl();
}
#endif