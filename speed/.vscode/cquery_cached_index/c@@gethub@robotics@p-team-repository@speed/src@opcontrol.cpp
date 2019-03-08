#include "main.h"

/**
* Runs the operator control code. This function will be started in its own task
* with the default priority and stack size whenever the robot is enabled via
* the Field Management System or the VEX Competition Switch in the operator
* control mode.
*
* If no competition control is connected, this function will run immediately
* following initialize().
*
* If the robot is disabled or communications is lost, the
* operator control task will be stopped. Re-enabling the robot will restart the
* task, not resume it from where it left off.
*/
okapi::Controller master_controller(okapi::ControllerId::master);
okapi::Motor left0(17,false,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor left1(13,true,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor left2(14,true,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor left3(20,false,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor right0(16,true,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor right1(8,false,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor right2(15,false,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor right3(11,true,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees);

okapi::MotorGroup Left={left0,left1,left2,left3};
okapi::MotorGroup Right={right0,right1,right2,right3};
okapi::ControllerButton GearUp=master_controller[okapi::ControllerDigital::R1];
okapi::ControllerButton GearDown=master_controller[okapi::ControllerDigital::R2];

void limit(int &val, int min,int max){
	if(val<min)	val=min;
	if(val>max)	val=max;
}
int gear=1;
double rpm=200;
void print(){
	master_controller.setText(1, 0, "setting:");
	master_controller.setText(1, 9, std::to_string(gear));
	master_controller.setText(2, 0, "rpm:");
	master_controller.setText(2, 5, std::to_string(rpm));
}
void opcontrol() {
	while (true) {
		if(GearUp.changed()){
			if(GearUp.isPressed()){
				gear++;
				limit(gear,1,10);
				rpm=200/gear;
				print();
			}
		}
		else if(GearDown.changed()){
			if(GearDown.isPressed()){
				gear--;
				limit(gear,1,10);
				rpm=200/gear;
				print();
			}
		}
		Left.moveVelocity(master_controller.getAnalog(okapi::ControllerAnalog::leftY)*rpm);
		Right.moveVelocity(master_controller.getAnalog(okapi::ControllerAnalog::rightY)*rpm);
		pros::delay(20);
	}
}
