void FrontAutFun(int Side){//+is red;   -is blue
    if(Side==1){//red front
        Drive(24,100);
        Drive(3,50);
        Drive(-33,100,0);
        DriveRecon(-50,500);
        Drive(2,50);
        Turn(-8.7*SGN(Side));
        //Drive(1);
        Puncher();
        Drive(12,100);
        if(PuncBall)    Puncher();
        Turn(-.5*SGN(Side));
        // IntakeAutoEnabled=false;
        Drive(8,100);

        Turn(-2.6*SGN(Side));
        Flip(FliperPosDown);
        Drive(-8,100,0);
        // IntakeAutoEnabled=true;
        Drive(-15,25,750);
        Flip(FliperPosUp);
    }
    else{//blue front
        Drive(25,100);//retune
        Drive(3,50);
        Drive(-33,100,0);
        DriveRecon(-50,500);
        Drive(2,50);
        Turn(-8.8*SGN(Side));
        //Drive(1);
        Puncher();
        Drive(12,100);
        if(PuncBall)    Puncher();
        Turn(-.5*SGN(Side));
        // IntakeAutoEnabled=false;
        Drive(8,100);

        Turn(-3.2*SGN(Side));
        Flip(FliperPosDown);
        Drive(-8,100,0);
        // IntakeAutoEnabled=true;
        Drive(-15,25,750);
        Flip(FliperPosUp);
    }
}
void BackAutFun(int Side){//+is red;   -is blue
    if(Side==1){//red
        Drive(39);
        Turn(-11);
        Flip(FliperPosDown);
        Drive(-11);
        Flip(FliperPosUp);
        Turn(20);
        IntakeAutoEnabled=false;
        Drive(-45,100);
    }
    else{//blue
        Drive(40);
        Turn(11);
        Flip(FliperPosDown);
        Drive(-10);
        Flip(FliperPosUp);
        Turn(-18.5);
        IntakeAutoEnabled=false;
        Drive(-43,100);
    }
}