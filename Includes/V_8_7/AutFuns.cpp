int IntakeAuton(){//handles intake in the backbround
    IntakeAutonEnabled=true;
    IntakeAutoEnabled=true;//for intakeauto void
    while(IntakeAutonEnabled){
        IntakeAutoUpDate();
        IntakeAuto();
        IntakeSMS(IntakeSetting);
        vex::task::sleep(20);
    }
    return 1;
}
//fliper
void Flip(int Val,bool Wait=true,int EndWait=FliperEndWait,int Pct=100){
    FliperRequested=Val;//used for both auton and usr needs to be reset
    FlipMotor.startRotateTo(FliperRequested,vex::rotationUnits::deg,Pct,vex::velocityUnits::pct);
    if(Wait){
        int WaitTime=0;
        while(std::abs(FliperRequested-FlipMotor.rotation(vex::rotationUnits::deg))>FliperPosTal && WaitTime<500){
            WaitTime++;
            EndTimeSlice(1);
        }
        FliperSMS(0);
        EndTimeSlice(EndWait);
    }
    Controller1.Screen.clearLine();
    Controller1.Screen.print("Fliped");

}
int FliperPunFireMoveBackFun(){
    while(PuncherCharged || PuncherSpinToControlRunEnabled){
        EndTimeSlice();
    }
    Flip(FliperPosIn,false);
    return 1;
}
//puncher
int PuncherSpinToAutFun(){//make globle
    PuncherSpinToControlEnabled=true;//init
    PuncherSpinToControlRunEnabled=true;//enable spin to contorol to run
    while(PuncherSpinToControlEnabled){//while spining to target
        PuncherSpinTo(PuncherDeg,true);//get to target,set the motor to spin
        EndTimeSlice();
    }
    return 1;
}
void PuncherAut(bool Wait=true,int EndWait=0){//Tar is 80 || 280 || 360;Tar PunPosFromChargedToReleased || PunPosFromReleasedToCharged || 360
   if(!PuncherCharged){//Charging
        if(FlipMotor.rotation(vex::rotationUnits::deg)>FliperPosInPun)  Flip(FliperPosInPun,false); //if fliperin FliperPosInPun
        PuncherDeg+=PunPosFromReleasedToCharged;
        PuncherSpinToControlRunEnabled=true;//enable puncherspinto
        PuncherCharged=true;
    }
    else if(PuncherCharged){//Fireing
        if(FliperRequested==FliperPosInPun)  vex::task FliperPunFireMoveBackTask(FliperPunFireMoveBackFun);//wait for the rack to fully fire and stop
        PuncherDeg+=PunPosFromChargedToReleased;
        PuncherSpinToControlRunEnabled=true;//enable puncherspinto
        PuncherCharged=false;
    }
    vex::task PuncherSpinToAutTask(PuncherSpinToAutFun);
    if(Wait){
        while(PuncherSpinToControlEnabled){
            EndTimeSlice();
        }
        EndTimeSlice(EndWait);
    }
}
//drive auton basic control fuctions
int DriveRamping(){//sets drive motors to spin
    DriveRampingEnabled=true;
    while(DriveRampingEnabled){
        LDR.TaskRun();
        RDR.TaskRun();
        DriveSMS(LDR.Pct,RDR.Pct);
        vex::task::sleep(LDR.ChangeMsec);
    }
    return 1;
}
void DI(int L,int R){//drive instentaniouly
    LDR.RequestedPct=L;
    RDR.RequestedPct=R;
    LDR.Pct=L;
    RDR.Pct=R;
    DriveSMS(LDR.Pct,RDR.Pct);
}
void DR(int L,int R){//update the drive ramping requested values
//    if(std::abs(L)<5 && std::abs(R)<5)    DI(0,0);//stop NOW!!!
//    else{
        LDR.RequestedPct=L;
        RDR.RequestedPct=R;
//    }
}
void QDRS(int CMS=2){//Quick Drive Ramp Stop; changes the accel to stop more suddenly
    //save old ramping Change Msec
    int LDRCMS=LDR.ChangeMsec;
    int RDRCMS=RDR.ChangeMsec;
    //set new ramping Change Msec
    LDR.ChangeMsec=CMS;
    RDR.ChangeMsec=CMS;
    //set drive to stop
    DR(0,0);
    //wait for drive to stop
    while(LDR.Pct!=0 || RDR.Pct!=0){EndTimeSlice();}
    //Revert drive ramping Change Msec
    LDR.ChangeMsec=LDRCMS;
    RDR.ChangeMsec=RDRCMS;
}
//drive functions
void Turn(double Dis,int LPct=25,int RPct=25,int EndWait=TurnEndWait){//-left,+right
    int Dir=SGN(Dis);
    Dis=std::abs(Dis)/12.56;
    LPct=LPct*Dir;
    RPct=RPct*Dir;
    FLDriveMotor.resetRotation();
    while(std::abs(FLDriveMotor.rotation(vex::rotationUnits::rev))<Dis){
        DI(LPct,-RPct);
        vex::task::sleep(1);
    }
    DI(0,0);
    Controller1.Screen.clearLine();
    Controller1.Screen.print("Turned");
    vex::task::sleep(EndWait);
}
void Drive(double Dis,int Pct=50,int EndWait=DriveEndWait,int Correction=1){
    double WheelCir=4*3.14159265;
    double Dir=SGN(Dis);
    double Rev=std::abs(Dis)/WheelCir;
    int Pct1=0;
    int Pct2=0;
    FLDriveMotor.resetRotation();
    FRDriveMotor.resetRotation();
    while(std::abs(FLDriveMotor.rotation(vex::rotationUnits::rev))<std::abs(Rev)){
        double Input1=FLDriveMotor.rotation(vex::rotationUnits::deg);
        double Input2=FRDriveMotor.rotation(vex::rotationUnits::deg);
        if(std::abs(Input1)>std::abs(Input2)){
            Pct1=Pct-Correction;
            Pct2=Pct;
        }
        else if(std::abs(Input1)<std::abs(Input2)){
            Pct1=Pct;
            Pct2=Pct-Correction;
        }
        else if(std::abs(Input1)==std::abs(Input2)){
            Pct1=Pct;
            Pct2=Pct;
        }
        Pct1=Pct1*Dir;
        Pct2=Pct2*Dir;
        DR(Pct1,Pct2);
        EndTimeSlice(1);
    }
    Controller1.Screen.clearLine();
    Controller1.Screen.print("Drived");
    if(EndWait==-1){//                                                          Junction
        //only use if another drive command fallows
    }
    else if(EndWait>0){//default; set stop, wait for stop, wait for endwait;    StopWait
        //QDRS();//quick drive ramp stop
        DR(0,0);
        while(LDR.Pct!=0 || RDR.Pct!=0){EndTimeSlice(LDR.ChangeMsec);}
        EndTimeSlice(EndWait);
    }
    else{//>=0,!=-1; set stop dont wait;                                        Stop
        DR(0,0);
    }
    Controller1.Screen.clearLine();
    Controller1.Screen.print("Drove");

}
void DriveRecon(int Pct,int Wait,int EndWait=250){
    DR(Pct,Pct);
    vex::task::sleep(Wait);
    if(EndWait>0){
        DR(0,0);
        while(LDR.Pct!=0 || RDR.Pct!=0){EndTimeSlice(LDR.ChangeMsec);}
        Controller1.Screen.clearLine();
        Controller1.Screen.print("RECONED");
    }
    else if(EndWait==0){
        Controller1.Screen.clearLine();
        Controller1.Screen.print("RECONED!END");
    }
}
void DriveWait(bool stop){
    if(stop)    DR(0,0);
    while(LDR.Pct!=0 || RDR.Pct!=0){EndTimeSlice(LDR.ChangeMsec);}
}

//need forward def
void StopAllMotors(){
    DI(0,0);//set drive ramping to 0
    DriveSMS(0,0);
    FlipMotor.stop();
    IntakeSMS(0);
    PuncherSMS(0);
    LiftMotor.stop();
}