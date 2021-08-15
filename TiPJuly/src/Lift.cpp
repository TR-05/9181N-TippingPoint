#include "vex.h"


//Driver Control
void Lift(int speed) {
  llift.spin(forward, speed, pct);
  rlift.spin(forward, speed, pct);
}


void LiftControls() {
  int RY = Controller.Axis2.value();
  bool shiftKey = Controller.ButtonR1.pressing();
  Lift(RY);


  if (shiftKey) {
    if (liftLimit.pressing()) {
      Lift(0);
      llift.resetPosition();
      rlift.resetPosition();
    } else {
      Lift(RY);
    }
  } 
  else if ( (abs(RY) > 10) && (rlift.position(deg) > 0) ){
  Lift(RY);
  }

}
//Autonomous