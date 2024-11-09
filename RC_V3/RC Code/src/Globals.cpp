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

void saveOffsets() {
    for (int i = 0; i < OFFSETS_COUNT; i++) {
        EEPROM.put(EEPROM_OFFSETS_ADDR + i * sizeof(int), offsets[i]);
    }
}

void loadValues()
{
    // Load NRF Address
    for (int i = 0; i < EEPROM_NRF_ADDRESS_SIZE; i++) {
        nrfAddress[i] = EEPROM.read(EEPROM_NRF_ADDRESS_ADDR + i);
    }

    // Load Dynamic Stride Length
    dynamicStrideLength = EEPROM.read(EEPROM_DYNAMIC_STRIDE_ADDR);

    // Load Sleep Delay Time
    EEPROM.get(EEPROM_SLEEP_DELAY_ADDR, sleepDelayTime);

    // Load Offsets
    for (int i = 0; i < OFFSETS_COUNT; i++) {
        EEPROM.get(EEPROM_OFFSETS_ADDR + i * sizeof(int), offsets[i]);
    }
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

    // Save Sleep Delay Time (long int, 4 bytes)
    EEPROM.put(EEPROM_SLEEP_DELAY_ADDR, sleepDelayTime);

    saveOffsets(); // Save offsets to EEPROM
}
