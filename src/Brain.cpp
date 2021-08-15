#include "vex.h"


//Useful Functions
float IMU() {
  float imu = (IMU1.rotation() + IMU2.rotation()) / 2;
  return imu;
}


//Owens Present
void delay(float waitTime){
  wait(waitTime, msec);
}

//convert rotations to inches
float degToIn(float input, float diameter) {
float output = input * (diameter * M_PI / 360);
return output;
}
//thread for math
int calculations() {
  while(1) {
  odom();
  //get_intersection(float l1x, float l1y, float l2x, float l2y, float radius)
  delay(10);
  }
  return 0;
}

//Brain Screen
int Printing() {
  //Setup
Brain.Screen.setFillColor(yellow);
Brain.Screen.setFont(monoL);
Brain.Screen.setPenColor(black);

while(1){
//Print
Brain.Screen.setCursor(1, 1);
Brain.Screen.clearLine();
Brain.Screen.print("Arm Limit %d", liftLimit.pressing());

Brain.Screen.setCursor(2, 1);
Brain.Screen.clearLine();
Brain.Screen.print("LiftHeight %f", KinematicLift());

Brain.Screen.setCursor(3, 1);
Brain.Screen.clearLine();
Brain.Screen.print("liftAng %f", liftAng());

Brain.Screen.setCursor(4, 1);
Brain.Screen.clearLine();
Brain.Screen.print("liftPower %d", calcLiftPID());

Brain.Screen.setCursor(5, 1);
Brain.Screen.clearLine();
Brain.Screen.print("lt %4.2f rt %4.2f st %4.2f", degToIn(ltrack.position(deg), 2.75), degToIn(rtrack.position(deg), 2.75), degToIn(strack.position(deg), 2.75));

Brain.Screen.setCursor(6, 1);
Brain.Screen.clearLine();
Brain.Screen.print("Sonic %f Sonic2 %f", bSonic.distance(inches), bSonic2.distance(inches));

Brain.Screen.setCursor(7, 1);
Brain.Screen.clearLine();
Brain.Screen.print("IMU %f", IMU());

Brain.Screen.setCursor(8, 1);
Brain.Screen.clearLine();
Brain.Screen.print("X %3.3f Y %3.3f", X(), Y());

  delay(10);
}
return 0;
}
