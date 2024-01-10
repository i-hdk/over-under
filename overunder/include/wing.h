#ifndef WING_H
#define WING_H
#include "main.h"
#include "api.h"
#include "utils.h"
#include <math.h>
#include <bits/stdc++.h>
#include "pros/misc.h"
using namespace okapi;

class Wing{
    static Wing* instance;
    public:
    bool wingOut;
    static Wing* getInstance();
    static void initialize();
    Wing();
    void out();

    void in();

    void change();
};

#endif