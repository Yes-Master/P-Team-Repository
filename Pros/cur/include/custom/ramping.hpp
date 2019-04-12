#ifndef RAMPING_HPP
#define RAMPING_HPP

class Ramping{
protected:
  double changeVal=1;    //the amout of Val change per loop
  int changeMsec=5;   //the amount of time inbetween loops

  double valRequested=0; //used to request value
  double valOutput=0;    //val output
  double gMax=0;  //max gate
  double gMin=0;  //min gate
  double vMax=0;  //max val
  double vMin=0;  //min val
  double Max=100; //maximum value
  double Min=-100;//minimum value

public:
  bool enabled=false;
  //need to move to prvotected

  Ramping(double CV,double CM,double max,double min);

  double calculate();
  double calculate(double cv);
  void request(int val);
  void instant(int val);

  double output();

  double get_requested();
  int get_changeMsec();

  double get_max();
  double get_min();
  void set_limits(double maxGate,double minGate,double maxVal,double minVal);
};


#endif /* end of include guard: RAMPING_HPP */
