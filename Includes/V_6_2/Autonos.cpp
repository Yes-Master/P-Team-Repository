void FrontAutFun(int Side){//+is red;   -is blue
    if(Side==1){//red front
        Drive(25,100);
        Drive(3,50);
        Drive(-33,100,0);
        DriveRecon(-50,500);
        Drive(2,50);
        Turn(-9*SGN(Side),25,25);
        //Drive(1);
        Puncher();
        Drive(12,100);
        if(PuncBall)    Puncher();
        Turn(-.5*SGN(Side));
       // IntakeAutoEnabled=false;
        Drive(8,100);

        Turn(-2.5*SGN(Side));
        Flip(Fliper(DOWN));
        Drive(-8,100,0);
       // IntakeAutoEnabled=true;
        Drive(-24,25,750);
        Flip(Fliper(UP));
    }
    else{//blue front
        Drive(25,100);
        Drive(3,50);
        Drive(-33,100,0);
        DriveRecon(-50,500);
        Drive(2,50);
        Turn(-8.8*SGN(Side),25,25);
        //Drive(1);
        Puncher();
        Drive(12,100);
        if(PuncBall)    Puncher();
        Turn(-.5*SGN(Side));
       // IntakeAutoEnabled=false;
        Drive(8,100);

        Turn(-3*SGN(Side));
        Flip(Fliper(DOWN));
        Drive(-8,100,0);
       // IntakeAutoEnabled=true;
        Drive(-24,25,750);
        Flip(Fliper(UP));
    }
}
void BackAutFun(int Side){//+is red;   -is blue
    if(Side==1){//red
        Drive(40);
        Turn(-10);
        Flip(Fliper(DOWN));
        Drive(-10);
        Flip(Fliper(UP));
        Turn(18);
        IntakeAutoEnabled=false;
        Drive(-38,100);
    }
    else{//blue
        Drive(40);
        Turn(10);
        Flip(Fliper(DOWN));
        Drive(-11);
        Flip(Fliper(UP));
        Turn(-18);
        IntakeAutoEnabled=false;
        Drive(-45,100);
    }
}