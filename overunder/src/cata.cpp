#include "cata.h"
Cata* Cata::instance = nullptr;

pros::Motor cata (20, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Rotation rotation(10);

Cata* Cata::getInstance(){
    if(instance==nullptr){
        instance = new Cata();
    }
    return instance;
}

void Cata::intialize(){
    cata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rotation.reset();
    rotation.reset_position();
    rotation.set_position(0);
}

Cata::Cata(){
    running = 0;
    waitTime = 0;
    waitStop = 0;
}

/**
    * @brief set cata target [0,72000]
    * 
    * @param stop1 lower bound
    * @param stop2 upper bound
    */
void Cata::setStop(double stop1, double stop2){
    run();
    stopL = stop1;
    stopR = stop2;
    waitStop = 1;
    running = 1;
}

void Cata::setTime(double sec){
    run();
    begin = std::chrono::steady_clock::now();
    toggleTime = sec;
    waitTime = 1;
    running = 1;
}

int Cata::position(){
    return rotation.get_position()%(18000*4);
}

void Cata::run(){
    cata.move_velocity(600);
}

void Cata::run(int speed){
    cata.move_velocity(speed);
}

bool Cata::isRunning(){
    return running;
}

void Cata::interrupt(){
    waitStop = 0;
    running = 0;
    waitTime = 0;
}

void Cata::periodic(){
    if(running){
        if(waitStop&&position()<=stopR&&position()>=stopL){
            cata.move_velocity(0);
            running = 0;
            waitStop = 0;
        }
        if(waitTime){
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            t = (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) /1000000.0;
            if(t>=toggleTime){
                cata.move_velocity(0);
                waitTime = 0;
                running = 0;
            }
        }
    }
}

