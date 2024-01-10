#include "intake.h"
Intake* Intake::instance = nullptr;

pros::Motor intake (9, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_ROTATIONS);


    
Intake* Intake::getInstance(){
    if(instance==nullptr) instance = new Intake();
    return instance;
}
void Intake::runIn(){
    intake.move_velocity(200);
}
void Intake::runOut(){
    intake.move_velocity(-200);
}
void Intake::run(int vel){
    intake.move_velocity(vel);
}

void Intake::initialize(){
    intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}
