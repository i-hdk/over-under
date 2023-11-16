#include "main.h"
#include "api.h"
#include <math.h>
#include <string>
#include <bits/stdc++.h>
using namespace okapi;

// button for lowering down to lowest spot for intake
// slower cata??

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor backL (1, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor backR (11, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor frontL (4, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor frontR (13, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_ROTATIONS); 
pros::Motor middleL (2, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor middleR (12, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_ROTATIONS); 
pros::Motor cata (20, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor intake (9, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::ADIDigitalIn limSwitch ('H');
pros::ADIDigitalOut wing ('G');


/**
 * @brief control left and right velocities of drivetrain, [-600,600]
 * 
 * @param leftVel 
 * @param rightVel 
 */
void setDriveVelocity(int leftVel, int rightVel){
	backL.move_velocity(leftVel);
	middleL.move_velocity(leftVel);
	frontL.move_velocity(leftVel);
	backR.move_velocity(rightVel);
	middleR.move_velocity(rightVel);
	frontR.move_velocity(rightVel);
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
	wing.set_value(false);
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
void autonomous() {
	/*
	/*
	setDriveVelocity(-320,-320);
	pros::delay(2750/2-200);
	setDriveVelocity(0,0);
	pros::delay(500);
	setDriveVelocity(-100,100); //reverse this for left/right side
	pros::delay(950);
	
	setDriveVelocity(0,0);
	cata.move_velocity(200);
	pros::delay(3500);
	cata.move_velocity(0);
	setDriveVelocity(-300,-300);
	pros::delay(900);
	cata.move_velocity(0);
	setDriveVelocity(0,0);

//go back
setDriveVelocity(500,500);
	pros::delay(400);
	setDriveVelocity(0,0);
setDriveVelocity(300,-300); //reverse this for left/right side
	pros::delay(470);
	
	setDriveVelocity(0,0);
	setDriveVelocity(600,600);
	pros::delay(500);
	setDriveVelocity(0,0);
	/*
	pros::delay(400);
setDriveVelocity(300,300);
	pros::delay(1000);
	setDriveVelocity(0,0);*/
	
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
 bool limPrev = 0;
 bool wingout = 0;
 bool leftPrev = 0;
 std::chrono::duration<double> elapsed_seconds;
 auto start = std::chrono::system_clock::now();
void opcontrol() {
	backL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	backR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	middleL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	middleR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	frontL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	frontR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	wing.set_value(false);
	while (true) {
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_X);
		/*
		backL = left - right;
		frontL = left - right;
		middleL = left -right;
		backR = left + right;
		frontR = left + right;
		middleR = left + right;*/
		
		//flip::
		
		backL = -left - right;
		frontL = -left - right;
		middleL = -left -right;
		backR = -left + right;
		frontR = -left + right;
		middleR = -left + right; 
		
		/*
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
			cata.move_velocity(200);
		}
		else{
			cata.move_velocity(0);
		}
		*/


		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A)==1&&aPrev==0){
			if(!aOn){
				cata.move_velocity(200);
				aOn = 1;
			}
			else{
				cata.move_velocity(0);
				aOn = 0;
			}
			aPrev = 1;
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_X)==1&&limSwitch.get_value()==0){
			cata.move_velocity(200);
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)==1&&limSwitch.get_value()==0){
			cata.move_velocity(200);
			limPrev = 0;
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)==1&&limSwitch.get_value()==1){
			if(!limPrev){
				start = std::chrono::system_clock::now();
			}
			else{
				auto end = std::chrono::system_clock::now();
				elapsed_seconds = end-start;
			}
			if(elapsed_seconds.count()>0.2){
				cata.move_velocity(200);
			}
			else{
				cata.move_velocity(0);
			}
			limPrev = 1;
		}
		else{
			aPrev = master.get_digital(pros::E_CONTROLLER_DIGITAL_A);
			cata.move_velocity(0);
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
			intake.move_velocity(200);
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
			intake.move_velocity(-200);
		}
		else{
			intake.move_velocity(0);
		}
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)&&leftPrev==0){
			leftPrev = 1;
			if(wingout==0){
				wing.set_value(true);
				wingout=1;
			}
			else{
				wing.set_value(false);
				wingout=0;
			}
		}
		leftPrev = master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);

pros::lcd::set_text(1, std::to_string(limSwitch.get_value()));
		pros::delay(20);
	}
}
