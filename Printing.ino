void print_value(String name, float value, bool newLine){
  Serial.print(name + ": ");

  if(newLine)Serial.println(value);
  else Serial.print(value);
  
}

void print_value(String name, String value, bool newLine){
  Serial.print(name + ": ");
  if(newLine)Serial.println(value);
  else Serial.print(value);
}

void print_value(String name, Vector3 value, bool newLine){
  Serial.print(name + ": ");
  if(newLine)Serial.println(value.toString());
  else Serial.print(value.toString());
}