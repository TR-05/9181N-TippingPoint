#include "vex.h"

using namespace vex;

competition Competition;



void pre_auton() {
  IMU1.calibrate();
  IMU2.calibrate();
  vexcodeInit();
rlift.setBrake(hold);
llift.setBrake(hold);
  task screen(Printing);
  task calcs(calculations);
}



void autonomous() {



}



void usercontrol() {
  while (1) {

    // Chassis Control
    DriverControls();
if (Controller.ButtonR1.pressing() == false) {
  LiftControls();
} else {
  Lift(calcLiftPID());
}
  
    delay(10);
  }
}



int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
