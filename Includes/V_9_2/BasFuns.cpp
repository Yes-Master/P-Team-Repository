//basic
void EndTimeSlice(int EndWait=5){
    vex::task::sleep(EndWait);
}
//screen

// double LastRotation=0;
// double MinChange=0;
//control
int ComRumerFun(){
    Controller1.rumble(".");
    return 1;
}
//basic motor functions
void PuncherSMS(int Pct){
    if(Pct==0){
        PuncherMotor.stop();
        PuncherSTS=false;
    }
    else{
        PuncherSTS=true;
        PuncherMotor.spin(vex::directionType::fwd,Pct,vex::velocityUnits::pct);
    }
}
void PuncherSpinTo(int Tar,bool SMS=true,bool Stop=true,bool Rel=false,int Pct=100,int Tal=10){
    if(Rel) Tar+=PuncherMotor.rotation(vex::rotationUnits::deg);
    int Dir=SGN(Tar-PuncherMotor.rotation(vex::rotationUnits::deg));
    if(std::abs(PuncherMotor.rotation(vex::rotationUnits::deg)-Tar)>Tal && PuncherSpinToControlRunEnabled){//outside of tal
        PuncherSpinToControlEnabled=true;
        Dir=SGN(Tar-PuncherMotor.rotation(vex::rotationUnits::deg));
        PuncherPctSetting=Pct*Dir;//set the motor to spin in the correct direction
    }
    else if(PuncherSpinToControlEnabled){//if in tar zone and was enabled; fist not enabled
        PuncherPctSetting=0;
        PuncherSpinToControlEnabled=false;//toggle
        if(Stop)    PuncherSpinToControlRunEnabled=false;//stop after it has been hit
    }
    if(SMS) PuncherSMS(PuncherPctSetting);
}

void PuncherPosSMS(int Pct){
    if(Pct==0){
        PuncherPosMotor.stop(vex::brakeType::hold);
        PuncherPosSTS=false;
    }
    else{
        PuncherPosSTS=true;
        PuncherPosMotor.spin(vex::directionType::fwd,Pct,vex::velocityUnits::pct);
    }
}
void PuncherPosSpinTo(int Tar,bool SMS=true,bool Stop=true,bool Rel=false,int Pct=100,int Tal=10){
    if(Rel) Tar+=PuncherPosMotor.rotation(vex::rotationUnits::deg);
    int Dir=SGN(Tar-PuncherPosMotor.rotation(vex::rotationUnits::deg));
    if(std::abs(PuncherPosMotor.rotation(vex::rotationUnits::deg)-Tar)>Tal && PuncherPosSpinToControlRunEnabled){//outside of tal
        PuncherPosSpinToControlEnabled=true;
        Dir=SGN(Tar-PuncherPosMotor.rotation(vex::rotationUnits::deg));
        PuncherPosPctSetting=Pct*Dir;//set the motor to spin in the correct direction
        if(SMS) PuncherPosSMS(PuncherPosPctSetting);
    }
    else if(PuncherPosSpinToControlEnabled){//if in tar zone and was enabled; fist not enabled
        PuncherPosPctSetting=0;
        if(SMS) PuncherPosSMS(PuncherPosPctSetting);
        PuncherPosSpinToControlEnabled=false;//toggle
        if(Stop)    PuncherPosSpinToControlRunEnabled=false;
    }
}

void IntakeSMS(int Pct){
    if(Pct==0){
        IntakeMotor.stop();
        IntakeSTS=false;
    }
    else{
        IntakeSTS=true;
        IntakeMotor.spin(vex::directionType::fwd,Pct,vex::velocityUnits::pct);
    }
}

void FliperSMS(int Pct){
    if(FlipMotor.rotation(vex::rotationUnits::deg)>FliperPosIn && Pct>0)     Pct=0;//upper limit
    if(FlipMotor.rotation(vex::rotationUnits::deg)<FliperPosDown && Pct<0)   Pct=0;//lower limit
    if(Pct==0){
        FlipMotor.stop();
        FliperSTS=false;
    }
    else{
        FliperSTS=true;
        FlipMotor.spin(vex::directionType::fwd,Pct,vex::velocityUnits::pct);
    }
}

void FLSMS(int V){
    if(V==0)    FLDriveMotor.stop();
    else{
        FLDriveMotor.spin(vex::directionType::fwd,V,vex::velocityUnits::pct);
    }
}
void FRSMS(int V){
    if(V==0)    FRDriveMotor.stop();
    else{
        FRDriveMotor.spin(vex::directionType::fwd,V,vex::velocityUnits::pct);
    }
}
void BLSMS(int V){
    if(V==0)    BLDriveMotor.stop();
    else{
        BLDriveMotor.spin(vex::directionType::fwd,V,vex::velocityUnits::pct);
    }
}
void BRSMS(int V){
    if(V==0)    BRDriveMotor.stop();
    else{
        BRDriveMotor.spin(vex::directionType::fwd,V,vex::velocityUnits::pct);
    }
}
void DriveSMS(int V1=0,int V2=0,int V3=0,int V4=0){//raw 
    FLSMS(V1);
    BLSMS(V2);
    FRSMS(V3);
    BRSMS(V4);
}
void DriveTankSMS(int j1,int j2,int j3=0,int j4=0){//left,right,side1,side2
    int LF=j1;//left
    int RF=j2;//right
    int SD=(j3+j4)/2;//side

    DriveSMS(//left go apart && right go into when going right
        LF+SD,
        LF-SD,
        RF-SD,
        RF+SD);
}
void DriveArcadeSMS(int J1,int J2,int J3=0){//forward,side,rotation
    int LF=J1+J3;//left
    int RF=J1-J3;//right
    int SD=J2;//side
    DriveSMS(//left go apart && right go into when going right
        LF+SD,
        LF-SD,
        RF-SD,
        RF+SD);
}
/*
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
*/
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
}*/

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
        FeildPos=StartPos::BackBlue;
        if(AutSel2.value(vex::percentUnits::pct)>70)        AutoProg = ProgPot::Yellow;
        else if(AutSel2.value(vex::percentUnits::pct)>25)   AutoProg = ProgPot::Green;
        else                                                AutoProg = ProgPot::Pink;
    }
}