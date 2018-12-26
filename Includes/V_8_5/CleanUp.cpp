void PreClean(){
    ControllerScreenStartFunEnabled=false;
    BrainScreenStartFunEnabled=false;

}
void AutoClean(){
    PreClean();
    StopAllMotors();
    //task stops
    ControllerScreenStartFunEnabled=false;
    DriveRampingEnabled=false;
    IntakeAutonEnabled=false;
}
void UserClean(){
    PreClean();
    Controller1.Screen.clearScreen();//get rid of drive dir
    StopAllMotors();
    //task stop

    ControllerScreenUsrFunEnabled=false;
    BrainScreenUsrFunEnabled=false;
    IntakeStateUpDateEnabled=false;
    ComRumerEnabled=false;
}
void MotorsCal(){
    if(!MotorsCaled){
        FliperCal();
        MotorsCaled=true;
    }
}
void UserStart(){
    MotorsCal();
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
void AutoStart(){
    MotorsCal();
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