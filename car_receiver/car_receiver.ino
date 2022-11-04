#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <AFMotor.h>

#define MAX_SPEED 500

// Motor shield variables
int i=0;
bool is_forward, is_backward, is_left, is_right;

// RF variables
uint8_t buf[4];
uint8_t buflen = sizeof(buf);

// Motor shield functions 
AF_DCMotor leftBack(1);  // Back Left
AF_DCMotor rightBack(2);  // Back Right
AF_DCMotor rightFront(3);  // Front Right
AF_DCMotor leftFront(4);  // Front Left

// RF function
RH_ASK driver(500, 53, 46, 0); // ESP8266 or ESP32: do not use pin 11 or 2

void setup()
{
    Serial.begin(9600);    // Debugging only

    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    char command;
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      Serial.print("Got:");
      command = (char) buf[0];
      Serial.println(command);


//      speedSet(MAX_SPEED);
//      drive(command);
//      delay(2000);
    }

    
    
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
