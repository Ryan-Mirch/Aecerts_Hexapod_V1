
#include <SPI.h>
#include <RF24.h>

RF24 radio(6, 5); // CE, CSN
const byte address[6] = "00011";

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

void setupNRF(){
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN,0);
  radio.stopListening(); 

  rc_data.joy1_X = 127;
  rc_data.joy1_Y = 127;
  rc_data.joy1_Button = LOW;

  rc_data.joy2_X = 127;
  rc_data.joy2_Y = 127;
  rc_data.joy2_Button = LOW;  

  rc_data.slider1 = 50;
  rc_data.slider2 = 50;

}

void sendNRFData(){
  radio.write(&rc_data, sizeof(RC_Data_Package));
}
