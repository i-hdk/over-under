#include "wing.h"
Wing* Wing::instance = nullptr;

pros::ADIDigitalOut wing ('G');

Wing* Wing::getInstance(){
    if(instance==nullptr) instance = new Wing();
    return instance;
}
void Wing::initialize(){
    wing.set_value(false);
}
Wing::Wing(){
    wingOut = 0;
}
void Wing::out(){
    wing.set_value(true);
    wingOut = 1;
}

void Wing::in(){
    wing.set_value(0);
    wingOut = 0;
}

void Wing::change(){
    if(wingOut) in();
    else out();
}
