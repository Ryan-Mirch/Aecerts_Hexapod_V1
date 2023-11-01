#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

#define DC  6
#define CS  7   //(SS)
#define SCL 13 //(SCK)
#define SDA 11 //(MOSI)
#define RES 4

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
  if(!screenSet){
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_ncenB10_tr);
      u8g2.drawStr(0,24,stringOne.c_str());
      u8g2.drawStr(0,48,stringTwo.c_str());
    } while ( u8g2.nextPage() );
    screenSet = true;
  }
  
}