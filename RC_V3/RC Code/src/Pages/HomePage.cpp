#include <Arduino.h>
#include "Page.h"
#include "Screen.h"
#include "Inputs.h"
#include "Popup.h"
#include "Globals.h"
#include "NRF.h"

void HomePage::init()
{
    rotaryEncoderButtonReady = false;

    legAnimProgress[0] = 0;
    legAnimProgress[1] = points / 2;
    legAnimProgress[2] = 0;
    legAnimProgress[3] = points / 2;
    legAnimProgress[4] = 0;
    legAnimProgress[5] = points / 2;

    legsCenter[0] = Vector2(-9, -5);
    legsCenter[1] = Vector2(-12, 0);
    legsCenter[2] = Vector2(-9, 5);
    legsCenter[3] = Vector2(9, 5);
    legsCenter[4] = Vector2(12, 0);
    legsCenter[5] = Vector2(9, -5);

    for (int i = 0; i < 6; i++)
        legs[i] = Vector3(legsCenter[i].x, legsCenter[i].y, 1);   
    
}

void HomePage::loop()
{    
    rc_control_data.joy1_X = getJoyValue(A).x;
    rc_control_data.joy1_Y = getJoyValue(A).y;
    rc_control_data.joy1_Button = getJoyButtonValue(A);
    rc_control_data.joy2_X = getJoyValue(B).x;
    rc_control_data.joy2_Y = getJoyValue(B).y;
    rc_control_data.joy2_Button = getJoyButtonValue(B);
    rc_control_data.slider1 = getPotValue(A);
    rc_control_data.slider2 = getPotValue(B);
    rc_control_data.pushButton1 = getBumperValue(A);
    rc_control_data.pushButton2 = getBumperValue(C); 
       
    rc_control_data.dynamic_stride_length = dynamicStrideLength;
    rc_control_data.gait = selectedGait;
    rc_control_data.idle = 0; 
    rc_control_data.sleep = (long int)getTimeSinceLastInput() > sleepDelayTime ? 1 : 0; 

    startTime = millis(); 

         

    int offset = 35;
    int textY = 6;
    int textX = 1;

    int lineY = 7;
    int lineL = 19;

    /*Switch Labels*/
    u8g2.setFont(FONT_TEXT_MONOSPACE);
    u8g2.drawStr(textX, textY, "Gyro");
    if (getSwitchValue(A) == ON)
        u8g2.drawHLine(textX, lineY, lineL);

    u8g2.drawStr(textX + offset, textY, "Step");
    if (getSwitchValue(B) == ON)
        u8g2.drawHLine(textX + offset, lineY, lineL);

    u8g2.drawStr(textX + offset * 2, textY, "Easy");
    if (getSwitchValue(C) == ON)
        u8g2.drawHLine(textX + offset * 2, lineY, lineL);

    /*
    u8g2.drawStr(textX + offset * 3, textY, "4th Toggle");
    if (getSwitchValue(D) == ON)
        u8g2.drawHLine(textX + offset * 3, lineY, lineL);
    */
    

    /*Main Menu Button*/
    drawStringButton(4, 59, "E", "Menu", FONT_TEXT);
    if (getRotaryEncoderSwitchValue() == UNPRESSED) rotaryEncoderButtonReady = true;
    if (getRotaryEncoderSwitchValue() == PRESSED  && rotaryEncoderButtonReady) currentPage = mainMenuPage;

    /*Gait Display*/
    drawStringButton(4, 25, "B", "Gait", FONT_TEXT);
    u8g2.setFont(FONT_BOLD_HEADER);
    u8g2.setFontMode(1);
    u8g2.drawStr(1, 43, gaitStrings[selectedGait].c_str());


    /*Info Display*/
    offset = 13;
    textX = 109;
    textY = 23;
    int iconX = 97;

    u8g2.setFont(FONT_TEXT_MONOSPACE);
    u8g2.drawStr(textX, textY, "100%");
    u8g2.drawStr(textX, textY + offset, String(hex_data.current_sensor_value).c_str());
    u8g2.drawStr(textX, textY + offset * 2, (String(getPotValue(A)) + "%").c_str());
    u8g2.drawStr(textX, textY + offset * 3, (String(getPotValue(B)) + "%").c_str());

    u8g2.setFont(u8g2_font_siji_t_6x10);
    u8g2.drawGlyph(iconX + 1, textY, 0xe15e);
    u8g2.drawGlyph(iconX, textY + offset, 0xe09e);
    u8g2.drawGlyph(iconX, textY + offset * 2, 0xe206);
    u8g2.drawGlyph(iconX, textY + offset * 3, 0xe10f);

    /*Hexapod Visualizer*/
    int joyValue = map(abs(getJoyValue(A).x - 128) + abs(getJoyValue(A).y - 128), 0, 256, 0, 40);

    for (int i = 0; i < 6; i++)
    {
        legAnimProgress[i] += joyValue;

        if (legAnimProgress[i] >= points)
        {
            legAnimProgress[i] = legAnimProgress[i] - points;
        }
    }

    // For the legs:
    // x,y = leg coordinates
    // z = is leg touching ground (0 is raised, 1 is on ground)

    for (int i = 0; i < 6; i++)
    {
        if (legAnimProgress[i] <= points / 2)
        {
            legs[i].y = legsCenter[i].y + lerp(-strideLength / 2, strideLength / 2, legAnimProgress[i] / (points / 2));
            legs[i].z = 1;
        }
        else
        {
            legs[i].y = legsCenter[i].y + lerp(strideLength / 2, -strideLength / 2, (legAnimProgress[i] - (points / 2)) / (points / 2));
            legs[i].z = 0;
        }
    }

    drawHexapod(Vector2(64, 37), legs[0], legs[1], legs[2], legs[3], legs[4], legs[5]);
    u8g2.drawRFrame(38, 12, 52, 52, 5);
    totalDrawTime = millis() - startTime;


    /*Gait Selection Popup*/
    if(getButtonValue(B) == PRESSED){        
        selectedGait = Gaits(openPopupMultiChoice("Select a Gait", gaitStrings, gaitCount, selectedGait));
        rotaryEncoderButtonReady = false;
    }   
    
}