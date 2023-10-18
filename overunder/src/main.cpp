#include "main.h"
#include "api.h"
#include <math.h>
#include <string>
#include <bits/stdc++.h>
using namespace okapi;

// button for lowering down to lowest spot for intake
//reverse drive

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor backL (1, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor backR (11, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor frontL (4, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor frontR (13, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_ROTATIONS); 
pros::Motor middleL (2, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor middleR (12, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_ROTATIONS); 
pros::Motor cata (20, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor intake (9, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_ROTATIONS);

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
void autonomous() {}

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
void opcontrol() {
	while (true) {
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_X);
		/*
		backL = left;
		frontL = left;
		middleL = left;
		backR = right;
		frontR = right;
		middleR = right;
		*/
		
		backL = left - right;
		frontL = left - right;
		middleL = left -right;
		backR = left + right;
		frontR = left + right;
		middleR = left + right;
		
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
		else{
			aPrev = master.get_digital(pros::E_CONTROLLER_DIGITAL_A);
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


		pros::delay(20);
	}
}
