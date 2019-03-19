#ifndef RAMPING_HPP
#define RAMPING_HPP

class Ramping{
protected:
  double ChangeVal=1;    //the amout of Val change per loop
  int ChangeMsec=5;   //the amount of time inbetween loops

  double ValRequested=0; //used to request value
  double ValOutput=0;    //val output
  double MaxVal=100;     //the max val output
  double MinVal=0;       //the min val output


public:
  bool Enabled=false;
  //need to move to prvotected

  Ramping(double CV,double CM,double maxV=100,double minV=0);

  double Calculate();
  double Calculate(double cv);
  void Request(int val);
  void Instant(int val);

  double Output();

  double get_requested();
  int get_changeMsec();

  double get_max();
  double get_min();
  void set_limits(double max,double min);
};


#endif /* end of include guard: RAMPING_HPP */
