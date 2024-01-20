#include "blocker.h"
Blocker* Blocker::instance = nullptr;

pros::ADIDigitalOut blocker ('H');

Blocker* Blocker::getInstance(){
    if(instance==nullptr) instance = new Blocker();
    return instance;
}
void Blocker::initialize(){
    blocker.set_value(false);
}
Blocker::Blocker(){
    blockerOut = 0;
}
void Blocker::out(){
    blocker.set_value(true);
    blockerOut = 1;
}

void Blocker::in(){
    blocker.set_value(0);
    blockerOut = 0;
}

void Blocker::change(){
    if(blockerOut) in();
    else out();
}
