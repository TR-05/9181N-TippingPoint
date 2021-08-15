#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

//motors
motor fl = motor(PORT13, ratio18_1, false);
motor bl = motor(PORT15, ratio18_1, false);
motor fr = motor(PORT19, ratio18_1, true);
motor br = motor(PORT18, ratio18_1, true);

motor llift = motor(PORT2, ratio36_1, true);
motor rlift = motor(PORT1, ratio36_1, false);

//sensor setup
triport expander = triport(PORT9);

//IMU
inertial IMU1 = inertial(PORT5);
inertial IMU2 = inertial(PORT6);


//Encoders
encoder leftTrack = encoder(Brain.ThreeWirePort.C);
encoder rightTrack = encoder(Brain.ThreeWirePort.E);
encoder backTrack = encoder(Brain.ThreeWirePort.G);

//Limit Switches
limit liftLimit = limit(Brain.ThreeWirePort.H);


//controller 
controller Controller = (primary);


void vexcodeInit(void) {
  // Nothing to initialize
}