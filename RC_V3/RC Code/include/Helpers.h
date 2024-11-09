#pragma once

#include <Arduino.h>

#define every(interval)\
  static uint32_t __every__##interval = millis();\
  if(millis() - __every__##interval >= interval && (__every__##interval = millis()))

#define OFF 0x1
#define ON  0x0

#define UNPRESSED 0x1
#define PRESSED  0x0



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

const int gaitCount = 6;
extern String gaitStrings[gaitCount];


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

void drawWrappedStr(const char* text, int x, int y, int maxWidth, bool centerAlign, int lineSpacing);

void drawPageHeader(String breadcrumb, String pageName);
void drawStringButton(int x, int y, String icon, String label, const uint8_t* font);
void drawGlyphButton(int x, int y, String icon, const uint8_t* font, int glyph);
void drawGrid();

void drawHexapodBody(Vector2 center);
void drawHexapod(Vector2 center, Vector3 leg1, Vector3 leg2, Vector3 leg3, Vector3 leg4, Vector3 leg5, Vector3 leg6);
void drawHexapodFoot(float x, float y, bool onGround);
void drawScrollBar(int totalItems, int hoveredIndex);