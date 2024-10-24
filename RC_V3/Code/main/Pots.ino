//"Pots" is short for "Potentiometers"

#define PotA_Pin A0
#define PotB_Pin A14

int potAVal = 0;
int potBVal = 0;
unsigned long potTimer = 0; 
unsigned long potInterval = 50; 

int getPotValue(IOLabels label){
  
  if(millis()-potTimer > potInterval){
    potAVal = map(analogRead(PotA_Pin),0,1023,100,0);
    potBVal = map(analogRead(PotB_Pin),0,1023,100,0);
    potTimer = millis();
  } 

  if(label == 0)return potAVal;
  if(label == 1)return potBVal;
  else return 0;
}