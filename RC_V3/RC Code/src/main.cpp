#include <Arduino.h>

#include "Wire.h"
#include "Helpers.h"
#include "Inputs.h"
#include "NRF.h"
#include "Screen.h"
#include "Page.h"

const bool DEBUG_PRINT = false;
#define UpdateScreenInterval 100

Page *pages[2];
Page *currentPage = nullptr;

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

  pages[0] = new HomePage();
  pages[1] = new DemoControlsPage();
}

void loop()
{

  if (getSwitchValue(D) == OFF)
    currentPage = pages[0];
  else
    currentPage = pages[1];

  
  drewScreen = false;
  every(UpdateScreenInterval)
  {    
    mpu.update();
    
    DemoControlsPage *demoPage = static_cast<DemoControlsPage *>(pages[1]);
    demoPage->string11 = String(drawTimerEnd - drawTimerStart);

    HomePage *homePage = static_cast<HomePage *>(pages[0]);
    homePage->loopTime = "Loop Time: " + String(drawTimerEnd - drawTimerStart);

    drawTimerStart = millis();
    currentPage->draw();
    drawTimerEnd = millis();

    drewScreen = true;
  }

  if (!drewScreen)
    sendNRFData();
}
