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


int counter = 0;

void DemoControlsPage::draw()
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

  int joyLeftXValue = map(analogRead(A6), 0, 1023, 254, 0);
  int joyLeftYValue = map(analogRead(A7), 0, 1023, 0, 254);

  string6 = ("JL X: " + String(joyLeftXValue) + " Y: " + String(joyLeftYValue));
  rc_data.joy1_X = joyLeftXValue;
  rc_data.joy1_Y = joyLeftYValue;

  int joyRightXValue = map(analogRead(A2), 0, 1023, 0, 254);
  int joyRightYValue = map(analogRead(A3), 0, 1023, 0, 254);

  string7 = ("JR X: " + String(joyRightXValue) + " Y: " + String(joyRightYValue));
  rc_data.joy2_X = joyRightXValue;
  rc_data.joy2_Y = joyRightYValue;

  stringLong1 = (getGyroString());

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_tom_thumb_4x6_mf);

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
  u8g2.sendBuffer();
}