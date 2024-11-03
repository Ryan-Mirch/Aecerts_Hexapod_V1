#pragma once

#include <Arduino.h>

#define every(interval)\
  static uint32_t __every__##interval = millis();\
  if(millis() - __every__##interval >= interval && (__every__##interval = millis()))

#define OFF 0x1
#define ON  0x0

#define UNPRESSED 0x1
#define PRESSED  0x0

#define FONT_HEADER u8g2_font_NokiaSmallPlain_tf
#define FONT_BOLD_HEADER u8g2_font_NokiaSmallBold_te
#define FONT_TEXT u8g2_font_5x7_mf
#define FONT_SMALL_TEXT u8g2_font_4x6_mf

enum IOLabels {
  A, //0
  B, //1
  C, //2
  D  //3
};

enum Gaits {
  TRI,      //0
  RIPPLE,   //1
  WAVE,     //2
  QUAD,     //3
  BI,       //4
  HOP       //5
};

extern String GaitStrings[6];

struct Vector2 {
  float x;
  float y;

  Vector2(float xVal, float yVal) : x(xVal), y(yVal) {}
  Vector2() : x(0), y(0) {}
  Vector2 operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
  }
};

struct Vector3 {
  float x;
  float y;
  float z;

  Vector3(float xVal, float yVal, float zVal) : x(xVal), y(yVal), z(zVal) {}
  Vector3() : x(0), y(0), z(0) {}
  Vector3 operator+(const Vector3& other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
  }
};

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
float lerp(float a, float b, float f);
float calculateHypotenuse(float x, float y);
void drawButton(int x, int y, String icon, String label);


void drawHexapod(Vector2 center, Vector3 leg1, Vector3 leg2, Vector3 leg3, Vector3 leg4, Vector3 leg5, Vector3 leg6);
void drawHexapodFoot(float x, float y, bool onGround);