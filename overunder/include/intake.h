#ifndef INTAKE_H
#define INTAKE_H
#include "main.h"
#include "api.h"
#include "utils.h"
#include <math.h>
#include <bits/stdc++.h>
#include "pros/misc.h"
using namespace okapi;

class Intake{
    static Intake* instance;
    public:
    static Intake* getInstance();
    void runIn();
    void runOut();
    void stop();
    void run(int vel);
    static void initialize();
};

#endif