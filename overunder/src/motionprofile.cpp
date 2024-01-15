#include "motionprofile.h"
MotionProfile* MotionProfile::instance = nullptr;

pros::Imu imu(8);

MotionProfile* MotionProfile::getInstance(){
  if(instance==nullptr) instance = new MotionProfile();
  return instance;
}

void MotionProfile::initialize(){
  imu.reset();
}

MotionProfile::MotionProfile(){
  isRunning = 0;
}

void MotionProfile::trapezoidal(double aT, double cT, double fV){
  startTime = std::chrono::steady_clock::now();
  type = trapezoid;
  accelerationTime = aT;
  constantTime = cT;
  flatVelocity = fV;
  isRunning = 1;
}

std::pair<double,bool> angleDifference(double target, double current){
  double leftDist, rightDist;
  if(target>current){
    leftDist = 360-target + current;
    rightDist = target-current;
  }
  else{

  }
  return std::make_pair(2.3,1);
}

void MotionProfile::update(){
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  double t = (std::chrono::duration_cast<std::chrono::microseconds>(end - startTime).count()) /1000000.0;
  if(isRunning&&type==trapezoid){
    double vel;
    if(t<=accelerationTime){
      vel = t/accelerationTime*flatVelocity;
    }
    else if(t>=accelerationTime&&t<=constantTime+accelerationTime){
      vel = flatVelocity;
    }
    else if(t<=constantTime+accelerationTime*2){
      vel = flatVelocity-(t-constantTime-accelerationTime)/accelerationTime*flatVelocity;
    }
    else if(t>constantTime+accelerationTime*2){
      vel = 0;
      isRunning = 0;
    }
    Chassis::getInstance()->setDriveVelocity(vel,vel);
  }
  if(isRunning&&type==turnPID){

  }
}

