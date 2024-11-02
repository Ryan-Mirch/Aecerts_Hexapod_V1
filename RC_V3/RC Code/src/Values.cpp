#include <Arduino.h>
#include "Values.h"
#include "Helpers.h"
#include <EEPROM.h>

Gaits selectedGait;

void loadValues(){
    selectedGait = TRI;
}