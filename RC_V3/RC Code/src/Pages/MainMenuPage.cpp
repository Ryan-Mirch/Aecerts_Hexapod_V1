#include <Arduino.h>
#include "Page.h"
#include "Screen.h"
#include "Inputs.h"
#include "Globals.h"
#include "NRF.h"


void MainMenuPage::init()
{
    backButtonReady = false;
    rotaryEncoderButtonReady = false;

    //ignore spins when entering the page
    getRotaryEncoderSpins();
}

void MainMenuPage::loop()
{   
    if (getButtonValue(A) == UNPRESSED) backButtonReady = true;
    if (getButtonValue(A) == PRESSED  && backButtonReady) currentPage = homePage;
    
    drawPageHeader("< Home < ", "Menu");
    
    /*Debug Text*/
    u8g2.setFont(FONT_TEXT_MONOSPACE);
    u8g2.drawStr(115, 63, String(getRotaryEncoderTotalSpins()).c_str());

    u8g2.setFont(FONT_TEXT_MONOSPACE);

    int rowSpacing = 17;
    int y = 25;

    int increment = 0;
    int spins = getRotaryEncoderSpins();
    if (spins > 0) increment = 1;
    if (spins < 0) increment = -1;

    hovered += increment;
    if (hovered >= numChoices) hovered = numChoices - 1;
    else if (hovered < 0) hovered = 0;

    static unsigned char controls_20icon_bits[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x03, 0xbe, 0x07, 0xfb, 0x0f,
        0xf1, 0x09, 0xfb, 0x09, 0x0f, 0x0f, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00};
    u8g2.drawXBM(4, y - 9, 12, 12, controls_20icon_bits);
    u8g2.drawStr(20, y, "Controls");
    if (hovered == 0)
        u8g2.drawRFrame(1, y - 11, 61, 16, 5);

    u8g2.setFont(u8g2_font_twelvedings_t_all);
    u8g2.drawGlyph(5, y + 2 + rowSpacing, 0x0047);
    u8g2.setFont(FONT_TEXT_MONOSPACE);
    u8g2.drawStr(20, y + rowSpacing, "Settings");
    if (hovered == 1)
        u8g2.drawRFrame(1, y + rowSpacing - 11, 61, 16, 5);

    static unsigned char stats_20icon_bits[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x60, 0x00, 0x60, 0x00,
        0x60, 0x03, 0x60, 0x03, 0x6c, 0x03, 0x6c, 0x03, 0x6c, 0x03, 0x00, 0x00};
    u8g2.drawXBM(4, y - 9 + rowSpacing * 2, 12, 12, stats_20icon_bits);
    u8g2.drawStr(20, y + rowSpacing * 2, "Stats");
    if (hovered == 2)
        u8g2.drawRFrame(1, y - 11 + rowSpacing * 2, 47, 16, 5);

    static unsigned char gait_20icon_bits[] = {
        0x00, 0x00, 0xf0, 0x00, 0xfc, 0x03, 0xdc, 0x03, 0xde, 0x07, 0xde, 0x07,
        0x1e, 0x04, 0xfe, 0x07, 0xfc, 0x03, 0xfc, 0x03, 0xf0, 0x00, 0x00, 0x00};
    u8g2.drawXBM(74, y - 9, 12, 12, gait_20icon_bits);
    u8g2.drawStr(90, y, "Gaits");
    if (hovered == 3)
        u8g2.drawRFrame(71, y - 11, 46, 16, 5);

    u8g2.setFont(u8g2_font_twelvedings_t_all);
    u8g2.drawGlyph(75, y + 2 + rowSpacing, 0x006d);
    u8g2.setFont(FONT_TEXT_MONOSPACE);
    u8g2.drawStr(90, y + rowSpacing, "Offsets");
    if (hovered == 4)
        u8g2.drawRFrame(71, y + rowSpacing - 11, 56, 16, 5);

    if (getRotaryEncoderSwitchValue() == UNPRESSED) rotaryEncoderButtonReady = true;
    if (getRotaryEncoderSwitchValue() == PRESSED  && rotaryEncoderButtonReady)
    {
        switch (hovered)
        {
        case 0:
            currentPage = controlsPage;
            return;

        case 1:
            currentPage = settingsPage;
            return;

        case 2:
            currentPage = statsPage;
            return;

        case 3:
            currentPage = gaitsPage;
            return;

        case 4:
            currentPage = offsetsPage;
            return;

        default:
            return;
        }
    }
}