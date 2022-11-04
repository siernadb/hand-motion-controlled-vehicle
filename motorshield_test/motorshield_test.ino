#include <AFMotor.h>

#define MAX_SPEED 500

AF_DCMotor leftBack(1);  // Back Left
AF_DCMotor rightBack(2);  // Back Right
AF_DCMotor rightFront(3);  // Front Right
AF_DCMotor leftFront(4);  // Front Left

int i=0;

bool is_forward, is_backward, is_left, is_right;


void setup() {
  // slowly bring the speed up to 
  // avoid loading down the batteries too quickly
  for (i = 0; i < MAX_SPEED; i += 2)
    speedSet(i); 

  is_forward  = false; 
  is_backward = false;
  is_left     = false; 
  is_right    = false;
  
}

void loop() {

  drive('f');
  delay(2000);
  drive('r');
  delay(5000);
 
}

void drive(char dir)
{
  if (dir == 'f')
    drive_forward();

  else if (dir == 'b')
    drive_backward();

  else if (dir == 'l')
    drive_left_forward();

  else if (dir == 'r')
    drive_right_forward();

  else
    brake();
}

void drive_forward()
{
//  if (!is_forward)
  is_forward = true;
  
  leftBack.run(FORWARD);
  rightBack.run(FORWARD);
  rightFront.run(FORWARD);
  leftFront.run(FORWARD);
}

void drive_left_forward()
{
  is_backward = true;
  leftBack.run(RELEASE);
  leftFront.run(RELEASE);
  rightBack.run(FORWARD);
  rightFront.run(FORWARD);
  
}

void drive_right_forward()
{
  is_right = true;
  leftBack.run(FORWARD);
  leftFront.run(FORWARD);
  rightBack.run(RELEASE);
  rightFront.run(RELEASE);
  
}

void drive_backward()
{
  is_left = true;
  leftBack.run(BACKWARD);
  rightBack.run(BACKWARD);
  rightFront.run(BACKWARD);
  leftFront.run(BACKWARD);
}

void brake()
{
  leftBack.run(RELEASE);
  rightBack.run(RELEASE);
  rightFront.run(RELEASE);
  leftFront.run(RELEASE);
}

void speedSet(int sp)
{
  leftBack.setSpeed(sp);
  rightBack.setSpeed(sp);
  rightFront.setSpeed(sp);
  leftFront.setSpeed(sp);
  delay(5);
}
