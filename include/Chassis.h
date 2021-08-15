
//Common Functions
void Drive(int left, int right);



//Driver
void DriverControls();



//Autonomous
void odom();

float X();
float Y();

void setPos();

float getY();
float getH();

//pure pursuit
void get_intersection(float l1x, float l1y, float l2x, float l2y, float radius);