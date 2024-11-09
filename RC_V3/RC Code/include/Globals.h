#pragma once

#include <Arduino.h>
#include "Helpers.h"
#include "Page.h"

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



extern Gaits selectedGait;
extern Page *currentPage;
extern Page *previousPage;

extern DemoControlsPage *demoPage;
extern HomePage *homePage;
extern MainMenuPage *mainMenuPage;
extern ControlsPage *controlsPage;
extern SettingsPage *settingsPage;
extern StatsPage *statsPage;
extern GaitsPage *gaitsPage;
extern OffsetsPage *offsetsPage;

#define EEPROM_NRF_ADDRESS_ADDR         0 //requires 5 bytes
#define EEPROM_NRF_ADDRESS_SIZE         5 // size of the NRF address in bytes
#define EEPROM_DYNAMIC_STRIDE_ADDR      5 //requires 1 byte
#define EEPROM_SLEEP_DELAY_ADDR         6 // requires 4 bytes
#define EEPROM_OFFSETS_ADDR             10 // Starting address for offsets, requires 18 * 4 bytes
#define OFFSETS_COUNT 18

extern uint8_t nrfAddress[EEPROM_NRF_ADDRESS_SIZE]; // NRF chip address as an array of bytes
extern bool dynamicStrideLength;                    // Boolean for Dynamic Stride Length
extern long int sleepDelayTime;                     // int for how many milliseconds to wait before sleeping
extern int offsets[OFFSETS_COUNT]; // Declare offsets array

void loadValues();
void saveValues();
void saveOffsets();