

#include <SPI.h>
#include <RF24.h>

//RF24 radio(9, 10); // CE, CSN
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

const int joy1XPin = A0;    
const int joy1YPin = A1;     
const int joy1ButtonPin = 2;  

const int joy2XPin = A2;     //X attach to A0
const int joy2YPin = A3;     //Y attach to A1
const int joy2ButtonPin = 3;     //Bt attach to digital 7

const int slider1Pin = A4;
const int slider2Pin = A5;  

const int pushButton1Pin = 4;
const int pushButton2Pin = 5;

int oldpotVal = -1;

void setup()
{
  Serial.begin(9600); //initialize serial

  pinMode(joy1ButtonPin,INPUT); //set btpin as INPUT
  digitalWrite(joy1ButtonPin, HIGH); //and HIGH  

  pinMode(joy2ButtonPin,INPUT); //set btpin as INPUT
  digitalWrite(joy2ButtonPin, HIGH); //and HIGH  

  pinMode(pushButton1Pin,INPUT); //set btpin as INPUT
  digitalWrite(pushButton1Pin, HIGH); //and HIGH  

  pinMode(pushButton2Pin,INPUT); //set btpin as INPUT
  digitalWrite(pushButton2Pin, HIGH); //and HIGH  

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN,0);
  radio.stopListening(); 
}

void loop()
{
  rc_data.joy1_X = map(analogRead(joy1XPin), 0, 1023, 0, 255);
  rc_data.joy1_Y = map(analogRead(joy1YPin), 0, 1023, 0, 255);
  rc_data.joy1_Button = !digitalRead(joy1ButtonPin);

  rc_data.joy2_X = map(analogRead(joy2XPin), 0, 1023, 0, 255);
  rc_data.joy2_Y = map(analogRead(joy2YPin), 0, 1023, 0, 255);
  rc_data.joy2_Button = !digitalRead(joy2ButtonPin);  

  rc_data.slider1 = map(smoothPotVal(analogRead(slider1Pin)),0,1023,100,0);
  rc_data.slider2 = map(smoothPotVal(analogRead(slider2Pin)),0,1023,100,0);

  rc_data.pushButton1 = !digitalRead(pushButton1Pin);
  rc_data.pushButton2 = !digitalRead(pushButton2Pin);  

      rc_data.joy1_X = 120;
      rc_data.joy1_Y = 120;
      rc_data.joy1_Button = !digitalRead(joy1ButtonPin);

      rc_data.joy2_X = 120;
      rc_data.joy2_Y = 120;
      rc_data.joy2_Button = !digitalRead(joy2ButtonPin);  

      rc_data.slider1 = 50;
      rc_data.slider2 = 50;

  
  //RC_DisplayData();
  radio.write(&rc_data, sizeof(RC_Data_Package));
}

int smoothPotVal(int potVal){
  int potValComp;

  if (potVal <= 44)
  {
    potValComp = map(potVal, 0, 44, 0, 255); // bottom 25% of pot remapped to 0 to 25% of 1023
  }
  if (potVal > 44 && potVal < 975)
  {
    potValComp = map(potVal, 45, 974, 255, 767); // 50% middle of pot remapped to 25% to 75%% of 1023
  }
  if (potVal >= 975 )
  {
    potValComp = map(potVal, 975, 1023, 767, 1023); // top 25% of pot remapped to 75% to 100%% of 1023
  }
  return potValComp;
}

void RC_DisplayData(){
  Serial.print("Joy1 X: ");
  Serial.print(rc_data.joy1_X);

  Serial.print(" | Joy1 Y: ");
  Serial.print(rc_data.joy1_Y);

  Serial.print(" | Joy1 Button: ");
  Serial.print(rc_data.joy1_Button);

  Serial.print(" | Joy2 X: ");
  Serial.print(rc_data.joy2_X);

  Serial.print(" | Joy2 Y: ");
  Serial.print(rc_data.joy2_Y);

  Serial.print(" | Joy2 Button: ");
  Serial.print(rc_data.joy2_Button);

  Serial.print(" | Slider 1: ");
  Serial.print(rc_data.slider1);

  Serial.print(" | Slider 2: ");
  Serial.print(rc_data.slider2);

  Serial.print(" | Push Button 1: ");
  Serial.print(rc_data.pushButton1);

  Serial.print(" | Push Button 2: ");
  Serial.println(rc_data.pushButton2);
}

