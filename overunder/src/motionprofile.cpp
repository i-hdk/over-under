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
  turnP = 4;
  turnI = 0;//0.01;
  turnD = 0;//1;
  overTurn = 0;
}

void MotionProfile::trapezoidal(double aT, double cT, double fV){
  startTime = std::chrono::steady_clock::now();
  type = trapezoid;
  accelerationTime = aT;
  constantTime = cT;
  flatVelocity = fV;
  isRunning = 1;
}

void MotionProfile::runTurnPID(double angle, double timelimit){
  overTurn = 0;
  turnTarget = angle;
  timeOut = timelimit;
  turnTotalError = 0;
  turnPrevError = angleDifference(angle, imu.get_heading()).first;
  startTime = std::chrono::steady_clock::now();
  type = turnPID;
  isRunning = 1;
}

//not rly functional
void MotionProfile::runTurnPID(double angle, double timelimit, bool longturn){
  overTurn = longturn;
  overTurnRight = 0;
  overTurnFirst = 0;
  overTurnLeft = 0;
  turnTarget = angle;
  timeOut = timelimit;
  turnTotalError = 0;
  turnPrevError = angleDifference(angle, imu.get_heading()).first;
  startTime = std::chrono::steady_clock::now();
  type = turnPID;
  isRunning = 1;
}

void MotionProfile::disableAuto(){
  isRunning = 0;
}

/**
 * @brief returns closest angle + turnRight or not
 * 
 * @param target 
 * @param current 
 * @return std::pair<double,bool> 
 */
std::pair<double,bool> MotionProfile::angleDifference(double target, double current){
  double leftDist, rightDist;
  while(target<0) target+=360;
  while(target>360) target-=360;
  if(target>current){
    leftDist = 360-target + current;
    rightDist = target-current;
  }
  else{
    leftDist = current-target;
    rightDist = 360-current + target;
  }
  int xxx = 1;
  while(xxx--){
    if(overTurn){
      if(overTurnFirst==0) overTurnFirst = 1;
      if(leftDist < rightDist){
        if(overTurnLeft){
          overTurn = 0;
          break;
        }
        overTurnRight = 1;
        return std::make_pair(rightDist,1);
      }
      else{
        overTurnLeft = 1;
        if(overTurnRight){
          overTurn = 0;
          break;
        }
        return std::make_pair(leftDist,0);
      }
    }
  }
  if(leftDist < rightDist){
    return std::make_pair(leftDist,0);
  }
  else{
    return std::make_pair(rightDist,1);
  }
}

bool MotionProfile::inMotion(){
  return isRunning;
}

void MotionProfile::update(){
  //debug:
  print("angle diff func",angleDifference(90,imu.get_heading()).first,0);
  print("right to 90",angleDifference(90, imu.get_heading()).second,1);
  print("imu", imu.get_heading(),2);

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
    double error = angleDifference(turnTarget, imu.get_heading()).first;
    bool right = angleDifference(turnTarget, imu.get_heading()).second;
    if(abs(error)>2){ //1
      double vel = turnP*error+turnI*turnTotalError+turnD*(error-turnPrevError);
      if(!right){
        Chassis::getInstance()->setDriveVelocity(-vel,vel);
      }
      else{
      Chassis::getInstance()->setDriveVelocity(vel,-vel);
      }
    }
    else{
      Chassis::getInstance()->setDriveVelocity(0,0);
      //isRunning = 0;
    }
    turnPrevError = error;
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    double t = (std::chrono::duration_cast<std::chrono::microseconds>(end - startTime).count()) /1000000.0;
    if(t>=timeOut){
      Chassis::getInstance()->setDriveVelocity(0,0);
      isRunning = 0;
    }
  }
}

void MotionProfile::setHeading(double h){
  imu.set_heading(h);
}

