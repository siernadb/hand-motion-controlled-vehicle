#include<Wire.h>
//#include<VirtualWire.h> //for transmission testing
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <string.h>


RH_ASK driver(500, 2, 12, 0); // ESP8266 or ESP32: do not use pin 11 or 2



const int MPU_addr=0x68; //MPU6050 I2C address
const int transmit_pin = 12;
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
//  vw_set_tx_pin(transmit_pin);
//  vw_set_rx_pin(receive_pin);
//  vw_set_ptt_pin(transmit_en_pin);
//  vw_set_ptt_inverted(true); // Required for DR3100
//  vw_setup(2000);   // Bits per sec
  Serial.begin(9600);
  if (!driver.init())
         Serial.println("init failed");
}
void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);
   
  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  
   
  Serial.print("AngleX= ");
  Serial.println(x);
   
  Serial.print("AngleY= ");
  Serial.println(y);

//  Serial.print("AngleZ= ");
//  Serial.println(zAng);
  
  Serial.println("-----------------------------------------");
//  const char *msg = " ";

  if ((x<5 || x>340) && (y>350 || y<15)) // Brake
    {
      Serial.println("----Flat, brake----\n");
      send("s");
    }
  
    else
    {
      if ((x>10 && x<40) && (y>350 || y<15)) //forward movement
      {
        Serial.println("----Down, forward----\n");
        send("f");
      }
  
      else if ((x>300 && x<340) && (y>350 || y<15)) //backward movement
      {
        Serial.println("----Up, backward----\n");
        send("b");
      }
  
      else if ((x>340 || x<20) && (y>280 && y<345)) //left movement
      {
        Serial.println("----Left----\n");
        send("l");
      }
  
      else if ((x>320 || x<20) && (y>15 && y<70))//right movement
      {
        Serial.println("----Right----\n");
        send("r");
      }
    }

    
    
}

void send(char *msg)
{
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  Serial.println(msg);
  delay(100);
}
