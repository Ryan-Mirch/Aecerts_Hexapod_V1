#include "SPI.h"
#include <Adafruit_GFX.h>
#include <ILI9488.h>

#define TFT_CS         7
#define TFT_DC         8
#define TFT_LED        -1
#define TFT_RST        4

ILI9488 tft = ILI9488(TFT_CS, TFT_DC, 11, 13, TFT_RST, 12);

void setupScreen(){
  Serial.println("ILI9488 Test!");
  tft.begin();
  //tft.fillScreen(ILI9488_BLACK);
  return;
}


void updateScreen(){
  testText();
  clearText();
}

unsigned long testText() {
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9488_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ILI9488_YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(ILI9488_RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(ILI9488_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
  return micros() - start;
}

unsigned long clearText() {
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9488_BLACK);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ILI9488_BLACK); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(ILI9488_BLACK);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(ILI9488_BLACK);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
  return micros() - start;
}