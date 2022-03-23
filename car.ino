// CAR
//Connect the RF RX data pin to Arduino pin 2
#include <AFMotor.h> //including library
#define TPin 6
#define EPin 5
#include <VirtualWire.h>

byte message[VW_MAX_MESSAGE_LEN];
byte messageLength = VW_MAX_MESSAGE_LEN;

int lm=12;
int lmr=8;
int rm=10;
int rmr=7;
int ledPin=13;

void distance()
{
  long duration, distance;

  digitalWrite(TPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TPin, LOW);

  duration = pulseIn(EPin, HIGH);
  distance = (duration/2) / 29.1;

  if (distance < 20)/*if there's an obstacle 20 centimers, ahead, do the following: */ {
    Serial.println ("Close Obstacle detected!" );
    Serial.println ("Obstacle Details:");
    Serial.print ("Distance From Robot is " );
    Serial.print ( distance);
    Serial.print ( " CM!");

  if(Serial.available())
  {
    t = Serial.read();
    Serial.println(t);
  }
if(distance<25)
{
  void setup()
  {
    Serial.begin(9600);
    pinMode(ledPin,OUTPUT);
    pinMode(lm,OUTPUT);
    pinMode(lmr,OUTPUT);
    pinMode(rm,OUTPUT);
    pinMode(rmr,OUTPUT);
    vw_setup(2000);
    vw_rx_start();
  }

  void loop()
  {
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen))
    {
      int i;
      Serial.print("Got: ");//debugging

      for (i = 0; i < buflen; i++)
      {
        // Serial.print(buf[i],HEX);
        //Serial.print(' ');// debugging
        if (buf[i]==0x73)//Stationary
        {
          digitalWrite(lm,LOW);
          digitalWrite(lmr,LOW);
          digitalWrite(rm,LOW);
          digitalWrite(rmr,LOW);

          digitalWrite(ledPin,LOW);
        }
        else
        {
          if(buf[i]==0x66)//Forward
          {
            digitalWrite(lm,LOW);
            digitalWrite(lmr,HIGH);
            digitalWrite(rm,HIGH);
            digitalWrite(rmr,LOW);

            digitalWrite(ledPin,HIGH);
          }

          if (buf[i]==0x61)//Backward
          {
            digitalWrite(lm,HIGH);
            digitalWrite(lmr,LOW);
            digitalWrite(rm,LOW);
            digitalWrite(rmr,HIGH);

            digitalWrite(ledPin,HIGH);
          }

          if (buf[i]==0x6C)//Left
          {
            digitalWrite(lm,LOW);
            digitalWrite(lmr,LOW);
            digitalWrite(rm,HIGH);
            digitalWrite(rmr,LOW);
            digitalWrite(ledPin,HIGH);
          }

          if (buf[i]==0x72)//Right
          {
            digitalWrite(lm,LOW);
            digitalWrite(lmr,HIGH);
            digitalWrite(rm,LOW);
            digitalWrite(rmr,LOW);
            digitalWrite(ledPin,HIGH);

          }
        }
      }
    }
  //delay(1000)
  }
}
else
{
  digitalWrite(lm,LOW);
  digitalWrite(lmr,LOW);
  digitalWrite(rm,LOW);
  digitalWrite(rmr,LOW);
  digitalWrite(ledPin,LOW);
}
}
