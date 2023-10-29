/*
#define NOT_SEQUENTIAL_PINOUT
#include "PCF8575.h"

PCF8575::DigitalInput di;


PCF8575 ioExtender(0x20, 4, 5);

void setupIOExtender(){
	ioExtender.begin();
}

uint8_t readIOExtenderPinValues(){
  di = ioExtender.digitalReadAll();
}

uint8_t getIOExtenderPinValue(int pin){
  switch(pin){
    case P00:
      return di.p00;
    case P01:
      return di.p01;
    case P02:
      return di.p02;
    case P03:
      return di.p03;
    case P04:
      return di.p04;
    case P05:
      return di.p05;
    case P06:
      return di.p06;
    case P07:
      return di.p07;
    case P10:
      return di.p10;
    case P11:
      return di.p11;
    case P12:
      return di.p12;
    case P13:
      return di.p13;
    case P14:
      return di.p14;
    case P15:
      return di.p15;
    case P16:
      return di.p16;
    case P17:
      return di.p17;
    default:
      return LOW;
  }
  
}
*/