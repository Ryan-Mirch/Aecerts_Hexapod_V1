
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(49, 4); // CE, CSN
uint8_t address[][6] = {"1Node", "2Node"};
bool radioNumber = 0;

unsigned long rc_send_interval = 50;


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

struct Hexapod_Data_Package {
  float current_sensor_value;
};

RC_Data_Package rc_data;
Hexapod_Data_Package hex_data;

void setupNRF(){
  radio.begin();  
  radio.setPALevel(RF24_PA_LOW);  
  radio.setPayloadSize(sizeof(rc_data));
  radio.setChannel(124);
  radio.enableAckPayload();
  radio.setRetries(5,5);
  radio.openWritingPipe(address[radioNumber]);

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
  every(rc_send_interval){
    bool report = radio.write(&rc_data, sizeof(rc_data));      // transmit & save the report
  
    if (report) {
      if (radio.isAckPayloadAvailable()) {
        radio.read(&hex_data, sizeof(hex_data));   
        float current = hex_data.current_sensor_value;
        //Serial.println(("Current Sensor: " + String(current)));
        setWord1("Current: " + String(current));
      }      

    } else {
      //Serial.print(F("Transmission failed or timed out with ")); // payload was not delivered
      //Serial.print(sizeof(rc_data));
      //Serial.println(F(" bytes"));
    }
    mpu.update();
  }  
}


