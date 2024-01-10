#ifndef ODOM_H
#define ODOM_H

#include "main.h"
#include "api.h"
#include "utils.h"
#include <math.h>
#include <bits/stdc++.h>
#include "pros/misc.h"
using namespace okapi;

class Odom{
    static Odom* instance;
    double x,y,theta;
    double lstLeft,lstRight,lstBack;

    //fill out these constants
    double SPIN_TO_IN_LR;
    double SPIN_TO_IN_S;
    double L_DISTANCE_IN;
    double R_DISTANCE_IN;
    double S_DISTANCE_IN;

    static Odom* getInstance();

    void update(double left, double right, double back);

};

#endif