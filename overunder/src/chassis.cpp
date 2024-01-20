#include "chassis.h"
Chassis* Chassis::instance = nullptr;

pros::Motor backR (1, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor backL (11, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor frontR (4, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor frontL (13, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_ROTATIONS); 
pros::Motor middleR (2, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor middleL (12, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_ROTATIONS); 

Chassis* Chassis::getInstance(){
    if(instance==nullptr){
        instance = new Chassis();
    }
    return instance;
}

void Chassis::initialize(){
    backL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	backR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	middleL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	middleR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	frontL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	frontR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void Chassis::coast(){
    backL.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	backR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	middleL.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	middleR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	frontL.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	frontR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}
void Chassis::setLeftVoltage(int volt){
    backL = volt;
    frontL = volt;
    middleL = volt;
}

void Chassis::setRightVoltage(int volt){
    backR = volt;
    frontR = volt;
    middleR = volt;
}

void Chassis::setRightVelocity(int vel){
	backR.move_velocity(vel);
	middleR.move_velocity(vel);
	frontR.move_velocity(vel);
}

void Chassis::setLeftVelocity(int vel){
	backL.move_velocity(vel);
	middleL.move_velocity(vel);
	frontL.move_velocity(vel);
}

void Chassis::setDriveVelocity(int leftVel, int rightVel){
    setRightVelocity(rightVel);
    setLeftVelocity(leftVel);
}
