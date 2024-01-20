#ifndef BLOCKER_H
#define BLOCKER_H
#include "main.h"
#include "api.h"
#include "utils.h"
#include <math.h>
#include <bits/stdc++.h>
#include "pros/misc.h"
using namespace okapi;

class Blocker{
    static Blocker* instance;
    public:
    bool blockerOut;
    static Blocker* getInstance();
    static void initialize();
    Blocker();
    void out();

    void in();

    void change();
};

#endif