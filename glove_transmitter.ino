#include<Wire.h>
#include <RH_ASK.h>   // RadioHead library
#include <SPI.h> 
#include <string.h>


RH_ASK driver(500, 2, 12, 0);   //transmitter and data pins for RX transmission



const int MPU_addr=0x68;    //MPU6050 I2C address
const int transmit_pin = 12;   // I2C communication between MPU 6050 and Arduino Nano
const int receive_pin = 11;
const int transmit_en_pin = 3;
int16_t AcX,AcY,AcZ;
 
int minVal=265;
int maxVal=402;
 
double x;
double y;
double z;
 
void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);   // Talk to register 6B
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  if (!driver.init())
         Serial.println("init failed");
}

void loop(){

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  // reading gravitational accelerometer along 3-axis
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();

  
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);

  //calculate tilt angle 
  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  
   
  Serial.print("AngleX= ");
  Serial.println(x);
   
  Serial.print("AngleY= ");
  Serial.println(y);

  Serial.println("-----------------------------------------");

  angleToCommand(x,y);
}

// send function: transmit the command to receiver
void send(char *msg)
{
  driver.send((uint8_t *)msg, strlen(msg));
 
  driver.waitPacketSent();
  Serial.println(msg);
  delay(10);
}


// covert the calculated angle to correspoding command
// call the send function to transmit the command to the vehicle
void angleToCommand(double x, double y) 
{
  if ((x<20 || x>330) && (y>330 || y<20)) // Stop
    {
      Serial.println("----Flat, brake----\n");
      send("s");
    }
  
    else
    {
      if ((x>50 && x<80) && (y>340 || y<25)) //forward movement
      {
        Serial.println("----Down, forward----\n");
        send("f");
      }
  
      else if ((x>280 && x<320) && (y>340 || y<25)) //backward movement
      {
        Serial.println("----Up, backward----\n");
        send("b");
      }
  
      else if ((x>340 || x<20) && (y>280 && y<320)) //left movement
      {
        Serial.println("----Left----\n");
        send("l");
      }
  
      else if ((x>320 || x<20) && (y>40 && y<90))//right movement
      {
        Serial.println("----Right----\n");
        send("r");
      }
    }
}
