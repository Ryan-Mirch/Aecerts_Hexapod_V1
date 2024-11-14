#pragma once

#include <Arduino.h>
#include "Helpers.h"
#include <SPI.h>
#include <RF24.h>

// Define the radio and addresses
extern RF24 radio;

extern unsigned long rc_send_interval;

// Define the data packages
struct RC_Control_Data_Package {
    byte type; // 1 byte
    
    byte joy1_X; // 1 byte
    byte joy1_Y; // 1 byte
    
    byte joy2_X; // 1 byte
    byte joy2_Y; // 1 byte  
    byte slider1; // 1 byte
    byte slider2; // 1 byte

    byte joy1_Button:1; // 1 bit
    byte joy2_Button:1; // 1 bit
    byte pushButton1:1; // 1 bit
    byte pushButton2:1; // 1 bit
    byte idle:1;        // 1 bit
    byte sleep:1;        // 1 bit
    byte dynamic_stride_length:1; // 1 bit
    byte reserved : 1;  // 1 bits padding, 1 byte total

    byte gait;  // 1 byte
};

struct RC_Settings_Data_Package {
    byte type; // 1 byte
    
    byte calibrating:1; //1 bit
    byte reserved:7;              //7 bits padding, 1 byte total

    int8_t offsets[18];             //18 bytes
};

struct Hexapod_Settings_Data_Package {
    byte type; // 1 byte
    int8_t offsets[18]; // 18 bytes
};

struct Hexapod_Sensor_Data_Package {
    byte type; // 1 byte
    float current_sensor_value; // 4 bytes
    Vector2int foot_positions[6]; // 6 * 2 * 2 bytes = 24 bytes
};

// Declare the data package variables
extern RC_Control_Data_Package rc_control_data;
extern RC_Settings_Data_Package rc_settings_data;
extern Hexapod_Settings_Data_Package hex_settings_data;
extern Hexapod_Sensor_Data_Package hex_sensor_data;

// Function declarations
void setupNRF();
void sendNRFData(PackageType type);