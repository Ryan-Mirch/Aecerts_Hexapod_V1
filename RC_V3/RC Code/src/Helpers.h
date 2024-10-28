
#pragma once

#include <Arduino.h>

#define every(interval)\
  static uint32_t __every__##interval = millis();\
  if(millis() - __every__##interval >= interval && (__every__##interval = millis()))

enum RotaryEncoderState {
  Nothing,    //0
  Pressed,    //1 
  Released    //2
};

enum IOLabels {
  A, //0
  B, //1
  C, //2
  D  //3
};

struct GyroAngleData {
    float X;
    float Y;
    float Z;
};

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

