#include "teleop.h"


pros::Controller master(pros::E_CONTROLLER_MASTER);


Teleop::Teleop(){
    for(auto u:buttons) prev[u] = 0;
}

bool Teleop::toggle(pros::controller_digital_e_t button){
    if(prev[button]==0&&master.get_digital(button)) return true;
    return false;
} //TODO: have ismoving functions for individual submodules to use in perioidic 

bool Teleop::hold(pros::controller_digital_e_t button){
    if(master.get_digital(button)) return true;
    return false;
}

/**
    * @brief runs every 20 ms
    * 
    */
void Teleop::periodic(){
    int left = master.get_analog(ANALOG_LEFT_Y);
    int right = master.get_analog(ANALOG_RIGHT_X);
    Chassis* drive = Chassis::getInstance();
    drive->setRightVoltage(left-right);
    drive->setLeftVoltage(left+right);
    for(auto u:buttons) prev[u] = master.get_digital(u);
}