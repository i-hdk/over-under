#include "main.h"
#include "api.h"
#include <math.h>
#include <string>
#include <bits/stdc++.h>
#include "teleop.h"
#include "motionprofile.h"
using namespace okapi;

double width = 11.75;
double vel_conversion = 1/6.5*60; //final has to be in rpm, so maybe move certain rotations & measure distance
//goes 6.5 per rotation
bool toggleTurnPID = false, turnLeft, turnPrev = false; 
double turnTarget, turnP = 4, turnI = 0.01, turnD = 1, turnPrevError, turnTotalError;

std::chrono::steady_clock::time_point begin;
void backgroundTask(){
	while(1){
		MotionProfile::getInstance()->update();
		pros::delay(10);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
	Cata::intialize();
	Intake::initialize();	
	Chassis::initialize();
	Wing::initialize();
	MotionProfile::initialize();
	pros::Task my_task(backgroundTask);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

//assuming wont turn over the 0/360 border

// void turnPID(double angle, double timeOut){
// 	turnTarget = angle;
// 	toggleTurnPID=1;
// 	begin = std::chrono::steady_clock::now();
// 	while(toggleTurnPID){
// 		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
// 		t = (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) /1000000.0;
// 		if(t>=timeOut) break;
// 		pros::delay(20);
// 	}
// 	toggleTurnPID = 0;
// 	setLeftVelocity(0);
// 	setRightVelocity(0);
// }


void autonomous() {
	MotionProfile::getInstance()->trapezoidal(0.2,0.3,600);
	
}

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

 bool aPrev = 0;
 bool aOn = 0;
 bool xPrev = 0;
 bool xOn = 0;
 bool bPrev = 0;
 bool bOn = 0;
 bool limPrev = 0;
 bool wingout = 0;
 bool leftPrev = 0;

void opcontrol(){
	Teleop teleop;
	while (true) {
		teleop.periodic();
		pros::delay(20);
	}
}
