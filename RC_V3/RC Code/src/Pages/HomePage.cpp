#include <Arduino.h>
#include "Page.h"
#include "Screen.h"

void HomePage::draw()
{
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_tom_thumb_4x6_mf);

    u8g2.drawStr(1, 12, loopTime.c_str());

    u8g2.sendBuffer();
}