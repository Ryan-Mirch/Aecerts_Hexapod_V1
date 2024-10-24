
#define ButtonA_Pin 12
#define ButtonB_Pin 10
#define ButtonC_Pin 8
#define ButtonD_Pin 6

#define BumperA_Pin 27
#define BumperB_Pin 29
#define BumperC_Pin 38
#define BumperD_Pin 37

#define ToggleA_Pin 35
#define ToggleB_Pin 34
#define ToggleC_Pin 33
#define ToggleD_Pin 32

#define JoyLeftButton_Pin 31
#define JoyRightButton_Pin 36

void setupButtons(){
  pinMode(ButtonA_Pin, INPUT_PULLUP);
  pinMode(ButtonB_Pin, INPUT_PULLUP);
  pinMode(ButtonC_Pin, INPUT_PULLUP);
  pinMode(ButtonD_Pin, INPUT_PULLUP);

  pinMode(BumperA_Pin, INPUT_PULLUP);
  pinMode(BumperB_Pin, INPUT_PULLUP);
  pinMode(BumperC_Pin, INPUT_PULLUP);
  pinMode(BumperD_Pin, INPUT_PULLUP);

  pinMode(ToggleA_Pin, INPUT_PULLUP);
  pinMode(ToggleB_Pin, INPUT_PULLUP);
  pinMode(ToggleC_Pin, INPUT_PULLUP);
  pinMode(ToggleD_Pin, INPUT_PULLUP);

  pinMode(JoyLeftButton_Pin, INPUT_PULLUP);
  pinMode(JoyRightButton_Pin, INPUT_PULLUP);
}

uint8_t getButtonState(IOLabels label){
  switch(label){
    case A: return digitalRead(ButtonA_Pin);
    case B: return digitalRead(ButtonB_Pin);
    case C: return digitalRead(ButtonC_Pin);
    case D: return digitalRead(ButtonD_Pin);
  }
}

uint8_t getBumperState(IOLabels label){
  switch(label){
    case A: return digitalRead(BumperA_Pin);
    case B: return digitalRead(BumperB_Pin);
    case C: return digitalRead(BumperC_Pin);
    case D: return digitalRead(BumperD_Pin);
  }
}

uint8_t getToggleState(IOLabels label){
  switch(label){
    case A: return digitalRead(ToggleA_Pin);
    case B: return digitalRead(ToggleB_Pin);
    case C: return digitalRead(ToggleC_Pin);
    case D: return digitalRead(ToggleD_Pin);
  }
}

uint8_t getJoyButtonState(IOLabels label){
  switch(label){
    case A: return digitalRead(JoyLeftButton_Pin);
    case B: return digitalRead(JoyRightButton_Pin);
  }
}

String getButtonsString(){
  uint8_t valueA = getButtonState(A);
  uint8_t valueB = getButtonState(B);
  uint8_t valueC = getButtonState(C);
  uint8_t valueD = getButtonState(D);

  String result = "";

  if(valueA == LOW)result += "A";
  if(valueB == LOW)result += "B";
  if(valueC == LOW)result += "C";
  if(valueD == LOW)result += "D";

  return "Btns: " + result;  
}

String getBumpersString(){
  uint8_t valueA = getBumperState(A);
  uint8_t valueB = getBumperState(B);
  uint8_t valueC = getBumperState(C);
  uint8_t valueD = getBumperState(D);

  String result = "";

  if(valueA == LOW)result += "A";
  if(valueB == LOW)result += "B";
  if(valueC == LOW)result += "C";
  if(valueD == LOW)result += "D";

  return "Bumps: " + result;  
}

String getTogglesString(){
  uint8_t valueA = getToggleState(A);
  uint8_t valueB = getToggleState(B);
  uint8_t valueC = getToggleState(C);
  uint8_t valueD = getToggleState(D);

  String result = "";

  if(valueA == LOW)result += "A";
  if(valueB == LOW)result += "B";
  if(valueC == LOW)result += "C";
  if(valueD == LOW)result += "D";

  return "Togs: " + result;  
}

String getJoyButtonsString(){
  uint8_t valueA = getJoyButtonState(A);
  uint8_t valueB = getJoyButtonState(B);

  String result = "";

  if(valueA == LOW)result += "A";
  if(valueB == LOW)result += "B";

  return "Joys: " + result;  
}