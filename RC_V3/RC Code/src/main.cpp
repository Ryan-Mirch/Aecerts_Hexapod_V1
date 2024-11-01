#include <Arduino.h>

#include "Wire.h"
#include "Helpers.h"
#include "Inputs.h"
#include "NRF.h"
#include "Screen.h"
#include "Page.h"

const bool DEBUG_PRINT = false;
#define UpdateScreenInterval 100

Page *currentPage = nullptr;

DemoControlsPage *demoPage;
HomePage *homePage;

unsigned long drawTimerStart = 0;
unsigned long drawTimerEnd = 0;
bool drewScreen = false;

void setup()
{
  Serial.begin(9600);
  setupScreen();
  setupInputs();
  Wire.begin();
  setupNRF();

  demoPage = new DemoControlsPage();
  homePage = new HomePage();
}

void loop()
{

  if (getSwitchValue(D) == OFF)
    currentPage = homePage;
  else
    currentPage = demoPage;

  
  drewScreen = false;
  every(UpdateScreenInterval)
  {    
    mpu.update();
    currentPage->draw();
    drewScreen = true;
  }

  if (!drewScreen)
    sendNRFData();
}
