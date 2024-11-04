#include <Arduino.h>
#include "Page.h"
#include "Screen.h"
#include "Inputs.h"
#include "Globals.h"

int testCount = 0;

void GaitsPage::init()
{
    hovered = selectedGait;
    resetAnimation();
}

void GaitsPage::loop()
{
    int previousHovered = hovered;

    if (getButtonValue(A) == PRESSED)
        currentPage = mainMenuPage;
    drawPageHeader("< Home < Menu < ", "Gaits");
    u8g2.setFont(FONT_TEXT_MONOSPACE);
    u8g2.drawStr(115, 63, String(getRotaryEncoderTotalSpins()).c_str());
    

    /*List*/
    int increment = 0;
    int spins = getRotaryEncoderSpins();
    if (spins > 0)
        increment = 1;
    if (spins < 0)
        increment = -1;

    hovered += increment;
    if (hovered >= gaitCount)
        hovered = gaitCount - 1;
    else if (hovered < 0)
        hovered = 0;

    if (previousHovered != hovered)
        resetAnimation();

    if (getRotaryEncoderSwitchValue() == PRESSED)
    {
        selectedGait = Gaits(hovered);
    }

    int rowSpacing = 14;
    int listYStart = 24;
    int listLeftSpacing = 12;

    if(hovered >= 2) listYStart = listYStart - rowSpacing*(hovered-2);

    u8g2.setFont(FONT_TEXT);
    for (int i = 0; i < gaitCount; i++)
    {
        if(hovered >= i+3)continue;
        u8g2.drawStr(listLeftSpacing, listYStart + rowSpacing * i, gaitStrings[i].c_str());
        if (selectedGait == i)
            u8g2.drawStr(1, listYStart + rowSpacing * i, ">");
        if (hovered == i)
            u8g2.drawRFrame(listLeftSpacing - 4, listYStart + rowSpacing * i - 10, u8g2.getStrWidth(gaitStrings[i].c_str()) + 8, 13, 5);
    }

    /*Hexapod Visualizer*/

    for (int i = 0; i < 6; i++)
    {
        legAnimProgress[i] += 8;
        if (legAnimProgress[i] >= points)
            legAnimProgress[i] = legAnimProgress[i] - points;
    }

    // For the legs:
    // x,y = leg coordinates
    // z = is leg touching ground (0 is raised, 1 is on ground)

    float pushPoints = points * pushFraction;
    float raisePoints = points - pushPoints;

    for (int i = 0; i < 6; i++)
    {
        if (legAnimProgress[i] < pushPoints)
        {
            legs[i].y = legsCenter[i].y + lerp(-strideLength / 2, strideLength / 2, legAnimProgress[i] / (pushPoints));
            legs[i].z = 1;
        }
        else
        {
            legs[i].y = legsCenter[i].y + lerp(strideLength / 2, -strideLength / 2, (legAnimProgress[i] - pushPoints) / raisePoints);
            legs[i].z = 0;
        }
    }

    drawHexapod(Vector2(96, 37), legs[0], legs[1], legs[2], legs[3], legs[4], legs[5]);
    //u8g2.drawRFrame(70, 12, 52, 52, 5);
}

void GaitsPage::resetAnimation()
{
    if (hovered == TRI)
    {
        legAnimProgress[0] = 0;
        legAnimProgress[1] = points / 2;
        legAnimProgress[2] = 0;
        legAnimProgress[3] = points / 2;
        legAnimProgress[4] = 0;
        legAnimProgress[5] = points / 2;

        pushFraction = 3.1 / 6.0;
    }

    else if (hovered == RIPPLE)
    {
        legAnimProgress[0] = 0;
        legAnimProgress[1] = (points / 6) * 4;
        legAnimProgress[2] = (points / 6) * 2;
        legAnimProgress[3] = (points / 6) * 5;
        legAnimProgress[4] = (points / 6);
        legAnimProgress[5] = (points / 6) * 3;

        pushFraction = 3.2 / 6.0;
    }

    else if (hovered == WAVE)
    {
        legAnimProgress[0] = 0;
        legAnimProgress[1] = (points / 6);
        legAnimProgress[2] = (points / 6) * 2;
        legAnimProgress[3] = (points / 6) * 5;
        legAnimProgress[4] = (points / 6) * 4;
        legAnimProgress[5] = (points / 6) * 3;

        pushFraction = 5.0 / 6.0;
    }

    else if (hovered == QUAD)
    {
        legAnimProgress[0] = 0;
        legAnimProgress[1] = (points / 3);
        legAnimProgress[2] = (points / 3) * 2;
        legAnimProgress[3] = 0;
        legAnimProgress[4] = (points / 3);
        legAnimProgress[5] = (points / 3) * 2;

        pushFraction = 4.1 / 6.0;
    }

    else if (hovered == BI)
    {
        legAnimProgress[0] = 0;
        legAnimProgress[1] = (points / 3);
        legAnimProgress[2] = (points / 3) * 2;
        legAnimProgress[3] = 0;
        legAnimProgress[4] = (points / 3);
        legAnimProgress[5] = (points / 3) * 2;

        pushFraction = 2.1 / 6.0;
    }

    else if (hovered == HOP)
    {
        legAnimProgress[0] = 0;
        legAnimProgress[1] = 0;
        legAnimProgress[2] = 0;
        legAnimProgress[3] = 0;
        legAnimProgress[4] = 0;
        legAnimProgress[5] = 0;

        pushFraction = 3 / 6.0;
    }

    else
    {
        legAnimProgress[0] = 0;
        legAnimProgress[1] = points / 2;
        legAnimProgress[2] = 0;
        legAnimProgress[3] = points / 2;
        legAnimProgress[4] = 0;
        legAnimProgress[5] = points / 2;

        pushFraction = 3.1 / 6.0;
    }

    legsCenter[0] = Vector2(-9, -5);
    legsCenter[1] = Vector2(-12, 0);
    legsCenter[2] = Vector2(-9, 5);
    legsCenter[3] = Vector2(9, 5);
    legsCenter[4] = Vector2(12, 0);
    legsCenter[5] = Vector2(9, -5);

    for (int i = 0; i < 6; i++)
        legs[i] = Vector3(legsCenter[i].x, legsCenter[i].y, 1);
}