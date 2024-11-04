#include <Arduino.h>
#include "Popup.h"
#include "Screen.h"
#include "Inputs.h"
#include "Globals.h"

int openPopup(String header, String choices[], int numChoices, int hovered)
{
    getRotaryEncoderSpins(); // calling it here ignores the initial spin value

    int selection = -1;

    header = " " + header + " ";
    u8g2.setFont(FONT_HEADER);
    int headerWidth = u8g2.getStrWidth(header.c_str());

    bool rotaryEncoderButtonReady = false;

    while (selection == -1)
    {
        if (getRotaryEncoderSwitchValue() == UNPRESSED) rotaryEncoderButtonReady = true;
        u8g2.clearBuffer();

        /*Draw Frame*/
        u8g2.drawRFrame(1, 1, 126, 62, 4);

        /*Draw Header*/
        u8g2.setFont(FONT_HEADER);
        u8g2.drawStr(64 - (headerWidth / 2), 14, header.c_str());

        /*Draw Choices*/
        int rowStartX = 18, currentY = 30, itemSpacing = 14; // starting positions and spacing
        int currentX = rowStartX;
        u8g2.setFont(FONT_TEXT);
        for (int i = 0; i < numChoices; i++)
        {

            int choiceWidth = u8g2.getStrWidth(choices[i].c_str()) + itemSpacing;

            // If the next choice would go off the screen, move to the next line
            if (currentX + choiceWidth > 128)
            {
                currentX = rowStartX;
                currentY += itemSpacing;
            }

            u8g2.drawStr(currentX, currentY, choices[i].c_str());
            if (hovered == i)
                u8g2.drawRFrame(currentX - 4, currentY - 10, choiceWidth - 6, itemSpacing - 1, 5);

            currentX += choiceWidth;
        }

        u8g2.sendBuffer();

        int increment = 0;
        int spins = getRotaryEncoderSpins();
        if (spins > 0) increment = 1;
        if (spins < 0) increment = -1;

        hovered += increment;
        if (hovered >= numChoices) hovered = numChoices - 1;
        else if (hovered < 0) hovered = 0;

        if (getRotaryEncoderSwitchValue() == PRESSED && rotaryEncoderButtonReady)
        {
            selection = hovered;
        }
    }
    return selection;
}
