using namespace vex;

extern brain Brain;

//Motors
extern motor fl;
extern motor bl;
extern motor fr;
extern motor br;

extern motor llift;
extern motor rlift;

//sensor setup
extern triport expander;

extern inertial IMU1;
extern inertial IMU2;

extern encoder ltrack;
extern encoder rtrack;
extern encoder btrack;

extern limit liftLimit;


//Controller
extern controller Controller;


void vexcodeInit(void);
