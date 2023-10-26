#include <Encoder.h>

Encoder encoder1(3, 2);  //CLK, DT
long encoder1PrevPos = 0;
const int switchPin = 6;

const int encoderPin1 = 4;
const int encoderPin2 = 5;

bool switchPressed = false;

long prevPosition  = 0;
long newPosition;

int spinRightCount = 0;
int spinLeftCount = 0;

int prevSpin = 1; //1: Right, 2:Left

const int DEBOUNCE_TIME = 1000;
unsigned long timeSinceSpun = 0;
unsigned long timeSinceReleased = 0;

void setupRotaryEncoder(){
  
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(encoderPin1, INPUT_PULLUP);
  pinMode(encoderPin2, INPUT_PULLUP);
}

RotaryEncoderState readRotaryEncoder(){
  int switchValue = digitalRead(switchPin);
  if(switchValue == LOW && !switchPressed){
    if(millis() - timeSinceReleased > DEBOUNCE_TIME){
      if(DEBUG_PRINT)Serial.println("Switch Pressed!");
      switchPressed = true;  
      return Pressed;
    }    
  }
  if(switchValue == HIGH && switchPressed){
    if(DEBUG_PRINT)Serial.println("Switch Released.");
    switchPressed = false;  
    timeSinceReleased = millis();
    return Released;    
  }

  newPosition = encoder1.read();
  

  if(newPosition != prevPosition){
    Serial.println(newPosition);
    if (newPosition < prevPosition) {
      spinRightCount++;   
    }
    else if(newPosition > prevPosition){      
      spinLeftCount++;         
    }
  prevPosition = newPosition;

  }

  if(prevSpin == 1){
    if(spinLeftCount >= 4){
      if(DEBUG_PRINT)Serial.println("Spun Left 1");
      prevSpin = 2;
      timeSinceSpun = millis();
      spinRightCount = 0;
      spinLeftCount = 0;
      return SpunLeft;   
    } 
    if(spinRightCount >= 4){
      if(DEBUG_PRINT)Serial.println("Spun Right 2");
      prevSpin = 1;
      timeSinceSpun = millis();
      spinRightCount = 0;
      spinLeftCount = 0;
      return SpunRight;
    }
  }

  if(prevSpin == 2){
    if(spinLeftCount >= 4){
      if(DEBUG_PRINT)Serial.println("Spun Left 3");
      prevSpin = 2;
      timeSinceSpun = millis();
      spinRightCount = 0;
      spinLeftCount = 0;
      return SpunLeft;
    } 
    if(spinRightCount >= 4){
      if(DEBUG_PRINT)Serial.println("Spun Right 4");
      prevSpin = 1;
      timeSinceSpun = millis();
      spinRightCount = 0;
      spinLeftCount = 0;
      return SpunRight;
    }
  }

  return Nothing;
}