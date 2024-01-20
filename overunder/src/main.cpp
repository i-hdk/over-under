#include "main.h"
#include "api.h"
#include <math.h>
#include <string>
#include <bits/stdc++.h>
#include "teleop.h"
#include "motionprofile.h"
#include "left.h"
#include "right.h"
using namespace okapi;

/**
 * TODO:
 * TEST TELEOP WINGS, intake	s
 */

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
	Blocker::initialize();
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

void autonomous() {
	Right::run();
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
	MotionProfile::getInstance()->disableAuto();
	while (true) {
		teleop.periodic();
		pros::delay(20);
	}
}
