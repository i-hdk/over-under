#include "teleop.h"
#include "pros/misc.h"


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

void Teleop::periodic(){ 
    Chassis* drive = Chassis::getInstance();
    int left = master.get_analog(ANALOG_LEFT_Y);
    int right = master.get_analog(ANALOG_RIGHT_X);
    drive->setRightVoltage(left-right);
    drive->setLeftVoltage(left+right);

    Cata* cata = Cata::getInstance();
    if(toggle(pros::E_CONTROLLER_DIGITAL_A)){
        cata->setStop(31000, 72000);
    }
    else if(toggle(pros::E_CONTROLLER_DIGITAL_X)){
        cata->setStop(31500, 36000);
    }
    else if(toggle(pros::E_CONTROLLER_DIGITAL_B)){
        cata->setTime(0.1);
    }
    else if(hold(pros::E_CONTROLLER_DIGITAL_Y)){
        cata->run();
        cata->interrupt();
    }
    else if(!cata->isRunning()){
        cata->run(0);
    }
    cata->periodic();

    Intake* intake = Intake::getInstance();
    if(hold(pros::E_CONTROLLER_DIGITAL_R1)) {
        intake->runIn();
    }
    else if(hold(pros::E_CONTROLLER_DIGITAL_R2)){
        intake->runOut();
    }
    else{
        intake->run(0);
    }

    Wing* wing = Wing::getInstance();
    if(toggle(pros::E_CONTROLLER_DIGITAL_L1)) wing->change();
    else if(toggle(pros::E_CONTROLLER_DIGITAL_LEFT)) wing->out();
    else if(toggle(pros::E_CONTROLLER_DIGITAL_RIGHT)) wing->in();
    Blocker* blocker = Blocker::getInstance();
    if(toggle(pros::E_CONTROLLER_DIGITAL_L2)) blocker->change();
    else if(toggle(pros::E_CONTROLLER_DIGITAL_UP)) blocker->out();
    else if(toggle(pros::E_CONTROLLER_DIGITAL_DOWN)) blocker->in();

    for(auto u:buttons) prev[u] = master.get_digital(u);
}