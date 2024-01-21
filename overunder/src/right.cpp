#include "right.h"

void Right::run(){
    Intake* intake = Intake::getInstance();
    Wing* wings = Wing::getInstance();
    Cata* cata = Cata::getInstance();
    MotionProfile* motion = MotionProfile::getInstance();

    intake->runOut();
    cata->setTime(0.17);
    while(cata->isRunning()){
        cata->periodic();
        wait(10);
    }
    intake->stop();
    cata->setStop(31500,36000);
    while(cata->isRunning()){
        cata->periodic();
        wait(10);
    }

    intake->runIn();
    motion->trapezoidal(0.28, 0.54, 600); //0.54
    while(motion->inMotion()==1) pros::delay(10);
    intake->stop();
    motion->runTurnPID(70,0.5);//90 87 85 75
    while(motion->inMotion()==1) pros::delay(10);

    intake->runOut();
    wait(700);
    motion->runTurnPID(-110,0.5); //-90
    while(motion->inMotion()==1) pros::delay(10);
    motion->trapezoidal(0.1, 0.2, -400);
    while(motion->inMotion()==1) pros::delay(10);

    //get 2nd tribal
    motion->trapezoidal(0.2, 0.2, 250); //0.1 0.2 250
    while(motion->inMotion()==1) pros::delay(10);
    intake->runIn();
    motion->runTurnPID(-25,0.8); //-40 -13 -20
    while(motion->inMotion()==1) pros::delay(10);
    motion->trapezoidal(0.2, 0.2, 200); //0.1, 0.2, 200
    while(motion->inMotion()==1) pros::delay(10);
    motion->runTurnPID(90,0.5); 
    while(motion->inMotion()==1) pros::delay(10);
    intake->runOut();
    wait(500);
    motion->trapezoidal(0.1, 0.1, -100); //new
     while(motion->inMotion()==1) pros::delay(10); //new
    motion->runTurnPID(-80,0.5); 
    while(motion->inMotion()==1) pros::delay(10);

    // motion->trapezoidal(0.1, 0.2, -200);
     //while(motion->inMotion()==1) pros::delay(10);
    // motion->trapezoidal(0.1, 0.2, 250);
    // while(motion->inMotion()==1) pros::delay(10);

    //get 3rd tribal
    motion->runTurnPID(-63,0.3); //-73s
    while(motion->inMotion()==1) pros::delay(10);
    intake->runIn();
    motion->trapezoidal(0.15, 0.2, 600); //0.18 0.2
    while(motion->inMotion()==1) pros::delay(10);
    motion->trapezoidal(0.2, 0.27, -600); // 0.2 0.3
    while(motion->inMotion()==1) pros::delay(10);
    motion->runTurnPID(100,0.9); //90
    while(motion->inMotion()==1) pros::delay(10);
    intake->runOut();
    wait(500);
    //motion->runTurnPID(-90,0.5); 
    //while(motion->inMotion()==1) pros::delay(10);
    //motion->trapezoidal(0.1, 0.1, -600); //-500
    //while(motion->inMotion()==1) pros::delay(10);
    //motion->trapezoidal(0.1, 0.2, 250);
    //while(motion->inMotion()==1) pros::delay(10);

    //motion->trapezoidal(0.1, 0.2, -250);
    //while(motion->inMotion()==1) pros::delay(10);

    //4th triball
    motion->runTurnPID(-120,0.7); //-118
    intake->runIn();
    while(motion->inMotion()==1) pros::delay(10);
    motion->trapezoidal(0.17, 0.3, 600); //0.15 0.3
    while(motion->inMotion()==1) pros::delay(10);
    motion->trapezoidal(0.1, 0.2, -600); //0.2 0.2
    while(motion->inMotion()==1) pros::delay(10);
    motion->runTurnPID(68,0.7); //87 0.7
    while(motion->inMotion()==1) pros::delay(10);
    intake->runOut();
        motion->trapezoidal(0.3, 0.5, 600); 
    // wait(300);
    // motion->runTurnPID(-100,1); //-110
    // while(motion->inMotion()==1) pros::delay(10);
    // Chassis::getInstance()->coast();
    // motion->trapezoidal(0, 1, -600); //0.2 0.2
    // while(motion->inMotion()==1) pros::delay(10);
}
