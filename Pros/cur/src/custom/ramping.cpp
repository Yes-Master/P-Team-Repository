#include "custom/ramping.hpp"

Ramping::Ramping(double CV, double CM, double max, double min) {
  changeVal = CV;
  changeMsec = CM;
  Max = max;
  Min = min;
}

double Ramping::calculate() {
  if (valRequested == valOutput) return valOutput;
  if (valRequested > valOutput)
    valOutput += changeVal;
  else if (valRequested < valOutput)
    valOutput -= changeVal;
  //limit Val
  if (valOutput > Max) valOutput = Max;
  if (valOutput < Min) valOutput = Min;
  if (valOutput > 0 && valOutput < gMin) valOutput = vMin;
  if (valOutput < 0 && valOutput > gMax) valOutput = vMax;

  return valOutput;
}
double Ramping::calculate(double cv) {
  request(cv);
  return calculate();
}

double Ramping::triDistance(double endValue) {
  double h = output();
  double b = changeMsec * h / changeVal;
  return (h * 3 / 500) * b / 2;
}
double Ramping::trapDistance(double endValue) {
  return triDistance(endValue);
}
void Ramping::request(int val) {
  valRequested = val;
}
void Ramping::instant(int val) {
  request(val);
  valOutput = val;
}

double Ramping::output() {
  return valOutput;
}

double Ramping::get_requested() {
  return valRequested;
}
int Ramping::get_changeMsec() {
  return changeMsec;
}

double Ramping::get_max() {
  return Max;
}
double Ramping::get_min() {
  return Min;
}
void Ramping::set_limits(double maxGate, double minGate, double maxVal, double minVal) {
  gMax = maxGate;
  gMin = minGate;
  vMax = maxGate;
  vMin = minGate;
}
