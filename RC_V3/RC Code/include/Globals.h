#pragma once

#include <Arduino.h>

#define BUMPER_A_DESCRIPTION "Not in use."
#define BUMPER_B_DESCRIPTION "Not in use."
#define BUMPER_C_DESCRIPTION "Not in use."
#define BUMPER_D_DESCRIPTION "Not in use."

#define SWITCH_A_DESCRIPTION "Gyro Toggle. Control the hex's body tilt by tilting the RC."
#define SWITCH_B_DESCRIPTION "High Step Toggle. Drastically increases the feet lift height."
#define SWITCH_C_DESCRIPTION "Easy Mode Toggle. Limits the move speed and acceleration."
#define SWITCH_D_DESCRIPTION "Not in use."

#define JOY_LEFT_DESCRIPTION "Strafe Stick. Makes the hex strafe when pushed in any direction."
#define JOY_RIGHT_DESCRIPTION "Rotation Stick. Makes the hex rotate when pushed left or right."

#define POT_A_DESCRIPTION "Max Speed Dial. Sets the hex's max speed."
#define POT_B_DESCRIPTION "Height Dial. Sets the hex's distance from the ground."

#define JOY_LEFT_BUTTON_DESCRIPTION "Not in use."
#define JOY_RIGHT_BUTTON_DESCRIPTION "Not in use."

#define ROTARY_ENCODER_DESCRIPTION "UI Dial. Used for UI navigation of the RC."

#define BUTTON_B_DESCRIPTION "Gait Change Button. Used to quickly change the Gait."
#define BUTTON_C_DESCRIPTION "Not in use."
#define BUTTON_D_DESCRIPTION "Not in use."

#define FONT_BOLD_HEADER u8g2_font_prospero_bold_nbp_tf
#define FONT_HEADER u8g2_font_prospero_nbp_tf 
#define FONT_TEXT u8g2_font_heisans_tr 
#define FONT_TEXT_MONOSPACE u8g2_font_spleen5x8_mf
#define FONT_TINY_TEXT u8g2_font_4x6_mf
#define FONT_TINY_NUMBERS u8g2_font_micro_mn 


#define OFF 0x1
#define ON  0x0

#define UNPRESSED 0x1
#define PRESSED  0x0

enum IOLabels {
  A, //0
  B, //1
  C, //2
  D  //3
};

enum Gaits {
  TRI,      //0
  RIPPLE,   //1
  WAVE,     //2
  QUAD,     //3
  BI,       //4
  HOP       //5
};

enum PackageType {
    RC_CONTROL_DATA = 1,
    RC_SETTINGS_DATA = 2,
    HEXAPOD_SETTINGS_DATA = 3,
    HEXAPOD_SENSOR_DATA = 4
};

const int gaitCount = 6;
extern String gaitStrings[gaitCount];


struct Vector2int{
    int x;
    int y;

    Vector2int(int xVal, int yVal) : x(xVal), y(yVal) {}
    Vector2int() : x(0), y(0) {}
};

struct Vector2 {
  float x;
  float y;

  Vector2(float xVal, float yVal) : x(xVal), y(yVal) {}
  Vector2() : x(0), y(0) {}
  Vector2 operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
  }
};

struct Vector3 {
  float x;
  float y;
  float z;

  Vector3(float xVal, float yVal, float zVal) : x(xVal), y(yVal), z(zVal) {}
  Vector3() : x(0), y(0), z(0) {}
  Vector3 operator+(const Vector3& other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
  }
};

// Forward declarations
class Page;
class HomePage;
class MainMenuPage;
class ControlsPage;
class SettingsPage;
class StatsPage;
class GaitsPage;
class OffsetsPage;

extern Gaits selectedGait;
extern Page *currentPage;
extern Page *previousPage;

extern HomePage *homePage;
extern MainMenuPage *mainMenuPage;
extern ControlsPage *controlsPage;
extern SettingsPage *settingsPage;
extern StatsPage *statsPage;
extern GaitsPage *gaitsPage;
extern OffsetsPage *offsetsPage;

#define EEPROM_NRF_ADDRESS_ADDR         0 //requires 6 bytes
#define EEPROM_NRF_ADDRESS_ARRAY_SIZE    6 // size of the NRF address in bytes

#define EEPROM_DYNAMIC_STRIDE_ADDR      6 //requires 1 byte
#define EEPROM_SLEEP_DELAY_ADDR         7 // requires 4 bytes


#define OFFSETS_COUNT 18

extern uint8_t nrfAddress[EEPROM_NRF_ADDRESS_ARRAY_SIZE]; // NRF chip address as an array of bytes
extern bool dynamicStrideLength;                    // Boolean for Dynamic Stride Length
extern long int sleepDelayTime;                     // int for how many milliseconds to wait before sleeping
extern int8_t hexSavedOffsets[OFFSETS_COUNT]; // Declare offsets array
extern int8_t offsets[OFFSETS_COUNT]; // Declare offsets array
extern float current_sensor_value; // Declare current sensor value
extern Vector2int foot_positions[6]; // Declare foot positions array

void loadValues();
void saveValues();