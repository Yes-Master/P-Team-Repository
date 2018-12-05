void AutFunFrontRed(){
    Drive(24,100,-1);
    Drive(3,50,250);
    Drive(-26,100,-1);
    DriveRecon(-25,500);

    Drive(2.5,50);
    Turn(-84);
    Drive(1,25);
    Puncher();
    Drive(11,100);
    if(PuncBall)    Puncher();
    Turn(-3);//slight turn to miss pole
    // IntakeAutoEnabled=false;
    Drive(2,100);

    Turn(-30);//45deg turn get cap
    Flip(FliperPosDown);
    Drive(-8,100,0);
    // IntakeAutoEnabled=true;
    Drive(-15,25,750);
    Flip(FliperPosUpMid);
}
void AutFunFrontBlue(){
    Drive(24,100,-1);
    Drive(3,50,250);
    Drive(-26,100,-1);
    DriveRecon(-25,500);

    Drive(2.5,50);
    Turn(90);
    Drive(1,25);
    Puncher();
    Drive(11,100);
    if(PuncBall)    Puncher();
    Turn(3);//slight turn to miss pole
    // IntakeAutoEnabled=false;
    Drive(2,100);

    Turn(30);//45deg turn get cap
    Flip(FliperPosDown);
    Drive(-8,100,0);
    // IntakeAutoEnabled=true;
    Drive(-15,25,750);
    Flip(FliperPosUpMid);
}
void AutFunBackRed(){
    Drive(20,100,-1);
    Drive(3,50,250);
    Turn(-100);
    Flip(FliperPosDown);
    Drive(-10);
    Flip(FliperPosIn);
    Turn(170);
    IntakeAutoEnabled=false;
    Drive(-44,100);//get on platform
}
void AutFunBackBlue(){
    Drive(40);
    Turn(84);
    Flip(FliperPosDown);
    Drive(-10);
    Flip(FliperPosIn);
    Turn(-18.5);
    IntakeAutoEnabled=false;
    Drive(-43,100);

}
void Sniper(){

}
void FrontSkills(){

}
void BackSkills(){

}
void Testing(){
    Turn(85);
}

void AutoSelRunFuns(){
    if(FeildPos==StartPos::BackRed){
        if(AutoProg==ProgPot::Pink)         BackSkills();//Skills
        else if(AutoProg==ProgPot::Green)   AutFunBackRed();//Normal
        else if(AutoProg==ProgPot::Yellow)  Sniper();//Sniper
    }
    else if(AutSel1.value(vex::analogUnits::pct)>50){
        if(AutoProg==ProgPot::Pink)         FrontSkills();//Skills
        else if(AutoProg==ProgPot::Green)   AutFunBackRed();//Normal
        else if(AutoProg==ProgPot::Yellow)  Sniper();//Sniper
    }
    else if(AutSel1.value(vex::analogUnits::pct)>17){
        if(AutoProg==ProgPot::Pink)         Testing();//Skills
        else if(AutoProg==ProgPot::Green)   AutFunBackRed();//Normal
        else if(AutoProg==ProgPot::Yellow)  Sniper();//Sniper
    }
    else{
        if(AutoProg==ProgPot::Pink)         Testing();//Skills
        else if(AutoProg==ProgPot::Green)   AutFunBackRed();//Normal
        else if(AutoProg==ProgPot::Yellow)  Sniper();//Sniper
    }
}