#ifndef CATA_H
#define CATA_H

#include "main.h"
#include "api.h"
#include "utils.h"
#include <math.h>
#include <bits/stdc++.h>
#include "pros/misc.h"
using namespace okapi;

class Cata{
    static Cata* instance; 

    bool running,waitStop,waitTime;
    double stopL,stopR,toggleTime;
    double t;
    std::chrono::steady_clock::time_point begin;

    public:

        static Cata* getInstance();

        static void intialize();
        Cata();

        /**
        * @brief set cata target [0,72000]
        * 
        * @param stop1 lower bound
        * @param stop2 upper bound
        */
        void setStop(double stop1, double stop2);

        void setTime(double sec);

        int position();

        void run();

        void run(int speed);

        bool isRunning();

        void interrupt();

        void periodic();

};

#endif