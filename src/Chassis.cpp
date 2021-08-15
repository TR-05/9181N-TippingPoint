#include "vex.h"

//Common Functions
void Drive(int left, int right) {
  fl.spin(forward, left, pct);
  bl.spin(forward, left, pct);
  fr.spin(forward, right, pct);
  br.spin(forward, right, pct);
}


//Driver Control
void DriverControls() {
  int LY = Controller.Axis3.value();
  int RX = Controller.Axis1.value();

  int lSpeed = LY + RX;
  int rSpeed = LY - RX;

  Drive(lSpeed, rSpeed);
}


//ultrasonic filter
int targRead = 10;
int maxRead = 40;
int readTime = 20;
float maxError = 0.1;
float filteredNum = 0;


float filter() {

  float baseDist[maxRead];
  float filNums[targRead];

  float sonicSum = 0;
  float filSum = 0;
    for (int x = 0; x < maxRead; x++) {
   //executed until x >= 100
   baseDist[x] = bSonic.distance(inches);
  sonicSum += baseDist[x];
  delay(readTime / maxRead);
}

float maxedAv = sonicSum / maxRead;
    for (int x = 0; x < targRead; x++) {
      if ((bSonic.distance(inches) < (maxedAv + maxError)) && ((bSonic.distance(inches) > (maxedAv - maxError)))) {
    filNums[x] = bSonic.distance(inches);
    filSum += filNums[x];
      }  else {
      x = x -1;
    }
  }
  filteredNum = filSum / targRead;
return filteredNum;
}


//Tracker
float xGoal = 0;
float yGoal = 0;
float hGoal = 0;

int prevLtrack = 0;
int prevRtrack = 0;
int prevStrack = 0;
float prevIMU = 0;

float SL = 5.25;
float SR = 5.25;
float SS = 2.23;

float LX = 0;
float LY = 0;
float RY = 0;
float RX = 0;

void odom() {

  float IMURAD = TO_RAD(IMU());
  float A = IMURAD - prevIMU;
  prevIMU = TO_RAD(IMU());

  int ltrackIn = ltrack.position(deg);
  int rtrackIn = rtrack.position(deg);
  int strackIn = strack.position(deg);

  float L = (ltrackIn - prevLtrack) * (2.75 * M_PI / 360);
  float R = (rtrackIn - prevRtrack) * (2.75 * M_PI / 360);
  float S = (strackIn - prevStrack) * (2.75 * M_PI / 360);

  prevLtrack = ltrack.position(deg);
  prevRtrack = rtrack.position(deg);
  prevStrack = strack.position(deg);

  	float h; // The hypotenuse of the triangle formed by the middle of the robot on the starting position and ending position and the middle of the circle it travels around
  	float i; // Half on the angle that I've traveled
  	float h2; // The same as h but using the back instead of the side wheels
  	float h3; // The hypotenuse of the triangle formed by the middle of the robot on the starting position and ending position and the middle of the circle it travels around

			if (A)
	  	{
	  		float r = R / A; // The radius of the circle the robot travel's around with the right side of the robot
	  		i = A / 2.0;
	  		float sinI = sin(i);
	  		h = ((r + SR) * sinI) * 2.0;

	  		float r2 = S / A; // The radius of the circle the robot travel's around with the back of the robot
	  		h2 = ((r2 + SS) * sinI) * 2.0;

        float r3 = L / A; // The radius of the circle the robot travel's around with the right side of the robot
	  		h3 = ((r3 + SL) * sinI) * 2.0;

	  	}
	  	else
	  	{
	  		h = R;
	  		i = 0;

	  		h2 = S;

        h3 = L;

	  	}


  	float p = i + IMURAD; // The global ending angle of the robot
  	float cosP = cos(p);
  	float sinP = sin(p);

  	// Update the global position
  	RY += h * cosP;
  	RX += h * sinP;

  	RY += h2 * -sinP; // -sin(x) = sin(-x)
  	RX += h2 * cosP; // cos(x) = cos(-x)

  	LY += h3 * cosP;
  	LX += h3 * sinP;

  	LY += h2 * -sinP; // -sin(x) = sin(-x)
  	LX += h2 * cosP; // cos(x) = cos(-x)

}

float X() {
float x = (LX + RX) / 2;
  return x;
}

float Y() {
float y = (LY + RY) / 2;
  return y;
}

//setPos
void setPos(float x, float y, float h) {
LX = x;
RX = x;
LY = y;
RY = y;

ltrack.resetRotation();
rtrack.resetRotation();
strack.resetRotation();

prevLtrack = 0;
prevRtrack = 0;
prevStrack = 0;

IMU1.setRotation(h, deg);
IMU2.setRotation(h, deg);
prevIMU = 0;

}


//Chassis PD
float YKP = 15;
float YKD = 1;
float prevYP = 0;

float getY(float yTarg, float xTarg) {
  float IMURAD = TO_RAD(IMU()); // heading of the robot in RAD
  float Yerror = yTarg - Y(); // error on Y axis
  float Xerror = xTarg - X(); // error on X axis

  float YP = Yerror * cos(IMURAD) + Xerror * sin(IMURAD);  //KP base
  float YD = YP - prevYP;  //KD base
  prevYP = YP; //previous error

  float speed = (YP * YKP) + (YD * YKD);
  return speed;
}

float HKP = 6;
float HKD = 1;
float prevHP = 0;

float getH(float hTarg) {
  float HP = hTarg - IMU();
  float HD = HP - prevHP;
  prevHP = HP;

  float speed = (HP * HKD) + (HD * HKD);
  return speed;
}


//Useful odom funcs
float angleToTarg() {
float ang = atan2(xGoal - X(), yGoal - Y());
  return TO_DEG(ang);
}

//makes sure that the angle is less than 180
float wrapAng(float ang) {
while(ang < -180) {
  ang += 360;
}
while(ang > 180) {
  ang -= 360;
}
  return ang;
}

//calculates the distance from the robots position to the target
float pointDistance() {
float dist = sqrt( pow(xGoal - X(), 2) + pow(yGoal - Y(), 2) );

return dist;
}

//calculates the angle the robot needs to turn to face the target
float relativeAngle() {
  float ang = angleToTarg() - IMU();
  return wrapAng(ang);
}

float xRelative() {
  float dist = cos(relativeAngle() * pointDistance());
  return dist;
}

float yRelative() {
  float dist = sin(relativeAngle() * pointDistance());
  return dist;
}

float length(float x, float y, float x2, float y2) {
	float X = x - x2;
	float Y = y - y2;
	float dist = sqrt(X * X + Y * Y);

	return dist;
}
int sign(float x) {
  if (x > 0.0) return 1;
  if (x < 0.0) return -1;
  return 0;
}

float xOutput = 0;
float yOutput = 0;


//pure pursuit function





void toPoint(float x, float y, float speed, float prefAng) {
  xGoal = x;
  yGoal = y;
  hGoal = prefAng;

  float relativeTurnAngle = relativeAngle() + prefAng;
  float turnPower = 0;
  if (pointDistance() < 4) {
  turnPower = 0;
  } else {
  turnPower = getH(relativeTurnAngle);
  }


}