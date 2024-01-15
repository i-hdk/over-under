#ifndef MOTIONPROFILE_H
#define MOTIONPROFILE_H

#include "main.h"
#include "api.h"
#include "utils.h"
#include <math.h>
#include <bits/stdc++.h>
#include "pros/misc.h"
#include "chassis.h"
using namespace okapi;

class MotionProfile{
    public:
    static MotionProfile* instance;
    bool isRunning;
    std::chrono::steady_clock::time_point startTime;
    double accelerationTime, constantTime, flatVelocity;
    enum profile{
    trapezoid,
    turnPID
    };
    profile type;

    static MotionProfile* getInstance();

    MotionProfile();

    void trapezoidal(double aT, double cT, double fV);

    void update();

    static void initialize();
};

#endif