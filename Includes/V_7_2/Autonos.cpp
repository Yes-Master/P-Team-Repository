void AutFunFrontRed(){
    Drive(24,100,-1);
    Drive(3,50,500);
    Drive(-27,100,-1);
    DriveRecon(-35,500);

    Drive(3,50);
    Turn(-84);
    Drive(1,25);
    Puncher();
    Drive(10,100);
    if(PuncBall)    Puncher();
    Turn(-6);//slight turn to miss pole
    // IntakeAutoEnabled=false;
    Drive(2,100);

    Turn(-30);//45deg turn get cap
    Flip(FliperPosDown);
    Drive(-8,100,0);
    // IntakeAutoEnabled=true;
    Drive(-15,25,750);
    Flip(FliperPosIn);
}
void AutFunFrontBlue(){
    Drive(24,100,-1);
    Drive(3,50,500);
    Drive(-27,100,-1);
    DriveRecon(-35,500);

    Drive(3,50);
    Turn(85);
    Drive(1,25);
    Puncher();
    Drive(12,100);
    if(PuncBall)    Puncher();
    Turn(5);//slight turn to miss pole
    // IntakeAutoEnabled=false;
    Drive(3,100);

    Turn(25);//45deg turn get cap
    Flip(FliperPosDown);
    Drive(-8,100,0);
    // IntakeAutoEnabled=true;
    Drive(-15,25,750);
    Flip(FliperPosIn);
}
void AutFunBackRed(){
    Drive(24,100,-1);
    Drive(3,50,250);
    Turn(-92);
    Flip(FliperPosDown);
    Drive(-9);
    Flip(FliperPosIn);
    Turn(165);
    IntakeAutoEnabled=false;
    Drive(-44,100);//get on platform
}
void AutFunBackBlue(){
    Drive(24,100,-1);
    Drive(3,50,250);
    Turn(95);
    Flip(FliperPosDown);
    Drive(-9);
    Flip(FliperPosIn);
    Turn(-170);
    IntakeAutoEnabled=false;
    Drive(-42,100);//get on platform
}
void Sniper(){

}
void FrontSkills(){
    
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
    Turn(100);
    EndTimeSlice(2000);
    Turn(-170);
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