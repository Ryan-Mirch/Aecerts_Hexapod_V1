#include <Arduino.h>
#include "Helpers.h"
#include "Screen.h"

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void drawButton(int x, int y, String icon, String label)
{
  u8g2.setFont(u8g2_font_4x6_mf);
  u8g2.drawStr(x-1, y+3, icon.c_str());
  u8g2.drawRFrame(x-4, y-4, 9,9,3);
  
  u8g2.setFont(u8g2_font_NokiaSmallPlain_tf );
  u8g2.drawStr(x+7, y+4, label.c_str());
}