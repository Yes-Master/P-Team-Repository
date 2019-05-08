#ifndef INTAKE_HPP
#define INTAKE_HPP
// #include "main.h"
namespace intake {
  //global vars
extern const int vIn;
extern const int vOut;
extern const int vStop;
extern const int vOver;

  enum class Controllers{MANUAL,AUTO,NONE};//add to motors class

  //vars FUNCTIONS
  // Controllers get_controller();
  // void set_controller(Controllers c);
  int get_VSetting();
  void set_VSetting(int v);
  void set_VSetting(int v,bool m);

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
    Modes get_mode();//return current intake mode
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
