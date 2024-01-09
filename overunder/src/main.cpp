#include "main.h"
#include "api.h"
#include <math.h>
#include <string>
#include <bits/stdc++.h>
#include "teleop.h"
using namespace okapi;

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
pros::Imu imu(8);
pros::Rotation rotation(10);

double width = 11.75;
double vel_conversion = 1/6.5*60; //final has to be in rpm, so maybe move certain rotations & measure distance
//goes 6.5 per rotation
bool toggleTurnPID = false, turnLeft, turnPrev = false; 
double turnTarget, turnP = 4, turnI = 0.01, turnD = 1, turnPrevError, turnTotalError;
bool trapezoidal = false, trapezoidalPrev = false;
double trapezoidal_accelTime, trapezoidal_constantTime, trapezoidal_flatVel;
double trapezoidal_curve;
bool curve = 0;
 std::chrono::duration<double> elapsed_seconds;
 auto start = std::chrono::system_clock::now();

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

void setLeftVelocity(int vel){
	backR.move_velocity(vel);
	middleR.move_velocity(vel);
	frontR.move_velocity(vel);
}

void setRightVelocity(int vel){
	backL.move_velocity(vel);
	middleL.move_velocity(vel);
	frontL.move_velocity(vel);
}

void arcRun(double curvatureRadius, double angularSpeed){
	//add for loop to accelerate/decelerate speed??
	//try 20in radius
	setLeftVelocity(vel_conversion*angularSpeed*(curvatureRadius-width/2));
	setRightVelocity(vel_conversion*angularSpeed*(curvatureRadius+width/2));
}

void arcRun(double curvatureRadius, double angularSpeed, double targetAngle){
	//add for loop to accelerate/decelerate speed??
	//try 20in radius
	setRightVelocity(vel_conversion*(curvatureRadius-width/2));
	setLeftVelocity(vel_conversion*(curvatureRadius+width/2));
	while(abs(imu.get_heading()-targetAngle)>2){
		pros::delay(20);	
	}
	setLeftVelocity(0);
	setRightVelocity(0);
}

//void arcRun(double curvatureRadius, double accelTime, double ds,double ds){}
double t = -1; //for use in task
std::chrono::steady_clock::time_point begin;
void backgroundTask(){
	while(1){

		if(trapezoidal){
			pros::lcd::set_text(7, std::to_string(t));
			double vel;
			if(trapezoidalPrev==0){
				start = std::chrono::system_clock::now();
				begin = std::chrono::steady_clock::now();
				//pros::lcd::set_text(1, "prev 0");
	
			}
			else{
				pros::lcd::set_text(5, "prev 1");
			}
			//auto end = std::chrono::system_clock::now();
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			//auto elapsed = end-start;
			t = (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) /1000000.0;
			//interpolate
			if(t<=trapezoidal_accelTime){
				vel = t/trapezoidal_accelTime*trapezoidal_flatVel;
			}
			else if(t>=trapezoidal_accelTime&&t<=trapezoidal_constantTime+trapezoidal_accelTime){
				vel = trapezoidal_flatVel;
			}
			else if(t<=trapezoidal_constantTime+trapezoidal_accelTime*2){
				vel = trapezoidal_flatVel-(t-trapezoidal_constantTime-trapezoidal_accelTime)/trapezoidal_accelTime*trapezoidal_flatVel;
			}
			else if(t>trapezoidal_constantTime+trapezoidal_accelTime*2){
				vel = 0;
				trapezoidal = 0;
			}
			if(curve){
				double angvel = vel/trapezoidal_curve;
				setLeftVelocity(vel_conversion*angvel*(trapezoidal_curve-width/2));
				setRightVelocity(vel_conversion*angvel*(trapezoidal_curve+width/2));
			}
			else{
				setLeftVelocity(vel);
				setRightVelocity(vel);
			}
		}
		pros::lcd::set_text(3, "e");
		trapezoidalPrev = trapezoidal;
		//pros::lcd::set_text(4, std::to_string(trapezoidalPrev));
		if(toggleTurnPID){
			if(turnPrev==0){
				turnTotalError = 0;
				turnPrevError = turnTarget-imu.get_heading();
				turnPrev = 1;
			}
			double error = turnTarget-imu.get_heading();
			pros::lcd::set_text(4, std::to_string(error));
			if(abs(error)>3){
				double vel = turnP*error+turnI*turnTotalError+turnD*(error-turnPrevError);
				if(turnLeft){
					setRightVelocity(vel);
					setLeftVelocity(-vel); 
				}
				else{
				setRightVelocity(-vel);
				setLeftVelocity(vel); 
				}
			}
			else{
				setRightVelocity(0);
				setLeftVelocity(0);
				
			}
			turnPrevError = error;
			pros::lcd::set_text(3, std::to_string(backL.get_actual_velocity()));
		}
		turnPrev = toggleTurnPID;
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
	wing.set_value(false);
	imu.reset();
	rotation.reset();
	rotation.reset_position();
	backL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	backR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	middleL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	middleR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	frontL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	frontR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	cata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	rotation.set_position(0);
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

void runTrapezoid(double accel, double ct, double fv){

	trapezoidal_accelTime =  accel;
	trapezoidal_constantTime = ct;
	trapezoidal_flatVel = fv;
	trapezoidal = 1;
}

void runTrapezoid(double accel, double ct, double fv, double arcradius){
	curve = 1;
	trapezoidal_curve = arcradius;
	trapezoidal_accelTime =  accel;
	trapezoidal_constantTime = ct;
	trapezoidal_flatVel = fv;
	trapezoidal = 1;
}

//assuming wont turn over the 0/360 border
void turnPID(double angle, double timeOut){
	turnTarget = angle;
	toggleTurnPID=1;
	begin = std::chrono::steady_clock::now();
	while(toggleTurnPID){
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		t = (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) /1000000.0;
		if(t>=timeOut) break;
		pros::delay(20);
	}
	toggleTurnPID = 0;
	setLeftVelocity(0);
	setRightVelocity(0);
}


void autonomous() {


	turnLeft = false;
	
	intake.move_velocity(-600);
	pros::delay(1000);
		intake.move_velocity(0);
	//cata.move_velocity(600);
	//pros::delay(200);
	//cata.move_velocity(0);
	imu.set_heading(360-45);
	runTrapezoid(0.1, 0.3, 100);
	
	

	while(trapezoidal==1) pros::delay(10);
	wing.set_value(1);
	pros::delay(1000);
	runTrapezoid(0.1, 0.3, -100);
	while(trapezoidal==1) pros::delay(10);
		pros::delay(1000);
		turnPID(105,3);
		wing.set_value(0);
	cata.move_velocity(600);
	while(!(rotation.get_position()%(18000*4)>31500&&rotation.get_position()%(18000*4)<36000)) pros::delay(10);
	cata.move_velocity(0);
	//pros::delay(1000);
	intake.move_velocity(-600);
	runTrapezoid(0.4, 0.25, 600);
	while(trapezoidal==1) pros::delay(10);
	pros::delay(100);
	runTrapezoid(0.4, 0.25, -600);
	while(trapezoidal==1) pros::delay(10);
	turnPID(90,2);
	//cata.move_velocity(600);
	//while(!(rotation.get_position()%(18000*4)>26000&&rotation.get_position()%(18000*4)<32000)){
	//pros::delay(20);
		
	//	cata.move_velocity(0);




	/*
	intake.move_velocity(-600);
	pros::delay(200);
		intake.move_velocity(0);


cata.move_velocity(600);
	while(!(rotation.get_position()%(18000*4)>32500&&rotation.get_position()%(18000*4)<36000)) pros::delay(10);
	cata.move_velocity(0);
	imu.set_heading(100);
	
	intake.move_velocity(600);
	pros::delay(1000);
	intake.move_velocity(0);
	pros::delay(1000);
	runTrapezoid(0.4, 0.4, 600);
	while(trapezoidal==1) pros::delay(10);
	pros::delay(1000);
	turnPID(10,3);
	intake.move_velocity(-600);
	runTrapezoid(0.1, 0.2, 600);
	while(trapezoidal==1) pros::delay(10);
	*/
	
	
	//skill:
	/*
	imu.set_heading(30);
	intake.move_velocity(-600);
	
	pros::delay(500);
	intake.move_velocity(0);

	turnPID(10,1);
	runTrapezoid(0.1, 0.1, 100);
	while(trapezoidal==1) pros::delay(10);
	intake.move_velocity(0);
	//pros::delay(500);
	//runTrapezoid(0.2, 0.2, 150);
	//while(trapezoidal==1) pros::delay(10);
	//setLeftVelocity(5);
	cata.move_velocity(600);
	backL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	backR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	middleL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	middleR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	frontL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	frontR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	imu.set_heading(40);
	//pros::delay(1000);
	pros::delay(40000);
	while(!(rotation.get_position()%(18000*4)>32500&&rotation.get_position()%(18000*4)<36000)) pros::delay(10);
	cata.move_velocity(0);
    turnPID(65,2);
	pros::delay(1000);
	runTrapezoid(0.4, 1.4, -600);
	while(trapezoidal==1) pros::delay(10);
	//imu.set_heading(90);
	pros::delay(500);
	turnPID(60,1);
imu.set_heading(100);
pros::delay(1000);
turnPID(55,1);
	runTrapezoid(0.1, 0.2, -600);
	while(trapezoidal==1) pros::delay(10);
	turnPID(10,1);
	runTrapezoid(0.4, 0.8, -600);
	while(trapezoidal==1) pros::delay(10);
	*/
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

void opcontrol() {
	trapezoidal=0;
	toggleTurnPID = 0;
	backL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	backR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	middleL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	middleR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	frontL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	frontR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	cata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	wing.set_value(false);
	
	aOn = false;
	xOn = false;
	bOn = false;

	Teleop teleop;
	while (true) {
		teleop.periodic();
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_X);
		
		backL = left - right;
		frontL = left - right;
		middleL = left -right;
		backR = left + right;
		frontR = left + right;
		middleR = left + right;

		//flip::
		/*
		backL = -left - right;
		frontL = -left - right;
		middleL = -left -right;
		backR = -left + right;
		frontR = -left + right;
		middleR = -left + right; */

/*
		backL = master.get_analog(ANALOG_RIGHT_Y);
		frontL = master.get_analog(ANALOG_RIGHT_Y);
		middleL = master.get_analog(ANALOG_RIGHT_Y);
		frontR = master.get_analog(ANALOG_LEFT_Y);
		middleR = master.get_analog(ANALOG_LEFT_Y);
		backR = master.get_analog(ANALOG_LEFT_Y);
		*/
		
		/*
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
			cata.move_velocity(200);
		}
		else{
			cata.move_velocity(0);
		}
		*/

		if(aOn&&rotation.get_position()%(18000*4)>31000&&rotation.get_position()%(18000*4)<18000*4){
			aOn = false;
			cata.move_velocity(0);
		}
//		if(xOn&&((rotation.get_position()%(18000*4)>18000*4-1000&&rotation.get_position()<=0)||rotation.get_position()%(18000*4)<2000)){

		if(xOn&&(rotation.get_position()%(18000*4)>31500&&rotation.get_position()%(18000*4)<36000)){
			xOn = false;
			cata.move_velocity(0);
		}
		if(bOn){
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		t = (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) /1000000.0;
		if(t>=0.1){
			cata.move_velocity(0);
			bOn = 0;
		}
		}
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A)==1&&aPrev==0){
			pros::lcd::set_text(5, "dfsdfsd");
			if(!aOn){
				cata.move_velocity(600);
				aOn = 1;
			}
			else{
				cata.move_velocity(0);
				aOn = 0;
			}
			aPrev = 1;
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_X)==1&&xPrev==0){
			if(!xOn){
				cata.move_velocity(600);
				xOn = 1;
			}
			else{
				cata.move_velocity(0);
				xOn = 0;
			}
			xPrev = 1;
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B)==1&&bPrev==0){
			cata.move_velocity(600);
			bOn = 1;
			bPrev =1;
			begin = std::chrono::steady_clock::now();
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)==1&&limSwitch.get_value()==0){
			cata.move_velocity(600);
			limPrev = 0;
		}
		//&&limSwitch.get_value()==1
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)==1&&limSwitch.get_value()==1){
			if(!limPrev){
				start = std::chrono::system_clock::now();
			}
			else{
				auto end = std::chrono::system_clock::now();
				elapsed_seconds = end-start;
			}
			if(elapsed_seconds.count()>0.2){
				cata.move_velocity(600); 
			}
			else{
				cata.move_velocity(0);
			}
			limPrev = 1;
		}
		else if(aOn==0&&xOn==0&&bOn==0){
			aPrev = master.get_digital(pros::E_CONTROLLER_DIGITAL_A);
			xPrev = master.get_digital(pros::E_CONTROLLER_DIGITAL_X);
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
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)&&leftPrev==0){
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
		leftPrev = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
aPrev = master.get_digital(pros::E_CONTROLLER_DIGITAL_A);
xPrev = master.get_digital(pros::E_CONTROLLER_DIGITAL_X);
bPrev = master.get_digital(pros::E_CONTROLLER_DIGITAL_B);
pros::lcd::set_text(1, std::to_string(limSwitch.get_value()));
pros::lcd::set_text(2, std::to_string(rotation.get_position()%(18000*4)));
pros::lcd::set_text(3, std::to_string(imu.get_heading()));
pros::lcd::set_text(4, std::to_string(rotation.get_position()%(18000*5)));
		pros::delay(20);
	}
}
