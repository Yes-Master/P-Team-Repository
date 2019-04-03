#include "custom/ramping.hpp"

Ramping::Ramping(double CV,double CM,double maxV,double minV){
  changeVal=CV;
  changeMsec=CM;
  maxVal=maxV;
  minVal=minV;
}

double Ramping::calculate(){
  if(valRequested>valOutput)      valOutput+=changeVal;
  else if(valRequested<valOutput) valOutput-=changeVal;
  //limit Val
  if(valOutput>maxVal)	valOutput=maxVal;
  if(valOutput<-maxVal)	valOutput=-maxVal;
  if(valOutput>0 && valOutput<minVal) valOutput=minVal;
  if(valOutput<0 && valOutput>minVal) valOutput=-minVal;

  return valOutput;
}
double Ramping::calculate(double cv){
  changeVal=cv;
  return calculate();
}

void Ramping::request(int val){
  valRequested=val;
}
void Ramping::instant(int val){
  request(val);
  valOutput=val;
}

double Ramping::output(){
  return valOutput;
}

double Ramping::get_requested(){
  return valRequested;
}
int Ramping::get_changeMsec(){
  return changeMsec;
}

double Ramping::get_max(){
  return maxVal;
}
double Ramping::get_min(){
  return minVal;
}
void Ramping::set_limits(double max,double min){
  maxVal=max;
  minVal=min;
}
