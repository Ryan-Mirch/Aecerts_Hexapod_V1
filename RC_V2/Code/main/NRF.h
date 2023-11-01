
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(6, 5); // CE, CSN
const byte addresses[][6] = {"00011", "00012"};

unsigned long rc_last_received_time = 0;
unsigned long rc_current_time = 0;

unsigned long rc_last_requested_time = 0;
unsigned long rc_requested_interval = 300;

int test = 0;

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
  byte requestData;

};

struct Hexapod_Data_Package {
  byte current_sensor_value;
};

RC_Data_Package rc_data;
Hexapod_Data_Package hex_data;

void setupNRF(){
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00012
  radio.openReadingPipe(1, addresses[0]); // 00011
  radio.setPALevel(RF24_PA_MIN,0);  

  rc_data.joy1_X = 127;
  rc_data.joy1_Y = 127;
  rc_data.joy1_Button = LOW;

  rc_data.joy2_X = 127;
  rc_data.joy2_Y = 127;
  rc_data.joy2_Button = LOW;  

  rc_data.slider1 = 50;
  rc_data.slider2 = 50;

  setWord1("Unconnected");
}

void sendNRFData(){ 

  radio.stopListening();
  rc_data.requestData = 0;
  if(millis() - rc_last_requested_time > rc_requested_interval){
    rc_data.requestData = 1;
    rc_last_requested_time = millis();
  }
  
  radio.write(&rc_data, sizeof(RC_Data_Package));
  radio.startListening(); 
  int incomingTest = 0;
  radio.read(&incomingTest, sizeof(incomingTest));
  if(incomingTest > 0){
    test = incomingTest;
    //setWord1(String(test) + " | " + String(millis()-rc_last_requested_time));
    Serial.println("Data Received: " + String(test));
  }  
  
}


