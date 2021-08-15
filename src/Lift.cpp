#include "vex.h"

//Small useful functions
void Lift(int speed) {
  llift.spin(forward, speed, pct);
  rlift.spin(forward, speed, pct);
}

void checkLimit() {
  if (liftLimit.pressing()) {
    rlift.resetPosition();
  }
}

float liftAng() {
  float ang = (rlift.position(deg) / 5) - 51 ;
  return ang;
}

//Driver Control Code
void LiftControls() {
  bool r1 = Controller.ButtonR1.pressing();
  bool r2 = Controller.ButtonR2.pressing();

  if ((r1)){
  Lift(100);
  } else if ( (r2) && (liftLimit.pressing() == 0) ) {
    Lift(-100);
  }
  else {
    Lift(0);
  }
  checkLimit();

}


//Autonomous stuff
float KinematicLift() {
  float liftMountHeight = 15;
  float barLength = 14.5;
float liftAngRad = TO_RAD(liftAng());
  float liftHeight = (barLength * sin(liftAngRad)) + liftMountHeight;


  return liftHeight;
}


//PID
float liftTarg = 25;
float LKP = 20;
float LKD = 50;

float preverror = 0;

int calcLiftPID() {
  //KP
  float error = liftTarg - KinematicLift();
  float LP = error * LKP;
  //KD
  float LD = (error - preverror) * LKD;
  preverror = error;

  int power = LP + LD;
  return power;
}