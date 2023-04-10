#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(49, 48); // CE, CSN



const byte address[6] = "00011";

unsigned long rc_last_received_time = 0;
unsigned long rc_current_time = 0;

struct RC_Data_Package {
  byte joy1_X;
  byte joy1_Y;
  byte joy1_Button;
  byte joy2_X;
  byte joy2_Y;
  byte joy2_Button;
  byte slider1;
  byte slider2;
  byte pushButton1;
  byte pushButton2;
};

RC_Data_Package rc_data;
RC_Data_Package rc_data_previous;

void RC_Setup();
bool RC_GetDataPackage();
void RC_DisplayData();
void RC_ResetData();

void RC_Setup(){
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

bool RC_GetDataPackage(){
  if (radio.available()) {
    rc_data_previous = rc_data;
    radio.read(&rc_data, sizeof(RC_Data_Package));
    rc_last_received_time = millis();
  }

  rc_current_time = millis();
  if(rc_current_time - rc_last_received_time > 250){
    RC_ResetData();
    return false;
  }

  return true;
}

void RC_DisplayData(){
  Serial.print("Joy1 X: ");
  Serial.print(rc_data.joy1_X);

  Serial.print("Joy1 Y: ");
  Serial.print(rc_data.joy1_Y);

  Serial.print("Joy1 Button: ");
  Serial.print(rc_data.joy1_Button);

  Serial.print("Joy2 X: ");
  Serial.print(rc_data.joy2_X);

  Serial.print("Joy2 Y: ");
  Serial.print(rc_data.joy2_Y);

  Serial.print("Joy2 Button: ");
  Serial.print(rc_data.joy2_Button);

  Serial.print("Slider 1: ");
  Serial.print(rc_data.slider1);

  Serial.print("Slider 2: ");
  Serial.print(rc_data.slider2);

  Serial.print("Push Button 1: ");
  Serial.print(rc_data.pushButton1);

  Serial.print("Push Button 2: ");
  Serial.println(rc_data.pushButton2);
}

void RC_ResetData(){
  rc_data.joy1_X = 127;
  rc_data.joy1_Y = 127;
  rc_data.joy1_Button = 0;

  rc_data.joy2_X = 127;
  rc_data.joy2_Y = 127;
  rc_data.joy2_Button = 0;

  rc_data.slider1 = 0;
  rc_data.slider2 = 0;

  rc_data.pushButton1 = 0;
  rc_data.pushButton2 = 0;
}