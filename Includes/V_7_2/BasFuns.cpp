//basic
void EndTimeSlice(int EndWait=5){
    vex::task::sleep(EndWait);
}
//screen
double LastRotation=0;
double MinChange=0;
int ControllerScreen(){
    while(1){
        if(DriveMotorInverted!=DriveMotorInvertedWas){
            Controller1.Screen.clearLine();
            if(DriveMotorInverted) Controller1.Screen.print("Fliper");
            else                   Controller1.Screen.print("Baller");
        }
        DriveMotorInvertedWas=DriveMotorInverted;
        vex::task::sleep(50);
    }
}
void BallFeedVars(){
    Brain.Screen.print(PuncSen.value(vex::analogUnits::pct));
    Brain.Screen.print(" , ");
    Brain.Screen.print(FeedSen1.value(vex::analogUnits::pct));
    Brain.Screen.print(" , ");
    Brain.Screen.print(FeedSen2.value(vex::analogUnits::pct));
}
int BrainScreen(){
    while(1){
        Brain.Screen.clearLine();

        //BallFeedVars();
        Brain.Screen.print(Gyro.value(vex::rotationUnits::deg));

        Brain.Screen.render();
        vex::task::sleep(20);
    }
}

int BrainScreenColorSet(){
    while(AutSel1.value(vex::analogUnits::pct)==0){}
    if(AutSel1.value(vex::analogUnits::pct)>50)//if red selected
        Brain.Screen.clearScreen(vex::color::red);
    else//if blue selected
        Brain.Screen.clearScreen(vex::color::blue);
    Brain.Screen.render();
    return 1;
}
int BrainScreenFlash(){
    for(int i=0; i<10; i++){
        Brain.Screen.clearScreen(vex::color::orange);
        vex::task::sleep(100);
        Brain.Screen.clearScreen(vex::color::purple);
    }
    vex::task BrainScreenColorSetTask(BrainScreenColorSet);
    return 1;    
}
//control
int ComRumer(){
    ComRumerEnabled=true;
    while(ComRumerEnabled){
        if(ComRum && IntakeAutoEnabled && IntakeSetting==IntakePctStop)  Controller1.rumble(".");
        vex::task::sleep(20);
    }
    return 1;
}
//basic motor functions
void LiftStop(){
    LiftMotor.stop();
}
void LiftSMS(int Pct){
    if(Pct==0)  LiftStop();
    else{
        LiftMotor.spin(vex::directionType::fwd,Pct,vex::velocityUnits::pct);
    }
}

void PuncherStop(){
    PuncherMotor.stop();
}
void PuncherSMS(int Pct){
    if(Pct==0)  PuncherStop();
    else{
        PuncherMotor.spin(vex::directionType::fwd,Pct,vex::velocityUnits::pct);
    }
}

void IntakeStop(){
    IntakeMotor.stop();
}
void IntakeSMS(int Pct){
    if(Pct==0)  IntakeStop();
    else{
        IntakeMotor.spin(vex::directionType::fwd,Pct,vex::velocityUnits::pct);
    }
}

void FliperStop(){
    FlipMotor.stop();
}
void FliperSMS(int Pct){
    if(FlipMotor.rotation(vex::rotationUnits::deg)>FliperPosIn && Pct>0)     Pct=0;//upper limit
    if(FlipMotor.rotation(vex::rotationUnits::deg)<FliperPosDown && Pct<0)   Pct=0;//lower limit
    if(Pct==0)  FliperStop();
    else{
        FlipMotor.spin(vex::directionType::fwd,Pct,vex::velocityUnits::pct);
    }
}

void LeftDriveStop(){
    FLDriveMotor.stop();
    BLDriveMotor.stop();
}
void RightDriveStop(){
    FRDriveMotor.stop();
    BRDriveMotor.stop();
}
void LeftDriveSMS(int pct){
    if(pct==0)   LeftDriveStop();
    else{
        FLDriveMotor.spin(vex::directionType::fwd,pct,vex::velocityUnits::pct);
        BLDriveMotor.spin(vex::directionType::fwd,pct,vex::velocityUnits::pct);
    }
}
void RightDriveSMS(int pct){
    if(pct==0)  RightDriveStop();
    else{
        FRDriveMotor.spin(vex::directionType::fwd,pct,vex::velocityUnits::pct);
        BRDriveMotor.spin(vex::directionType::fwd,pct,vex::velocityUnits::pct);
    }
}
void DriveSMS(int left, int right){
    LeftDriveSMS(left);
    RightDriveSMS(right);
}
//Calibration
/*
int FliperCalibration(){
    int Rpm=200;       //Velocity to hit the end stop
    int TimeOut=1000;   //Max time to hit end stop
    int UpdateMsec=20;  //the time delay in the loop
    int CalTimer=0;     //resets a local timer
    FlipMotor.spin(vex::directionType::fwd, Rpm, vex::velocityUnits::rpm);     //starts the spin to hit the end stop 
     MinChange=(std::abs(Rpm)/240000*UpdateMsec)/5;//gear ratio                                 ///(1/4)*(Rpm/60/1000); MinChange = 1/4 of requested rpm changed into msec
     LastRotation=FlipMotor.rotation(vex::rotationUnits::rev)+4*MinChange;  //makes sure that the while loop starts
    vex::task::sleep(100);                                                  //wait for the motor get some speed
    while(std::abs(FlipMotor.rotation(vex::rotationUnits::rev)-LastRotation)>MinChange && CalTimer<TimeOut){//while the motors displacement is more then the MinChange and while the the timer is less then the timeout time
        LastRotation=FlipMotor.rotation(vex::rotationUnits::rev);//update LastRotation
        CalTimer=CalTimer+UpdateMsec;   //add time to the timer
        vex::task::sleep(UpdateMsec);   //wait for the motor to spin
    }                                   //motor stoped spinning or time ran out
    Controller1.Screen.print("fliper cal done");
    if(CalTimer>=TimeOut) return 0;     //if timed out return error code 0 or false
    else{                               //hit the end stop
        FlipMotor.resetRotation();             //reset the rotation
        FliperSMS(0);                      //dont burn out the motor
        return 1;                           //return 1 or true
    }
    FliperCalTime=Brain.timer(vex::timeUnits::msec);
}

int PuncherCalibration(){
    int Rpm=-200;       //Velocity to hit the end stop
    int TimeOut=1000;   //Max time to hit end stop
    int UpdateMsec=20;  //the time delay in the loop
    int CalTimer=0;     //resets a local timer
    PuncherMotor.spin(vex::directionType::fwd, Rpm, vex::velocityUnits::rpm);    //starts the spin to hit the end stop 
    double MinChange=Rpm/240000*UpdateMsec;                                 ///(1/4)*(Rpm/60/1000); MinChange = 1/4 of requested rpm changed into msec instead of min
    int LastRotation=PuncherMotor.rotation(vex::rotationUnits::rev)+4*MinChange; //makes sure that the while loop starts
    vex::task::sleep(100);                                                  //wait for the motor get some speed
    while(std::abs(PuncherMotor.rotation(vex::rotationUnits::rev)-LastRotation)>MinChange && CalTimer<TimeOut){//while the motors displacement is more then the MinChange and while the the timer is less then the timeout time
        LastRotation=PuncherMotor.rotation(vex::rotationUnits::rev);//update LastRotation
        CalTimer=CalTimer+UpdateMsec;   //add time to the timer
        vex::task::sleep(UpdateMsec);   //wait for the motor to spin
    }                                   //motor stoped spinning or time ran out
    if(CalTimer>=TimeOut) return 0;     //if timed out return error code 0 or false
    else{                               //hit the end stop
    PuncherMotor.resetRotation();            //reset the rotation
    PuncherMotor.stop();                     //dont burn out the motor
    return 1;                           //return 1 or true
    }
    PuncherCalTime=Brain.timer(vex::timeUnits::msec);
}
*/
void GyroCalibration(bool Wait=true){
    Gyro.startCalibration();
    if(Wait){
        while(!Gyro.isCalibrating()){//wait for calibration
            EndTimeSlice();
        }
        while(Gyro.isCalibrating()){//wait for calibration
            EndTimeSlice();
        }
    }
    //GyroCalTime=Brain.timer(vex::timeUnits::msec);
}
//
void AutonSelFun(){
    if(AutSel1.value(vex::analogUnits::pct)>80){            //red back
        FeildPos=StartPos::BackRed;
        if(AutSel2.value(vex::percentUnits::pct)>70)        AutoProg = ProgPot::Yellow;
        else if(AutSel2.value(vex::percentUnits::pct)>25)   AutoProg = ProgPot::Green;
        else                                                AutoProg = ProgPot::Pink;
    }
    else if(AutSel1.value(vex::analogUnits::pct)>50){       //red front
        FeildPos=StartPos::FrontRed;
        if(AutSel2.value(vex::percentUnits::pct)>70)        AutoProg = ProgPot::Yellow;
        else if(AutSel2.value(vex::percentUnits::pct)>25)   AutoProg = ProgPot::Green;
        else                                                AutoProg = ProgPot::Pink;
    }
    else if(AutSel1.value(vex::analogUnits::pct)>17){       //blue front
        FeildPos=StartPos::FrontBlue;
        if(AutSel2.value(vex::percentUnits::pct)>70)        AutoProg = ProgPot::Yellow;
        else if(AutSel2.value(vex::percentUnits::pct)>25)   AutoProg = ProgPot::Green;
        else                                                AutoProg = ProgPot::Pink;
    }
    else{                                                   //blue back
        FeildPos=::StartPos::BackBlue;
        if(AutSel2.value(vex::percentUnits::pct)>70)        AutoProg = ProgPot::Yellow;
        else if(AutSel2.value(vex::percentUnits::pct)>25)   AutoProg = ProgPot::Green;
        else                                                AutoProg = ProgPot::Pink;
    }
}
void AutoSelPrintFun(){
    if(FeildPos==StartPos::BackRed){            //red back
    Brain.Screen.print("Back  Red ");
    Brain.Screen.print("-");
        if(AutoProg==ProgPot::Pink)         Brain.Screen.print("Skills");
        else if(AutoProg==ProgPot::Green)   Brain.Screen.print("Normal");
        else if(AutoProg==ProgPot::Yellow)  Brain.Screen.print("Sniper");
    }
    else if(AutSel1.value(vex::analogUnits::pct)>50){       //red front
    Brain.Screen.print("Front Red ");
    Brain.Screen.print("-");
        if(AutoProg==ProgPot::Pink)         Brain.Screen.print("Skills");
        else if(AutoProg==ProgPot::Green)   Brain.Screen.print("Normal");
        else if(AutoProg==ProgPot::Yellow)  Brain.Screen.print("Sniper");
    }
    else if(AutSel1.value(vex::analogUnits::pct)>17){       //blue front
    Brain.Screen.print("Front Blue");
    Brain.Screen.print("-");
        if(AutoProg==ProgPot::Pink)         Brain.Screen.print("Testin");
        else if(AutoProg==ProgPot::Green)   Brain.Screen.print("Normal");
        else if(AutoProg==ProgPot::Yellow)  Brain.Screen.print("Sniper");
    }
    else{                                                   //blue back
    Brain.Screen.print("Back  Blue");
    Brain.Screen.print("-");
        if(AutoProg==ProgPot::Pink)         Brain.Screen.print("Testin");
        else if(AutoProg==ProgPot::Green)   Brain.Screen.print("Green ");
        else if(AutoProg==ProgPot::Yellow)  Brain.Screen.print("Sniper");
    }
}
void BrainPrintStart(){
    Brain.Screen.clearLine();
    AutonSelFun();
    AutoSelPrintFun();
    Brain.Screen.print(" - ");
    Brain.Screen.print(Gyro.value(vex::rotationUnits::deg));
    Brain.Screen.render();
}
int Start(){

    StartEnabled=true;
    Controller1.Screen.clearLine();
    Controller1.Screen.print("IM NOT READY");
    while(StartEnabled){
        if(Brain.Screen.pressing() && !BrainPressed){
            Controller1.Screen.clearLine();
            Controller1.Screen.print("DONT");
            Brain.Screen.clearLine();
            Brain.Screen.print("NO TOUCHY");
            Brain.Screen.render();
            EndTimeSlice(1000);
            BrainPrintStart();
            Controller1.Screen.print("NOT NOW");
            Brain.Screen.clearLine();
            Brain.Screen.print("NOT NOW");
            Brain.Screen.render();
            GyroCalibration();
            BrainPrintStart();
            Controller1.Screen.clearLine();
            Controller1.Screen.print("YOU CAN DO IT");
        }
        else{
            BrainPrintStart();
            EndTimeSlice(20);
        }
        if(!Brain.Screen.pressing())   BrainPressed=false;

    }
    return 1;
}