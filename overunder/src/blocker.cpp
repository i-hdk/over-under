#include "blocker.h"
Blocker* Blocker::instance = nullptr;

pros::ADIDigitalOut outBlocker ('A');
//pros::ADIDigitalOut inBlocker ('A');

Blocker* Blocker::getInstance(){
    if(instance==nullptr) instance = new Blocker();
    return instance;
}
void Blocker::initialize(){
    outBlocker.set_value(0);
    //inBlocker.set_value(1);
    
}

Blocker::Blocker(){
    blockerOut = 0;
}
void Blocker::out(){
    outBlocker.set_value(true);
    //inBlocker.set_value(0);
    blockerOut = 1;
}

void Blocker::in(){
    outBlocker.set_value(0);
    //inBlocker.set_value(1);
    blockerOut = 0;
}

void Blocker::change(){
    if(blockerOut) in();
    else out();
}
