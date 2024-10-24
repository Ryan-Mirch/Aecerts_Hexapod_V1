/* Get tilt angles on X and Y, and rotation angle on Z
 * Angles are given in degrees
 * 
 * License: MIT
 */

#include "Wire.h"
#include <MPU6050_light.h>


unsigned long gyroTimer = 0;
GyroAngleData gad;

void setupGyro(){ 

  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  //Serial.println(F("Calculating offsets, do not move MPU6050"));
  mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
}

GyroAngleData readGyro(){  
  mpu.update();
  
  gad.X = mpu.getAngleX();
  gad.Y = mpu.getAngleY();
  gad.Z = mpu.getAngleZ();
    
  String gyroText = "GX: " + String(gad.X) + " GY: " + String(gad.Y) + " GZ: " + String(gad.Z);
  setLongWord1(gyroText); 
  return gad;
}

