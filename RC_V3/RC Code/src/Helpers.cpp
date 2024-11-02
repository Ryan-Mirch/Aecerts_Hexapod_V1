#include <Arduino.h>
#include "Helpers.h"
#include "Screen.h"
#include "Inputs.h"

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float lerp(float a, float b, float f)
{
  return a * (1.0 - f) + (b * f);
}

float calculateHypotenuse(float x, float y)
{
  float result = sqrt(pow(x, 2) + pow(y, 2));
  return result;
}

void drawButton(int x, int y, String icon, String label)
{
  u8g2.setFont(u8g2_font_4x6_mf);
  u8g2.drawStr(x - 1, y + 3, icon.c_str());
  u8g2.drawRFrame(x - 4, y - 4, 9, 9, 3);

  u8g2.setFont(u8g2_font_NokiaSmallPlain_tf);
  u8g2.drawStr(x + 7, y + 4, label.c_str());
}

#define hex_20base_width 13
#define hex_20base_height 15
static unsigned char hex_20base_bits[] = {
    0xe0, 0x00, 0x1c, 0x07, 0x0c, 0x06, 0x44, 0x04, 0xa2, 0x08, 0x12, 0x09,
    0x0b, 0x1a, 0x0b, 0x1a, 0x0b, 0x1a, 0x12, 0x09, 0xa2, 0x08, 0x44, 0x04,
    0x0c, 0x06, 0x1c, 0x07, 0xe0, 0x00};



void drawHexapod(Vector2 center, Vector3 leg1, Vector3 leg2, Vector3 leg3, Vector3 leg4, Vector3 leg5, Vector3 leg6)
{
  

  u8g2.setBitmapMode(1);
  u8g2.drawXBM(center.x - 6, center.y - 7, hex_20base_width, hex_20base_height, hex_20base_bits);

  Vector2 leg1Base = center + Vector2(-4, -6);
  Vector2 leg2Base = center + Vector2(-6, 0);
  Vector2 leg3Base = center + Vector2(-4, 6);
  Vector2 leg4Base = center + Vector2(4, 6);
  Vector2 leg5Base = center + Vector2(6, 0);
  Vector2 leg6Base = center + Vector2(4, -6);

  leg1 = leg1 + Vector3(leg1Base.x, leg1Base.y, 0);
  leg2 = leg2 + Vector3(leg2Base.x, leg2Base.y, 0);
  leg3 = leg3 + Vector3(leg3Base.x, leg3Base.y, 0);
  leg4 = leg4 + Vector3(leg4Base.x, leg4Base.y, 0);
  leg5 = leg5 + Vector3(leg5Base.x, leg5Base.y, 0);
  leg6 = leg6 + Vector3(leg6Base.x, leg6Base.y, 0);

  u8g2.drawLine(leg1Base.x, leg1Base.y, leg1.x, leg1.y);
  u8g2.drawLine(leg2Base.x, leg2Base.y, leg2.x, leg2.y);
  u8g2.drawLine(leg3Base.x, leg3Base.y, leg3.x, leg3.y);
  u8g2.drawLine(leg4Base.x, leg4Base.y, leg4.x, leg4.y);
  u8g2.drawLine(leg5Base.x, leg5Base.y, leg5.x, leg5.y);
  u8g2.drawLine(leg6Base.x, leg6Base.y, leg6.x, leg6.y);

  drawHexapodFoot(leg1.x, leg1.y, leg1.z == 1);
  drawHexapodFoot(leg2.x, leg2.y, leg2.z == 1);
  drawHexapodFoot(leg3.x, leg3.y, leg3.z == 1);
  drawHexapodFoot(leg4.x, leg4.y, leg4.z == 1);
  drawHexapodFoot(leg5.x, leg5.y, leg5.z == 1);
  drawHexapodFoot(leg6.x, leg6.y, leg6.z == 1);
}

void drawHexapodFoot(float x, float y, bool onGround)
{
  if (onGround)
    {
      u8g2.drawBox(x - 1, y - 1, 3, 3);
      return;
    }

    u8g2.setColorIndex(0);
    u8g2.drawPixel(x, y);

    u8g2.setColorIndex(1);
    u8g2.drawPixel(x - 1, y);
    u8g2.drawPixel(x + 1, y);
    u8g2.drawPixel(x, y - 1);
    u8g2.drawPixel(x, y + 1);
}