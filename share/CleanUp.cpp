void PreClean(){//cleans up after pre auton
    ControllerScreenStartFunEnabled=false;
    BrainScreenStartFunEnabled=false;
}
//forward defed
int Liftcaltaskfun(){
    Lift.Calibrate(-100,1/2,500,10,150);
    
    Lift.SetTargetSetting(LiftPosDown);
    Lift.SendControl=SendControl::SST;//start user in sst mode
    Lift.SetVSetting(100);
    LiftExecute();//start spin to bottom

    return 0;
}
int LiftAuton(){
    LiftA=true;
    EndTimeSlice(1000);
    while(LiftA){
        Lift.SST(Lift.GetTargetSetting(),Lift.GetVSetting());
        ClampExecute();// get out of way for the puncher

        EndTimeSlice(20);
    }
    return 0;
}
void StartInit(bool Task=false){//Init for first time started
    if(!StartInited){
        StartInited=true;//tog
        PreClean();//clean pre auton
        //motorcal
        AllMotorsResetRotation();//clear out encoders
        if(Task){
            vex::task LiftCalTask(Liftcaltaskfun);
        }
        else
        {
            Liftcaltaskfun();
        }
    }
}
void BothClean(){
    FLDrive.SetVRatio(1);
    FRDrive.SetVRatio(1);
    BLDrive.SetVRatio(1);
    BRDrive.SetVRatio(1);

    Clamp.SetVSetting(0);
    Lift.SetVSetting(0);
    Puncher.SetVSetting(0);
    Intake.SetVSetting(0);
    FLDrive.SetVSetting(0);
    FRDrive.SetVSetting(0);
    BLDrive.SetVSetting(0);
    BRDrive.SetVSetting(0);

    Clamp.SMS(Clamp.GetVSetting());
    Lift.SMS(Lift.GetVSetting());
    Puncher.SMS(Puncher.GetVSetting());
    Intake.SMS(Intake.GetVSetting());
    FLDrive.SMS(FLDrive.GetVSetting());
    FRDrive.SMS(FRDrive.GetVSetting());
    BLDrive.SMS(BLDrive.GetVSetting());
    BRDrive.SMS(BRDrive.GetVSetting());
}
void BothStart(){
    Lift.SetTargetSetting(LiftPosDown);
    Lift.SendControl=SendControl::SST;//start user in sst mode

    Clamp.SetTargetSetting(ClampPosIn);
    ClampExecute();// get out of way for the puncher
}
//clean up
void AutoClean(){//cleans up auton
    // PreClean();
    // StopAllMotors();
    //task stops
    ControllerScreenStartFunEnabled=false;
    Left.Enabled=false;
    IntakeAutonEnabled=false;
    LiftA=false;
}
void UserClean(){//cleans up user
    // PreClean();
    Controller1.Screen.clearScreen();//get rid of drive dir
    // StopAllMotors();
    //task stop

    ControllerScreenUsrFunEnabled=false;
    BrainScreenUsrFunEnabled=false;
    IntakeStateUpDateEnabled=false;
    ComRumerEnabled=false;
}
//set up
void UserStart(){//sets up for user
    AutoClean();
    BothClean();
    BothStart();
    StartInit();

    DriveSetStop(vex::brakeType::coast);
    // DriveSMS(1,1,1,1);
    // DriveSMS(0,0,0,0);

    vex::task ControllerScreenUsrTask(ControllerScreenUsrFun);
    vex::task BrainScreenUsrTask(BrainScreenUsrFun);
    vex::task BallUpDateTask(IntakeStateUpDate);
    vex::task ConRumTask(ComRumer);

    Lift.SetTargetSetting(LiftPosDown);
    Lift.SendControl=SendControl::SST;//start user in sst mode

    Clamp.SetTargetSetting(ClampPosUp);

    IntakeAutoEnabled=true;

    ControlMode=ControlModes::Flag;

    FlagInit();

}
void AutoStart(){//sets up for auton
    UserClean();
    BothClean();
    BothStart();
    StartInit(true);

    Controller1.Screen.print("auto started");

    DriveSetStop(vex::brakeType::hold);
    // DriveSMS(1,1,1,1);
    // DriveSMS(0,0,0,0);

    FLDrive.ResetRotation();
    FRDrive.ResetRotation();
    BLDrive.ResetRotation();
    BRDrive.ResetRotation();

    FLDrive.SetTargetSetting(0);
    FRDrive.SetTargetSetting(0);
    BLDrive.SetTargetSetting(0);
    BRDrive.SetTargetSetting(0);

    Clamp.SetTargetSetting(ClampPosUp);

    vex::task ControllerScreenStartTask(ControllerScreenStartFun);
    vex::task DriveRampTask(DriveRamping);
    vex::task LiftAutonTask(LiftAuton);
    vex::task IntakeAutonTask(IntakeAuton);
}