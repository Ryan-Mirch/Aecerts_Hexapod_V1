#include "Screen.h"
#include "Helpers.h"
#include <SPI.h>
#include <Wire.h>
#include <MPU6050_light.h>

#define DC 49  //(CE)
#define CS 42  //(SS)
#define SCL 52 //(SCK)
#define SDA 51 //(MOSI)
#define RES 40

U8G2_SSD1309_128X64_NONAME0_F_4W_HW_SPI u8g2(U8G2_R0, CS, DC, RES);

void setupScreen()
{
    /* U8g2 Project: SSD1306 Test Board */
    pinMode(DC, OUTPUT);
    pinMode(CS, OUTPUT);
    digitalWrite(DC, 0);
    digitalWrite(CS, 0);
    u8g2.begin();

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_squeezed_r6_tr);
    u8g2.drawStr(40, 30, "Calibrating Gyro");
    u8g2.sendBuffer();
}