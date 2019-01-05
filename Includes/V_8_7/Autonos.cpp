void AutFunFrontRed(){
    Drive(29,100,-1);
    Drive(3,50,500);
    Drive(-29.5,100,-1);
    DriveRecon(-25,500);

    Drive(11,25);
    PuncherAut(false);//charge the puncher dont wait
    Turn(-9);
    Drive(1,25);
    PuncherAut();//fire
    PuncherAut(false);//charge the puncher dont wait
    Drive(7,100);
    EndTimeSlice(100);//time
    PuncherAut();//fire
    // EndTimeSlice(100);//time
    //Drive(2,50);//drive up to pole
    Turn(-0.5);//slight turn to miss pole
    // IntakeAutoEnabled=false;
    Drive(5,100);//drive into flag

    Turn(-3.4);//45deg turn get cap
    Flip(FliperPosDown);
    Drive(-4,100,-1);
    Drive(-25,25,100);
    Flip(FliperPosUpMid);
}
void AutFunFrontBlue(){
    Drive(29,100,-1);
    Drive(3,50,500);
    Drive(-29.5,100,-1);
    DriveRecon(-25,500);

    Drive(5,25);
    PuncherAut(false);//charge
    Turn(9.3);//the good times
    Drive(1,25);
    PuncherAut();//fire
    PuncherAut(false);//chrge
    Drive(7,100);
    EndTimeSlice(100);
    PuncherAut();//fire
    // EndTimeSlice(100);//time
    //Drive(2,50);//drive up to pole
    Turn(0.5);//slight turn to miss pole
    // IntakeAutoEnabled=false;
    Drive(8,100);

    Turn(3.5);//45deg turn get cap
    Flip(FliperPosDown);
    Drive(-4,100,-1);
    Drive(-20,25,100);
    Flip(FliperPosUpMid);
}
void AutFunBackRed(){
    Drive(22,100,-1);
    Drive(3,50,250);
    Turn(-11);
    Flip(FliperPosDown);
    Drive(-9);
    Flip(FliperPosIn);
    Turn(18);
    IntakeAutoEnabled=false;
    Drive(-48,100);//get on platform
}
void AutFunBackBlue(){
    Drive(24,100,-1);
    Drive(3,50,250);
    Turn(11);
    Flip(FliperPosDown);
    Drive(-9);
    Flip(FliperPosIn);
    Turn(-18.5);
    IntakeAutoEnabled=false;
    Drive(-39,100);//get on platform
}
void Sniper(){
    PuncherAut(false);
    PuncherAut();
}
void FrontSkills(){
    Drive(26,100,-1);
    Drive(3,50,1000);
    Drive(-29.5,100,-1);
    DriveRecon(-25,500);
    DriveRecon(-5,250);

    Drive(8.5,25);
    Turn(-9.3);
    //Drive(1,25);
    //Puncher();
    Drive(8,100);
    if(PuncBall)    //Puncher();
    //Drive(2,50);//drive up to pole
    Turn(-0.8);//slight turn to miss pole
    // IntakeAutoEnabled=false;
    Drive(7,100);//drive into flag

    Turn(-3.1);//45deg turn get cap
    Flip(FliperPosDown);
    Drive(-4,100,-1);
    Drive(-20,25,750);
    Flip(FliperPosUpMid);
    //=======================================
    Turn(-4.4);//turn to wall
    Drive(23,50);//drive to wall
    IntakeAutoEnabled=false;
    DriveRecon(15,500);//recon
    DriveRecon(5,250);//recon
    Drive(-5,50);//drive away form wall
    IntakeAutoEnabled=true;
    Turn(-10.5);//tsurn perallel to wall
    Drive(46.5,50);//drive perallel to wall && line up to park
    Turn(9.5);//turn to park
    Drive(6,50);//drive to wall
    IntakeAutoEnabled=false;
    DriveRecon(15,500);//recon
    DriveRecon(5,250);
    Drive(-70,100);//drive on park
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
    //Puncher();
    //
    Drive(12,100);
    if(PuncBall)    //Puncher();
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
        if(PuncBall){}    //Puncher();
        Drive(12,100);
        if(PuncBall){}    //Puncher();
    }
    else if(PuncBall && !FeedBall){}    //Puncher();
}
void TestingFront(){
    Controller1.Screen.clearLine();
    Controller1.Screen.print("test");
    IntakeAutoEnabled=false;
    PuncherAut();
    EndTimeSlice(750);
    PuncherAut();
}
void TestingBack(){
    PuncherAut();
    Controller1.Screen.clearLine();
    Controller1.Screen.print("done with punc");
}
//
void AutoSelRunFuns(){//runs selected auton
    if(FeildPos==StartPos::BackRed){
        if(AutoProg==ProgPot::Pink)         BackSkills();//Skills
        else if(AutoProg==ProgPot::Green)   AutFunBackRed();//Normal
        else if(AutoProg==ProgPot::Yellow)  Sniper();//Sniper
    }
    else if(FeildPos==StartPos::FrontRed){
        if(AutoProg==ProgPot::Pink)         FrontSkills();//Skills
        else if(AutoProg==ProgPot::Green)   AutFunFrontRed();//Normal
        else if(AutoProg==ProgPot::Yellow)  Sniper();//Sniper
    }
    else if(FeildPos==StartPos::FrontBlue){
        if(AutoProg==ProgPot::Pink)         TestingFront();
        else if(AutoProg==ProgPot::Green)   AutFunFrontBlue();//Normal
        else if(AutoProg==ProgPot::Yellow)  Sniper();//Sniper
    }
    else if(FeildPos==StartPos::BackBlue){
        if(AutoProg==ProgPot::Pink)         TestingBack();
        else if(AutoProg==ProgPot::Green)   AutFunBackBlue();//Normal
        else if(AutoProg==ProgPot::Yellow)  Sniper();//Sniper
    }
}