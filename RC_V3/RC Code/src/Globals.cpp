#include <Arduino.h>
#include "Globals.h"
#include "Helpers.h"
#include "Page.h"
#include <EEPROM.h>
#include "NRF.h"

Gaits selectedGait = TRI;

String gaitStrings[gaitCount] = {
    "Tri",
    "Ripple",
    "Wave",
    "Quad",
    "Bi",
    "Hop"};

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
    for (int i = 0; i < EEPROM_NRF_ADDRESS_ARRAY_SIZE; i++) {
        nrfAddress[i] = EEPROM.read(EEPROM_NRF_ADDRESS_ADDR + i);
    }

    // Load Dynamic Stride Length
    dynamicStrideLength = EEPROM.read(EEPROM_DYNAMIC_STRIDE_ADDR);

    // Load Sleep Delay Time
    EEPROM.get(EEPROM_SLEEP_DELAY_ADDR, sleepDelayTime);
}

void saveValues(){
    // Save NRF Address (array of bytes)
    bool addressChanged = false;
    for (int i = 0; i < EEPROM_NRF_ADDRESS_ARRAY_SIZE; i++) {
        if (EEPROM.read(EEPROM_NRF_ADDRESS_ADDR + i) != nrfAddress[i]) {
            addressChanged = true;
            break;
        }
    }
    if (addressChanged) {
        for (int i = 0; i < EEPROM_NRF_ADDRESS_ARRAY_SIZE; i++) {
            EEPROM.update(EEPROM_NRF_ADDRESS_ADDR + i, nrfAddress[i]);
        }
        setupNRF();
    }
    
    // Save Dynamic Stride Length (boolean, 1 byte)
    EEPROM.update(EEPROM_DYNAMIC_STRIDE_ADDR, dynamicStrideLength);

    // Save Sleep Delay Time (long int, 4 bytes)
    EEPROM.put(EEPROM_SLEEP_DELAY_ADDR, sleepDelayTime);
}
