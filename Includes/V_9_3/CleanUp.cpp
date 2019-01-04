void PreClean(){//cleans up after pre auton
    ControllerScreenStartFunEnabled=false;
    BrainScreenStartFunEnabled=false;
}
//need forward def
void StartInit(bool Task=false){//Init for first time started
    if(!StartInited){
        StartInited=true;//tog
        PreClean();//clean pre auton
        //motorcal
        if(Task)    vex::task FliperCalTask(FliperCalTaskFun);
        else        FliperCal();
        MotorsCaled=true;
    }
}
//clean up
void AutoClean(){//cleans up auton
    PreClean();
    StopAllMotors();
    //task stops
    ControllerScreenStartFunEnabled=false;
    DriveRampingEnabled=false;
    IntakeAutonEnabled=false;
}
void UserClean(){//cleans up user
    PreClean();
    Controller1.Screen.clearScreen();//get rid of drive dir
    StopAllMotors();
    //task stop

    ControllerScreenUsrFunEnabled=false;
    BrainScreenUsrFunEnabled=false;
    IntakeStateUpDateEnabled=false;
    ComRumerEnabled=false;
}
//set up
void UserStart(){//sets up for user
    StartInit();
    //    vex::task FliperCalTask(FliperCal);
    //    vex::task PuncherCalTask(PuncherCal);

    FLDriveMotor.setStopping(vex::brakeType::coast);
    FRDriveMotor.setStopping(vex::brakeType::coast);
    BLDriveMotor.setStopping(vex::brakeType::coast);
    BRDriveMotor.setStopping(vex::brakeType::coast);

    vex::task ControllerScreenUsrTask(ControllerScreenUsrFun);
    vex::task BrainScreenUsrTask(BrainScreenUsrFun);
    vex::task BallUpDateTask(IntakeStateUpDate);
    vex::task ConRumTask(ComRumer);

    IntakeAutoEnabled=true;
    DriveHold=false;
    FliperRequested=FliperPosIn;//auton uses this var
}
void AutoStart(){//sets up for auton
    StartInit(true);
    //    vex::task FliperCalTask(FliperCal);
    //    vex::task PuncherCalTask(PuncherCal);
    Controller1.Screen.print("auto started");

    FLDriveMotor.setStopping(vex::brakeType::hold);
    FRDriveMotor.setStopping(vex::brakeType::hold);
    BLDriveMotor.setStopping(vex::brakeType::hold);
    BRDriveMotor.setStopping(vex::brakeType::hold);

    //vex::task ControllerScreenStartTask(ControllerScreenStartFun);
    vex::task DriveRampingTask(DriveRamping);
    vex::task IntakeAutonTask(IntakeAuton);
}