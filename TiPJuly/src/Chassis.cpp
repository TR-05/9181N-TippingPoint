#include "vex.h"


//Common Functions
void Drive(int left, int right) {
  fl.spin(forward, left, pct);
  bl.spin(forward, left, pct);
  fr.spin(forward, right, pct);
  br.spin(forward, right, pct);
}


//Driver Control
void DriveControls() {
  int LY = Controller.Axis3.value();
  int RX = Controller.Axis1.value();

  int lSpeed = LY + RX;
  int rSpeed = LY - RX;

  Drive(lSpeed, rSpeed);
}






//Autonomous




//Tracker
