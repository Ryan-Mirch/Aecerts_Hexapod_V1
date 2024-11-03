#pragma once

#include <Arduino.h>
#include "Helpers.h"
#include "Page.h"

extern Gaits selectedGait;
extern Page *currentPage;
extern Page *previousPage;

extern DemoControlsPage *demoPage;
extern HomePage *homePage;
extern MainMenuPage *mainMenuPage;

void loadValues();