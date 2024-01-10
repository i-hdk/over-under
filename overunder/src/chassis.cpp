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

/**
    * @brief Set the Left Voltage object
    * 
    * @param volt [-128,127]
    */
void Chassis::setLeftVoltage(int volt){
    backL = volt;
    frontL = volt;
    middleL = volt;
}

/**
    * @brief Set the Right Voltage object
    * 
    * @param volt [-128,127]
    */
void Chassis::setRightVoltage(int volt){
    backR = volt;
    frontR = volt;
    middleR = volt;
}
