#include <Arduino.h>
#include "Page.h"
#include "Screen.h"
#include "Inputs.h"
#include "Globals.h"

String inputName = "";
String inputDescription = "";

int switchAPreviousValue;
int switchBPreviousValue;
int switchCPreviousValue;
int switchDPreviousValue;

int potAPreviousValue;
int potBPreviousValue;

const uint8_t *testFont = u8g2_font_5x7_tf;

void ControlsPage::init()
{
    switchAPreviousValue = getSwitchValue(A);
    switchBPreviousValue = getSwitchValue(B);
    switchCPreviousValue = getSwitchValue(C);
    switchDPreviousValue = getSwitchValue(D);
    
    potAPreviousValue = getPotValue(A);
    potBPreviousValue = getPotValue(B);

    inputName = "";
    inputDescription = "";

    rotaryEncoderButtonReady = false;
}

void ControlsPage::loop()
{
    u8g2.setFont(FONT_BOLD_HEADER);
    u8g2.drawStr(64 - (u8g2.getStrWidth(inputName.c_str()) / 2), 25, inputName.c_str());

    u8g2.setFont(FONT_TEXT);
    drawWrappedStr(inputDescription.c_str(), 2, 37, 127, true, 1);

    if (getRotaryEncoderSwitchValue() == UNPRESSED) rotaryEncoderButtonReady = true;

    if (getButtonValue(A) == PRESSED)
        currentPage = mainMenuPage;
    drawPageHeader("< Home < Menu < ", "Controls");

    if (inputName == "")
    {
        u8g2.setFont(FONT_HEADER);
        u8g2.drawStr(30, 40, "Use any input...");
    }

    if (getBumperValue(A) == PRESSED)
    {
        inputName = "Front Left Bumper";
        inputDescription = BUMPER_A_DESCRIPTION;
    }

    else if (getBumperValue(B) == PRESSED)
    {
        inputName = "Back Left Bumper";
        inputDescription = BUMPER_B_DESCRIPTION;
    }

    else if (getBumperValue(C) == PRESSED)
    {
        inputName = "Front Right Bumper";
        inputDescription = BUMPER_C_DESCRIPTION;
    }

    else if (getBumperValue(D) == PRESSED)
    {
        inputName = "Back Right Bumper";
        inputDescription = BUMPER_D_DESCRIPTION;
    }

    else if (getSwitchValue(A) != switchAPreviousValue)
    {
        inputName = "Switch A";
        inputDescription = SWITCH_A_DESCRIPTION;
        switchAPreviousValue = getSwitchValue(A);
    }

    else if (getSwitchValue(B) != switchBPreviousValue)
    {
        inputName = "Switch B";
        inputDescription = SWITCH_B_DESCRIPTION;
        switchBPreviousValue = getSwitchValue(B);
    }

    else if (getSwitchValue(C) != switchCPreviousValue)
    {
        inputName = "Switch C";
        inputDescription = SWITCH_C_DESCRIPTION;
        switchCPreviousValue = getSwitchValue(C);
    }

    else if (getSwitchValue(D) != switchDPreviousValue)
    {
        inputName = "Switch D";
        inputDescription = SWITCH_D_DESCRIPTION;
        switchDPreviousValue = getSwitchValue(D);
    }

    else if (abs(getJoyValue(A).x-128) > 30 || abs(getJoyValue(A).y-128) > 30)
    {
        inputName = "Left Joystick";
        inputDescription = JOY_LEFT_DESCRIPTION;
    }

    else if (abs(getJoyValue(B).x-128) > 30 || abs(getJoyValue(B).y-128) > 30)
    {
        inputName = "Right Joystick";
        inputDescription = JOY_RIGHT_DESCRIPTION;
    }

    else if (getPotValue(A) > potAPreviousValue+2 || getPotValue(A) < potAPreviousValue-2)
    {
        inputName = "Dial A";
        inputDescription = POT_A_DESCRIPTION;
        potAPreviousValue = getPotValue(A);
    }

    else if (getPotValue(B) > potBPreviousValue+2 || getPotValue(B) < potBPreviousValue-2)
    {
        inputName = "Dial B";
        inputDescription = POT_B_DESCRIPTION;
        potBPreviousValue = getPotValue(B);
    }

    else if (getJoyButtonValue(A) == PRESSED)
    {
        inputName = "Left Joystick Button";
        inputDescription = JOY_LEFT_BUTTON_DESCRIPTION;
    }

    else if (getJoyButtonValue(B) == PRESSED)
    {
        inputName = "Right Joystick Button";
        inputDescription = JOY_RIGHT_BUTTON_DESCRIPTION;
    }

    
    else if ((getRotaryEncoderSpins() != 0 || getRotaryEncoderSwitchValue() == PRESSED) && rotaryEncoderButtonReady){
        inputName = "Rotary Encoder";
        inputDescription = ROTARY_ENCODER_DESCRIPTION;
    }

    else if (getButtonValue(B) == PRESSED)
    {
        inputName = "Button B";
        inputDescription = BUTTON_B_DESCRIPTION;
    }

    else if (getButtonValue(C) == PRESSED)
    {
        inputName = "Button C";
        inputDescription = BUTTON_C_DESCRIPTION;
    }

    else if (getButtonValue(D) == PRESSED)
    {
        inputName = "Button D";
        inputDescription = BUTTON_D_DESCRIPTION;
    }
}