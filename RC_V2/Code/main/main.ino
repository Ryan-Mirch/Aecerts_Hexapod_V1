#include "Wire.h"
#include "Screen.h"
#include "NRF.h"


const bool DEBUG_PRINT = false;

enum RotaryEncoderState {
  Nothing,    //0
  Pressed,    //1 
  Released    //2
};

enum IOLabels {
  A, //0
  B, //1
  C, //2
  D  //3
};

struct GyroAngleData {
    float X;
    float Y;
    float Z;
};

int counter = 0;

unsigned long loopTimer = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  setupNRF();
  setupScreen();
  setupRotaryEncoder();
  setupGyro();
  setupButtons();
  
}

void loop() {
  setWord10(String(millis()-loopTimer));
  loopTimer = millis();

  GyroAngleData gad = readGyro();
  
  if(!updateScreen())sendNRFData();
  
  
  setWord1(getButtonsString());

  counter += getRotaryEncoderSpins();
  setWord2("RE Count: " + String(counter));
  setWord3("RE Switch: " + getRotaryEncoderSwitchString());
      
  int potAValue = getPotValue(A);
  int potBValue = getPotValue(B);

  rc_data.slider1 = potAValue;
  rc_data.slider2 = potBValue;

  setWord4("Pot A: " + String(potAValue));
  setWord5("Pot B: " + String(potBValue));
  int joyLeftXValue = map(analogRead(A6),0,1023,254,0);
  int joyLeftYValue = map(analogRead(A7),0,1023,0,254);

  setWord6("JoyLeft X: " + String(joyLeftXValue) + " Y: " + String(joyLeftYValue));
  rc_data.joy1_X = joyLeftXValue;
  rc_data.joy1_Y = joyLeftYValue;
  int joyRightXValue = map(analogRead(A2),0,1023,0,254);
  int joyRightYValue = map(analogRead(A3),0,1023,0,254);

  setWord7("JoyLeft X: " + String(joyRightXValue) + " Y: " + String(joyRightYValue));
  rc_data.joy2_X = joyRightXValue;
  rc_data.joy2_Y = joyRightYValue;

  
  
  
}
