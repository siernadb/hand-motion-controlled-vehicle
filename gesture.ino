//Connect the RF TX data pin to Arduino pin 8
int xPin=4;//Connect x pin of MPU 6050 to pin A4
int yPin=5;//Connect y pin of MPU 6050 to pin A5
#include <VirtualWire.h>
void setup()
{
  vw_setup(2000);
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}


void loop()
{
  int xval=analogRead(xPin);
  int yval=analogRead(yPin);

  Serial.print("xval=");
  Serial.println(xval);
  Serial.print("yval=");
  Serial.println(yval);
  delay(1000);
  Serial.print("\n");

  if ((xval>330 && xval<340) && (yval>340 && yval<350)) // Brake
  {
  digitalWrite(ledPin,LOW);
  send("s");
  }

  else
  {
    if ((xval>325 && xval<345) && (yval>380 && yval<410)) //forward movement
    {
      digitalWrite(ledPin,HIGH);
      send("f");
    }

    if ((xval>315 && xval<345) && (yval>250 && yval<275)) //backward movement
    {
      digitalWrite(ledPin,HIGH);
      send("a");
    }

    if ((xval>385 && xval<415) && (yval>315 && yval<350)) //left movement
    {
      digitalWrite(ledPin,HIGH);
      send("l");
    }

    if ((xval>255 && xval<275) && (yval>320 && yval<345))//right movement
    {
      digitalWrite(ledPin,HIGH);
      send("r");
    }
  }

  delay(1000);
}


void send(char *message)
{
 vw_send((uint8_t *)message, strlen(message));
 vw_wait_tx();
}
