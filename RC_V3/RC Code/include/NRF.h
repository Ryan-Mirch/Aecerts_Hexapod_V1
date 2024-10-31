#pragma once

#include <Arduino.h>
#include "Helpers.h"
#include <SPI.h>
#include <RF24.h>

// Define the radio and addresses
extern RF24 radio;
extern uint8_t address[][6];
extern bool radioNumber;

extern unsigned long rc_send_interval;

// Define the data packages
struct RC_Data_Package {
    byte joy1_X;
    byte joy1_Y;
    byte joy1_Button;
    byte joy2_X;
    byte joy2_Y;
    byte joy2_Button;
    byte slider1;
    byte slider2;
    byte pushButton1;
    byte pushButton2;
};

struct Hexapod_Data_Package {
    float current_sensor_value;
};

// Declare the data package variables
extern RC_Data_Package rc_data;
extern Hexapod_Data_Package hex_data;

// Function declarations
void setupNRF();
void sendNRFData();