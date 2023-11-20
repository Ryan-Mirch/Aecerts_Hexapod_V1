
#define ButtonA_Pin 12
#define ButtonB_Pin 10
#define ButtonC_Pin 8
#define ButtonD_Pin 6

#define BumperA_Pin 27
#define BumperB_Pin 29
#define BumperC_Pin 38
#define BumperD_Pin 37

void setupButtons(){
  pinMode(ButtonA_Pin, INPUT_PULLUP);
  pinMode(ButtonB_Pin, INPUT_PULLUP);
  pinMode(ButtonC_Pin, INPUT_PULLUP);
  pinMode(ButtonD_Pin, INPUT_PULLUP);

  pinMode(BumperA_Pin, INPUT_PULLUP);
  pinMode(BumperB_Pin, INPUT_PULLUP);
  pinMode(BumperC_Pin, INPUT_PULLUP);
  pinMode(BumperD_Pin, INPUT_PULLUP);
}

uint8_t getButtonState(IOLabels label){
  switch(label){
    case A:
      return digitalRead(ButtonA_Pin);
    case B:
      return digitalRead(ButtonB_Pin);
    case C:
      return digitalRead(ButtonC_Pin);
    case D:
      return digitalRead(ButtonD_Pin);
  }
}

uint8_t getBumperState(IOLabels label){
  switch(label){
    case A:
      return digitalRead(BumperA_Pin);
    case B:
      return digitalRead(BumperB_Pin);
    case C:
      return digitalRead(BumperC_Pin);
    case D:
      return digitalRead(BumperD_Pin);
  }
}