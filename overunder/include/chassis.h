#ifndef CHASSIS_H
#define CHASSIS_H

#include "main.h"
#include "api.h"
#include "utils.h"
#include <math.h>
#include <bits/stdc++.h>
#include "pros/misc.h"
using namespace okapi;

class Chassis{

    static Chassis* instance;

    public:

        static Chassis* getInstance();

    /**
    * @brief Set the Left Voltage object
    * 
    * @param volt [-128,127]
    */
        void setLeftVoltage(int volt);
    
    /**
    * @brief Set the Right Voltage object
    * 
    * @param volt [-128,127]
    */
        void setRightVoltage(int volt);
        void setRightVelocity(int vel);
        void setLeftVelocity(int vel);
        void setDriveVelocity(int leftVel, int rightVel);
        static void initialize();
        void coast();
};

#endif