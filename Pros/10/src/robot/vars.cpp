// #include "robot/vars.hpp"
//
//
//
//
// //AllVars
//     //Basic Motors
// double DRMax=1;
// bool DriveSide=false;//used for auton janky plz no
// //Flow Control
//     // enum class AutoMoveStop{//control of auto functions ending
//     //     StopWait,//Stop move and wait for move to finish
//     //     Stop,//stop move don't wait for move to finish
//     //     Junction//don't stop move or wait for move to finish
//     //     };//there is still an EndWait after this block
//
// //Autonos
//     // int FliperEndWait=0;
//
// //Controler Init
//     // int LVJoy=0;
//     // int RVJoy=0;
//     // int LHJoy=0;
//     // int RHJoy=0;
//     // bool L1Pressed=false;//lift     clamp
//     // bool L2Pressed=false;//brake    brake
//     // bool R2Pressed=false;//intake   liftdown
//     // bool R1Pressed=false;//puncher  liftup
//     // bool XPressed=false;//intake    intake
//     // bool YPressed=false;//intake    intake
//     // bool BPressed=false;//NULL      NULL
//     // bool APressed=false;//intake    intake
//     // bool UPressed=false;//caps      flag
//     // bool RPressed=false;//
//     // bool DPressed=false;//
//     // bool LPressed=false;//lift      lift
// //Tog Bools
//     // bool ConModeTogBtnPressed=false;//mode tog
//     // bool Parked=false;//toggle for if lift is set to parking state
//     // bool DrivePIDTAskEnabled=false;
// //Task Bools
//     bool PuncherControlEnabled=false;
//     bool IntakeStateUpDateEnabled=true;
//     bool ComRumerEnabled=false;
//     bool BrainScreenStartFunEnabled=false;
//     bool ControllerScreenStartFunEnabled=false;
//     bool ControllerScreenUsrFunEnabled=false;
//     bool BrainScreenUsrFunEnabled=false;
//     // bool LiftRampingEnabled=false;
//     bool LiftA=false;
// //Clamp
//     //Positions
//         int ClampPosIn=-75;
//         int ClampPosUp=25;
//         int ClampPosDown=250;
// //Lift
//     //Positions
//
// //Puncher
//     //Control
// //PuncherPos
//     //Control
//     //Positions
//         int PuncherPosPosSetting=0;
//         int PucherPosPos[4]={0,5,30,75};
//     //Pct
//         int PuncherPosPctSetting=0;
//     //SpinTo
//         //Auton
//
// //Intake
//     //Control
// //Drive
//         //Control
//             vex::brakeType DriveBrakeType=vex::brakeType::coast;
// //FlowControl
//     //Screens
//         //con
//             int BrainBatWas=Brain.Battery.capacity();
