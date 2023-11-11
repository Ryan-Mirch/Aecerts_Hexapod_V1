const byte encoderPinA = 2;//outputA digital pin2
const byte encoderPinB = 3;//outoutB digital pin3
#define switchPin P06
volatile int count = 0;
int protectedCount = 0;
int previousCount = 0;

#define readA bitRead(PIND,2)//faster than digitalRead()
#define readB bitRead(PIND,3)//faster than digitalRead()

bool switchPressed = false;

const int DEBOUNCE_TIME = 1;
unsigned long timeSinceReleased = 0;

void setupRotaryEncoder(){  
  ioExtender.pinMode(switchPin, INPUT);
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(encoderPinA), isrA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), isrB, CHANGE);
}

void isrA() {
  if(readB != readA) {
    count ++;
  } else {
    count --;
  }
}
void isrB() {
  if (readA == readB) {
    count ++;
  } else {
    count --;
  }
}

int getRotaryEncoderSpins(){
  noInterrupts();
  protectedCount = count/4;
  interrupts();
  int spins = protectedCount - previousCount;
  previousCount = protectedCount;
  return spins;
}

RotaryEncoderState readRotaryEncoder(){
  uint8_t switchValue = getIOExtenderPinValue(switchPin);
  if(switchValue == HIGH && !switchPressed){
    if(millis() - timeSinceReleased > DEBOUNCE_TIME){
      if(DEBUG_PRINT)Serial.println("Switch Pressed!");
      switchPressed = true;  
      return Pressed;
    }    
  }
  if(switchValue == LOW && switchPressed){
    if(DEBUG_PRINT)Serial.println("Switch Released.");
    switchPressed = false;  
    timeSinceReleased = millis();
    return Released;    
  }

  return Nothing;
}