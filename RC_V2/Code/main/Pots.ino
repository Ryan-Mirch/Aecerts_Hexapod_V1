//"Pots" is short for "Potentiometers"

#define PotA_Pin A0
#define PotB_Pin A7

int getPotValue(IOLabels label){
  if(label == 0){
    int valA = map(analogRead(PotA_Pin),0,1023,0,100);
    if(valA%2 != 0)valA++;
    return valA;
  }
  else if(label == 1){
    int valB = map(analogRead(PotB_Pin),0,1023,0,100);
    if(valB%2 != 0)valB++;
    return valB;
  }
  else{
    return 0;
  }
}