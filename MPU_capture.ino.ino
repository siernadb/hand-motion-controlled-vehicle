
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
const float accelerationThreshold = 5; // threshold of significant in G's
const int numSamples = 119;
const int NUM_AXES = 6;
const int half_range = 20;
const int half_range_gyro = 100;
int samplesRead = numSamples;
double baseline[NUM_AXES];
 sensors_event_t a, g, temp;
void calibrate()
{
    Serial.println("Calibrating...");
    for (int i = 0; i < 10; i++) {
        mpu.getEvent(&a, &g, &temp);
        delay(10);
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



void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!mpu.begin()) {
    Serial.println("Failed to initialize MPU!");
    while (1){
    delay(10);
    }
  }

  // print the header
  
    // set accelerometer range to +-4G
  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);

  // set gyro range to +- 500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  delay(100);
 
  calibrate();
  Serial.println("aX,aY,aZ,gX,gY,gZ");
}


void loop() {
  float aX, aY, aZ, gX, gY, gZ;


  // wait for significant motion
   
  while (samplesRead == numSamples) {
     
      mpu.getEvent(&a, &g, &temp);
      // read the acceleration data
    aX = constrain(a.acceleration.x - baseline[0], -half_range, half_range);
    aY = constrain(a.acceleration.y - baseline[1], -half_range, half_range);
    aZ = constrain(a.acceleration.z - baseline[2], -half_range, half_range);
      // sum up the absolutes
      float aSum = fabs(aX) + fabs(aY) + fabs(aZ);
  
      // check if it's above the threshold
      if (aSum >= accelerationThreshold) {
        // reset the sample read count
  
        samplesRead = 0; 
        break;
      }
    
  }

  // check if the all the required samples have been read since
  // the last time the significant motion was detected
  while (samplesRead < numSamples) {
    mpu.getEvent(&a, &g, &temp);
      // read the acceleration and gyroscope data
    aX = constrain(a.acceleration.x - baseline[0], -half_range, half_range);
    aY = constrain(a.acceleration.y - baseline[1], -half_range, half_range);
    aZ = constrain(a.acceleration.z - baseline[2], -half_range, half_range);
    
    gX = constrain(g.gyro.x - baseline[4], -half_range_gyro, half_range_gyro);
    gY = constrain(g.gyro.y - baseline[5], -half_range_gyro, half_range_gyro);
    gZ = constrain(g.gyro.z - baseline[6], -half_range_gyro, half_range_gyro);

      samplesRead++;

      // print the data in CSV format
      Serial.print(aX, 3);
      Serial.print(',');
      Serial.print(aY, 3);
      Serial.print(',');
      Serial.print(aZ, 3);
      Serial.print(',');
      Serial.print(gX, 3);
      Serial.print(',');
      Serial.print(gY, 3);
      Serial.print(',');
      Serial.print(gZ, 3);
      Serial.println();

      if (samplesRead == numSamples) {
        // add an empty line if it's the last sample
        Serial.println();
      }
    
  }
}
