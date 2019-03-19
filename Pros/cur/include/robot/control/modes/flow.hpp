#ifndef FLOW_HPP
#define FLOW_HPP
//config
// extern int IntakeTimer;//timer for the intake
namespace Flow{
  //vars
  enum class Modes{FLAG,CAPS,DEBUG,NONE};
  //vars FUNCTIONS
  Modes get_mode();
  void set_mode(Modes m);
  //methods
  void init();
  void user();

}
// //auton
// extern int DriveEndWait;
// extern int TurnEndWait;
// extern int PuncherEndWait;
//
// enum class StartPos {FrontRed,BackRed,FrontBlue,BackBlue};
// enum class ProgPot {Pink,Green,Yellow};
// enum class Variant {White,Black,Purple};
// extern StartPos FeildPos ;
// extern ProgPot AutoProg ;
// extern Variant AVariant ;
// //screens
// extern StartPos FeildPosBrainScreenSetColorLast;
//
// extern StartPos FeildPosControllerScreenPrintAutonosLast;
// extern ProgPot AutoProgControllerScreenPrintAutonosLast;
// extern Variant AVariantControllerScreenPrintAutonosLast ;
//
// // extern ControlModes ControlModeConPrintWas;
// // bool IntakeAutoEnabledConPrintWas=IntakeAutoEnabled;
// //tasks
// extern bool DriveRampingEnabled;//task
// extern bool IntakeAutonEnabled;//task
// extern bool ControllerScreenEnabled;//task
// extern bool StartEnabled;//task
//
// extern bool StartInited;
// namespace Flow{
// }

#endif /* end of include guard: FLOW_HPP */
