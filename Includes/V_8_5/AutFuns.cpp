int IntakeAuton(){
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

int DriveRamping(){
    DriveRampingEnabled=true;
    while(DriveRampingEnabled){
        LDR.TaskRun();
        RDR.TaskRun();
        DriveSMS(LDR.Pct,RDR.Pct);
        vex::task::sleep(LDR.ChangeMsec);
    }
    return 1;
}
void DR(int L,int R){
    LDR.RequestedPct=L;
    RDR.RequestedPct=R;
}
void QDRS(int CMS=2){//quick drive ramp stop
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
void DI(int L,int R){
    LDR.RequestedPct=L;
    RDR.RequestedPct=R;
    LDR.Pct=L;
    RDR.Pct=R;
    DriveSMS(LDR.Pct,RDR.Pct);
}
void Flip(int Val,bool Wait=true,int EndWait=FliperEndWait,int Pct=100){
    FliperRequested=Val;//used for both auton and usr needs to be reset
    FlipMotor.startRotateTo(Val,vex::rotationUnits::deg,Pct,vex::velocityUnits::pct);
    if(Wait){
        int WaitTime=0;
        while(ABS(Val-FlipMotor.rotation(vex::rotationUnits::deg))>FliperPosTal && WaitTime<500){
            WaitTime++;
            vex::task::sleep(1);
        }
        FliperSMS(0);
        vex::task::sleep(EndWait);
    }
    Controller1.Screen.clearLine();
    Controller1.Screen.print("Fliped");

}
void Puncher(bool Wait=true,int EndWait=PuncherEndWait,int Pct=100){
    if(FliperRequested==FliperPosIn) Flip(FliperPosInPun,true,0);//send fliper to mid no end wait
    PuncherControlEnabled=true;
    IntakeSetting=IntakePctStop;
    PuncherMotor.startRotateFor(370,vex::rotationUnits::deg,Pct,vex::velocityUnits::pct);
    if(Wait){
        while(PuncherMotor.isSpinning()){
            vex::task::sleep(20);
        }
    }
    if(FliperRequested==FliperPosInPun)    Flip(FliperPosIn,true,0);//resets fliper back to up if it had to be ajusted with no end wait
    vex::task::sleep(EndWait);
    IntakeTimeEnabled=true;
    PuncherControlEnabled=false;
        Controller1.Screen.clearLine();
    Controller1.Screen.print("Punched");

}

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

void Drive(double Dis,int Pct=50,int EndWait=DriveEndWait,int Correction=2){
    double WheelCir=4*3.14159265;
    double Dir=SGN(Dis);
    double Rev=ABS(Dis)/WheelCir;
    int Pct1=0;
    int Pct2=0;
    FLDriveMotor.resetRotation();
    FRDriveMotor.resetRotation();
    while(ABS(FLDriveMotor.rotation(vex::rotationUnits::rev))<ABS(Rev)){
        double Input1=FLDriveMotor.rotation(vex::rotationUnits::deg);
        double Input2=FRDriveMotor.rotation(vex::rotationUnits::deg);
        if(ABS(Input1)>ABS(Input2)){
            Pct1=Pct-Correction;
            Pct2=Pct;
        }
        else if(ABS(Input1)<ABS(Input2)){
            Pct1=Pct;
            Pct2=Pct-Correction;
        }
        else if(ABS(Input1)==ABS(Input2)){
            Pct1=Pct;
            Pct2=Pct;
        }
        Pct1=Pct1*Dir;
        Pct2=Pct2*Dir;
        DR(Pct1,Pct2);
        vex::task::sleep(1);
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
        vex::task::sleep(EndWait);
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

//need to do forward def
void StopAllMotors(){
    DI(0,0);//set drive ramping to 0
    DriveSMS(0,0);
    FlipMotor.stop();
    IntakeSMS(0);
    PuncherSMS(0);
    LiftMotor.stop();
}