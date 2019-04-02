// #include "custom/mecanum_drive.hpp"
// // FrontLeft(((x-y-10*(z*M_PI/180))/WheelCir));
// // BackLeft(((x+y+10*(z*M_PI/180))/WheelCir));
// // FrontRight(((x+y-10*(z*M_PI/180))/WheelCir));
// // BackRight(((x-y+10*(z*M_PI/180))/WheelCir));
//
// Mecanumdrive::  MecanumDrive(const okapi::Motor &fl,const okapi::Motor &bl,const okapi::Motor &fr,const okapi::Motor &br,double wheelcir,double width,double length){
//   FrontLeft=const_cast<okapi::Motor *>(&fl);
//   BackLeft=const_cast<okapi::Motor *>(&bl);
//   FrontRight=const_cast<okapi::Motor *>(&fr);
//   BackRight=const_cast<okapi::Motor *>(&br);
//   switch(FrontLeft->getGearing()){
//     case okapi::AbstractMotor::gearset::red:
//     maxRPM=100;
//     break;
//     case okapi::AbstractMotor::gearset::green:
//     maxRPM=200;
//     break;
//     case okapi::AbstractMotor::gearset::blue:
//     maxRPM=600;
//     break;
//     case okapi::AbstractMotor::gearset::invalid:
//     maxRPM=200;
//     break;
//   };
//   WheelCir=wheelcir;
//   Width=width;
//   Length=length;
// }
// void Mecanumdrive::left(double v){
//   FrontLeft->moveVelocity(v);
//   BackLeft->moveVelocity(v);
// }
// void Mecanumdrive::right(double v){
//   FrontRight->moveVelocity(v);
//   BackRight->moveVelocity(v);
// }
// void Mecanumdrive::tank(double left, double right, double strafe){
//   FrontLeft->moveVelocity(left+strafe);
//   BackLeft->moveVelocity(left-strafe);
//   FrontRight->moveVelocity(right-strafe);
//   BackRight->moveVelocity(right+strafe);
// }
// // void Mecanumdrive::tank(okapi::Controller con){
// //   int LHJoy=con.getAnalog(okapi::ControllerAnalog::leftX)*200;
// //   int LVJoy=con.getAnalog(okapi::ControllerAnalog::leftY)*200;
// //   int RVJoy=con.getAnalog(okapi::ControllerAnalog::rightY)*200;
// //   int RHJoy=con.getAnalog(okapi::ControllerAnalog::rightX)*200;
// //
// //
// //   if(std::abs(LVJoy)<5)    LVJoy=0;
// //   if(std::abs(RVJoy)<5)    RVJoy=0;
// //   if(std::abs(LHJoy)<100)    LHJoy=0;
// //   if(std::abs(RHJoy)<100)    RHJoy=0;
// //
// //   if(LVJoy!=0 || RVJoy!=0 || LHJoy!=0 || RHJoy!=0){
// //     set_controller(Controllers::MANUAL);
// //     tank(
// //       get_inverted() ?  -RVJoy : LVJoy,
// //       get_inverted() ?  -LVJoy : RVJoy,
// //       get_inverted() ?  -RHJoy : LHJoy,
// //       get_inverted() ?  -LHJoy : RHJoy);
// //     }
// //     else{
// //       if(get_controller()==Controllers::MANUAL)  tank(0,0,0,0);//Last loop before disableing; used to release drivemanualcontrol
// //       set_controller(Controllers::NONE);
// //     }
// // }
//
// void Mecanumdrive::calcDis(double forward, double strafe, double yaw){
//   forwardSum+=forward;
//   strafeSum+=strafe;
//   yawSum+=yaw;
//
//   FrontLeft->set_target((forward-strafe-((Width+Length)/2)*(yaw*M_PI/180))/WheelCir);
//   BackLeft->set_target((forward+strafe+((Width+Length)/2)*(yaw*M_PI/180))/WheelCir);
//   FrontRight->set_target((forward+strafe-((Width+Length)/2)*(yaw*M_PI/180))/WheelCir);
//   BackRight->set_target((forward-strafe+((Width+Length)/2)*(yaw*M_PI/180))/WheelCir);
// }
// void Mecanumdrive::calcVelRatio(){
//   double maxTargetDelta=std::max(FrontLeft->get_targetDelta(), std::max(BackLeft->get_targetDelta(), std::max(FrontRight->get_targetDelta(), BackRight->get_targetDelta())));
//
//   FrontLeft->set_RPM(FrontLeft->get_targetDelta()/maxTargetDelta);
//   BackLeft->set_RPM(BackLeft->get_targetDelta()/maxTargetDelta);
//   FrontRight->set_RPM(FrontRight->get_targetDelta()/maxTargetDelta);
//   BackRight->set_RPM(BackRight->get_targetDelta()/maxTargetDelta);
// }
// void Mecanumdrive::Absolute(double forward, double strafe, double yaw){
//   calcDis(forward, strafe, yaw);
//   calcVelRatio();
//
//   FrontLeft->moveAbsolute(FrontLeft->get_target(),FrontLeft->get_RPM());
//   BackLeft->moveAbsolute(BackLeft->get_target(),BackLeft->get_RPM());
//   FrontRight->moveAbsolute(FrontRight->get_target(),FrontRight->get_RPM());
//   BackRight->moveAbsolute(BackRight->get_target(),BackRight->get_RPM());
// }
// void Mecanumdrive::AbsolutelyRelative(double forward, double strafe, double yaw){
//   forward+=forwardSum;
//   strafe+=strafeSum;
//   yaw+=yawSum;
//   calcDis(forward, strafe, yaw);
//   calcVelRatio();
//
//   FrontLeft->moveAbsolute(FrontLeft->get_target(),FrontLeft->get_RPM());
//   BackLeft->moveAbsolute(BackLeft->get_target(),BackLeft->get_RPM());
//   FrontRight->moveAbsolute(FrontRight->get_target(),FrontRight->get_RPM());
//   BackRight->moveAbsolute(BackRight->get_target(),BackRight->get_RPM());
// }
