#ifndef TELEOP_H
#define TELEOP_H

#include "main.h"
#include "api.h"
#include "utils.h"
#include <math.h>
#include <string>
#include <bits/stdc++.h>
#include "pros/misc.h"
#include "chassis.h"

using namespace okapi;

class Teleop{
    std::map<pros::controller_digital_e_t,bool> prev;
    std::vector<pros::controller_digital_e_t> buttons = {
        pros::E_CONTROLLER_DIGITAL_L1,
        pros::E_CONTROLLER_DIGITAL_L2,
        pros::E_CONTROLLER_DIGITAL_R1,
        pros::E_CONTROLLER_DIGITAL_R2,
        pros::E_CONTROLLER_DIGITAL_UP,
        pros::E_CONTROLLER_DIGITAL_DOWN,
        pros::E_CONTROLLER_DIGITAL_LEFT,
        pros::E_CONTROLLER_DIGITAL_RIGHT,
        pros::E_CONTROLLER_DIGITAL_X,
        pros::E_CONTROLLER_DIGITAL_B,
        pros::E_CONTROLLER_DIGITAL_Y,
        pros::E_CONTROLLER_DIGITAL_A
    }; 

    bool toggle(pros::controller_digital_e_t button);

    bool hold(pros::controller_digital_e_t button);

    /**
     * @brief runs every 20 ms
     * 
     */
    public: 
        void periodic();
        Teleop();
};
#endif