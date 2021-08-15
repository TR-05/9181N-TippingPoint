#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

//motors
motor fl = motor(PORT13, ratio18_1, true);
motor bl = motor(PORT15, ratio18_1, false);
motor fr = motor(PORT19, ratio18_1, false);
motor br = motor(PORT18, ratio18_1, true);

motor llift = motor(PORT2, ratio36_1, false);
motor rlift = motor(PORT1, ratio36_1, true);

//sensor setup
triport expander = triport(PORT9);

//IMU
inertial IMU1 = inertial(PORT5);
inertial IMU2 = inertial(PORT7);


//Encoders
encoder ltrack = encoder(Brain.ThreeWirePort.G);
encoder rtrack = encoder(Brain.ThreeWirePort.E);
encoder strack = encoder(Brain.ThreeWirePort.C);

//Limit Switches
limit liftLimit = limit(Brain.ThreeWirePort.A);

//ultrasonics
sonar bSonic = sonar(expander.G);
sonar bSonic2 = sonar(expander.A);

//controller 
controller Controller = (primary);

bool RemoteControlCodeEnabled = true;


void vexcodeInit(void) {
  // Nothing to initialize
}