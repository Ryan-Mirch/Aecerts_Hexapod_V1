#include <Arduino.h>
#include "Page.h"
#include "Helpers.h"
#include "Inputs.h"
#include "NRF.h"
#include "Screen.h"

String string1 = "String 1";
String string2 = "String 2";
String string3 = "String 3";
String string4 = "String 4";
String string5 = "String 5";
String string6 = "String 6";
String string7 = "String 7";
String string8 = "String 8";
String string9 = "String 9";
String string10 = "String 10";
String string11 = "String 11";
String stringLong1 = "String Long 1";


int counter;

void DemoControlsPage::init()
{ 
  counter = 0;
}

void DemoControlsPage::loop()
{ 
  string1 = (getButtonsString());
  string2 = (getSwitchesString());
  string3 = (getBumpersString());
  string4 = (getJoyButtonsString());

  counter += getRotaryEncoderSpins();
  string8 = ("RE Count: " + String(counter));
  string9 = ("RE Switch: " + getRotaryEncoderSwitchString());

  int potAValue = getPotValue(A);
  int potBValue = getPotValue(B);

  rc_data.slider1 = potAValue;
  rc_data.slider2 = potBValue;

  string5 = ("Pot A: " + String(potAValue));
  string10 = ("Pot B: " + String(potBValue));

  string6 = getJoyValueString(A);
  Vector2 leftJoyValue = getJoyValue(A);
  rc_data.joy1_X = leftJoyValue.x;
  rc_data.joy1_Y = leftJoyValue.y;

  string7 = getJoyValueString(B);
  Vector2 rightJoyValue = getJoyValue(B);
  rc_data.joy2_X = rightJoyValue.x;
  rc_data.joy2_Y = rightJoyValue.y;

  stringLong1 = (getGyroString());

  u8g2.setFont(FONT_TINY_TEXT);

  u8g2.drawStr(1, 12, string1.c_str());
  u8g2.drawStr(1, 20, string2.c_str());
  u8g2.drawStr(1, 28, string3.c_str());
  u8g2.drawStr(1, 36, string4.c_str());
  u8g2.drawStr(1, 44, string5.c_str());
  u8g2.drawStr(64, 12, string6.c_str());
  u8g2.drawStr(64, 20, string7.c_str());
  u8g2.drawStr(64, 28, string8.c_str());
  u8g2.drawStr(64, 36, string9.c_str());
  u8g2.drawStr(64, 44, string10.c_str());
  u8g2.drawStr(64, 52, string11.c_str());
  u8g2.drawStr(1, 62, stringLong1.c_str());
}