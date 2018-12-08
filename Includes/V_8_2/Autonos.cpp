void AutFunFrontRed(){
    Drive(21,100,-1);
    Drive(3,50,500);
    Drive(-25,100,-1);
    DriveRecon(-15,500);

    Drive(3,50);
    Turn(-9.4);
//    Drive(1,25);
    Puncher();
    Drive(10,100);
    if(PuncBall)    Puncher();
    Turn(-1.2);//slight turn to miss pole
    // IntakeAutoEnabled=false;
    Drive(6,100,50);

    Turn(-3);//45deg turn get cap
    Flip(FliperPosDown);
    Drive(-8,100,-1);
    // IntakeAutoEnabled=true;
    Drive(-12,25,500);
    Flip(FliperPosIn);
}
void AutFunFrontBlue(){
    Drive(24,100,-1);
    Drive(3,50,500);
    Drive(-28,100,-1);
    DriveRecon(-15,500);

    Drive(6,50);
    Turn(9.3);//the good times
   // Drive(1,25);
    Puncher();
    Drive(8,100);
    if(PuncBall)    Puncher();
    Turn(0.7);//slight turn to miss pole
    // IntakeAutoEnabled=false;
    Drive(9,100,50);

    Turn(3.5);//45deg turn get cap
    Flip(FliperPosDown);
    Drive(-8,100,-1);
    // IntakeAutoEnabled=true;
    Drive(-15,25,500);
    Flip(FliperPosIn);
}
void AutFunBackRed(){
    Drive(24,100,-1);
    Drive(3,50,250);
    Turn(-10);
    Flip(FliperPosDown);
    Drive(-9);
    Flip(FliperPosIn);
    Turn(18);
    IntakeAutoEnabled=false;
    Drive(-44,100);//get on platform
}
void AutFunBackBlue(){
    Drive(24,100,-1);
    Drive(3,50,250);
    Turn(10);
    Flip(FliperPosDown);
    Drive(-9);
    Flip(FliperPosIn);
    Turn(-17.5);
    IntakeAutoEnabled=false;
    Drive(-42,100);//get on platform
}
void Sniper(){

}
void FrontSkills(){
    Drive(25,100,-1);
    Drive(3,50,500);
    Drive(-29,100,-1);
    DriveRecon(-15,750);

    Drive(3,50);
    Turn(-9.4);
//    Drive(1,25);
    Puncher();
    Drive(10,100);
    if(PuncBall)    Puncher();
    Turn(-1.2);//slight turn to miss pole
    // IntakeAutoEnabled=false;
    Drive(6,100,50);

    Turn(-3);//45deg turn get cap
    Flip(FliperPosDown);
    Drive(-8,100,-1);
    // IntakeAutoEnabled=true;
    Drive(-12,25,500);
    Flip(FliperPosIn);
    IntakeAutoEnabled=false;
    //=======================================
    Turn(-5);//turn to wall
    Drive(23,50);//drive to wall
    DriveRecon(15,500);//recon
    Drive(-5,50);//drive away form wall
    Turn(-10);//turn perallel to wall
    Drive(45,50);//drive perallel to wall && line up to park
    Turn(9.4);//turn to park
    Drive(4,50);//drive to wall
    DriveRecon(15,750);//recon
    DI(-100,-100);//no ramping
    Drive(-85,100);//drive on park
}
void BackSkills(){
    Drive(27,100,500);
    Drive(-28,100);
    DriveRecon(-25,250);
    DriveRecon(-10,250);
    DriveRecon(-5,500);
    Drive(2.5,50);
    Turn(-87);
    Drive(32,100);
    Puncher();
    //
    Drive(12,100);
    if(PuncBall)    Puncher();
    Turn(-7);//slight turn to miss pole
    // IntakeAutoEnabled=false;
    Drive(3,100);

    Turn(-24);//45deg turn get cap
    Flip(FliperPosDown);
    Drive(-8,100,0);
    // IntakeAutoEnabled=true;
    Drive(-15,25,750);
    Flip(FliperPosIn);

    Turn(43);//turn straight with feild tiles
    Drive(-17);
    Turn(84);//turn straight to cap
    Drive(30);//pick up ball
    Turn(-84);//turn to flags
    DriveRecon(-25,1500);//straighten
    Drive(2);//line up for first flag

    if(PuncBall && FeedBall){
        if(PuncBall)    Puncher();
        Drive(12,100);
        if(PuncBall)    Puncher();
    }
    else if(PuncBall && !FeedBall)    Puncher();



}
void Testing(){
    Turn(9);
    EndTimeSlice(250);
    Turn(-3);
}

void AutoSelRunFuns(){
    if(FeildPos==StartPos::BackRed){
        if(AutoProg==ProgPot::Pink)         BackSkills();//Skills
        else if(AutoProg==ProgPot::Green)   AutFunBackRed();//Normal
        else if(AutoProg==ProgPot::Yellow)  Sniper();//Sniper
    }
    else if(AutSel1.value(vex::analogUnits::pct)>50){
        if(AutoProg==ProgPot::Pink)         FrontSkills();//Skills
        else if(AutoProg==ProgPot::Green)   AutFunFrontRed();//Normal
        else if(AutoProg==ProgPot::Yellow)  Sniper();//Sniper
    }
    else if(AutSel1.value(vex::analogUnits::pct)>17){
        if(AutoProg==ProgPot::Pink)         Testing();//Skills
        else if(AutoProg==ProgPot::Green)   AutFunFrontBlue();//Normal
        else if(AutoProg==ProgPot::Yellow)  Sniper();//Sniper
    }
    else{
        if(AutoProg==ProgPot::Pink)         Testing();//Skills
        else if(AutoProg==ProgPot::Green)   AutFunBackBlue();//Normal
        else if(AutoProg==ProgPot::Yellow)  Sniper();//Sniper
    }
}