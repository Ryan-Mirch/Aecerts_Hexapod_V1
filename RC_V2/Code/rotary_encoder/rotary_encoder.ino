#include <Encoder.h>


Encoder encoder1(5, 4);  //CLK, DT
long encoder1PrevPos = 0;
const int switchPin = 6;
bool switchPressed = false;

long prevPosition  = 0;
long newPosition;

int spinRightCount = 0;
int spinLeftCount = 0;

int prevSpin = 1; //1: Right, 2:Left

unsigned long timeSinceSpun = 0;

void setup() {
  Serial.begin(9600);
  pinMode(switchPin, INPUT_PULLUP);

}

void loop() {
  int switchValue = digitalRead(switchPin);
  if(switchValue == LOW && !switchPressed){
    Serial.println("Switch Pressed!");
    switchPressed = true;  
  }
  if(switchValue == HIGH && switchPressed){
    Serial.println("Switch Released.");
    switchPressed = false;  
  }
  
  newPosition = encoder1.read();

  if(newPosition != prevPosition){
    if (newPosition < prevPosition) {
      spinRightCount++;   
    }
    else if(newPosition > prevPosition){      
      spinLeftCount++;         
    }
  prevPosition = newPosition;
  }

  if(prevSpin == 1){
    if(spinLeftCount >= 2){
      if(millis() - timeSinceSpun > 100){
        Serial.println("Spun Left");
        prevSpin = 2;
        timeSinceSpun = millis();
        spinRightCount = 0;
        spinLeftCount = 0;
      }      
    } 
    if(spinRightCount >= 2){
      Serial.println("Spun Right");
      prevSpin = 1;
      timeSinceSpun = millis();
      spinRightCount = 0;
      spinLeftCount = 0;
    }
  }

  if(prevSpin == 2){
    if(spinLeftCount >= 2){
      Serial.println("Spun Left");
      prevSpin = 2;
      timeSinceSpun = millis();
      spinRightCount = 0;
      spinLeftCount = 0;
    } 
    if(spinRightCount >= 2){
      if(millis() - timeSinceSpun > 100){
        Serial.println("Spun Right");
        prevSpin = 1;
        timeSinceSpun = millis();
        spinRightCount = 0;
        spinLeftCount = 0;
      }      
    }
  }
}
