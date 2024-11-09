#include <Arduino.h>
#include "Page.h"
#include "Screen.h"
#include "Inputs.h"
#include "Globals.h"
#include "Popup.h"
#include <EEPROM.h>

enum SettingType
{
    BOOLEAN,
    INTEGER,
    STRING
};

struct Setting
{
    const char *name;        // Name of the setting
    SettingType type;        // Type of the setting
    void *value;             // Pointer to the value
    long int minVal, maxVal; // For integers, define a range
};

uint8_t nrfAddress[EEPROM_NRF_ADDRESS_SIZE]; // NRF chip address as an array of bytes
bool dynamicStrideLength = true;  // Boolean for Dynamic Stride Length
long int sleepDelayTime = 1000;   // int for how many milliseconds to wait before sleeping
uint8_t stringTest[10] = "test test";

Setting settings[] = {
    {"NRF Addr", STRING, &nrfAddress, EEPROM_NRF_ADDRESS_SIZE, EEPROM_NRF_ADDRESS_SIZE}, // Address as string
    {"Dyn Stride Length", BOOLEAN, &dynamicStrideLength},
    {"Sleep Delay", INTEGER, &sleepDelayTime, 0, 100000},
    {"Test", STRING, &stringTest, 10, 10}
    };

const int numSettings = sizeof(settings) / sizeof(settings[0]);

void SettingsPage::init()
{
    rotaryEncoderButtonReady = false;
}

void SettingsPage::loop()
{
    if (getRotaryEncoderSwitchValue() == UNPRESSED) rotaryEncoderButtonReady = true;

    /*Back*/
    if (getButtonValue(A) == PRESSED){
        currentPage = mainMenuPage;
    }       
    
    /*Scrolling*/
    int increment = 0;
    int spins = getRotaryEncoderSpins();

    // limit to scrolling 1 item per frame
    if (spins > 0)
        increment = 1;
    if (spins < 0)
        increment = -1;

    // stop scrolling at ends of list
    hovered += increment;
    if (hovered >= numSettings)
        hovered = numSettings - 1;
    else if (hovered < 0)
        hovered = 0;

    /*Display Header*/
    drawPageHeader("< Home < Menu < ", "Settings");

    /*Display Debug*/
    u8g2.setFont(FONT_TEXT_MONOSPACE);
    u8g2.drawStr(115, 63, String(getRotaryEncoderTotalSpins()).c_str());

    

    /*Display the list*/
    int rowSpacing = 14;
    int listYStart = 24;
    int listLeftSpacing = 7;

    if (hovered >= 2)
        listYStart = listYStart - rowSpacing * (hovered - 2);

    char buffer[32];

    u8g2.setFont(FONT_TEXT);
    for (int i = 0; i < numSettings; i++)
    {
        // Get the setting name and value pointer
        const char *name = settings[i].name;
        void *valuePtr = settings[i].value;

        // Convert the value based on its type
        if (settings[i].type == INTEGER)
        {
            // Format as a normal integer
            sprintf(buffer, "%s: %ld", name, *(long int*)valuePtr);
        }
        else if (settings[i].type == BOOLEAN)
        {
            // Format as "On" or "Off" for boolean settings
            sprintf(buffer, "%s: %s", name, (*(bool *)valuePtr) ? "On" : "Off");
        }
        else if (settings[i].type == STRING)
        {
            // Display the string directly
            sprintf(buffer, "%s: %s", name, (char*)valuePtr);
        }

        // Draw the setting string on the display
        if (hovered < i + 3)
        {
            u8g2.drawStr(listLeftSpacing, listYStart, buffer);
            if (hovered == i)
                u8g2.drawRFrame(listLeftSpacing - 4, listYStart - 10, u8g2.getStrWidth(buffer) + 8, 13, 5);
        }

        listYStart += rowSpacing; // Move down for the next setting
    }

    /*Change Setting Value*/
    if (getRotaryEncoderSwitchValue() == PRESSED && rotaryEncoderButtonReady)
    {
        // When a setting is selected, open a popup window to select a new value, then save the value
        if (settings[hovered].type == BOOLEAN)
        {
            String options[] = {"Off", "On"};
            bool newValue = openPopupMultiChoice(settings[hovered].name, options, 2, *(bool*)settings[hovered].value);

            *(bool*)settings[hovered].value = newValue;
            saveValues();

            rotaryEncoderButtonReady = false;            
        }

        // When a setting is selected, open a popup window to select a new value, then save the value
        if (settings[hovered].type == INTEGER)
        {
            long int newValue = openPopupNumber(settings[hovered].name, *(long int*)settings[hovered].value, settings[hovered].minVal, settings[hovered].maxVal);
            *(long int*)settings[hovered].value = newValue;
            saveValues();

            rotaryEncoderButtonReady = false;
        }

        if (settings[hovered].type == STRING)
        {
            String newValue = openPopupString(settings[hovered].name, String((char*)settings[hovered].value), settings[hovered].maxVal);
            strncpy((char*)settings[hovered].value, newValue.c_str(), settings[hovered].maxVal);
            saveValues();
            rotaryEncoderButtonReady = false;
        }
    }

    /*Draw Scroll Bar*/
    drawScrollBar(numSettings, hovered);
}