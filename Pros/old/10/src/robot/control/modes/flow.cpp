#include "robot/control/modes/flow.hpp"
#include "robot/control/modes/flag.hpp"
#include "robot/control/modes/caps.hpp"

#include "robot/control/systems/drive.hpp"
#include "robot/control/systems/intake.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/puncher.hpp"

namespace Flow{
  //vars
  Modes Mode=Modes::NONE;
  //vars FUNCTIONS
  Modes get_mode(){
    return Mode;
  }
  void set_mode(Modes m){
    Mode=m;
  }
  //methods
  namespace Control{
    void modeTog(){
      if(BtnTog.changed()){
        if(BtnTog.isPressed()){
          switch (get_mode()) {
            case Modes::FLAG:
              Caps::init();
            break;
            case Modes::CAPS:
              Flag::init();
            break;
            case Modes::DEBUG:
              Flag::init();
            break;
            case Modes::NONE:
            break;
          }
        }
        else{

        }
      }
      else if(BtnTog.isPressed()){

      }
      else{

      }
    }
    void toCapsTog(){
      if(BtnToCaps.changed()){
        if(BtnToCaps.isPressed()){
          Caps::init();
        }
        else{

        }
      }
      else if(BtnToCaps.isPressed()){

      }
      else{

      }
    }
  }
  void init(){
    Flag::init();
  }
  void execute(){
    Drive::execute();
    Intake::execute();
    Lift::execute();
    Puncher::execute();
  }
  void user(){
    Control::modeTog();
    switch (get_mode()) {
      case Modes::FLAG:
        Control::toCapsTog();
        Flag::user();
      break;
      case Modes::CAPS:
        Caps::user();
      break;
      case Modes::DEBUG:
        //debug
      break;
      case Modes::NONE:
        //nothing is going on here
      break;
    }
    execute();
  }
}
