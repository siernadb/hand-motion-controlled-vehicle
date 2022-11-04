// ask_receiver.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to receive messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) receiver with an Rx-B1 module
// Tested on Arduino Mega, Duemilanova, Uno, Due, Teensy, ESP-12

#include <RH_ASK.h>

#include <SPI.h> // Not actually used but needed to compile


RH_ASK driver(500, 53, 46, 0); // ESP8266 or ESP32: do not use pin 11 or 2

uint8_t buf[4];
uint8_t buflen = sizeof(buf);

void setup()
{
    Serial.begin(9600);	  // Debugging only

    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
	    Serial.print("Got:");
      Serial.println((char*) buf);
    }
}
