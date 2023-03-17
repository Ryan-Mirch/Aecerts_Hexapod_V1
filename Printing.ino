void print_value(String name, float value){
  Serial.print(name + ": ");
  Serial.println(value);
}

void print_value(String name, Vector3 value){
  Serial.print(name + ": ");
  Serial.println(value.toString());
}