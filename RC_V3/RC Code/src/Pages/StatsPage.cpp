#include <Arduino.h>
#include "Page.h"
#include "Screen.h"
#include "Inputs.h"
#include "Globals.h"
#include "Helpers.h" // Include Helpers.h

const int totalStats = 10;

void StatsPage::init()
{
    hovered = 0;
}

void StatsPage::loop()
{
    if (getButtonValue(A) == PRESSED) currentPage = mainMenuPage;

    int increment = 0;
        int spins = getRotaryEncoderSpins();
        if (spins > 0)
            increment = 1;
        if (spins < 0)
            increment = -1;

        hovered += increment;
        if (hovered >= totalStats)
            hovered = totalStats - 1;
        else if (hovered < 0)
            hovered = 0;

    drawPageHeader("< Home < Menu < ","Stats");

    /*Debug Text*/
    u8g2.setFont(FONT_TEXT_MONOSPACE);

    for (int i = 0; i < 5; i++) {
        int statIndex = hovered + i;
        if (statIndex < totalStats) {
            u8g2.drawStr(4, 20 + i * 10, ("Stat " + String(statIndex + 1) + ": " + String(statIndex * 10)).c_str());
        }
    }

    // Draw scroll bar using helper function
    drawScrollBar(totalStats, hovered);
}