#ifndef AutFun_cpp
#define AutFun_cpp

int IntakeAuton(){
    IntakeAutonEnabled=true;
    IntakeAutoEnabled=true;//for intakeauto void
    while(IntakeAutonEnabled){
        IntakeAutoUpDate();
        IntakeAuto();
        Intake.SMS(IntakeSetting);
        vex::task::sleep(20);
        Controller1.Screen.print("inAuto");
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
        while(std::abs(Val-FlipMotor.rotation(vex::rotationUnits::deg))>int(FliperPct::TAL) && WaitTime<500){
            WaitTime++;
            vex::task::sleep(1);
        }
        Fliper.SMS(0);
        vex::task::sleep(EndWait);
    }
}
void Punch(bool Wait=true,int EndWait=PuncherEndWait,int Pct=100){
    if(FliperRequested==int(FliperPct::UP)) Flip(int(FliperPct::MID),true,0);//send fliper to mid no end wait
    PuncherMotor.startRotateFor(360,vex::rotationUnits::deg,Pct,vex::velocityUnits::pct);
    if(Wait){
        while(PuncherMotor.isSpinning()){
            vex::task::sleep(20);
        }
    }
    if(FliperRequested==int(FliperPct::MID))    Flip(int(FliperPct::UP),true,0);//resets fliper back to up if it had to be ajusted down
    vex::task::sleep(EndWait); 
}
void Turn(double Dis,int LPct=50,int RPct=50,int EndWait=TurnEndWait){//-left,+right
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
    while(BLDriveMotor.isSpinning() || BRDriveMotor.isSpinning()){
        vex::task::sleep(1);
    }
    vex::task::sleep(EndWait);
}
void Drive(double Dis,int Pct=100,int EndWait=DriveEndWait,int Correction=2){
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
        vex::task::sleep(1);
    }
    DR(0,0);
    while(BLDriveMotor.isSpinning() || BRDriveMotor.isSpinning()){
        vex::task::sleep(1);
    }
    vex::task::sleep(EndWait);
}
void DriveRecon(int Pct,int Wait,int EndWait=250,int TimeOut=5){
    DI(Pct,Pct);
    vex::task::sleep(Wait);
    DI(0,0);
}
#endif