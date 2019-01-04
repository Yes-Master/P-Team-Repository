//basic
void EndTimeSlice(int EndWait=5){
    vex::task::sleep(EndWait);
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
int ComRumerFun(){
    Controller1.rumble(".");
    return 1;
}
//basic motor functions
// void LiftStop(){
//     LiftMotor.stop();
// }
// void LiftSMS(int Pct){
//     if(Pct==0)  LiftStop();
//     else{
//         LiftMotor.spin(vex::directionType::fwd,Pct,vex::velocityUnits::pct);
//     }
// }

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
    // int Dir=SGN(Tar-PuncherMotor.rotation(vex::rotationUnits::deg));//only use if it can go both dir's
    int Dir=1;
    if(std::abs(PuncherMotor.rotation(vex::rotationUnits::deg)-Tar)>Tal && PuncherSpinToControlRunEnabled){//outside of tal
        PuncherSpinToControlEnabled=true;
        //Dir=SGN(Tar-PuncherMotor.rotation(vex::rotationUnits::deg));//only use if it can go both dir's
        PuncherPctSetting=Pct*Dir;//set the motor to spin in the correct direction
    }
    else if(PuncherSpinToControlEnabled){//if in tar zone and was enabled; fist not enabled
        PuncherPctSetting=0;
        PuncherSpinToControlEnabled=false;//toggle
        if(Stop)    PuncherSpinToControlRunEnabled=false;//stop after it has been hit
    }
    if(SMS) PuncherSMS(PuncherPctSetting);
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
/*why
void FliperSpinTo(int Tar,bool SMS=true,bool Stop=false,bool Rel=false,int Pct=100,int Tal=10){
    if(Rel) Tar+=FlipMotor.rotation(vex::rotationUnits::deg);
    int Dir=SGN(Tar-FlipMotor.rotation(vex::rotationUnits::deg));
    if(std::abs(FlipMotor.rotation(vex::rotationUnits::deg)-Tar)>Tal && FliperSpinToControlRunEnabled){//outside of tal
        FliperSpinToControlEnabled=true;
        Dir=SGN(Tar-FlipMotor.rotation(vex::rotationUnits::deg));
        FliperPctSetting=Pct*Dir;//set the motor to spin in the correct direction
    }
    else if(FliperSpinToControlEnabled){//if in tar zone and was enabled; fist not enabled
        FliperPctSetting=0;
        FliperSpinToControlEnabled=false;//toggle
        if(Stop)    FliperSpinToControlRunEnabled=false;//stop after it has been hit
    }
    if(SMS) PuncherSMS(FliperPctSetting);
}
*/
void FliperCal(){
    FliperCaled=false;
    int Rpm=100;
    int TimeOut=1000;
    int UpdateMsec=50;
    int CalTimer=0;
    FlipMotor.spin(vex::directionType::fwd, Rpm, vex::velocityUnits::rpm);     //starts the spin to hit the end stop 
    double MinChange=Rpm/120000*UpdateMsec;///(1/4)*(Rpm/60/1000); MinChange = 1/4 of requested rpm but in msec`s
    vex::task::sleep(250);//wait for acel
    LastRotation=FlipMotor.rotation(vex::rotationUnits::rev)/1000;//make sure it goes first loop
    while(std::abs(FlipMotor.rotation(vex::rotationUnits::rev)-LastRotation)>MinChange && CalTimer<TimeOut){//if displacement is more then 1/4 of what it is set to be and it is not out of time
        LastRotation=FlipMotor.rotation(vex::rotationUnits::rev);
        CalTimer=CalTimer+UpdateMsec;
        vex::task::sleep(UpdateMsec);
    }
    FlipMotor.resetRotation();
    FlipMotor.stop();
    FliperCaled=true;
    FliperRequested=FliperPosIn;
}
int FliperCalTaskFun(){
    FliperCal();
    return 1;
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