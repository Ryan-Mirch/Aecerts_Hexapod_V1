#include "NRF.h"
#include "Globals.h"

// Initialize the radio and addresses
RF24 radio(49, 4); // CE, CSN
bool radioNumber = 0;

unsigned long rc_send_interval = 50;

// Initialize the data packages
RC_Control_Data_Package rc_control_data;
RC_Settings_Data_Package rc_settings_data;
Hexapod_Data_Package hex_data;

void setupNRF() {
    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.setPayloadSize(32);
    radio.setChannel(124);
    radio.enableAckPayload();
    radio.setRetries(5, 5);
    radio.openWritingPipe(nrfAddress);

    rc_control_data.type = CONTROL_DATA;

    rc_control_data.joy1_X = 127;
    rc_control_data.joy1_Y = 127;
    rc_control_data.joy1_Button = UNPRESSED;

    rc_control_data.joy2_X = 127;
    rc_control_data.joy2_Y = 127;
    rc_control_data.joy2_Button = UNPRESSED;

    rc_control_data.slider1 = 50;
    rc_control_data.slider2 = 50;

    rc_control_data.pushButton1 = UNPRESSED;
    rc_control_data.pushButton2 = UNPRESSED;


    rc_settings_data.type = SETTINGS_DATA;
    rc_settings_data.dynamic_stride_length = 1;
    rc_settings_data.sleep_delay = 1000;

    for (int i = 0; i < 18; i++) {
        rc_settings_data.offsets[i] = 0;
    }
}

void sendNRFData(PackageType type) {
    every(rc_send_interval) {
        bool report = false;

        if (type == CONTROL_DATA) {
            report = radio.write(&rc_control_data, sizeof(rc_control_data)); // Send control data
        } else if (type == SETTINGS_DATA) {
            report = radio.write(&rc_settings_data, sizeof(rc_settings_data)); // Send settings data
        }

        if (report) {
            if (radio.isAckPayloadAvailable()) {
                radio.read(&hex_data, sizeof(hex_data));
                // Process received data
            }
        }
    }
}