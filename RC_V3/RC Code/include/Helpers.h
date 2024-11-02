#pragma once

#include <Arduino.h>

#define every(interval)\
  static uint32_t __every__##interval = millis();\
  if(millis() - __every__##interval >= interval && (__every__##interval = millis()))

#define OFF 0x1
#define ON  0x0

#define UNPRESSED 0x1
#define PRESSED  0x0

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

struct Vector2 {
  float x;
  float y;

  Vector2(float xVal, float yVal) : x(xVal), y(yVal) {}
  Vector2() : x(0), y(0) {}
};

struct Vector3 {
  float x;
  float y;
  float z;

  Vector3(float xVal, float yVal, float zVal) : x(xVal), y(yVal), z(zVal) {}
  Vector3() : x(0), y(0), z(0) {}
};

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
void drawButton(int x, int y, String icon, String label);
void drawHexapod(Vector2 center, Vector3 leg1, Vector3 leg2, Vector3 leg3, Vector3 leg4, Vector3 leg5, Vector3 leg6);