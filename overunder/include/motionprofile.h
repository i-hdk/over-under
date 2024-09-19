#ifndef MOTIONPROFILE_H
#define MOTIONPROFILE_H

#include "main.h"
#include "api.h"
#include "utils.h"
#include <math.h>
#include <bits/stdc++.h>
#include "pros/misc.h"
#include "chassis.h"
#include <fstream>
using namespace okapi;

class MotionProfile{
    public:
    static MotionProfile* instance;
    bool isRunning;
    std::chrono::steady_clock::time_point startTime;
    double accelerationTime, constantTime, flatVelocity, turnTarget, turnPrevError, turnTotalError, timeOut;
    double turnP,turnI,turnD;
    bool overTurn, overTurnRight, overTurnFirst, overTurnLeft;
    std::vector<double> time;
    std::vector<double> length;
    std::vector<double> radius;
    std::vector<double> linVel;
    std::vector<double> angVel;
    enum profile{
    trapezoid,
    turnPID,
    path
    };
    profile type;

    static MotionProfile* getInstance();

    MotionProfile();

    void trapezoidal(double aT, double cT, double fV);
    void runPath();
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