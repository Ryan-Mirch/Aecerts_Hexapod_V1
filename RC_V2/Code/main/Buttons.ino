
#define ButtonA_Pin P13
#define ButtonB_Pin P12
#define ButtonC_Pin P11
#define ButtonD_Pin P10

#define BumperA_Pin P14
#define BumperB_Pin P17
#define BumperC_Pin P05
#define BumperD_Pin P04

void setupButtons(){
  ioExtender.pinMode(ButtonA_Pin, INPUT);
  ioExtender.pinMode(ButtonB_Pin, INPUT);
  ioExtender.pinMode(ButtonC_Pin, INPUT);
  ioExtender.pinMode(ButtonD_Pin, INPUT);

  ioExtender.pinMode(BumperA_Pin, INPUT);
  ioExtender.pinMode(BumperB_Pin, INPUT);
  ioExtender.pinMode(BumperC_Pin, INPUT);
  ioExtender.pinMode(BumperD_Pin, INPUT);
}

uint8_t getButtonState(IOLabels label){
  switch(label){
    case A:
      return getIOExtenderPinValue(ButtonA_Pin);
    case B:
      return getIOExtenderPinValue(ButtonB_Pin);
    case C:
      return getIOExtenderPinValue(ButtonC_Pin);
    case D:
      return getIOExtenderPinValue(ButtonD_Pin);
  }
}

uint8_t getBumperState(IOLabels label){
  switch(label){
    case A:
      return getIOExtenderPinValue(BumperA_Pin);
    case B:
      return getIOExtenderPinValue(BumperB_Pin);
    case C:
      return getIOExtenderPinValue(BumperC_Pin);
    case D:
      return getIOExtenderPinValue(BumperD_Pin);
  }
}