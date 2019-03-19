#include "custom/ramping.hpp"

Ramping::Ramping(double CV,double CM,double maxV,double minV){
  ChangeVal=CV;
  ChangeMsec=CM;
  MaxVal=maxV;
  MinVal=minV;
}

double Ramping::Calculate(){
  if(ValRequested>ValOutput)      ValOutput+=ChangeVal;
  else if(ValRequested<ValOutput) ValOutput-=ChangeVal;
  //limit Val
  if(ValOutput>MaxVal)	ValOutput=MaxVal;
  if(ValOutput<-MaxVal)	ValOutput=-MaxVal;
  if(ValOutput>0 && ValOutput<MinVal) ValOutput=MinVal;
  if(ValOutput<0 && ValOutput>MinVal) ValOutput=-MinVal;

  return ValOutput;
}
double Ramping::Calculate(double cv){
  ChangeVal=cv;
  return Calculate();
}

void Ramping::Request(int val){
  ValRequested=val;
}
void Ramping::Instant(int val){
  Request(val);
  ValOutput=val;
}

double Ramping::Output(){
  return ValOutput;
}

double Ramping::get_requested(){
  return ValRequested;
}
int Ramping::get_changeMsec(){
  return ChangeMsec;
}

double Ramping::get_max(){
  return MaxVal;
}
double Ramping::get_min(){
  return MinVal;
}
void Ramping::set_limits(double max,double min){
  MaxVal=max;
  MinVal=min;
}
