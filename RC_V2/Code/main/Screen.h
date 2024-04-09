#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include <MPU6050_light.h>

#define DC  49   //(CE)
#define CS  42   //(SS)
#define SCL 52 //(SCK)
#define SDA 51 //(MOSI)
#define RES 40

#define UpdateScreenInterval 100

MPU6050 mpu(Wire);

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

U8G2_SSD1309_128X64_NONAME0_F_4W_HW_SPI u8g2(U8G2_R0, CS, DC, RES);

void setupScreen(){
  /* U8g2 Project: SSD1306 Test Board */
  pinMode(DC, OUTPUT);
  pinMode(CS, OUTPUT);
  digitalWrite(DC, 0);
  digitalWrite(CS, 0);	
  u8g2.begin();  

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_squeezed_r6_tr);  
  u8g2.drawStr(40,30,"Calibrating Gyro");
  u8g2.sendBuffer();
}



void setWord1(String s){
  string1 = s;
}

void setWord2(String s){
  string2 = s;
}

void setWord3(String s){
  string3 = s;
}

void setWord4(String s){
  string4 = s;  
}

void setWord5(String s){
  string5 = s;  
}

void setWord6(String s){
  string6 = s;  
}

void setWord7(String s){
  string7 = s;  
}

void setWord8(String s){
  string8 = s;  
}

void setWord9(String s){
  string9 = s;  
}

void setWord10(String s){
  string10 = s;  
}

void setWord11(String s){
  string11 = s;  
}

void setLongWord1(String s){
  stringLong1 = s;  
}

bool updateScreen(){ 
  every(UpdateScreenInterval){
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_squeezed_r6_tr);
    
    u8g2.drawStr(1,12,string1.c_str());
    u8g2.drawStr(1,20,string2.c_str());
    u8g2.drawStr(1,28,string3.c_str());
    u8g2.drawStr(1,36,string4.c_str());
    u8g2.drawStr(1,44,string5.c_str());
    u8g2.drawStr(64,12,string6.c_str());
    u8g2.drawStr(64,20,string7.c_str());
    u8g2.drawStr(64,28,string8.c_str());
    u8g2.drawStr(64,36,string9.c_str());
    u8g2.drawStr(64,44,string10.c_str()); 
    u8g2.drawStr(64,52,string11.c_str()); 
    u8g2.drawStr(1,62,stringLong1.c_str()); 
    u8g2.sendBuffer();

    mpu.update();
    return true;
  }
  return false;
}

