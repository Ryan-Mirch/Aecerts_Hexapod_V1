#include <Arduino.h>
#include "Popup.h"
#include "Screen.h"
#include "Inputs.h"
#include "Globals.h"

int openPopupMultiChoice(String header, String choices[], int numChoices, int hovered)
{
    getRotaryEncoderSpins(); // calling it here ignores the initial spin value

    int selection = -1;

    header = " " + header + " ";
    u8g2.setFont(FONT_HEADER);
    int headerWidth = u8g2.getStrWidth(header.c_str());

    bool rotaryEncoderButtonReady = false;

    while (selection == -1)
    {
        if (getRotaryEncoderSwitchValue() == UNPRESSED)
            rotaryEncoderButtonReady = true;
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
        if (spins > 0)
            increment = 1;
        if (spins < 0)
            increment = -1;

        hovered += increment;
        if (hovered >= numChoices)
            hovered = numChoices - 1;
        else if (hovered < 0)
            hovered = 0;

        if (getRotaryEncoderSwitchValue() == PRESSED && rotaryEncoderButtonReady)
        {
            selection = hovered;
        }
    }
    return selection;
}

long int openPopupNumber(String header, long int initialValue, long int minValue, long int maxValue)
{
    getRotaryEncoderSpins(); // calling it here ignores the initial spin value

    long int value = initialValue;

    header = " " + header + " ";
    u8g2.setFont(FONT_HEADER);
    int headerWidth = u8g2.getStrWidth(header.c_str());

    bool rotaryEncoderButtonReady = false;
    unsigned long lastIncrementTime = 0;
    unsigned long maxScrollDelay = 200; // Start with a 200ms delay
    unsigned long currentScrollDelay = maxScrollDelay;
    unsigned long minScrollDelay = 40;

    while (true)
    {
        if (getRotaryEncoderSwitchValue() == UNPRESSED)
            rotaryEncoderButtonReady = true;
        u8g2.clearBuffer();

        /*Draw Frame*/
        u8g2.drawRFrame(1, 1, 126, 62, 4);

        /*Draw Header*/
        int headerAndValueXOffset = 20;
        int headerAndValueYOffset = 14;
        u8g2.setFont(FONT_HEADER);
        u8g2.drawStr(64 - (headerWidth / 2) + headerAndValueXOffset, 14 + headerAndValueYOffset, header.c_str());

        /*Draw Value*/
        u8g2.setFont(FONT_TEXT_MONOSPACE);
        String valueStr = String(value);
        int valueWidth = u8g2.getStrWidth(valueStr.c_str());
        int valueX = 64 - (valueWidth / 2) + headerAndValueXOffset;
        u8g2.drawLine(valueX, 32 + headerAndValueYOffset, valueX + valueWidth-2, 32 + headerAndValueYOffset);     
        u8g2.drawStr(valueX, 30 + headerAndValueYOffset, valueStr.c_str());

        /*Draw Buttons*/
        int buttonSpacing = 14;
        drawStringButton(10, 10, "A", "+100", FONT_TEXT_MONOSPACE);
        drawStringButton(10, 10 + buttonSpacing, "B", "-100", FONT_TEXT_MONOSPACE);
        drawStringButton(10, 10 + buttonSpacing*2, "C", "+1000", FONT_TEXT_MONOSPACE);
        drawStringButton(10, 10 + buttonSpacing*3, "D", "-1000", FONT_TEXT_MONOSPACE);

        u8g2.sendBuffer();

        int increment = getRotaryEncoderSpins();

        long int newValue = value + increment;
        if (newValue >= minValue && newValue <= maxValue)
            value = newValue;        

        unsigned long currentTime = millis();
        if (currentTime - lastIncrementTime >= currentScrollDelay || currentScrollDelay == maxScrollDelay)
        {
            if (getButtonValue(A) == PRESSED)
            {
                newValue = value + 100;
                if (newValue <= maxValue)
                    value = newValue;
                lastIncrementTime = currentTime;
                currentScrollDelay = max(minScrollDelay, currentScrollDelay - minScrollDelay); // Decrease delay, minimum 40ms
            }
            else if (getButtonValue(B) == PRESSED)
            {
                newValue = value - 100;
                if (newValue >= minValue)
                    value = newValue;
            }
            else if (getButtonValue(C) == PRESSED)
            {
                newValue = value + 1000;
                if (newValue <= maxValue)
                    value = newValue;
            }
            else if (getButtonValue(D) == PRESSED)
            {
                newValue = value - 1000;
                if (newValue >= minValue)
                    value = newValue;
            }
            else
            {
                currentScrollDelay = maxScrollDelay; // Reset delay when no button is pressed
            }
        }

        if (getRotaryEncoderSwitchValue() == PRESSED && rotaryEncoderButtonReady) return value;
    }
}

String openPopupString(String header, String initialValue, int stringLength)
{
    getRotaryEncoderSpins(); // calling it here ignores the initial spin value

    // Ensure the initial value is the correct length
    String value = initialValue;
    if ((int)value.length() < stringLength) {
        for (int i = (int)value.length(); i < stringLength; i++) {
            value += ' ';
        }
    }
    int hovered = 0;
    int scrollOffset = 0; // Add scroll offset

    header = " " + header + " ";
    u8g2.setFont(FONT_HEADER);
    int headerWidth = u8g2.getStrWidth(header.c_str());

    bool rotaryEncoderButtonReady = false;
    unsigned long lastIncrementTime = 0;
    unsigned long maxScrollDelay = 200; // Start with a 500ms delay
    unsigned long currentScrollDelay = maxScrollDelay;
    unsigned long minScrollDelay = 40;
    bool cursorVisible = true;
    unsigned long lastCursorBlinkTime = 0;
    const unsigned long cursorBlinkInterval = 500; // 500ms interval for cursor blink

    while (true)
    {
        if (getRotaryEncoderSwitchValue() == UNPRESSED)
            rotaryEncoderButtonReady = true;
        u8g2.clearBuffer();

        /*Debug Text
        u8g2.setFont(FONT_TEXT_MONOSPACE);
        u8g2.drawStr(115, 63, String(hovered).c_str());

        u8g2.drawStr(55, 60, String(value[hovered]).c_str());*/

        /*Draw Frame*/
        u8g2.drawRFrame(1, 1, 126, 62, 4);

        /*Draw Header*/
        int headerAndValueXOffset = 25;
        int headerAndValueYOffset = 10;
        u8g2.setFont(FONT_HEADER);
        u8g2.drawStr(64 - (headerWidth / 2) + headerAndValueXOffset, 14 + headerAndValueYOffset, header.c_str());

        /*Draw Value*/
        u8g2.setFont(FONT_TEXT);
        int charSpacing = 10;                                 // Set width for each character
        int startX = 64 - ((min(stringLength, 6) * charSpacing) / 2) + headerAndValueXOffset; // Center the string for 6 characters

        for (int i = scrollOffset; i < min(stringLength, scrollOffset + 6); i++)
        {
            int charX = startX + ((i - scrollOffset) * charSpacing);
            u8g2.drawStr(charX, 32 + headerAndValueYOffset, String(value[i]).c_str());

            // Draw hover frame around the selected character
            if (hovered == i && cursorVisible)
            {
                u8g2.drawRFrame(charX - 2, 20 + headerAndValueYOffset, charSpacing, 14, 2);
            }

            // Draw narrow line under each character
            u8g2.drawLine(charX, 36 + headerAndValueYOffset, charX + charSpacing - 4, 36 + headerAndValueYOffset);
        }

        /*Draw Buttons*/
        int buttonSpacing = 14;
        drawStringButton(10, 10, "A", "+", FONT_TEXT);
        drawStringButton(10, 10 + buttonSpacing, "B", "-", FONT_TEXT);
        drawStringButton(10, 10 + buttonSpacing*2, "C", "Cancel", FONT_TEXT);
        drawStringButton(10, 10 + buttonSpacing*3, "D", "Reset", FONT_TEXT);

        u8g2.sendBuffer();

        int increment = 0;
        int spins = getRotaryEncoderSpins();
        if (spins > 0)
            increment = 1;
        if (spins < 0)
            increment = -1;

        int previousHovered = hovered;
        hovered += increment;
        if (hovered >= stringLength)
            hovered = stringLength - 1;
        else if (hovered < 0)
            hovered = 0;

        // Adjust scroll offset
        if (hovered < scrollOffset)
            scrollOffset = hovered;
        else if (hovered >= scrollOffset + 6)
            scrollOffset = hovered - 5;

        // Reset cursor visibility when scrolling to a new character
        if (hovered != previousHovered)
        {
            cursorVisible = true;
            lastCursorBlinkTime = millis();
        }

        if (hovered < stringLength)
        {
            unsigned long currentTime = millis();
            if (currentTime - lastIncrementTime >= currentScrollDelay || currentScrollDelay == maxScrollDelay)
            {
                if (value[hovered] < 32)value[hovered] = 32;
                if (value[hovered] > 126)value[hovered] = 126;
                if (getButtonValue(A) == PRESSED || getButtonValue(B) == PRESSED){
                    lastIncrementTime = currentTime;
                    currentScrollDelay = max(minScrollDelay, currentScrollDelay - minScrollDelay); // Decrease delay, minimum 50ms
                }

                if (getButtonValue(A) == PRESSED && value[hovered] < 126)value[hovered]++; // Increase

                else if (getButtonValue(B) == PRESSED && value[hovered] > 32)value[hovered]--; // Decrease

                else currentScrollDelay = maxScrollDelay; // Reset delay when no button is pressed
            }

            // Handle cursor blinking
            if (currentTime - lastCursorBlinkTime >= cursorBlinkInterval)
            {
                cursorVisible = !cursorVisible;
                lastCursorBlinkTime = currentTime;
            }
        }

        if (getRotaryEncoderSwitchValue() == PRESSED && rotaryEncoderButtonReady)
        {
            return value.substring(0, stringLength);
        }

        if (getButtonValue(C) == PRESSED) // Cancel
        {
            return initialValue;
        }
        else if (getButtonValue(D) == PRESSED) // Reset
        {
            value = "";
            for (int i = 0; i < stringLength; i++)
            {
                value += "~";
            }
        }
    }
}
