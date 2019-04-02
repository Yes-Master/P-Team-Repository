#ifndef INTAKE_HPP
#define INTAKE_HPP
// #include "main.h"
namespace intake {
  //global vars
  extern const int VOut;
  extern const int VStop;
  extern const int VIn;
  extern const int VOver;

  enum class Controllers{MANUAL,AUTO,NONE};//add to motors class

  //vars FUNCTIONS
  // Controllers get_controller();
  // void set_controller(Controllers c);
  int get_VSetting();
  void set_VSetting(int v);
  //methods
  void execute();//execute motor requests
  namespace control{
    //vars
    //vars FUNCTIONS
    //methods
    void combo();
    void feedOut();
    void feedIn();
    void toggle();
    void execute();
  }
  namespace automatic{
    //vars
    enum Modes{FAST,SLOW,OUT,NONE};
    //vars FUNCTIONS
    Modes get_Mode();//return current intake mode
    namespace balls {
      //vars
      //vars FUNCTIONS
      bool get_puncherActual();
      bool get_puncher();
      void set_puncher(bool p);
      bool get_over();
      // void set_over(bool o);
      void set_overEnabled(bool e);
      bool get_feed();
      //methods
    }

    //methods
    void toggle();
    void enable();
    void disable();

    void execute();
  }
}
#endif /* end of include guard: INTAKE_HPP */
