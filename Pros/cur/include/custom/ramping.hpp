#ifndef RAMPING_HPP
#define RAMPING_HPP

class Ramping{
protected:
  double changeVal=1;    //the amout of Val change per loop
  int changeMsec=5;   //the amount of time inbetween loops

  double valRequested=0; //used to request value
  double valOutput=0;    //val output
  double maxVal=100;     //the max val output
  double minVal=0;       //the min val output

public:
  bool enabled=false;
  //need to move to prvotected

  Ramping(double CV,double CM,double maxV=100,double minV=0);

  double calculate();
  double calculate(double cv);
  void request(int val);
  void instant(int val);

  double output();

  double get_requested();
  int get_changeMsec();

  double get_max();
  double get_min();
  void set_limits(double max,double min);
};


#endif /* end of include guard: RAMPING_HPP */
