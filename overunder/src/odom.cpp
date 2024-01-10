#include "odom.h"
Odom* Odom::instance = nullptr;

Odom* Odom::getInstance(){
    if(instance==nullptr) instance = new Odom();
    return instance;
}

void Odom::update(double left, double right, double back){
    float L = (left - lstLeft) * SPIN_TO_IN_LR; // The amount the left side of the robot moved
    float R = (right - lstRight) * SPIN_TO_IN_LR; // The amount the right side of the robot moved
    float S = (back - lstBack) * SPIN_TO_IN_S; // The amount the back side of the robot moved

    // Update the last values
    lstLeft = left;
    lstRight = right;
    lstBack = back;

    float h; // The hypotenuse of the triangle formed by the middle of the robot on the starting position and ending position and the middle of the circle it travels around
    float i; // Half on the angle that I've traveled
    float h2; // The same as h but using the back instead of the side wheels
    float a = (L - R) / (L_DISTANCE_IN + R_DISTANCE_IN); // The angle that I've traveled
    if (a)
    {
        float r = R / a; // The radius of the circle the robot travel's around with the right side of the robot
        i = a / 2.0;
        float sinI = sin(i);
        h = ((r + R_DISTANCE_IN) * sinI) * 2.0;

        float r2 = S / a; // The radius of the circle the robot travel's around with the back of the robot
        h2 = ((r2 + S_DISTANCE_IN) * sinI) * 2.0;
    }
    else
    {
        h = R;
        i = 0;

        h2 = S;
    }
    float p = i + theta; // The global ending angle of the robot
    float cosP = cos(p);
    float sinP = sin(p);

    // Update the global position
    y += h * cosP;
    x += h * sinP;

    y += h2 * -sinP; // -sin(x) = sin(-x)
    x += h2 * cosP; // cos(x) = cos(-x)

    theta += a;
}

