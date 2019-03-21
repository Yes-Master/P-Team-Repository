#include "main.h"
#include "display/lvgl.h"
#include "robot/auton/selection.hpp"
namespace Auton{
  namespace Selection{
    Autons AutonSelection= Autons::BLUE;//default
    Autons get_sel(){
      lv_obj_t * scr = lv_page_create(NULL, NULL);
      lv_scr_load(scr);

      lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_align(btn1,NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
      return AutonSelection;
    }
    void set_sel(Autons sel){
      AutonSelection=sel;
    }
    void on_left_btn(){
      set_sel(Autons::RED);
      pros::lcd::set_text(1,"Red");
      master_controller.setText(1, 0, "Red       ");
    }
    void on_center_btn(){
      set_sel(Autons::SKILLS);
      pros::lcd::set_text(1,"Skills");
      master_controller.setText(1, 0, "Skills    ");
    }
    void on_right_btn(){
      set_sel(Autons::BLUE);
      pros::lcd::set_text(1,"Blue");
      master_controller.setText(1, 0, "Blue      ");
    }
  }
}
