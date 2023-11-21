//"Pots" is short for "Potentiometers"

#define PotA_Pin A0
#define PotB_Pin A14

int getPotValue(IOLabels label){
  if(label == 0){
    int valA = map(analogRead(PotA_Pin),0,1023,100,0);
    return valA;
  }
  else if(label == 1){
    int valB = map(analogRead(PotB_Pin),0,1023,100,0);
    return valB;
  }
  else{
    return 0;
  }
}