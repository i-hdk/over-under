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

//
 wings->in();
    motion->runTurnPID(105,2); //100
    while(motion->inMotion()==1) pros::delay(10);
   //blocker->out();
    //cata->setStop(31500,36000);
    while(cata->isRunning()){
        cata->periodic();
        wait(10);
    }
    intake->runOut();



    motion->trapezoidal(0.35,0.4,500); //+ trust the opponents to touch the bar???

}