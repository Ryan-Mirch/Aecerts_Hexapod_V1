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
    //load eeprom stuff here
}
