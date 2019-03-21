#ifndef SELECTION_HPP
#define SELECTION_HPP

namespace Auton{
  namespace Selection{
    enum class Autons{RED,BLUE,SKILLS};
    Autons get_sel();
    void on_left_btn();
    void on_center_btn();
    void on_right_btn();
  }
}

#endif /* end of include guard: SELECTION_HPP */
