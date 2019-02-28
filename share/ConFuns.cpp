void UsrLogic(){
    AutoClean();
    UserStart();

    while (1) {
        // WristControl();
        ConModeTog();
        IntakeControl();
        DriveControl();
        LiftParkControl();
        switch(ControlMode){
            case ControlModes::Caps:
                LiftCapsControl();
                ClampCapsControl();
                break;
            case ControlModes::Flag:
                PuncherFlagControl();
                IntakeFlagControl();
                ConModeL1Tog();
                break;
            case ControlModes::Debug:
                
                break;
        }
        ClampExecute();
        LiftExecute();
        PuncherExecute();
        IntakeExecute();
        EndTimeSlice(20); //Sleep the task for a short amount of time to prevent wasted resources. 
    }
}
void PrgLogic(){
    UserClean();
    AutoStart();
    // vex::task ControllerScreenPrintSpiningTask(ControllerScreenPrintSpining);
    // Drive(12,100);
    AutonSelFun();      //update vars
    AutoSelRunFuns();   //run funs
}
void PreLogic(){
    Brain.Screen.render(true,false);
    vex::task BrainScreenStartTask(BrainScreenStartFun);
    vex::task ControllerScreenStartTask(ControllerScreenStartFun);
    // while(AutSel[0].value(vex::analogUnits::pct)==0){}
    Clamp.SetStop(vex::brakeType::coast);
    Clamp.SetTolerance(1);

    Lift.SetStop(vex::brakeType::hold);
    Lift.SetPosLimits(10,450);
    // Lift.SetTolerance(1);
    // Lift.SetVSetting(0);
    // Lift.SendControl=SendControl::SST;//start user in sst mode

    Puncher.SetStop(vex::brakeType::coast);
    Intake.SetStop(vex::brakeType::brake);

    FLDrive.SetStop(vex::brakeType::coast);
    FRDrive.SetStop(vex::brakeType::coast);
    BLDrive.SetStop(vex::brakeType::coast);
    BRDrive.SetStop(vex::brakeType::coast);

    FLDrive.SetRUnits(vex::rotationUnits::rev);
    FRDrive.SetRUnits(vex::rotationUnits::rev);
    BLDrive.SetRUnits(vex::rotationUnits::rev);
    BRDrive.SetRUnits(vex::rotationUnits::rev);
        // ClaCon.SpinToControlEnabled=true;
        // ClaCon.SpinToRunEnabled=true;
        Clamp.SetVSetting(100);
    PunCon.SpinToControlEnabled=true;//enable control
    PunCon.MonoDir=true;
    PunCon.Dir=1;



    // LifCon.RampingInit(LR);//init ramping for the lift controller using the lift ramp object
}