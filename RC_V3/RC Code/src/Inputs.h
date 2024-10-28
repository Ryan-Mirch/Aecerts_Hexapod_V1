
#pragma once

#include <Arduino.h>
#include "Helpers.h"
#include <Wire.h>
#include <MPU6050_light.h>

#define ButtonA_Pin 12
#define ButtonB_Pin 10
#define ButtonC_Pin 8
#define ButtonD_Pin 6

#define BumperA_Pin 27 // Left front
#define BumperB_Pin 29 // Left back
#define BumperC_Pin 38 // Right front
#define BumperD_Pin 37 // Right back

#define SwitchA_Pin 35
#define SwitchB_Pin 34
#define SwitchC_Pin 33
#define SwitchD_Pin 32

#define JoyLeftButton_Pin 31
#define JoyRightButton_Pin 36

#define PotA_Pin A0
#define PotB_Pin A14

#define RotaryEncoderButton_Pin 39

/*---------------------------------------------- Potentiometers ----------------------------------------------*/
int potAVal = 0;
int potBVal = 0;
unsigned long potTimer = 0; 
unsigned long potInterval = 50; 

int getPotValue(IOLabels label){
  
  if(millis()-potTimer > potInterval){
    potAVal = map(analogRead(PotA_Pin),0,1023,100,0);
    potBVal = map(analogRead(PotB_Pin),0,1023,100,0);
    potTimer = millis();
  } 

  if(label == 0)return potAVal;
  if(label == 1)return potBVal;
  else return 0;
}

/*---------------------------------------------- Buttons ----------------------------------------------*/

int getButtonValue(IOLabels label){
  switch(label){
    case A: return digitalRead(ButtonA_Pin);
    case B: return digitalRead(ButtonB_Pin);
    case C: return digitalRead(ButtonC_Pin);
    case D: return digitalRead(ButtonD_Pin);
    default: return 0;
  }
}

String getButtonsString(){
  uint8_t valueA = getButtonValue(A);
  uint8_t valueB = getButtonValue(B);
  uint8_t valueC = getButtonValue(C);
  uint8_t valueD = getButtonValue(D);

  String result = "";

  if(valueA == LOW)result += "A";
  if(valueB == LOW)result += "B";
  if(valueC == LOW)result += "C";
  if(valueD == LOW)result += "D";

  return "Btns: " + result;  
}

/*---------------------------------------------- Bumpers ----------------------------------------------*/

int getBumperValue(IOLabels label){
  switch(label){
    case A: return digitalRead(BumperA_Pin);
    case B: return digitalRead(BumperB_Pin);
    case C: return digitalRead(BumperC_Pin);
    case D: return digitalRead(BumperD_Pin);
    default: return 0;
  }
}

String getBumpersString(){
  uint8_t valueA = getBumperValue(A);
  uint8_t valueB = getBumperValue(B);
  uint8_t valueC = getBumperValue(C);
  uint8_t valueD = getBumperValue(D);

  String result = "";

  if(valueA == LOW)result += "A";
  if(valueB == LOW)result += "B";
  if(valueC == LOW)result += "C";
  if(valueD == LOW)result += "D";

  return "Bumps: " + result;  
}

/*---------------------------------------------- Switches ----------------------------------------------*/

int getSwitchValue(IOLabels label){
  switch(label){
    case A: return digitalRead(SwitchA_Pin);
    case B: return digitalRead(SwitchB_Pin);
    case C: return digitalRead(SwitchC_Pin);
    case D: return digitalRead(SwitchD_Pin);
    default: return 0;
  }
}

String getSwitchesString(){
  uint8_t valueA = getSwitchValue(A);
  uint8_t valueB = getSwitchValue(B);
  uint8_t valueC = getSwitchValue(C);
  uint8_t valueD = getSwitchValue(D);

  String result = "";

  if(valueA == LOW)result += "A";
  if(valueB == LOW)result += "B";
  if(valueC == LOW)result += "C";
  if(valueD == LOW)result += "D";

  return "Switches: " + result;  
}

/*---------------------------------------------- Joystick Buttons ----------------------------------------------*/

int getJoyButtonValue(IOLabels label){
  switch(label){
    case A: return digitalRead(JoyLeftButton_Pin);
    case B: return digitalRead(JoyRightButton_Pin);
    default : return 0;
  }
}

String getJoyButtonsString(){ 
  uint8_t valueA = getJoyButtonValue(A);
  uint8_t valueB = getJoyButtonValue(B);

  String result = "";

  if(valueA == LOW)result += "A";
  if(valueB == LOW)result += "B";

  return "Joys: " + result;  
}

/*---------------------------------------------- Gyro ----------------------------------------------*/
unsigned long gyroTimer = 0;
GyroAngleData gad;
MPU6050 mpu(Wire);

GyroAngleData readGyro(){  
  mpu.update();
  
  gad.X = mpu.getAngleX();
  gad.Y = mpu.getAngleY();
  gad.Z = mpu.getAngleZ();    
  
  return gad;
}

String getGyroString(){
  GyroAngleData gad = readGyro();
  return "GX: " + String(gad.X) + " GY: " + String(gad.Y) + " GZ: " + String(gad.Z);  
}

/*---------------------------------------------- Rotary Encoder ----------------------------------------------*/
volatile int count = 0;
int protectedCount = 0;
int previousCount = 0;

bool switchPressed = false;

const int DEBOUNCE_TIME = 1;
unsigned long timeSinceReleased = 0;


const byte encoderPinA = 2;//outputA digital pin2
const byte encoderPinB = 3;//outputB digital pin3

void isrA() {
  if(digitalRead(encoderPinB) != digitalRead(encoderPinA)) {
    count ++;
  } else {
    count --;
  }
  delay(5);
}
void isrB() {
  if (digitalRead(encoderPinA) == digitalRead(encoderPinB)) {
    count ++;
  } else {
    count --;
  }
  delay(5);
}

int getRotaryEncoderSpins(){
  noInterrupts();
  protectedCount = count/4;
  interrupts();
  int spins = protectedCount - previousCount;
  previousCount = protectedCount;
  return spins;
}

RotaryEncoderState getRotaryEncoderSwitchValue(){
  uint8_t switchValue = digitalRead(RotaryEncoderButton_Pin);
  if(switchValue == LOW)return Pressed;
  return Nothing;


  if(switchValue == LOW && !switchPressed){
    if(millis() - timeSinceReleased > DEBOUNCE_TIME){
      if(false)Serial.println("Switch Pressed!");
      switchPressed = true;  
      return Pressed;
    }    
  }
  if(switchValue == HIGH && switchPressed){
    if(false)Serial.println("Switch Released.");
    switchPressed = false;  
    timeSinceReleased = millis();
    return Released;    
  }

  return Nothing;
}

String getRotaryEncoderSwitchString(){
  RotaryEncoderState rotaryEncoderState = getRotaryEncoderSwitchValue();

  String rotaryPressed = "";
  if(rotaryEncoderState == Pressed){
    rotaryPressed = "Pressed";
  }

  return rotaryPressed;
}

/*---------------------------------------------- Setup ----------------------------------------------*/

void setupInputs(){
  //Buttons
  pinMode(ButtonA_Pin, INPUT_PULLUP);
  pinMode(ButtonB_Pin, INPUT_PULLUP);
  pinMode(ButtonC_Pin, INPUT_PULLUP);
  pinMode(ButtonD_Pin, INPUT_PULLUP);

  //Bumpers
  pinMode(BumperA_Pin, INPUT_PULLUP);
  pinMode(BumperB_Pin, INPUT_PULLUP);
  pinMode(BumperC_Pin, INPUT_PULLUP);
  pinMode(BumperD_Pin, INPUT_PULLUP);

  //Switches
  pinMode(SwitchA_Pin, INPUT_PULLUP);
  pinMode(SwitchB_Pin, INPUT_PULLUP);
  pinMode(SwitchC_Pin, INPUT_PULLUP);
  pinMode(SwitchD_Pin, INPUT_PULLUP);

  //Joystick Buttons
  pinMode(JoyLeftButton_Pin, INPUT_PULLUP);
  pinMode(JoyRightButton_Pin, INPUT_PULLUP);

  //Gyro
  byte status = mpu.begin();
  while(status!=0){ }  
  mpu.calcOffsets(); 

  //Rotary Encoder
  pinMode(RotaryEncoderButton_Pin, INPUT_PULLUP);
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);

  attachInterrupt(digitalPinToInterrupt(encoderPinA), isrA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), isrB, CHANGE);

}