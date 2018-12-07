void AutoClean(){
    StartEnabled=false;
    //stop all motors
    DriveSMS(0,0);
    DI(0,0);//set drive ramping to 0
    FlipMotor.stop();
    IntakeSMS(0);
    PuncherSMS(0);
    LiftMotor.stop();

    DriveRampingEnabled=false;
    IntakeAutonEnabled=false;
    //PuncherMotorIsSpinningUpDaterEnabled=false;
}
void UserClean(){
    StartEnabled=false;
    Controller1.Screen.clearScreen();
    //stop all motors
    DriveSMS(0,0);
    DI(0,0);//set drive ramping to 0
    FlipMotor.stop();
    IntakeSMS(0);
    PuncherSMS(0);
    LiftMotor.stop();

    //PuncherMotorIsSpinningUpDaterEnabled=false;
    IntakeStateUpDateEnabled=false;
    ComRumerEnabled=false;
    ControllerScreenEnabled=false;
}
void UserStart(){
    //    vex::task FliperCalTask(FliperCal);
    //    vex::task PuncherCalTask(PuncherCal);

    FLDriveMotor.setStopping(vex::brakeType::coast);
    FRDriveMotor.setStopping(vex::brakeType::coast);
    BLDriveMotor.setStopping(vex::brakeType::coast);
    BRDriveMotor.setStopping(vex::brakeType::coast);

    vex::task ControllerScreenTask(ControllerScreen);
    vex::task BrainScreenTask(BrainScreen);
    //vex::task PuncherMotorIsSpinningUpDaterTask(PuncherMotorIsSpinningUpDater);
    vex::task BallUpDateTask(IntakeStateUpDate);
    vex::task ConRumTask(ComRumer);
    IntakeAutoEnabled=true;
    DriveBrake=false;
    FliperRequested=FliperPosIn;//auton uses this var
    //FliperPosControlEnabled=true;//enable the fliper pos to move to target set above

}
void AutoStart(){
    //    vex::task FliperCalTask(FliperCal);
    //    vex::task PuncherCalTask(PuncherCal);
    Controller1.Screen.print("auto started");

    FLDriveMotor.setStopping(vex::brakeType::hold);
    FRDriveMotor.setStopping(vex::brakeType::hold);
    BLDriveMotor.setStopping(vex::brakeType::hold);
    BRDriveMotor.setStopping(vex::brakeType::hold);
    vex::task BrainScreenTask(BrainScreen);
    //vex::task ControllerScreenTask(ControllerScreen);
    vex::task DriveRampingTask(DriveRamping);
    //vex::task PuncherMotorIsSpinningUpDaterTask(PuncherMotorIsSpinningUpDater);
    vex::task IntakeAutonTask(IntakeAuton);
}