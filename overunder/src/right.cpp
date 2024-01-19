#include "right.h"

void Right::run(){
    Intake* intake = Intake::getInstance();
    Wing* wings = Wing::getInstance();
    Cata* cata = Cata::getInstance();
    MotionProfile* motion = MotionProfile::getInstance();
    intake->runIn();
    motion->trapezoidal(0.28, 0.54, 600); //0.53
    while(motion->inMotion()==1) pros::delay(10);
    intake->stop();
    motion->runTurnPID(90,0.5);//90 87
    while(motion->inMotion()==1) pros::delay(10);

    intake->runOut();
    wait(700);
    motion->runTurnPID(-110,0.5); //-90
    while(motion->inMotion()==1) pros::delay(10);
    motion->trapezoidal(0.1, 0.2, -400);
    while(motion->inMotion()==1) pros::delay(10);

    //get 2nd tribal
    motion->trapezoidal(0.1, 0.2, 200);
    while(motion->inMotion()==1) pros::delay(10);
    intake->runIn();
    motion->runTurnPID(-40,0.3);
    while(motion->inMotion()==1) pros::delay(10);
    motion->trapezoidal(0.1, 0.2, 200);
    while(motion->inMotion()==1) pros::delay(10);
    motion->runTurnPID(90,0.5); 
    while(motion->inMotion()==1) pros::delay(10);
    intake->runOut();
    wait(500);
    motion->runTurnPID(-80,0.5); 
    while(motion->inMotion()==1) pros::delay(10);
    // motion->trapezoidal(0.1, 0.2, -400);
    // while(motion->inMotion()==1) pros::delay(10);
    // motion->trapezoidal(0.1, 0.2, 250);
    // while(motion->inMotion()==1) pros::delay(10);

    //get 3rd tribal
    motion->runTurnPID(-73,0.3); 
    while(motion->inMotion()==1) pros::delay(10);
    intake->runIn();
    motion->trapezoidal(0.2, 0.2, 600); //0.2 0.2
    while(motion->inMotion()==1) pros::delay(10);
    motion->trapezoidal(0.2, 0.2, -600); // 0.2 0.15
    while(motion->inMotion()==1) pros::delay(10);
    motion->runTurnPID(90,0.5); 
    while(motion->inMotion()==1) pros::delay(10);
    intake->runOut();
    wait(500);
    motion->runTurnPID(-90,0.5); 
    while(motion->inMotion()==1) pros::delay(10);
    motion->trapezoidal(0.1, 0.1, -600); //-500
    while(motion->inMotion()==1) pros::delay(10);
    motion->trapezoidal(0.1, 0.2, 250);
    while(motion->inMotion()==1) pros::delay(10);

    //4th triball
    motion->runTurnPID(-120,0.25); //-118
    intake->runIn();
    while(motion->inMotion()==1) pros::delay(10);
    motion->trapezoidal(0.15, 0.3, 600); 
    while(motion->inMotion()==1) pros::delay(10);
    motion->trapezoidal(0.1, 0.2, -600); //0.2 0.2
    while(motion->inMotion()==1) pros::delay(10);
    motion->runTurnPID(90,0.5); 
    while(motion->inMotion()==1) pros::delay(10);
    intake->runOut();
    wait(500);
    motion->runTurnPID(-100,1); 
    while(motion->inMotion()==1) pros::delay(10);
    motion->trapezoidal(0, 1, -600); //0.2 0.2
    while(motion->inMotion()==1) pros::delay(10);
}
