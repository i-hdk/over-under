#include "left.h"

void Left::run(){
    Intake* intake = Intake::getInstance();
    Wing* wings = Wing::getInstance();
    Cata* cata = Cata::getInstance();
    MotionProfile* motion = MotionProfile::getInstance();
Blocker* blocker = Blocker::getInstance();


    intake->runOut();
    wait(1000);
    intake->stop();
    motion->setHeading(360-45);
    motion->trapezoidal(0.1, 0.3, 100);
    while(motion->inMotion()==1) pros::delay(10);
    wings->out();
    wait(1000);
    motion->trapezoidal(0.1, 0.3, -100);
    while(motion->inMotion()==1) pros::delay(10);
    wait(1000);
     motion->runTurnPID(180-40,2); 
    while(motion->inMotion()==1) pros::delay(10);
    motion->runTurnPID(100,2); //105
    while(motion->inMotion()==1) pros::delay(10);
    wings->in();
    cata->setStop(31500,36000);
    while(cata->isRunning()){
        cata->periodic();
        wait(10);
    }
    //might have to add delay & wait for cata to finish running
    intake->runOut();
    motion->trapezoidal(0.35,0.4,500);
    //blocker->out();
}