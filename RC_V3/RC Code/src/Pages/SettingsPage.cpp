#include <Arduino.h>
#include "Page.h"
#include "Screen.h"
#include "Inputs.h"
#include "Globals.h"
#include "Popup.h"

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
    uint32_t minVal, maxVal; // For integers, define a range
};

uint32_t nrfAddress = 0x12345678; // Example NRF chip address
bool dynamicStrideLength = true;  // Boolean for Dynamic Stride Length

Setting settings[] = {
    {"NRF Address", INTEGER, &nrfAddress, 0x00000000, 0xFFFFFFFF}, // Address range as 32-bit unsigned integer
    {"Dyn Stride Length", BOOLEAN, &dynamicStrideLength},
    {"test 1", BOOLEAN, &dynamicStrideLength},
    {"test 2", BOOLEAN, &dynamicStrideLength},
    {"test 3", BOOLEAN, &dynamicStrideLength}};

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
        return;
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
    int listLeftSpacing = 4;

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
            // Format as hexadecimal for the NRF address
            sprintf(buffer, "%s: 0x%08" PRIx32, name, *(uint32_t *)valuePtr);
        }
        else if (settings[i].type == BOOLEAN)
        {
            // Format as "On" or "Off" for boolean settings
            sprintf(buffer, "%s: %s", name, (*(bool *)valuePtr) ? "On" : "Off");
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
            bool currentValue = *(bool*)settings[hovered].value;
            bool newValue = openPopup(settings[hovered].name, options, 2, currentValue);

            *(bool*)settings[hovered].value = newValue;
            saveValues();

            rotaryEncoderButtonReady = false;            
        }
    }
}