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

uint8_t nrfAddress[EEPROM_NRF_ADDRESS_SIZE]; // NRF chip address as an array of bytes

void loadValues()
{
    // Load NRF Address
    for (int i = 0; i < EEPROM_NRF_ADDRESS_SIZE; i++) {
        nrfAddress[i] = EEPROM.read(EEPROM_NRF_ADDRESS_ADDR + i);
    }

    // Load Dynamic Stride Length
    dynamicStrideLength = EEPROM.read(EEPROM_DYNAMIC_STRIDE_ADDR);
}

void saveValues(){
    // Save NRF Address (array of bytes)
    bool addressChanged = false;
    for (int i = 0; i < EEPROM_NRF_ADDRESS_SIZE; i++) {
        if (EEPROM.read(EEPROM_NRF_ADDRESS_ADDR + i) != nrfAddress[i]) {
            addressChanged = true;
            break;
        }
    }
    if (addressChanged) {
        for (int i = 0; i < EEPROM_NRF_ADDRESS_SIZE; i++) {
            EEPROM.update(EEPROM_NRF_ADDRESS_ADDR + i, nrfAddress[i]);
        }
    }
    
    // Save Dynamic Stride Length (boolean, 1 byte)
    EEPROM.update(EEPROM_DYNAMIC_STRIDE_ADDR, dynamicStrideLength);
}
