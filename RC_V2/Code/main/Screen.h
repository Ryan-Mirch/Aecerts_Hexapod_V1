#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

#define DC  6   //(CE)
#define CS  7   //(SS)
#define SCL 13 //(SCK)
#define SDA 11 //(MOSI)
#define RES 4

#define UpdateScreenInterval 1

unsigned long last_update_time = 0;

String stringOne = "String 1";   
String stringTwo = "String 2";   

bool screenSet = false;

//U8G2_SSD1309_128X64_NONAME0_1_4W_SW_SPI u8g2(U8G2_R0, SCL, SDA, CS, DC, RES); 
U8G2_SSD1309_128X64_NONAME0_1_4W_HW_SPI u8g2(U8G2_R0, CS, DC, RES);

void setupScreen(){
  /* U8g2 Project: SSD1306 Test Board */
  pinMode(DC, OUTPUT);
  pinMode(CS, OUTPUT);
  digitalWrite(DC, 0);
  digitalWrite(CS, 0);	
  u8g2.begin();

  
}

void setWord1(String s){
  stringOne = s;
  screenSet = false;
}

void setWord2(String s){
  stringTwo = s;
  screenSet = false;
}


void updateScreen(){
  
  
  if(!screenSet && millis() - last_update_time > UpdateScreenInterval){
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_squeezed_r6_tr); 
      u8g2.drawStr(8,12,stringOne.c_str());
      u8g2.drawStr(8,20,stringTwo.c_str());
      u8g2.drawButtonUTF8(62, 40, U8G2_BTN_HCENTER|U8G2_BTN_BW1|U8G2_BTN_XFRAME, 34,  2,  2, "Btn" );

      u8g2.drawRFrame(1, 1, 126, 62, 4);
    } while ( u8g2.nextPage() );
    screenSet = true;
    last_update_time = millis();
  }
  
}