#include <Arduino.h>
#include "Page.h"
#include "Screen.h"
#include "Inputs.h"
#include "Popup.h"
#include "Globals.h"

long int startTime;
long int totalDrawTime;
int legAnimProgress[6];
float points = 100;
int strideLength = 8;

Vector3 legs[6];
Vector2 legsCenter[6];

int testX = 0;
int testY = 0;
int testZ = 0;

void HomePage::init()
{
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
    startTime = millis();

    int offset = 35;
    int textY = 6;
    int textX = 1;

    int lineY = 7;
    int lineL = 19;

    /*Switch Labels*/
    u8g2.setFont(FONT_TEXT);
    u8g2.drawStr(textX, textY, "Gyro");
    if (getSwitchValue(A) == ON)
        u8g2.drawHLine(textX, lineY, lineL);

    u8g2.drawStr(textX + offset, textY, "Step");
    if (getSwitchValue(B) == ON)
        u8g2.drawHLine(textX + offset, lineY, lineL);

    u8g2.drawStr(textX + offset * 2, textY, "Bala");
    if (getSwitchValue(C) == ON)
        u8g2.drawHLine(textX + offset * 2, lineY, lineL);

    u8g2.drawStr(textX + offset * 3, textY, "Slow");
    if (getSwitchValue(D) == ON)
        u8g2.drawHLine(textX + offset * 3, lineY, lineL);

    /*Main Menu Button*/
    drawButton(4, 59, "D", "Menu");
    if(getButtonValue(D) == PRESSED)currentPage = mainMenuPage;

    /*Gait Display*/
    drawButton(4, 25, "B", "Gait");
    u8g2.setFont(FONT_BOLD_HEADER);
    u8g2.drawStr(1, 39, GaitStrings[selectedGait].c_str());

    /*Info Display*/
    offset = 13;
    textX = 109;
    textY = 23;
    int iconX = 97;

    u8g2.setFont(FONT_TEXT);
    u8g2.drawStr(textX, textY, "100%");
    u8g2.drawStr(textX, textY + offset, "99A");
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

    /*Value Testing
    if (getBumperValue(A) == PRESSED)
        testX += 1;
    if (getBumperValue(B) == PRESSED)
        testX -= 1;
    if (getBumperValue(C) == PRESSED)
        testY += 1;
    if (getBumperValue(D) == PRESSED)
        testY -= 1;

    testZ = getRotaryEncoderTotalSpins();



    u8g2.setFont(u8g2_font_4x6_mf);
    u8g2.drawStr(0, 53, String(testX).c_str());
    u8g2.drawStr(10, 53, String(testY).c_str());
    u8g2.drawStr(20, 53, String(testZ).c_str());
    */
    totalDrawTime = millis() - startTime;


    /*Gait Selection Popup*/
    if(getButtonValue(B) == PRESSED){
        selectedGait = Gaits(openPopup("Select a Gait", GaitStrings, 6, selectedGait));
    }
    
}