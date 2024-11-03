#include <Arduino.h>
#include "Page.h"
#include "Screen.h"
#include "Inputs.h"
#include "Globals.h"

void MainMenuPage::init()
{
}

void MainMenuPage::loop()
{
    /*Back Button*/
    drawButton(5, 4, "A", "< Home");
    if (getButtonValue(A) == PRESSED)
        currentPage = homePage;

    u8g2.drawStr(60, 7, String(getRotaryEncoderTotalSpins()).c_str());

    u8g2.setFont(FONT_HEADER);
    u8g2.drawStr(85, 8, "Main Menu");

    u8g2.drawHLine(-1,10,130);

    u8g2.setFont(FONT_TEXT);

    int rowSpacing = 17;
    int y = 25;

    static unsigned char controls_20icon_bits[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x03, 0xbe, 0x07, 0xfb, 0x0f,
        0xf1, 0x09, 0xfb, 0x09, 0x0f, 0x0f, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00};
    u8g2.drawXBM(4, y-9, 12, 12, controls_20icon_bits);
    u8g2.drawStr(20, y, "Controls");
    u8g2.drawRFrame(1, y-11, 61, 16, 5);

    static unsigned char gait_20icon_bits[] = {
   0x00, 0x00, 0xf0, 0x00, 0xfc, 0x03, 0xdc, 0x03, 0xde, 0x07, 0xde, 0x07,
   0x1e, 0x04, 0xfe, 0x07, 0xfc, 0x03, 0xfc, 0x03, 0xf0, 0x00, 0x00, 0x00 };
   u8g2.drawXBM(74, y-9, 12, 12, gait_20icon_bits);
    u8g2.drawStr(90, y, "Gait");

    u8g2.setFont(u8g2_font_twelvedings_t_all);
    u8g2.drawGlyph(5, y+2+rowSpacing, 0x0047);
    u8g2.setFont(FONT_TEXT);
    u8g2.drawStr(20, y+rowSpacing, "Settings");

    u8g2.setFont(u8g2_font_twelvedings_t_all);
    u8g2.drawGlyph(75, y+2+rowSpacing, 0x006d);
    u8g2.setFont(FONT_TEXT);
    u8g2.drawStr(90, y+rowSpacing, "Offsets");

    static unsigned char stats_20icon_bits[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x60, 0x00, 0x60, 0x00,
        0x60, 0x03, 0x60, 0x03, 0x6c, 0x03, 0x6c, 0x03, 0x6c, 0x03, 0x00, 0x00};
    u8g2.drawXBM(4, y-9+rowSpacing*2, 12, 12, stats_20icon_bits);
    u8g2.drawStr(20, y+rowSpacing*2, "Stats");
}