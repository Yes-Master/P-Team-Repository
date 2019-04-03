#ifndef FLOW_HPP
#define FLOW_HPP
//config
// extern int IntakeTimer;//timer for the intake
namespace flow{
  //vars
  enum class Modes{FLAG,CAPS,DEBUG,NONE};
  //vars FUNCTIONS
  Modes get_mode();
  void set_mode(Modes m);
  //methods
  void init();
  void user();
}
#endif /* end of include guard: FLOW_HPP */
