/* Get tilt angles on X and Y, and rotation angle on Z
 * Angles are given in degrees
 * 
 * License: MIT
 */


#include <MPU6050_light.h>

MPU6050 mpu(Wire);
unsigned long timer = 0;


void setupGyro(){
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
}

GyroAngleData readGyro(){
  GyroAngleData gad;

  mpu.update();  
  gad.X = mpu.getAngleX();
  gad.Y = mpu.getAngleY();

  return gad;
}

void calibrateGyro(){
  mpu.calcOffsets();
}

