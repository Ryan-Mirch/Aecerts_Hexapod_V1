const byte encoderPinA = 2;//outputA digital pin2
const byte encoderPinB = 3;//outoutB digital pin3
#define switchPin 39
volatile int count = 0;
int protectedCount = 0;
int previousCount = 0;

bool switchPressed = false;

const int DEBOUNCE_TIME = 1;
unsigned long timeSinceReleased = 0;

void setupRotaryEncoder(){  
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);

  attachInterrupt(digitalPinToInterrupt(encoderPinA), isrA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), isrB, CHANGE);
}

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

RotaryEncoderState getRotaryEncoderSwitch(){
  uint8_t switchValue = digitalRead(switchPin);
  if(switchValue == LOW)return Pressed;
  return Nothing;


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

  return Nothing;
}

String getRotaryEncoderSwitchString(){
  RotaryEncoderState rotaryEncoderState = getRotaryEncoderSwitch();

  String rotaryPressed = "";
  if(rotaryEncoderState == Pressed){
    rotaryPressed = "Pressed";
  }

  return rotaryPressed;
}