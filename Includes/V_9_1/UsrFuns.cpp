/*Need to add
*/
/*Change Log
right down  hold(outfeed) && toggle(DriveMode=Baller,Autointake=true,FLiperrequested=fliperposin,)
right up    hold(puncher,DriveHold);
BtnX->BtnR1 Puncher Control && Post Punch enable auto intake if rotated more than 340 deg and there is not a ball in the puncher
*/
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
            FliperRequested=FliperPosIn;//put fliper in
        }
    }
    else if(!Controller1.ButtonA.pressing() && APressed)    APressed=false;

    IntakeAuto();
}
//right down  hold(outfeed) && toggle(DriveMode=Baller,Autointake=true,FLiperrequested=fliperposin,)
void IntakeManualControl(){//Controller Manual OverRide
    if(Controller1.ButtonR2.pressing()){
        IntakeManualControlEnabled=true;//halt auto intake function from running
        IntakeSetting=IntakePctOut;//out feed the intake
        if(!R2Pressed){//if btnR2 pressed but was not pressed
            FliperRequested=FliperPosIn;//put fliper in
            IntakeAutoEnabled=true;//intake balls auto after manual overide
            DriveMotorInverted=false;//Baller drive dir;
        }
    }
    else if(!Controller1.ButtonR2.pressing() && R2Pressed)  R2Pressed=false;

    else if(Controller1.ButtonX.pressing()){//btnR1->btnY;
        IntakeManualControlEnabled=true;   
        IntakeSetting=IntakePctIn;
    }
    else if(IntakeManualControlEnabled){//first loop not manualy controlled
        //IntakeAutoEnabled=false;
        IntakeManualControlEnabled=false;
        if(!IntakeAutoEnabled)  IntakeSetting=IntakePctStop;//if not auto controlled stop intakeing
    }
}
void IntakeControl(){//OverRide Control Code
    IntakeManualControl();
    if(!IntakeManualControlEnabled) IntakeAutoControl();
    IntakeSMS(IntakeSetting);
}
//
//right up    hold(puncher,DriveHold);
void PuncherControl(){
    int StartDeg=PuncherMotor.rotation(vex::rotationUnits::deg);//save start pos;needs to be here for scope
    if(Controller1.ButtonR1.pressing()){
        PuncherControlEnabled=true;
        if(!R1Pressed){//toggle initializer
            IntakeManualControlEnabled=true;//halt auto intake from running via manual control override
            IntakeSetting=IntakePctStop;//stop intaking

        }
        if(FliperRequested==FliperPosIn) FliperRequested=FliperPosInPun;//move fliper out of the way;this is outside of the init just in case of drive toggle problems
        PuncherSMS(100);
    }
    else if(PuncherControlEnabled){//first loop not enabled
        PuncherControlEnabled=false;//toggle
        PuncherSMS(0);//stop puncher
        if(FliperRequested==FliperPosInPun)    FliperRequested=FliperPosIn;//undo flipper move if required
        if(std::abs(PuncherMotor.rotation(vex::rotationUnits::deg)-StartDeg)>340 && !PuncBall) IntakeAutoEnabled=true;//if puncher displacement is > 340 and there is not a ball in the puncher then Enable IntakeAuto
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
    if(FliperRequested==FliperPosIn || FliperRequested==FliperPosInPun){//getting out of baller
        FliperRequested=FliperPosDown;
        DriveMotorInverted=true;//set drive dir to flipper
        IntakeAutoEnabled=false;//disable auto intake
    }
    else if(FliperRequested==FliperPosUpMid)    FliperRequested=FliperPosDown;
    else if(FliperRequested==FliperPosDown)     FliperRequested=FliperPosUpMid;
    if(DriveMotorInverted==false)               FliperRequested=FliperPosIn;//if in baller be in
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
    if(Controller1.ButtonUp.pressing() && !UpPressed){
        UpPressed=true;
        DriveMotorInverted=!DriveMotorInverted;
        if(DriveMotorInverted==true)    IntakeAutoEnabled=false;//disable intake auto when switching to cap drive dir
        FliperRequested=FliperPosIn;
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