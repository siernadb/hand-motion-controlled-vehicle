# hand-motion-controlled-vehicle

This document is for the details of first implementation of Machine learning on Hand gesture detection using Arduino. 

Introduction
The samples for two gestures were collected using ardunio (code in c). 
The machine learning was performed using python tesorflowlite as well as random forest classifier method. 
The trained model was fed to the detection sketch, therefore the gestures were detected and printed on console.
_____________________________________________________________________________________________________________________________________________________________________________
Dependencies
Sampling technique: 
10 samples per gesture. 
Each sample have 119 readings from accelerometer and gyro sensors combined (6-axes).
Two samples for left and back gestures were recorded.


_____________________________________________________________________________________________________________________________________________________________________________
Machine Learning
Tiny ML for Arduino -tensorflowlite libraries to be installed
Python code have libraries for pip installation (read imports in program for missing libraries)


_____________________________________________________________________________________________________________________________________________________________________________
Detection
The detection sketch is already high in memory, thus it only compiles for atmega arduino devices (not nano or uno)
Raspberry pi is good alternative


_____________________________________________________________________________________________________________________________________________________________________________
Pros
Once setup, the accuracy can be easily improved by increasing number of samples instead of improving the statistical/arithmetic algortihm in angular calculation approach - https://docs.google.com/document/d/18hMysbB4p_f3koSMhks9Gx9vecJpTk2bJhv--e-2KLk/edit?usp=sharing
Better understanding of ML
Hands on experience on ML


_____________________________________________________________________________________________________________________________________________________________________________
Cons
Hardware requirements (costly raspberry pi or higher end of arduino)
Code Implementation need high order thinking 
Accuracy can be challenged by angular calculation approach - https://docs.google.com/document/d/18hMysbB4p_f3koSMhks9Gx9vecJpTk2bJhv--e-2KLk/edit?usp=sharing


_____________________________________________________________________________________________________________________________________________________________________________
Resources
ML concepts and intro to tinyML - https://data-flair.training/blogs/machine-learning-tutorial/
Introduction  of Tensorflow lite on arduino  -  https://blog.tensorflow.org/2019/11/how-to-get-started-with-machine.html
Code inspiration for sample collection and detection  - https://github.com/Neutrino-1/Gesture_Detection_Esp8266
MPU sensor library and API information  - https://adafruit.github.io/Adafruit_MPU6050/html/class_adafruit___m_p_u6050.html#a64e6b74741d31138fb60f14ec2e7d9c1
Tiny ML more resources -  https://eloquentarduino.com/portfolio/continous-motion-classification-with-eloquent-tinyml/
