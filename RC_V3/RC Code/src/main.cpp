#include <Arduino.h>

#include "Wire.h"
#include "Helpers.h"
#include "Values.h"
#include "Inputs.h"
#include "NRF.h"
#include "Screen.h"
#include "Page.h"

const bool DEBUG_PRINT = false;
#define UpdateScreenInterval 100

Page *currentPage = nullptr;
Page *previousPage = nullptr;

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
  loadValues();

  demoPage = new DemoControlsPage();
  homePage = new HomePage();

  currentPage = homePage;
}

void loop()
{
  drewScreen = false;
  every(UpdateScreenInterval)
  {
    mpu.update();

    if (previousPage != currentPage)
    {
      currentPage->init();
      previousPage = currentPage;
    }

    currentPage->draw();
    drewScreen = true;
  }

  if (!drewScreen)
    sendNRFData();
}
