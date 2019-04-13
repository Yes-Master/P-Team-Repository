#include "robot/control/auton/selection.hpp"
#include "display/lvgl.h"
#include "robot/config/controller_config.hpp"
#include "robot/control/auton/routines.hpp"
#include <string>
#include <algorithm>
namespace auton{
  namespace selection{
    /*forward defs*/
    void StyleInit();
    void BtnInit(lv_obj_t * btn,lv_style_t * sty,int row,int col);
    void LabelInit(_lv_obj_t * lab,lv_style_t * sty,int row,int x,int y);
    std::string RoutsToString(int one,int two);
    void ControllerScreen();
    static lv_res_t On_Click(_lv_obj_t * btn);

    lv_obj_t * Btn1_1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t * Btn1_2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t * Btn1_3 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t * Btn1_4 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t * Btn1_5 = lv_btn_create(lv_scr_act(), NULL);

    lv_obj_t * Btn2_1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t * Btn2_2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t * Btn2_3 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t * Btn2_4 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t * Btn2_5 = lv_btn_create(lv_scr_act(), NULL);

    lv_obj_t * Btn3_1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t * Btn3_2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t * Btn3_3 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t * Btn3_4 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t * Btn3_5 = lv_btn_create(lv_scr_act(), NULL);

    lv_obj_t * Btn4_1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t * Btn4_2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t * Btn4_3 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t * Btn4_4 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t * Btn4_5 = lv_btn_create(lv_scr_act(), NULL);

    lv_obj_t * row0 = lv_label_create(lv_scr_act(), NULL);
    lv_obj_t * row1 = lv_label_create(lv_scr_act(), NULL);
    lv_obj_t * row2 = lv_label_create(lv_scr_act(), NULL);
    lv_obj_t * row3 = lv_label_create(lv_scr_act(), NULL);

    lv_style_t style_red;
    lv_style_t style_blue;
    lv_style_t style_config;
    // lv_style_t style_btn;

    int row;//if nothing is selected run this
    int col;//if nothing is selected run this
    std::string ConHeaders[4]={"RF","RB","BB","BF"};
    std::string RowHeaders[4]={"F","B","B","F"};
    std::string routines[4][5]={
      {"Simple","norMid","","","TestR"}, /*first is over written by header*//*both->RF*/
      {"FarPar","","","","Skills"}, /*first is over written by header*//*both->RB*/
      {"FarPar","","","","Default"}, /*first is over written by header*//*both->BB*/
      {"Simple","norMid","","","TestB"}, /*first is over written by header*//*both->RF*/
    };
    void execute(){
      std::clamp(row, -1, 3);
      std::clamp(col,  0, 4);
      // if(row==-1){
      //   if(col==0)      routines::defaultSelection();
      //   else if(col==1) routines::skills();
      //   else if(col==2) {}
      //   else if(col==3) {}
      //   else if(col==4) {}
      // }
      if(row==0){
        if(col==0)      routines::red::front::cloFar();
        else if(col==1) routines::red::front::midBoth();
        else if(col==2) {}
        else if(col==3) {}
        else if(col==4) routines::testR();
      }
      else if(row==1){
        if(col==0)      routines::red::back::farPark();
        else if(col==1) {}
        else if(col==2) {}
        else if(col==3) {}
        else if(col==4) routines::skills();
      }
      else if(row==2){
        if(col==0)      routines::blue::back::farPark();
        else if(col==1) {}
        else if(col==2) {}
        else if(col==3) {}
        else if(col==4) routines::defaultSelection();
      }
      else if(row==3){
        if(col==0)      routines::blue::front::cloFar();
        else if(col==1) routines::blue::front::midBoth();
        else if(col==2) {}
        else if(col==3) {}
        else if(col==4) routines::testB();
      }
    }
    void screenInit(){
      StyleInit();

      LabelInit(row0,&style_red, 0,5,45);
      LabelInit(row1,&style_red, 1,5,60);
      LabelInit(row2,&style_blue,2,5,165);
      LabelInit(row3,&style_blue,3,5,180);

      BtnInit(Btn1_1,&style_red,0,0);
      BtnInit(Btn1_2,&style_red,0,1);
      BtnInit(Btn1_3,&style_red,0,2);
      BtnInit(Btn1_4,&style_red,0,3);
      BtnInit(Btn1_5,&style_config,0,4);

      BtnInit(Btn2_1,&style_red,1,0);
      BtnInit(Btn2_2,&style_red,1,1);
      BtnInit(Btn2_3,&style_red,1,2);
      BtnInit(Btn2_4,&style_red,1,3);
      BtnInit(Btn2_5,&style_config,1,4);

      BtnInit(Btn3_1,&style_blue,2,0);
      BtnInit(Btn3_2,&style_blue,2,1);
      BtnInit(Btn3_3,&style_blue,2,2);
      BtnInit(Btn3_4,&style_blue,2,3);
      BtnInit(Btn3_5,&style_config,2,4);

      BtnInit(Btn4_1,&style_blue,3,0);
      BtnInit(Btn4_2,&style_blue,3,1);
      BtnInit(Btn4_3,&style_blue,3,2);
      BtnInit(Btn4_4,&style_blue,3,3);
      BtnInit(Btn4_5,&style_config,3,4);


      lv_btn_set_state(Btn3_5, LV_BTN_STATE_PR);
      On_Click(Btn3_5);

    }
    void StyleInit(){
      lv_style_copy(&style_red, &lv_style_plain);
      style_red.text.color = LV_COLOR_HEX(0xFF0000);

      lv_style_copy(&style_blue, &lv_style_plain);
      style_blue.text.color = LV_COLOR_HEX(0x0000FF);

      lv_style_copy(&style_config, &lv_style_plain);
      style_config.text.color = LV_COLOR_HEX(0x00FF00);

      // lv_style_copy(&style_btn, &lv_style_plain);
    }
    void BtnInit(lv_obj_t * btn,lv_style_t * sty,int row,int col){
      lv_obj_t * label;
      int x=465/5*col+480-465;
      int y=240/4*row;
      lv_btn_set_toggle(btn, true);
      lv_obj_set_pos(btn,x,y);
      lv_obj_set_size(btn,465/5,240/4);
      lv_btn_set_action(btn, LV_BTN_ACTION_CLICK,On_Click);
      // lv_obj_set_style(btn,&style_btn);

      label = lv_label_create(btn, NULL);
      lv_obj_set_style(label,sty);
      lv_label_set_text(label, routines[row][col].c_str());

      std::cout <<"Btn on row "<< row <<" and col "<< col <<" Inited";
      if(sty==&style_red) std::cout<<"red"<<std::endl;
      else  std::cout<<"blue"<<std::endl;
    }
    void LabelInit(_lv_obj_t * lab,lv_style_t * sty,int row,int x,int y){
      lv_obj_set_pos(lab, x, y);  /*Align to the top*/      // lv_obj_set_size(lab,350/5,240/4);
      lv_obj_set_style(lab,sty);
      lv_label_set_text(lab,RowHeaders[row].c_str());

      std::cout <<"Label on row "<< row <<" Inited"<<std::endl;
    }
    std::string RoutsToString(int one,int two){
      return routines[one][two];
    }
    void ControllerScreen(){
      std::clamp(row, 0, 3);
      std::clamp(col, 0, 4);
      if(col==4)  controllerMaster.setText(0, 0, RoutsToString(row,col)+"            ");
      else  controllerMaster.setText(0, 0, ConHeaders[row]+" "+RoutsToString(row,col)+"            ");
    }
       static lv_res_t On_Click(_lv_obj_t * btn){
      if(btn==Btn1_1){  row=0;  col=0;  } else {  lv_btn_set_state(Btn1_1, LV_BTN_STATE_REL);  /*lv_obj_set_style(Btn1_1,&style_btn);*/  }
      if(btn==Btn1_2){  row=0;  col=1;  } else {  lv_btn_set_state(Btn1_2, LV_BTN_STATE_REL);  /*lv_obj_set_style(Btn1_2,&style_btn);*/  }
      if(btn==Btn1_3){  row=0;  col=2;  } else {  lv_btn_set_state(Btn1_3, LV_BTN_STATE_REL);  /*lv_obj_set_style(Btn1_3,&style_btn);*/  }
      if(btn==Btn1_4){  row=0;  col=3;  } else {  lv_btn_set_state(Btn1_4, LV_BTN_STATE_REL);  /*lv_obj_set_style(Btn1_4,&style_btn);*/  }
      if(btn==Btn1_5){  row=0;  col=4;  } else {  lv_btn_set_state(Btn1_5, LV_BTN_STATE_REL);  /*lv_obj_set_style(Btn1_5,&style_btn);*/  }
      if(btn==Btn2_1){  row=1;  col=0;  } else {  lv_btn_set_state(Btn2_1, LV_BTN_STATE_REL);  /*lv_obj_set_style(Btn2_1,&style_btn);*/  }
      if(btn==Btn2_2){  row=1;  col=1;  } else {  lv_btn_set_state(Btn2_2, LV_BTN_STATE_REL);  /*lv_obj_set_style(Btn2_2,&style_btn);*/  }
      if(btn==Btn2_3){  row=1;  col=2;  } else {  lv_btn_set_state(Btn2_3, LV_BTN_STATE_REL);  /*lv_obj_set_style(Btn2_3,&style_btn);*/  }
      if(btn==Btn2_4){  row=1;  col=3;  } else {  lv_btn_set_state(Btn2_4, LV_BTN_STATE_REL);  /*lv_obj_set_style(Btn2_4,&style_btn);*/  }
      if(btn==Btn2_5){  row=1;  col=4;  } else {  lv_btn_set_state(Btn2_5, LV_BTN_STATE_REL);  /*lv_obj_set_style(Btn2_5,&style_btn);*/  }
      if(btn==Btn3_1){  row=2;  col=0;  } else {  lv_btn_set_state(Btn3_1, LV_BTN_STATE_REL);  /*lv_obj_set_style(Btn3_1,&style_btn);*/  }
      if(btn==Btn3_2){  row=2;  col=1;  } else {  lv_btn_set_state(Btn3_2, LV_BTN_STATE_REL);  /*lv_obj_set_style(Btn3_2,&style_btn);*/  }
      if(btn==Btn3_3){  row=2;  col=2;  } else {  lv_btn_set_state(Btn3_3, LV_BTN_STATE_REL);  /*lv_obj_set_style(Btn3_3,&style_btn);*/  }
      if(btn==Btn3_4){  row=2;  col=3;  } else {  lv_btn_set_state(Btn3_4, LV_BTN_STATE_REL);  /*lv_obj_set_style(Btn3_4,&style_btn);*/  }
      if(btn==Btn3_5){  row=2;  col=4;  } else {  lv_btn_set_state(Btn3_5, LV_BTN_STATE_REL);  /*lv_obj_set_style(Btn3_5,&style_btn);*/  }
      if(btn==Btn4_1){  row=3;  col=0;  } else {  lv_btn_set_state(Btn4_1, LV_BTN_STATE_REL);  /*lv_obj_set_style(Btn4_1,&style_btn);*/  }
      if(btn==Btn4_2){  row=3;  col=1;  } else {  lv_btn_set_state(Btn4_2, LV_BTN_STATE_REL);  /*lv_obj_set_style(Btn4_2,&style_btn);*/  }
      if(btn==Btn4_3){  row=3;  col=2;  } else {  lv_btn_set_state(Btn4_3, LV_BTN_STATE_REL);  /*lv_obj_set_style(Btn4_3,&style_btn);*/  }
      if(btn==Btn4_4){  row=3;  col=3;  } else {  lv_btn_set_state(Btn4_4, LV_BTN_STATE_REL);  /*lv_obj_set_style(Btn4_4,&style_btn);*/  }
      if(btn==Btn4_5){  row=3;  col=4;  } else {  lv_btn_set_state(Btn4_5, LV_BTN_STATE_REL);  /*lv_obj_set_style(Btn4_5,&style_btn);*/  }
      std::cout <<"row: "<<row<<" col: "<<col<<std::endl;
      ControllerScreen();
      return LV_RES_OK;
    }
  }
}
