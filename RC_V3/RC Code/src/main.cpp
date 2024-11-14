#include <Arduino.h>

#include "Wire.h"
#include "Helpers.h"
#include "Globals.h"
#include "Inputs.h"
#include "NRF.h"
#include "Screen.h"
#include "Page.h"

const bool DEBUG_PRINT = false;
#define UpdateScreenInterval 100
unsigned long drawTimerStart = 0;
unsigned long drawTimerEnd = 0;
bool drewScreen = false;

void setup()
{
  Serial.begin(9600);
  setupScreen();
  setupInputs();
  Wire.begin();
  loadValues();
  setupNRF();
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

    if (currentPage == offsetsPage)
      rc_settings_data.calibrating = 1;
    else
      rc_settings_data.calibrating = 0;

    u8g2.clearBuffer();
    currentPage->loop();
    u8g2.sendBuffer();

    drewScreen = true;
  }

  if (!drewScreen)
  {
    if (currentPage == homePage)
      sendNRFData(RC_CONTROL_DATA);
    else
      sendNRFData(RC_SETTINGS_DATA);
  }
}
