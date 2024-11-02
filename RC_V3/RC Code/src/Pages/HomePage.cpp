#include <Arduino.h>
#include "Page.h"
#include "Screen.h"
#include "Inputs.h"

long int startTime;
long int totalDrawTime;

void HomePage::draw()
{
    startTime = millis();
    u8g2.clearBuffer();

    u8g2.setFont(u8g2_font_4x6_mf);
    u8g2.drawStr(50, 64, String(totalDrawTime).c_str());
    u8g2.drawStr(70, 64, String(getRotaryEncoderTotalSpins()).c_str());

    int offset = 35;
    int textY = 6;
    int textX = 1;    

    int lineY = 7;
    int lineL = 19;

    
    /*Switch Labels*/
    u8g2.setFont(u8g2_font_5x7_mf);
    u8g2.drawStr(textX, textY, "Gyro");
    if(getSwitchValue(A) == ON)u8g2.drawHLine(textX, lineY, lineL);

    u8g2.drawStr(textX+offset, textY, "Step");
    if(getSwitchValue(B) == ON)u8g2.drawHLine(textX+offset, lineY, lineL);

    u8g2.drawStr(textX+offset*2, textY, "Bala");  
    if(getSwitchValue(C) == ON)u8g2.drawHLine(textX+offset*2, lineY, lineL);

    u8g2.drawStr(textX+offset*3, textY, "Slow");
    if(getSwitchValue(D) == ON)u8g2.drawHLine(textX+offset*3, lineY, lineL);


    /*Main Menu Button*/
    drawButton(4,59,"D","Menu");


    /*Gait Display*/
    drawButton(4,25,"B","Gait");
    u8g2.setFont(u8g2_font_NokiaSmallBold_te );
    u8g2.drawStr(1,39, "Tri");

    
    /*Info Display*/
    offset = getRotaryEncoderTotalSpins();
    textX = 110;
    textY = 20;
    int iconX = 98; 

    u8g2.setFont(u8g2_font_NokiaSmallPlain_tf );
    u8g2.drawStr(textX, textY, "100%");
    u8g2.drawStr(textX, textY+offset, "99A");
    u8g2.drawStr(textX, textY+offset*2, (String(getPotValue(A)) + "%").c_str());
    u8g2.drawStr(textX, textY+offset*3, (String(getPotValue(B)) + "%").c_str());    
    
    u8g2.setFont(u8g2_font_siji_t_6x10);
    u8g2.drawGlyph(iconX+1, textY, 0xe15e);
    u8g2.drawGlyph(iconX, textY+offset, 0xe09e);
    u8g2.drawGlyph(iconX, textY+offset*2, 0xe083);
    u8g2.drawGlyph(iconX, textY+offset*3, 0xe10f);

    u8g2.sendBuffer();
    totalDrawTime = millis() - startTime;
}