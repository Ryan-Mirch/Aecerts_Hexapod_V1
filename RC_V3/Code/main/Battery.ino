float new_average = 0;
float old_average = 0;
float min_average = 100;
int currentSampleCount = 0;
const int maxSampleCount = 1000;
const int IsChargingPin = 9;

void setupBattery(){
  pinMode(IsChargingPin, INPUT);
}


int getBatteryPercentage(){

  float batteryVoltage = mapFloat(analogRead(1),0,1024,0,5);
  float batteryPercentage = mapFloat(batteryVoltage,3.7,4,0,100);

   if(isCharging()){
    currentSampleCount = 0;
    new_average = 0;
    min_average = 100;
    return old_average;
  }
  
  if(new_average == 0){
    new_average = batteryPercentage;
  }

  currentSampleCount = min(currentSampleCount + 1, maxSampleCount);
  old_average = new_average;
  new_average = (old_average * (maxSampleCount-1) + batteryPercentage) / maxSampleCount;
  
  if(currentSampleCount > maxSampleCount/4){
    min_average = min(min_average,new_average);
  }
  else{
    min_average = new_average;
  }

  return (int)min_average;
}


bool isCharging(){
  return (digitalRead(IsChargingPin));
}