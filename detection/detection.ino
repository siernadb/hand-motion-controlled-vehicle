

// For accelerometer and gyro readings from MPU6050
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "model.h" //Replace this with your model file

#define NUM_SAMPLES 119 //Number of smaples to be read, during motion detection
#define NUM_AXES 6 //acc 3 axis + gyro 3 axis

const float accelerationThreshold = 5; // threshold of significant in G's
const int half_range = 20;
const int half_range_gyro = 100;

float features[NUM_AXES * NUM_SAMPLES]; //stores the gesture (before detection)
int INT_PIN  = 0; //Button interrupt
volatile boolean StartDetection = false; //When to detect
double baseline[NUM_AXES]; // Used for calibration

Adafruit_MPU6050 mpu;

Eloquent::ML::Port::RandomForest classifier; //This class is inside the model.h file

void calibrate()
{
    sensors_event_t a, g, temp;
    Serial.println("Calibrating...");
 
    for (int i = 0; i < 10; i++) {
        mpu.getEvent(&a, &g, &temp);
        delay(100);
    }

    baseline[0] = double(a.acceleration.x);
    baseline[1] = double(a.acceleration.y);
    baseline[2] = double(a.acceleration.z); 
    baseline[3] = double(g.gyro.x); 
    baseline[4] = double(g.gyro.y);
    baseline[5] = double(g.gyro.z);  
    Serial.println("done Calibrating!");
    return;
}

/*This function records the sensor data when the motion is triggered*/
void record_data() {
    float ax, ay, az;
    float gx, gy, gz;
    sensors_event_t a, g, temp;
    for (int i = 0; i < NUM_SAMPLES; i++) {
         mpu.getEvent(&a, &g, &temp);
  
    ax = constrain(a.acceleration.x - baseline[0], -half_range, half_range);
    ay = constrain(a.acceleration.y - baseline[1], -half_range, half_range);
    az = constrain(a.acceleration.z - baseline[2], -half_range, half_range);
    
    gx = constrain(g.gyro.x - baseline[4], -half_range_gyro, half_range_gyro);
    gy = constrain(g.gyro.y - baseline[5], -half_range_gyro, half_range_gyro);
    gz = constrain(g.gyro.z - baseline[6], -half_range_gyro, half_range_gyro);
    
    int index = i*NUM_AXES;
    features[index] = ax;
    features[index+1] = ay;
    features[index+2] = az;
    features[index+3] = gx;
    features[index+4] = gy;
    features[index+5] = gz;
    
    }
}

/*This function detedcts the motion of the device*/
bool motionDetected(float ax, float ay, float az) {
    return (abs(ax) + abs(ay) + abs(az)) > accelerationThreshold;
}


/*This function will do the detection*/
void classify() {
    Serial.print("Detected gesture: ");
    String gesture = classifier.predictLabel(features);
    Serial.println(gesture);
}

void setup() {
  Serial.begin(9600);
 // pinMode(INT_PIN, INPUT);
  //attachInterrupt(digitalPinToInterrupt(INT_PIN), IntCallback, FALLING);
  
    // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
  delay(100);
  calibrate();
 
}

void loop() {
  // put your main code here, to run repeatedly:
    float ax, ay, az; 
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
  
   ax = constrain(a.acceleration.x - baseline[0], -half_range, half_range);
    ay = constrain(a.acceleration.y - baseline[1], -half_range, half_range);
    az = constrain(a.acceleration.z - baseline[2], -half_range, half_range);

    if (!motionDetected(ax, ay, az)) {
        delay(10);
        return;
    }
    Serial.println("Motion detected!");
      record_data();
      classify(); 
}
