# hand-motion-controlled-vehicle

In today’s world, we are all used to utilizing tactile buttons such as the ones found on a TV remote controllers and joysticks. However, some people might find it challenging to perform particular actions; i.e., people with disabilities, missing limbs, and motor control deprivation might have problems using a joystick. 
Our objective is to make the interaction with these particular devices a little easier. We came up with an easy solution to interact by modeling a car that receives hand gesture commands from a glove. The position of how the glove is held determines the movement of the car, making this a hassle-free solution for people/patients in need.

At the end of this project, we see a user-friendly hand gesture-enabled glove which is capable of moving a small car. We will be using a transmitter and a receiver to make the experience wireless and free from cable management.

Here is the design overview of the system:
https://docs.google.com/presentation/d/1nHLvyyE1lTEq3-VNv1RfH6rzfLTk452c/edit?usp=sharing&ouid=103051844508699374789&rtpof=true&sd=true
_____________________________________________________________________________________________________________________________________________________________________

################ KNOW ME ################

Follow the gesture instruction in the table from the design overview above to operate the car.

The car and glove module design and architecture can be seen in the design folder of main branch in this repo.
The list of the components can be seen in the architecture diagram in design folder

_____________________________________________________________________________________________________________________________________________________________________

 ################ SETUP ################

Dependencies for Arduino NANO (Glove microcontroller)
1. Install RH_ASK library for RF modules using official installation guide  at http://www.airspayce.com/mikem/arduino/RadioHead/
2. Install MPU6050 library for accelerometer and gyroscope from wire  at https://rheingoldheavy.com/arduino-wire-library/

Dependencies for Arduino NANO (Glove microcontroller)
1. Install RH_ASK library for RF modules using official installation guide  at http://www.airspayce.com/mikem/arduino/RadioHead/
2. Install motorshield driver library "AFMotor.h" using the official installation guide at https://learn.adafruit.com/adafruit-motor-shield/library-install


_____________________________________________________________________________________________________________________________________________________________________

 ################ Connecting to ARDUINO microcontroller ################
 
 Things to keep in mind before flashing the code onto the Arduino boards:
 1. Make sure the transmitter code goes to Arduino NANO and the Arduino IDE compiles the code for NANO by selecting TOOLS>BOARDS>Arduino NANO
 2. Similarly for Receiver and the motor Sheild code make sure the code is flashed onto Arduino ATMEGA and the IDE compiles the code for ATMEGA by selecting               TOOLS>BOARDS>Arduino ATMEGA
 3. Select the correct port for USB communication with boards by going TOOLS>PORT>COMM ##

_____________________________________________________________________________________________________________________________________________________________________

 ################ Sketches requried for basic function ################
 1. glove_transmitter.ino for Arduino NANO
 2. car_receiver.ino for Arduino MEGA


_____________________________________________________________________________________________________________________________________________________________________

 ################ Machine Learning Implementation on Arduino using TinyML ################
 
- As a scope of research, the designers of this project have worked on the Machine learning aspect of this robot. 
- Using ML, the user is able to generate the gestures of their own choice.
- This implementation is done using TinyML and Tensorflow Lite framework.
- All the ML code and required material can be found in Machine_learning_PS branch of this repo
- The samples for Forwards and left gestures are recorded for your convinience

Disclaimer -  The ML based implementation is implemented to explore future scope of this device, the intended functionality of this device was implemented using mathematical algorithms as seen in the code from main branch.  
