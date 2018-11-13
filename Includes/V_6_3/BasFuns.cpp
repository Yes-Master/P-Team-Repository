int ControllerScreen() {
    while(1){
        if(DriveMotorInverted!=DriveMotorInvertedWas){
           // Controller1.Screen.newLine();
            if(DriveMotorInverted) Controller1.Screen.print("Fliper");
            else                   Controller1.Screen.print("Baller");
        }
        DriveMotorInvertedWas=DriveMotorInverted;
        vex::task::sleep(50);
    }
}
void BallFeedVars(){
    Brain.Screen.newLine();
    Brain.Screen.print(PuncSen.value(vex::analogUnits::pct));
    Brain.Screen.print(" , ");
    Brain.Screen.print(FeedSen1.value(vex::analogUnits::pct));
    Brain.Screen.print(" , ");
    Brain.Screen.print(FeedSen2.value(vex::analogUnits::pct));
}
int BrainScreen(){
    if(AutSel.value(vex::analogUnits::pct)>50){//if red selected
        Brain.Screen.clearScreen(vex::color::blue);
    }
    else{//if blue selected
        Brain.Screen.clearScreen(vex::color::red);
    }
    Brain.Screen.render();
    while(1){
       Brain.Screen.print(AutSel.value(vex::analogUnits::pct));
           Brain.Screen.newLine();

       // BallFeedVars();
        Brain.Screen.render();
        vex::task::sleep(500);
    }
}
int ComRumer(){
    ComRumerEnabled=true;
    while(ComRumerEnabled){
        if(ComRum && IntakeAutoEnabled && IntakeSetting==Intake(STOP))  Controller1.rumble(".");
        vex::task::sleep(20);
    }
    return 1;
}
int ComRumShort(){
    Controller1.rumble(".");
    return 1;
}
int ComRumLong(){
    Controller1.rumble("-");
    return 1;  
}
void LiftStop(){
    LiftMotor.stop();
}
void LiftSMS(int Pct){
    if(Pct==0)  LiftStop();
    else{
        LiftMotor.spin(vex::directionType::fwd,Pct,vex::velocityUnits::pct);
    }
}
//
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
    if(FlipMotor.rotation(vex::rotationUnits::deg)>Fliper(UP) && Pct>0)     Pct=0;//upper limit
    if(FlipMotor.rotation(vex::rotationUnits::deg)<Fliper(DOWN) && Pct<0)   Pct=0;//lower limit
    if(Pct==0)  FliperStop();
    else{
        FlipMotor.spin(vex::directionType::fwd,Pct,vex::velocityUnits::pct);
    }
}
//
void DriveTimeOutSet(int TimeOut){
    FLDriveMotor.setTimeout(TimeOut,vex::timeUnits::msec);
    FRDriveMotor.setTimeout(TimeOut,vex::timeUnits::msec);
    BRDriveMotor.setTimeout(TimeOut,vex::timeUnits::msec);
    BLDriveMotor.setTimeout(TimeOut,vex::timeUnits::msec);
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
//