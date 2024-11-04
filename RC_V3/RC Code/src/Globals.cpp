#include <Arduino.h>
#include "Globals.h"
#include "Helpers.h"
#include "Page.h"
#include <EEPROM.h>

Gaits selectedGait = TRI;

DemoControlsPage *demoPage = new DemoControlsPage();
HomePage *homePage = new HomePage();
MainMenuPage *mainMenuPage = new MainMenuPage();
ControlsPage *controlsPage = new ControlsPage();
SettingsPage *settingsPage = new SettingsPage();
StatsPage *statsPage = new StatsPage();
GaitsPage *gaitsPage = new GaitsPage();
OffsetsPage *offsetsPage = new OffsetsPage();

Page *previousPage = nullptr;
Page *currentPage = homePage;

void loadValues()
{
    // Load NRF Address
    EEPROM.get(EEPROM_NRF_ADDRESS_ADDR, nrfAddress);

    // Load Dynamic Stride Length
    dynamicStrideLength = EEPROM.read(EEPROM_DYNAMIC_STRIDE_ADDR);
}

void saveValues(){
    // Save NRF Address (32-bit integer, 4 bytes)
    EEPROM.put(EEPROM_NRF_ADDRESS_ADDR, nrfAddress);
    
    // Save Dynamic Stride Length (boolean, 1 byte)
    EEPROM.update(EEPROM_DYNAMIC_STRIDE_ADDR, dynamicStrideLength);
}
