#include "Wire.h"

const bool DEBUG_PRINT = true;

enum RotaryEncoderState {
  Nothing,    //0
  Pressed,    //1 
  Released,   //2
  SpunRight,  //3
  SpunLeft    //4
};

struct GyroAngleData {
    int X;
    int Y;
};

int prevGyroX = 0;
int prevGyroY = 0;

void setup() {
  Serial.begin(9600);

  Wire.begin();

  setupRotaryEncoder();
  setupGyro();

}

void loop() {
  RotaryEncoderState rotaryEncoderState = readRotaryEncoder();


  if(rotaryEncoderState != Nothing){
    Serial.println(rotaryEncoderState);
  }

  GyroAngleData gad = readGyro(); 
  if(gad.X != prevGyroX || gad.Y != prevGyroY){
    Serial.print("X : ");
    Serial.print(gad.X);
    Serial.print("\tY : ");
    Serial.println(gad.Y);
  }
  prevGyroX = gad.X;
  prevGyroY = gad.Y;  
}
