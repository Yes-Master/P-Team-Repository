    #include <cmath>
    #include "Lib/Released/Basic.cpp"
    #include "Lib/Released/Ramping_2.cpp"
    #include "Lib/Beta/PID.h"
    #include "Lib/Beta/TMotors.h"
    #include "Lib/Beta/TControllers.h"
    //
    vex::brain Brain;
    vex::controller Controller1 = vex::controller();

    vex::motor PuncherMotors[] = {vex::motor(vex::PORT17,vex::gearSetting::ratio36_1,0)};
    
    vex::motor LiftMotors[] = {vex::motor(vex::PORT16,vex::gearSetting::ratio36_1,1)};

    vex::motor ClampMotors[] = {vex::motor(vex::PORT15,vex::gearSetting::ratio18_1,1)};

    vex::motor IntakeMotors[] = {vex::motor(vex::PORT18,vex::gearSetting::ratio6_1,0)};

    vex::motor FLDriveMotors[] = {vex::motor(vex::PORT12,vex::gearSetting::ratio18_1,0)};
    vex::motor FRDriveMotors[] = {vex::motor(vex::PORT13,vex::gearSetting::ratio18_1,1)};
    vex::motor BLDriveMotors[] = {vex::motor(vex::PORT19,vex::gearSetting::ratio18_1,0)};
    vex::motor BRDriveMotors[] = {vex::motor(vex::PORT20,vex::gearSetting::ratio18_1,1)};

    vex::vision Vis1 = vex::vision(vex::PORT1);

    vex::line PuncSen = vex::line(Brain.ThreeWirePort.A);
    vex::line OverSen = vex::line(Brain.ThreeWirePort.B);
    vex::line FeedSen2 = vex::line(Brain.ThreeWirePort.C);
    vex::line FeedSen1 = vex::line(Brain.ThreeWirePort.D);

    vex::pot AutSel[] = {
        vex::pot(Brain.ThreeWirePort.E),
        vex::pot(Brain.ThreeWirePort.F),
        vex::pot(Brain.ThreeWirePort.G)};
    //
        TMotors Clamp(ClampMotors,1);
        TMotors Lift(LiftMotors,1);
        TMotors Puncher(PuncherMotors,1);
        TMotors Intake(IntakeMotors,1);
        TMotors FLDrive(FLDriveMotors,1);
        TMotors FRDrive(FRDriveMotors,1);
        TMotors BLDrive(BLDriveMotors,1);
        TMotors BRDrive(BRDriveMotors,1);
    //
        // TControllers ClaCon(Clamp);
        // TControllers LifCon(Lift);
        TControllers PunCon(Puncher);
    //
    // Ramping LR(5,1);//LiftRamp
    Ramping Left(1,4);
    Ramping Right(1,4);
    Ramping LeftS(1,4);
    Ramping RightS(1,4);
    // Ramping DAR(1,4);
    //
    #include "P-Team-Repository/share/AllVars.cpp"
    #include "P-Team-Repository/share/BasFuns.cpp"
    #include "P-Team-Repository/share/AllScrs.cpp"
    #include "P-Team-Repository/share/AutFuns.cpp"
    #include "P-Team-Repository/share/Autonos.cpp"
    #include "P-Team-Repository/share/UsrFuns.cpp"
    #include "P-Team-Repository/share/CleanUp.cpp"
    #include "P-Team-Repository/share/ConFuns.cpp"