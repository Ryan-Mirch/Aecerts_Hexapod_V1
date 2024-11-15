#include "Inputs.h"

// Define global variables
int potAVal = 0;
int potBVal = 0;
unsigned long potTimer = 0;
unsigned long potInterval = 50;
unsigned long potLastChanged[2] = {0, 0};

const int POT_THRESHOLD = 2; // Define a threshold for potentiometer value changes
const int JOY_THRESHOLD = 4; // Define a threshold for joystick value changes

unsigned long gyroTimer = 0;
Vector3 gad;
MPU6050 mpu(Wire);

volatile int count = 0;
int protectedCount = 0;
int previousCount = 0;
bool switchPressed = false;
const int DEBOUNCE_TIME = 1;
unsigned long timeSinceReleased = 0;

const byte encoderPinA = 2; // outputA digital pin2
const byte encoderPinB = 3; // outputB digital pin3

unsigned long buttonLastPressed[4] = {0, 0, 0, 0};
unsigned long bumperLastPressed[4] = {0, 0, 0, 0};
unsigned long switchLastChanged[4] = {0, 0, 0, 0};
unsigned long joyButtonLastPressed[2] = {0, 0};
unsigned long timeSinceLastInput = 0;

String lastInputName = ""; // Add this line to define the new global variable

// Define functions
int getPotValue(IOLabels label)
{
    if (millis() - potTimer > potInterval)
    {
        int newPotAVal = map(analogRead(PotA_Pin), 0, 1023, 100, 0);
        int newPotBVal = map(analogRead(PotB_Pin), 0, 1023, 100, 0);
        if (abs(newPotAVal - potAVal) > POT_THRESHOLD)
        {
            potAVal = newPotAVal;
            potLastChanged[0] = millis();
            lastInputName = "PotA"; // Add this line
            timeSinceLastInput = millis();
        }
        if (abs(newPotBVal - potBVal) > POT_THRESHOLD)
        {
            potBVal = newPotBVal;
            potLastChanged[1] = millis();
            lastInputName = "PotB"; // Add this line
            timeSinceLastInput = millis();
        }
        potTimer = millis();
    }

    if (label == 0)
        return potAVal;
    if (label == 1)
        return potBVal;
    else
        return 0;
}

int getButtonValue(IOLabels label)
{
    int value = 0;
    switch (label)
    {
    case A:
        value = digitalRead(ButtonA_Pin);
        break;
    case B:
        value = digitalRead(ButtonB_Pin);
        break;
    case C:
        value = digitalRead(ButtonC_Pin);
        break;
    case D:
        value = digitalRead(ButtonD_Pin);
        break;
    default:
        return 0;
    }
    if (value == PRESSED)
    {
        buttonLastPressed[label] = millis();
        timeSinceLastInput = millis();
        lastInputName = "Button" + String((char)('A' + label)); // Add this line
    }
    return value;
}

String getButtonsString()
{
    uint8_t valueA = getButtonValue(A);
    uint8_t valueB = getButtonValue(B);
    uint8_t valueC = getButtonValue(C);
    uint8_t valueD = getButtonValue(D);

    String result = "";

    if (valueA == PRESSED)
        result += "A";
    if (valueB == PRESSED)
        result += "B";
    if (valueC == PRESSED)
        result += "C";
    if (valueD == PRESSED)
        result += "D";

    return "Btns: " + result;
}

int getBumperValue(IOLabels label)
{
    int value = 0;
    switch (label)
    {
    case A:
        value = digitalRead(BumperA_Pin);
        break;
    case B:
        value = digitalRead(BumperB_Pin);
        break;
    case C:
        value = digitalRead(BumperC_Pin);
        break;
    case D:
        value = digitalRead(BumperD_Pin);
        break;
    default:
        return 0;
    }
    if (value == PRESSED)
    {
        bumperLastPressed[label] = millis();
        timeSinceLastInput = millis();
        lastInputName = "Bumper" + String((char)('A' + label)); // Add this line
    }
    return value;
}

String getBumpersString()
{
    uint8_t valueA = getBumperValue(A);
    uint8_t valueB = getBumperValue(B);
    uint8_t valueC = getBumperValue(C);
    uint8_t valueD = getBumperValue(D);

    String result = "";

    if (valueA == PRESSED)
        result += "A";
    if (valueB == PRESSED)
        result += "B";
    if (valueC == PRESSED)
        result += "C";
    if (valueD == PRESSED)
        result += "D";

    return "Bumps: " + result;
}

int getSwitchValue(IOLabels label)
{
    static int previousSwitchValues[4] = {digitalRead(SwitchA_Pin), digitalRead(SwitchB_Pin), digitalRead(SwitchC_Pin), digitalRead(SwitchD_Pin)};
    int value = 0;
    switch (label)
    {
    case A:
        value = digitalRead(SwitchA_Pin);
        break;
    case B:
        value = digitalRead(SwitchB_Pin);
        break;
    case C:
        value = digitalRead(SwitchC_Pin);
        break;
    case D:
        value = digitalRead(SwitchD_Pin);
        break;
    default:
        return 0;
    }
    if (value != previousSwitchValues[label])
    {
        switchLastChanged[label] = millis();
        timeSinceLastInput = millis();
        lastInputName = "Switch" + String((char)('A' + label)); // Add this line
        previousSwitchValues[label] = value;
    }
    return value;
}

String getSwitchesString()
{
    uint8_t valueA = getSwitchValue(A);
    uint8_t valueB = getSwitchValue(B);
    uint8_t valueC = getSwitchValue(C);
    uint8_t valueD = getSwitchValue(D);

    String result = "";

    if (valueA == ON)
        result += "A";
    if (valueB == ON)
        result += "B";
    if (valueC == ON)
        result += "C";
    if (valueD == ON)
        result += "D";

    return "Switches: " + result;
}

int getJoyButtonValue(IOLabels label)
{
    int value = 0;
    switch (label)
    {
    case A:
        value = digitalRead(JoyLeftButton_Pin);
        break;
    case B:
        value = digitalRead(JoyRightButton_Pin);
        break;
    default:
        return 0;
    }
    if (value == PRESSED)
    {
        joyButtonLastPressed[label] = millis();
        timeSinceLastInput = millis();
        lastInputName = "JoyButton" + String((char)('A' + label)); // Add this line
    }
    return value;
}

String getJoyButtonsString()
{
    uint8_t valueA = getJoyButtonValue(A);
    uint8_t valueB = getJoyButtonValue(B);

    String result = "";

    if (valueA == PRESSED)
        result += "A";
    if (valueB == PRESSED)
        result += "B";

    return "Joys: " + result;
}

Vector2 getJoyValue(IOLabels label)
{
    Vector2 joyValue;
    static Vector2 previousJoyValueA(0, 0);
    static Vector2 previousJoyValueB(0, 0);
    switch (label)
    {
    case A:
        joyValue = Vector2(map(analogRead(A6), 0, 1023, 254, 0), map(analogRead(A7), 0, 1023, 0, 254));
        if (abs(joyValue.x) > JOY_THRESHOLD || abs(joyValue.y) > JOY_THRESHOLD)
        {
            previousJoyValueA = joyValue;
            timeSinceLastInput = millis();
            lastInputName = "JoyA"; // Add this line
        }
        break;
    case B:
        joyValue = Vector2(map(analogRead(A2), 0, 1023, 0, 254), map(analogRead(A3), 0, 1023, 0, 254));
        if (abs(joyValue.x) > JOY_THRESHOLD || abs(joyValue.y) > JOY_THRESHOLD)
        {
            previousJoyValueB = joyValue;
            timeSinceLastInput = millis();
            lastInputName = "JoyB"; // Add this line
        }
        break;
    default:
        return Vector2(0, 0);
    }
    return joyValue;
}

String getJoyValueString(IOLabels label)
{
    Vector2 joyValue = getJoyValue(label);
    static Vector2 previousJoyValueA(0, 0);
    static Vector2 previousJoyValueB(0, 0);

    if (label == A && (abs(joyValue.x - previousJoyValueA.x) > JOY_THRESHOLD || abs(joyValue.y - previousJoyValueA.y) > JOY_THRESHOLD))
    {
        previousJoyValueA = joyValue;
        return ("JL X: " + String(joyValue.x) + " Y: " + String(joyValue.y));
    }

    if (label == B && (abs(joyValue.x - previousJoyValueB.x) > JOY_THRESHOLD || abs(joyValue.y - previousJoyValueB.y) > JOY_THRESHOLD))
    {
        previousJoyValueB = joyValue;
        return ("JR X: " + String(joyValue.x) + " Y: " + String(joyValue.y));
    }

    return "";
}

Vector3 readGyro()
{

    gad.x = mpu.getAngleX();
    gad.y = mpu.getAngleY();
    gad.z = mpu.getAngleZ();

    return gad;
}

String getGyroString()
{
    gad = readGyro();
    return "GX: " + String(gad.x) + " GY: " + String(gad.y) + " GZ: " + String(gad.z);
}

void isrA()
{
    if (digitalRead(encoderPinB) != digitalRead(encoderPinA))
    {
        count++;
    }
    else
    {
        count--;
    }
    delay(5);
}

void isrB()
{
    if (digitalRead(encoderPinA) == digitalRead(encoderPinB))
    {
        count++;
    }
    else
    {
        count--;
    }
    delay(5);
}

int getRotaryEncoderSpins()
{
    noInterrupts();
    protectedCount = count / 4;
    interrupts();
    int spins = protectedCount - previousCount;
    previousCount = protectedCount;
    return spins;
}

int getRotaryEncoderTotalSpins()
{
    return count / 4;
}

int getRotaryEncoderSwitchValue()
{
    uint8_t switchValue = digitalRead(RotaryEncoderButton_Pin);
    if (switchValue == PRESSED)
    {
        timeSinceLastInput = millis();
        lastInputName = "RotaryEncoderSwitch"; // Add this line
        return PRESSED;
    }
    if (switchValue == PRESSED && !switchPressed)
    {
        if (millis() - timeSinceReleased > DEBOUNCE_TIME)
        {
            if (false)
                Serial.println("Switch Pressed!");
            switchPressed = true;
            return PRESSED;
        }
    }
    if (switchValue == UNPRESSED && switchPressed)
    {
        if (false)
            Serial.println("Switch Released.");
        switchPressed = false;
        timeSinceReleased = millis();
        return PRESSED;
    }

    return UNPRESSED;
}

String getRotaryEncoderSwitchString()
{
    int rotaryEncoderState = getRotaryEncoderSwitchValue();

    String rotaryPressed = "";
    if (rotaryEncoderState == PRESSED)
    {
        rotaryPressed = "Pressed";
    }

    if (rotaryEncoderState == UNPRESSED)
    {
        rotaryPressed = "Unpressed";
    }

    return rotaryPressed;
}

unsigned long getTimeSinceButtonPressed(IOLabels label)
{
    return millis() - buttonLastPressed[label];
}

unsigned long getTimeSinceBumperPressed(IOLabels label)
{
    return millis() - bumperLastPressed[label];
}

unsigned long getTimeSinceSwitchChanged(IOLabels label)
{
    return millis() - switchLastChanged[label];
}

unsigned long getTimeSinceJoyButtonPressed(IOLabels label)
{
    return millis() - joyButtonLastPressed[label];
}

unsigned long getTimeSincePotChanged(IOLabels label)
{
    return millis() - potLastChanged[label];
}

unsigned long getTimeSinceLastInput()
{
    return millis() - timeSinceLastInput;
}

String getLastInputName()
{
    return lastInputName;
}

void setupInputs()
{
    // Buttons
    pinMode(ButtonA_Pin, INPUT_PULLUP);
    pinMode(ButtonB_Pin, INPUT_PULLUP);
    pinMode(ButtonC_Pin, INPUT_PULLUP);
    pinMode(ButtonD_Pin, INPUT_PULLUP);

    // Bumpers
    pinMode(BumperA_Pin, INPUT_PULLUP);
    pinMode(BumperB_Pin, INPUT_PULLUP);
    pinMode(BumperC_Pin, INPUT_PULLUP);
    pinMode(BumperD_Pin, INPUT_PULLUP);

    // Switches
    pinMode(SwitchA_Pin, INPUT_PULLUP);
    pinMode(SwitchB_Pin, INPUT_PULLUP);
    pinMode(SwitchC_Pin, INPUT_PULLUP);
    pinMode(SwitchD_Pin, INPUT_PULLUP);

    // Joystick Buttons
    pinMode(JoyLeftButton_Pin, INPUT_PULLUP);
    pinMode(JoyRightButton_Pin, INPUT_PULLUP);

    // Gyro
    byte status = mpu.begin();
    while (status != 0)
    {
    }
    mpu.calcOffsets();

    // Rotary Encoder
    pinMode(RotaryEncoderButton_Pin, INPUT_PULLUP);
    pinMode(encoderPinA, INPUT);
    pinMode(encoderPinB, INPUT);

    attachInterrupt(digitalPinToInterrupt(encoderPinA), isrA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderPinB), isrB, CHANGE);
}
