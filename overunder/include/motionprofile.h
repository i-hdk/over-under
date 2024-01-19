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
    double accelerationTime, constantTime, flatVelocity, turnTarget, turnPrevError, turnTotalError, timeOut;
    double turnP,turnI,turnD;
    bool overTurn, overTurnRight, overTurnFirst, overTurnLeft;
    enum profile{
    trapezoid,
    turnPID
    };
    profile type;

    static MotionProfile* getInstance();

    MotionProfile();

    void trapezoidal(double aT, double cT, double fV);
    void runTurnPID(double angle, double timelimit);
    void runTurnPID(double angle, double timelimit, bool longturn);
    std::pair<double,bool> angleDifference(double target, double current);
    void update();
    void disableAuto();
    void setHeading(double h);

    bool inMotion();

    static void initialize();
};

#endif