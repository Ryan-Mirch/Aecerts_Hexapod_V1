#include <Arduino.h>
#include "Page.h"
#include "Screen.h"
#include "Inputs.h"
#include "Globals.h"

void SettingsPage::init()
{

}

void SettingsPage::loop()
{

    if (getButtonValue(A) == PRESSED) currentPage = mainMenuPage;
    drawPageHeader("< Home < Menu < ","Settings");
    u8g2.setFont(FONT_TEXT_MONOSPACE);
    u8g2.drawStr(115, 63, String(getRotaryEncoderTotalSpins()).c_str());


}